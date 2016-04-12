//
// class PWAtool - provides the quantity to be minimized in the
//                 extended maximum likelihood method for the
//                 partial-wave analysis of omega decay angular
//                 distributions from the Radphi experiment
//
// authors: richard.t.jones at uconn.edu, fridah.mokaya at uconn.edu
// version: april 5, 2016
//
// For implementation details, see the source file PWAtool.cc
//

#include <vector>
#include <TChain.h>
#include <TMinuit.h>
#include <TMatrixD.h>
#include <TH1D.h>
#include <TRandom3.h>

#ifndef PWATOOL_H
#define PWATOOL_H 1

class PWAtool : public TObject
{
 public:
   PWAtool();
   ~PWAtool();

   struct angles_t {
      double costheta; // range [-1, 1]
      double phi;      // range [-pi, pi]
   };
   typedef struct angles_t angles_T;
   struct event_t {
      double costheta; // range [-1, 1]
      double phi;      // range [-pi, pi]
      double weight;
   };
   typedef struct event_t event_T;
   struct pwa_ntuple_t {
      Double_t	tabs;
      Double_t	Ebeam;
      Double_t	omegaphi;
      Double_t	gjcosthe;
      Double_t	gjthe;
      Double_t	gjphi;
      Double_t	helcosthe;
      Double_t	helthe;
      Double_t	helphi;
      Double_t	wgt[8];
      Double_t	Ewgt1[7];
      Double_t	Ewgt2[7];
      Double_t	Ewgt3[7];
      Double_t	Ewgt4[7];
   };
   typedef struct pwa_ntuple_t treerow_T;
   struct pwa_mctuple_t {
      double tabs;
      double Ebeam;
      double omegaphi;
      double gjcosthe;
      double gjphi;
      double helcosthe;
      double helphi;
      double wgt[8];
   };
   typedef struct pwa_mctuple_t mctreerow_T;

   double W(const angles_T &Omega);

   void set_rho(double sdm11, double sdm00, double sdmM1, 
                double Re_sdm10, double Im_sdm10=0);
   double get_Re_rho(int m1, int m2) const;
   double get_Im_rho(int m1, int m2) const;
   void set_rho(double param[4]);
   void print_last_param();
   const TMatrixD &get_PartialD() { return PartialD; }

   int get_real_events() const { return real_events.size(); }
   int get_mc_events() const { return mc_events.size(); }
   void gen_real_events(int nevents);
   void gen_mc_events(int nevents);
   const event_T &get_real_event(unsigned int i) const;
   const event_T &get_mc_event(unsigned int i) const;
   TH1D *hist_real_costheta(const char *name, double phimin=-M_PI,
                                              double phimax=M_PI);
   TH1D *hist_real_phi(const char *name, double costmax=-1,
                                         double costmin=1);
   TH1D *hist_mc_costheta(const char *name, int weighted=0, double phimin=-M_PI,
                                                            double phimax=M_PI);
   TH1D *hist_mc_phi(const char *name, int weighted=0, double costmin=-1,
                                                       double costmax=1);

   // configure class functor to serve as TMinuit fcn //
   double operator()(int &npar, double grad[3], int iflag);
   static void FCN(int &npar, double grad[3], double &nll,
                   double param[3], int iflag);
   void SetFCN(TMinuit &fitter);

   int load_real_events(TChain *data,
                        double tabsmin=0, double tabsmax=99,
                        double Emin=-1, double Emax=99);
   int load_mc_events(TChain *mc,
                      double tabsmin=0, double tabsmax=99,
                      double Emin=-1, double Emax=99);

 protected:
   double rho11;
   double rho00;
   double rhoM1;
   double Re_rho10;
   double Im_rho10;
   double rhoMM() const { return rho11; }
   double rho1M() const { return rhoM1; }
   double Re_rho01() const { return +Re_rho10; }
   double Im_rho01() const { return -Im_rho10; }
   double Re_rho0M() const { return -Re_rho10; }
   double Im_rho0M() const { return +Im_rho10; }
   double Re_rhoM0() const { return -Re_rho10; }
   double Im_rhoM0() const { return -Im_rho10; }
   double a[3];
   double b[3];
   double c[3];
   double Wprime[4];
   TMatrixD PartialD;

   std::vector<event_T> real_events;
   std::vector<event_T> mc_events;

   ClassDef(PWAtool, 1);

 private:
   PWAtool(PWAtool& src); // copy constructor not supported
   static PWAtool* owner;
   static TRandom3* randoms;
};

#endif
