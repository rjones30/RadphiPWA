//
// class PWAtool - provides the quantity to be minimized in the
//                 extended maximum likelihood method for the
//                 partial-wave analysis of omega decay angular
//                 distributions from the Radphi experiment.
//
// authors: richard.t.jones at uconn.edu, fridah.mokaya at uconn.edu
// version: april 5, 2016
//
// implementation notes:
// 1) To use this class, the following steps are required:
//     * construct a new PWAtool instance and call methods
//       load_real_events and load_mc_events to prepare for
//       subsequent calls to the functor.
//     * construct a new TMinuit instance and call its SetFCN
//       method with a pointer to the PWAtool functor created
//       in the previous step.
//     * tell your TMinuit to do the fit, and examine the results.
// 2) The specific reaction that is coded into this class implementation
//    is gamma(unpolarized),p -> omega(pi0,gamma),p where the direction
//    of the pi0 in the omega decay rest frame is given by the pair
//    (costheta,phi). The decay channel-specific code is all local to
//    the W() method, and so it would be straight-forward to extend
//    it to cover other decay channels or to the decays of other 
//    vector mesons.
// 3) For carrying out the full PWA project, it is expected that the
//    user will want to write utility functions to handle the loading
//    of the data from various sources, execution of the fits, plotting
//    of results, and estimation of errors. This is most conveniently
//    done in python -- see example code in PWAomega.py for this.

#define VERBOSE 5

#include <PWAtool.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <math.h>

PWAtool *PWAtool::owner = 0;
TRandom3 *PWAtool::randoms = 0;

PWAtool::PWAtool() 
 : PartialD(4, 4)
{
   // takes ownership of FCN

   owner = this;
   if (randoms == 0)
      randoms = new TRandom3();
}

PWAtool::~PWAtool()
{ 
   // empty destructor

   if (owner == this)
      owner = 0;
}

double PWAtool::W(const angles_T &Omega)
{
   // compute W = sum_{m,m'} [A*_m(Omega) rho(m,m') A_m'(Omega)]
   // where A_m(Omega) is the quantum amplitude for decay from
   // omega state m into the final two-body direction described
   // by angles_t object Omega. If comp=0 then the value of W is
   // returned; if comp=1..4 then the gradient component 1..4 of
   // W is computed instead and returned. Note that the condition
   // trace{rho} = 1 is not assumed.
 
   double cost = Omega.costheta;
   double sint = sqrt(1 - cost*cost);
   double phi = Omega.phi;
   Wprime[0] = 1 + cost*cost;
   Wprime[1] = 2 - Wprime[0];
   Wprime[2] = Wprime[1] * cos(2*phi);
   Wprime[3] = 2*sqrt(2.) * sint*cost * cos(phi);
   return Wprime[0] * rho11 +
          Wprime[1] * rho00 + 
          Wprime[2] * rhoM1 + 
          Wprime[3] * Re_rho10;
}

void PWAtool::set_rho(double sdm11, double sdm00, double sdmM1, 
                      double Re_sdm10, double Im_sdm10)
{
   // load from arguments directly into the density matrix,
   // no check is made that the values actually satisfy the
   // positivity requirements for W.

   rho11 = sdm11;
   rho00 = sdm00;
   rhoM1 = sdmM1;
   Re_rho10 = Re_sdm10;
   Im_rho10 = Im_sdm10;
}

void PWAtool::set_rho(double param[4])
{
   // load from arguments directly into the density matrix,
   // using a parameterization that guarantees the positivity
   // and parity conservation constraints for rho in the decays
   // of a vector meson. The parameterization is as follows.
   //
   //                _3_ 
   //                \     / a_i \*
   //    rho[m,m'] = /__   | c_i |  ( a_i  c_i  b_i )
   //                i=1   \ b_i /
   //
   // where the spinors ( a_i  c_i  b_i ) are a complete set
   // of mutually orthogonal basis vectors whose normalization
   // is not fixed in the parameterization. This construction
   // guarantees the positivity of the W pdf for any set of
   // complex coefficients {a_i, b_i, c_i}. There are 18 free
   // parameters in this set, but this set gets reduced to 9
   // through the following conventions:
   //   1) arbitrary phase on each basis vector (-3)
   //   2) orthogonality conditions (-6)
   // Defining c_i as pure real takes care of (1) and (2) must
   // be enforced by constraining some of the coefficients from
   // the others.
   //
   // Parity conservation further requires that
   //      rho[-m,-m'] = (-1)^(m-m') rho[m,m']
   // which is satisfied by either one of two conditions that
   // must hold for each i:
   //      (a) a_i = -b_i, for any c_i, or
   //      (b) a_i = +b_i, for c_i = 0
   // The parity constraints reduce the number of free parameters
   // from 9 to 5.
   //
   // We select a_1, c_1, a_2, and c_3 as the parameters: a_1 has
   // two degrees of freedom because it is complex, whereas a_2 has
   // a spurious phase and so it is taken to be real. In the special
   // case of an unpolarized beam, it turns out that only the real
   // elements of rho contribute to the differential cross section,
   // so we furthermore restrict a_1 to be real. Thus we end up with
   // a complete parameterization of rho which simultaneously ensures
   // constraints from positivity and parity conservation, plus the
   // unpolarized beam condition, for arbitrary values of the inputs.
   //
   // WARNING: This parameterization has a built-in dualism: two
   // completely different parameter vectors lead to exactly the same
   // rho matrix. One of the two choices typically leads to very poor
   // convergence because the scales of one of the parameters is very
   // far from the others. The equivalence transformation is as follows.
   //    a'_1 = c_1 c_3, c'_1 = -2 a_1 c_3, c'_3 = -1 / (2 c_3)
   // If the scale of the c_3 parameter gets far from the scales of the
   // a_1 and c_1, switching from one choice to the other can improve
   // the convergence rate of the fit.

   a[0] = param[0];
   c[0] = param[1];
   b[0] = -param[0];
   a[1] = param[2];
   c[1] = 0;
   b[1] = param[2];
   a[2] = param[1]*param[3];
   c[2] = -2*param[0]*param[3];
   b[2] = -param[1]*param[3];

   // compute the 4 independent rho matrix elements from the parameters
   rho11    = a[0]*a[0] + a[1]*a[1] + a[2]*a[2];
   rho00    = c[0]*c[0]             + c[2]*c[2];
   rhoM1    = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
   Re_rho10 = b[0]*c[0]             + b[2]*c[2];
   Im_rho10 = 0;

   // evaluate the partial derivatives of the rho matrix elements
   // with respect to the parameters, ordered as PartialD[row_i][param_j] 
   //     row_i = 0 (rho11), 1 (rho00), 2 (rhoM1), or 3 (Re_rho10); and
   PartialD[0][0] = 2*a[0];
   PartialD[0][1] = 2*a[2]*param[3];
   PartialD[0][2] = 2*a[1];
   PartialD[0][3] = 2*a[2]*param[1];
   PartialD[1][0] = -4*c[2]*param[3];
   PartialD[1][1] = 2*c[0];
   PartialD[1][2] = 0;
   PartialD[1][3] = -4*c[2]*param[0];
   PartialD[2][0] = -2*a[0];
   PartialD[2][1] = -2*a[2]*param[3];
   PartialD[2][2] = 2*a[1];
   PartialD[2][3] = -2*a[2]*param[1];
   PartialD[3][0] = -c[0] - 2*b[2]*param[3];
   PartialD[3][1] = b[0] - c[2]*param[3];
   PartialD[3][2] = 0;
   PartialD[3][3] = 4*a[2]*param[0];
}

void PWAtool::print_last_param()
{
   printf("%12.7f  %12.7f  %12.7f\n", a[0], a[1], a[2]);
   printf("%12.7f  %12.7f  %12.7f\n", c[0], c[1], c[2]);
   printf("%12.7f  %12.7f  %12.7f\n", b[0], b[1], b[2]);
}

double PWAtool::get_Re_rho(int m1, int m2) const
{
   if (m1 == 0 && m2 == 0)
      return rho00;
   else if (m1 == 0 && m2 == 1)
      return Re_rho01();
   else if (m1 == 0 && m2 == -1)
      return Re_rho0M();
   else if (m1 == 1 && m2 == 0)
      return Re_rho10;
   else if (m1 == 1 && m2 == 1)
      return rho11;
   else if (m1 == 1 && m2 == -1)
      return rho1M();
   else if (m1 == -1 && m2 == 0)
      return Re_rhoM0();
   else if (m1 == -1 && m2 == 1)
      return rhoM1;
   else if (m1 == -1 && m2 == -1)
      return rhoMM();
   else
      throw std::range_error("wave index out of range");
}

double PWAtool::get_Im_rho(int m1, int m2) const
{
   if (m1 == 0 && m2 == 0)
      return 0;
   else if (m1 == 0 && m2 == 1)
      return Im_rho01();
   else if (m1 == 0 && m2 == -1)
      return Im_rho0M();
   else if (m1 == 1 && m2 == 0)
      return Im_rho10;
   else if (m1 == 1 && m2 == 1)
      return 0;
   else if (m1 == 1 && m2 == -1)
      return 0;
   else if (m1 == -1 && m2 == 0)
      return Im_rhoM0();
   else if (m1 == -1 && m2 == 1)
      return 0;
   else if (m1 == -1 && m2 == -1)
      return 0;
   else
      throw std::range_error("wave index out of range");
}

const PWAtool::event_T &PWAtool::get_real_event(unsigned int i) const
{
   if (i < real_events.size())
      return real_events[i];
   else
      throw std::range_error("event index out of range");
}

const PWAtool::event_T &PWAtool::get_mc_event(unsigned int i) const
{
   if (i < mc_events.size())
      return mc_events[i];
   else
      throw std::range_error("event index out of range");
}

int PWAtool::load_real_events(TChain *data,
                              double tabsmin, double tabsmax,
                              double Emin, double Emax)
{
   // read in real event information from a root tree
   // and store it in memory in the real_events vector.
 
   treerow_T row;
   data->SetBranchAddress("pwa_ntuple", (double*)&row);
   double tbins[8] = {0.0, 0.08, 0.18, 0.3, 0.45, 0.65, 0.9, 1.2};

   int nevents = 0;
   long long int nrows = data->GetEntries();
   for (long long int r = 0; r < nrows; ++r) {
      event_T event;
      data->GetEntry(r);
      if (row.tabs < tabsmin || row.tabs > tabsmax ||
          row.Ebeam < Emin || row.Ebeam > Emax)
      {
         continue;
      }
      event.costheta = row.helcosthe;
      event.phi = row.helphi;
      int tbin = 0;
      for (; tbin < 8 && row.tabs > tbins[tbin]; ++tbin) {}
      if (tbin < 1 || tbin > 7)
         continue;
      event.weight = row.wgt[tbin];
      real_events.push_back(event);
      ++nevents;
   }
   return nevents;
}

int PWAtool::load_mc_events(TChain *mc,
                            double tabsmin, double tabsmax,
                            double Emin, double Emax)
{
   // read in mc event information from a root tree
   // and store it in memory in the mc_events vector.

   mctreerow_T row;
   mc->SetBranchAddress("pwa_ntuple", (double*)&row);
   double tbins[8] = {0.0, 0.08, 0.18, 0.3, 0.45, 0.65, 0.9, 1.2};

   int nevents = 0;
   long long int nrows = mc->GetEntries();
   for (long long int r = 0; r < nrows; ++r) {
      event_T event;
      mc->GetEntry(r);
      if (row.tabs < tabsmin || row.tabs > tabsmax ||
          row.Ebeam < Emin || row.Ebeam > Emax)
      {
         continue;
      }
      event.costheta = row.helcosthe;
      event.phi = row.helphi * M_PI/180;
      int tbin = 0;
      for (; tbin < 8 && row.tabs > tbins[tbin]; ++tbin) {}
      if (tbin < 1 || tbin > 7)
         continue;
      event.weight = row.wgt[tbin];
      mc_events.push_back(event);
      ++nevents;
   }
   return nevents;
}

void PWAtool::gen_real_events(int nevents)
{
   // generate random events and store them in the real_events vector

   for (int i=0; i < nevents; ++i) {
      event_T event;
      event.costheta = randoms->Uniform(-1, 1);
      event.phi = randoms->Uniform(-M_PI, M_PI);
      event.weight = 1;
      real_events.push_back(event);
   }
}

void PWAtool::gen_mc_events(int nevents)
{
   // generate random events and store them in the mc_events vector

   for (int i=0; i < nevents; ++i) {
      event_T event;
      event.costheta = randoms->Uniform(-1, 1);
      event.phi = randoms->Uniform(-M_PI, M_PI);
      event.weight = 1;
      mc_events.push_back(event);
   }
}

// configure class functor to serve as TMinuit fcn //
double PWAtool::operator() (int &npar, double grad[4], int iflag)
{
   // evaluate the negative-log-likelihood function on the loaded data set,
   // where flag=1 : do initialization to prepare for a fit
   //       flag=2 : return the gradient in parameter space
   //       flag=3 : do any necessary wrap-up steps after a fit
   //       flag=4 : evaluate nll only (also implied for 1-3)

   double nll = 0;
   double gradnll[4] = {};
   int nreal = real_events.size();
   for (int i=0; i < nreal; ++i) {
      angles_T Omega = {real_events[i].costheta,
                        real_events[i].phi};
      double weight = real_events[i].weight;
      double w = W(Omega) + 1e-99;
      if (w < 0) {
         printf("error - real event %d has negative W %f,"
                " invalidating result!\n", i, w);
         nll = sqrt(-1);
         break;
      }
      nll -= log(w) * weight;
      gradnll[0] -= (Wprime[0] / w) * weight;
      gradnll[1] -= (Wprime[1] / w) * weight;
      gradnll[2] -= (Wprime[2] / w) * weight;
      gradnll[3] -= (Wprime[3] / w) * weight;
   } 
   if (VERBOSE > 3) {
      printf(" sum over real events gives %f\n", nll);
   }

   int nmc = mc_events.size();
   for (int i=0; i < nmc; ++i) {
      angles_T Omega = {mc_events[i].costheta,
                        mc_events[i].phi};
      double weight = mc_events[i].weight;
      double w = W(Omega) + 1e-99;
      if (w < 0) {
         printf("error - mc event %d has negative W %f,"
                " invalidating result!\n", i, w);
         nll = sqrt(-1);
         break;
      }
      nll += w * weight;
      gradnll[0] += Wprime[0] * weight;
      gradnll[1] += Wprime[1] * weight;
      gradnll[2] += Wprime[2] * weight;
      gradnll[3] += Wprime[3] * weight;
   }
   if (VERBOSE > 2) {
      printf(" sum over all terms gives %f\n", nll);
   }

   if (iflag == 2 || VERBOSE > 1) {
      for (int comp=0; comp < 4; ++comp) {
         grad[comp] = 0;
         for (int i=0; i < 4; ++i)
             grad[comp] += gradnll[i] * PartialD[i][comp];
      }
   }
   return nll;
}

void PWAtool::FCN(int &npar, double grad[4], double &nll,
                  double param[3], int iflag)
{
   // play the role of the FCN function for the Minuit fit package

   if (VERBOSE > 1) {
      printf(" param is %12.9f, %12.9f, %12.9f, %12.9f\n", 
             param[0], param[1], param[2], param[3]);
   }

   owner->set_rho(param);
   nll = (*owner)(npar, grad, iflag);

   static int nentries = 0;
   printf("fcn entry %d, iflag = %d, nll = %f\n", ++nentries, iflag, nll);
   if (VERBOSE > 1) {
      printf(" rho11, rho00, rhoM1, Re_rho10 = %f, %f, %f, %f\n",
             owner->rho11, owner->rho00, owner->rhoM1, owner->Re_rho10);
      printf(" gradient is %f, %f, %f, %f\n", 
             grad[0], grad[1], grad[2], grad[3]);
   }
}

void PWAtool::SetFCN(TMinuit &fitter)
{
   // call TMinuit::SetFCN to associate this functor with the fitter

   fitter.SetFCN(&PWAtool::FCN);
}

TH1D *PWAtool::hist_real_costheta(const char *name, double phimin,
                                                    double phimax)
{
   // create histogram of the real data in costheta

   TH1D *h = new TH1D(name, "real costheta distribution", 200, -1, 1);
   for (unsigned int i=0; i < real_events.size(); ++i) {
      if (real_events[i].phi >= phimin && real_events[i].phi <= phimax)
         h->Fill(real_events[i].costheta, real_events[i].weight);
   }
   return h;
}

TH1D *PWAtool::hist_real_phi(const char *name, double costmin,
                                               double costmax)
{
   // create histogram of the real data in phi

   TH1D *h = new TH1D(name, "real phi distribution", 200, -M_PI, M_PI);
   for (unsigned int i=0; i < real_events.size(); ++i) {
      if (real_events[i].costheta >= costmin && 
          real_events[i].costheta <= costmax)
      {
         h->Fill(real_events[i].phi, real_events[i].weight);
      }
   }
   return h;
}

TH1D *PWAtool::hist_mc_costheta(const char *name, int weighted, double phimin,
                                                                double phimax)
{
   // create histogram of the mc data in costheta
   // and weight it with the fitted W pdf if weighted > 0.

   TH1D *h = new TH1D(name, "mc costheta distribution", 200, -1, 1);
   for (unsigned int i=0; i < mc_events.size(); ++i) {
      if (mc_events[i].phi >= phimin && mc_events[i].phi <= phimax) {
         double weight = mc_events[i].weight;
         if (weighted) {
            angles_T Omega = {mc_events[i].costheta, mc_events[i].phi};
            weight *= W(Omega);
         }
         h->Fill(mc_events[i].costheta, weight);
      }
   }
   return h;
}

TH1D *PWAtool::hist_mc_phi(const char *name, int weighted, double costmin,
                                                           double costmax)
{
   // create histogram of the mc data in phi
   // and weight it with the fitted W pdf if weighted > 0.

   TH1D *h = new TH1D(name, "mc phi distribution", 200, -M_PI, M_PI);
   for (unsigned int i=0; i < mc_events.size(); ++i) {
      if (mc_events[i].costheta >= costmin && mc_events[i].costheta <= costmax) 
      {
         double weight = mc_events[i].weight;
         if (weighted) {
            angles_T Omega = {mc_events[i].costheta, mc_events[i].phi};
            weight *= W(Omega);
         }
         h->Fill(mc_events[i].phi, weight);
      }
   }
   return h;
}
