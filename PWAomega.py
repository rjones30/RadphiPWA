#!/usr/bin/python
#
# PWAomega.py - wrapper script about the c++ class PWAtool
#               for doing PWA fits to the decay angular distributions
#               of the omega->gamma,pi0 reaction in the Radphi data.
#
# authors: richard.t.jones at uconn.edu, fridah.mokaya at uconn.edu
# version: april 5, 2016

import os
import sys
import numpy
import math

from ROOT import *
gSystem.Load("PWAtool_cc.so")
c1 = TCanvas("c1", "c1", 5, 10, 550, 500)

initial_value = 0.3
initial_stepsize = 0.1

def init(check=0, tlim=[0, 99]):
   """
   Load real events and Monte Carlo events from their respective
   root trees, and define the fit parameters in preparation for
   a call to fit(). Setting the first argument to a non-zero value
   forces Minuit to check the computation of the local gradient of
   the negative-log-likelihood function against its approximation by
   finite differences. The tlim argument provides a way for the user
   to request a restricted range in kinematic t in the selection of
   events for the fit. Normally this function would be called before
   each invocation of fit().
   """
   realdata_dir = "/home/mokaya/radphi/toroot/pwa_data"
   realdata = TChain("pwa_tree", "real omega ntuple")
   for rfile in os.listdir(realdata_dir):
      realdata.Add(realdata_dir + "/" + rfile)
      
   mcdata_dir = "/home/mokaya/radphi/toroot/pwa_MC"
   mcdata = TChain("pwa_tree", "mc omega ntuple")
   for mfile in os.listdir(mcdata_dir):
      mcdata.Add(mcdata_dir + "/" + mfile)
   
   print realdata.GetEntries(), "real events found"
   print mcdata.GetEntries(), "mc events found"
   
   global tool
   tool = PWAtool()
   tool.load_real_events(realdata, tlim[0], tlim[1])
   tool.load_mc_events(mcdata, tlim[0], tlim[1])
   
   print "real events kept:", tool.get_real_events()
   print "mc events kept:", tool.get_mc_events()
   
   global fitter
   if not fitter:
      fitter = TMinuit(4)
      tool.SetFCN(fitter)
      err1 = Long()
      fitter.mnparm(0, "a0", initial_value, initial_stepsize, 0, 0, err1)
      err2 = Long()
      fitter.mnparm(1, "c0", initial_value, initial_stepsize, 0, 0, err2)
      err3 = Long()
      fitter.mnparm(2, "a1", initial_value, initial_stepsize, 0, 0, err3)
      err4 = Long()
      fitter.mnparm(3, "c2", initial_value, initial_stepsize, 0, 0, err4)
      if err1 > 0 or err2 > 0 or err3 > 0 or err4 > 0:
         print "fitter.mnparm choked, cannot continue!"
         sys.exit(1)
      if check > 0:
         fitter.Command("set gradient")
      fitter.Command("set gradient 1")

def fit(maxcalls=300):
   """
   Perform a PWA fit using the MIGRAD facility of Minuit. At the end
   of the first pass the user is given a chance to enter follow-up
   commands to refine the search, or simply hit enter to accept it.
   """
   fitter.Command("migrad " + str(maxcalls))
   while True:
      resp = raw_input("Enter a Minuit command, s to swap parameters," +
                       "or return to accept: ")
      if resp:
         if resp == 's':
            swap_parameters()
         else:
            fitter.Command(resp)
      else:
         break

def fit7t(maxcalls=300):
   """
   Perform a series of fits over the 7 separate divisions of the data
   according to |t|. The |t| divisions are hard-wired in the code below.
   """
   tbins = [#[0.0, 0.08], \
            #[0.08, 0.18], \
            #[0.18, 0.30], \
            #[0.30, 0.45], \
            #[0.45, 0.65], \
            [0.65, 0.90], \
            [0.90, 1.20]]
   for bin in range(0, len(tbins)):
      print "Now fitting |t| range", str(tbins[bin][0]) + ",", \
                                     str(tbins[bin][1]) + " GeV^2"
      global initial_stepsize
      resp = raw_input("starting step size? [" + str(initial_stepsize) + "] ")
      try:
         resp = float(resp)
      except ValueError:
         resp = initial_stepsize
      initial_stepsize = resp
      global fitter
      fitter = 0
      init(0, tbins[bin])
      fit(maxcalls)
      report_errors()
         
def report_errors():
   """
   Print a report showing the best-fit parameters for the SDM and
   total acceptance-corrected yield, together with their errors.
   """
   rho11 = tool.get_Re_rho(1,1)
   rho00 = tool.get_Re_rho(0,0)
   rhoM1 = tool.get_Re_rho(-1,1)
   rho10 = tool.get_Re_rho(1,0)
   normfact = 2*rho11 + rho00
   rho11 /= normfact
   rho00 /= normfact
   rhoM1 /= normfact
   rho10 /= normfact
   emat = numpy.array([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], dtype=numpy.float64)
   fitter.mnemat(emat, 4)
   covar = TMatrixD(4,4)
   n = 0
   for row in range(0, 4):
      for col in range(0, 4):
         covar[row][col] = emat[n]
         n += 1
   D = tool.get_PartialD()
   DT = TMatrixD(D)
   DT.Transpose(D)
   Dcovar = TMatrixD(4, 4)
   Dcovar.Mult(D, covar)
   covar.Mult(Dcovar, DT)
   print "total acceptance-corrected yield = {0:8.5f} +/- {1:8.5f}".format(
         normfact * 1e8, math.sqrt(4*covar[0][0] + covar[1][1]) * 1e8)
   print "   rho11 = {0:8.5f} +/- {1:8.5f}".format(rho11, 
                                            math.sqrt(covar[0][0]) / normfact)
   print "   rho00 = {0:8.5f} +/- {1:8.5f}".format(rho00, 
                                            math.sqrt(covar[1][1]) / normfact)
   print "   rhoM1 = {0:8.5f} +/- {1:8.5f}".format(rhoM1,
                                            math.sqrt(covar[2][2]) / normfact)
   print "Re_rho10 = {0:8.5f} +/- {1:8.5f}".format(rho10,
                                            math.sqrt(covar[3][3]) / normfact)
   print
   print "complete correlation matrix, order as listed above:"
   for i in range(0, 4):
      print "{0:8.3f}  {1:8.3f}  {2:8.3f}  {3:8.3f}".format(
            covar[i][0] / math.sqrt(covar[i][i] * covar[0][0]),
            covar[i][1] / math.sqrt(covar[i][i] * covar[1][1]),
            covar[i][2] / math.sqrt(covar[i][i] * covar[2][2]),
            covar[i][3] / math.sqrt(covar[i][i] * covar[3][3]))

def swap_parameters():
   """
   There is a dualism in the rho parameterization that is used in this PWA,
   such that two very different parameter sets give rise to the same rho
   matrix and hence the same NLL value. Sometimes one of these two sets is
   easier to work with than the other because all of the parameters are of
   the same scale. This function fetches the current parameters from the
   fitter, computes and uploads the dual parameter set to the fitter, and
   checks that the NLL is the unchanged.
   """
   a1 = Double()
   c1 = Double()
   a2 = Double()
   c3 = Double()
   err = Double()
   fitter.GetParameter(0, a1, err)
   fitter.GetParameter(1, c1, err)
   fitter.GetParameter(2, a2, err)
   fitter.GetParameter(3, c3, err)
   param = numpy.array([a1, c1, a2, c3])
   grad = numpy.array([0., 0., 0., 0.])
   nll = Double()
   npars = Long(4)
   fitter.Eval(npars, grad, nll, param, 4)
   a_1 = c1 * c3
   c_1 = -2 * a1 * c3
   a_2 = a2
   c_3 = -1 / (2 * c3)
   fitter.Command("set parameter 1 {0:20.12f}".format(a_1))
   fitter.Command("set parameter 2 {0:20.12f}".format(c_1))
   fitter.Command("set parameter 3 {0:20.12f}".format(a_2))
   fitter.Command("set parameter 4 {0:20.12f}".format(c_3))
   nllnew = Double()
   fitter.Eval(npars, grad, nllnew, param, 4)
   print ""
   print "swapping param = {0:12.8f}, {1:12.8f}, {2:12.8f}, {3:12.8f}".format(
                              a1,        c1,        a2,        c3   )
   print "  for dual set = {0:12.8f}, {1:12.8f}, {2:12.8f}, {3:12.8f}".format(
                              a_1,       c_1,       a_2,       c_3  )
   print "nll old, new = {0:12.7f}, {1:12.7f}".format(nll, nllnew)

def contour(ph, pv, nbins=10, nbox=9, nsigma=1):
   """
   Plot the nll function in the region +/- nsigma about the current fit
   value in parameter space as a 2D histogram with dimensions nbins x nbins,
   plotting parameter ph on the horizontal axis and pv on the vertical. The
   current minimum of the nll function is subtracted before it is plotted.
   The nbox argument asks for each bin in the histogram to be replaced with
   a square nbox x nbox smaller bins and filled using a linear extrapolation
   from the center square using the gradient evaluated there. It works best
   when nbox is an odd number, so the center bin is centered in the box.
   Parameter numbers in the ph,pv arguments are based at 1.
   """
   a1 = Double()
   c1 = Double()
   a2 = Double()
   c3 = Double()
   a1err = Double()
   c1err = Double()
   a2err = Double()
   c3err = Double()
   fitter.GetParameter(0, a1, a1err)
   fitter.GetParameter(1, c1, c1err)
   fitter.GetParameter(2, a2, a2err)
   fitter.GetParameter(3, c3, c3err)
   param = numpy.array([a1, c1, a2, c3])
   parerr = numpy.array([a1err, c1err, a2err, c3err])
   grad = numpy.array([0., 0., 0., 0.])
   nll_min = Double()
   npars = Long(4)
   fitter.Eval(npars, grad, nll_min, param, 4)
   xlim = (param[ph-1] - nsigma * parerr[ph-1],
           param[ph-1] + nsigma * parerr[ph-1])
   ylim = (param[pv-1] - nsigma * parerr[pv-1],
           param[pv-1] + nsigma * parerr[pv-1])
   h = gROOT.FindObject("contour")
   if h:
      h.Delete()
   h = TH2D("contour", "nll contour in parameter " + str(pv) +
                       " vs " + str(ph), 
            nbins * nbox, xlim[0], xlim[1], nbins * nbox, ylim[0], ylim[1])
   nll = Double()
   for ix in range(1, nbox * nbins + 1, nbox):
      param[ph-1] = h.GetXaxis().GetBinCenter(ix + nbox/2)
      for iy in range(1, nbox * nbins + 1, nbox):
         param[pv-1] = h.GetYaxis().GetBinCenter(iy + nbox/2)
         fitter.Eval(npars, grad, nll, param, 2)
         for bx in range (0, nbox):
            dx = (bx - nbox/2) * h.GetXaxis().GetBinWidth(ix)
            for by in range (0, nbox):
               dy = (by - nbox/2) * h.GetYaxis().GetBinWidth(iy)
               val = nll - nll_min + grad[ph-1]*dx + grad[pv-1]*dy
               h.SetBinContent(ix + bx, iy + by, val)
   h.SetContour(100)
   h.Draw("colz")
   return h
   
def compare_costheta(phicut=(-math.pi,math.pi)):
   """
   Plot the costheta distribution for the real data, and superimpose on
   top the Monte Carlo phase space distribution (red error bars) renormalized
   to match the total number of real events, and the PWA fit (blue error bars).
   The interval defined in the optional argument phicut selects a region in
   phi within which the events are selected for inclusion in this plot.
   """
   hreal = tool.hist_real_costheta("real_costheta", phicut[0], phicut[1])
   hmcraw = tool.hist_mc_costheta("mcraw_costheta", 0, phicut[0], phicut[1])
   hmcwgt = tool.hist_mc_costheta("mcwgt_costheta", 1, phicut[0], phicut[1])
   hreal.Draw()
   hmcraw.Scale(hreal.Integral() / hmcraw.Integral())
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def compare_phi(costhetacut=(-1,1)):
   """
   Plot the phi distribution for the real data, and superimpose on
   top the Monte Carlo phase space distribution (red error bars) renormalized
   to match the total number of real events, and the PWA fit (blue error bars).
   The interval defined in the optional argument phicut selects a region in
   costheta within which the events are selected for inclusion in this plot.
   """
   hreal = tool.hist_real_phi("real_phi", costhetacut[0], costhetacut[1])
   hmcraw = tool.hist_mc_phi("mcraw_phi", 0, costhetacut[0], costhetacut[1])
   hmcwgt = tool.hist_mc_phi("mcwgt_phi", 1, costhetacut[0], costhetacut[1])
   hreal.Draw()
   hmcraw.Scale(hreal.Integral() / hmcraw.Integral())
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def test_rho_svd():
   """
   This function contains various mathematical experiments that I did to
   prove to myself that the parameterization I adopted for the SDM makes
   sense. None of this needs to be repeated for new fits, it was just a
   one-time exercise. In particular, I was curious why certain values for
   the SDM matrix elements that lie outside the limits imposed by the Schwarz
   inequality for off-diagonal elements (but not too far) seemed to never
   produce negative W values anywhere in phase space. This turns out to be
   true in the unpolarized case, but probably not true for the more general
   case with a polarized beam. Nevermind, because the SDM still must respect
   the Schwarz inequality on its own, regardless of whether violating it
   does or does not cause W to dip below zero at some point or other in the
   space of decay kinematics for this particular channel.
   """
   rho = TMatrixD(3,3)
   svd = TDecompSVD(rho)
   rgen = TRandom3();
   while True:
      rho11 = rgen.Uniform(0.5)
      rho00 = rgen.Uniform(1)
      scale10 = math.sqrt(rho11 * rho00) * 3
      rho10 = rgen.Uniform(-scale10, scale10)
      scaleM1 = rho11 * 2
      rhoM1 = rgen.Uniform(-scaleM1, scaleM1)
      rho[0][0] = rho11
      rho[1][0] = -rho10
      rho[2][0] = rhoM1
      rho[0][1] = -rho10
      rho[1][1] = rho00
      rho[2][1] = rho10
      rho[0][2] = rhoM1
      rho[1][2] = rho10
      rho[2][2] = rho11
      print "rho:" 
      for i in range(0, 3):
         print "{0:12.7f} {1:12.7f} {2:12.7f}".format(
                 rho[i][0], rho[i][1], rho[i][2])
      tool.set_rho(rho11, rho00, rhoM1, rho10)
      grad = numpy.array([0,0,0,0], dtype=numpy.float64)
      nll = Double()
      npars = Long(4)
      nll = tool(npars, grad, 4)
      if math.isnan(nll):
         if abs(rho10) <= math.sqrt(rho00 * rho11) and abs(rhoM1) <= rho11:
            print "simple boundary check failed!"
         else:
            continue
      else:
         if rho10 * rho10 > rho00 * rho11 or rhoM1 * rhoM1 > rho11 * rho11:
            print "simple boundary check foiled!"
         else:
            continue
      svd.SetMatrix(rho)
      svd.Decompose()
      sval = svd.GetSig()
      U = svd.GetU()
      V = svd.GetV()
      print "svd of rho:"
      for sig in range(0, len(sval)):
         if U[0][sig] * V[0][sig] < 0:
            sval[sig] = -sval[sig]
            V[0][sig] = -V[0][sig]
            V[1][sig] = -V[1][sig]
            V[2][sig] = -V[2][sig]
      for sig in range(0, len(sval)):
         print "{0:12.7f}   {1:10.7f} {2:10.7f} {3:10.7f}" + \
               " {4:10.7f} {5:10.7f} {6:10.7f}".format(
                sval[sig], U[sig][0], U[sig][1], U[sig][2],
                V[sig][0], V[sig][1], V[sig][2])

      resp = raw_input("Press return to continue, e to evaluate: ")
      if len(resp) == 0 or resp[0] != 'e':
         continue
      param = numpy.array([0,0,0,0], dtype=numpy.float64)
      i1 = 0
      for sig in range(0, 3):
         if U[1][sig] == 0:
            i1 = sig
            break
      i2 = (i1 + 1) % 3
      i0 = (i1 + 2) % 3
      param[0] = sval[i0] * U[0][i0]
      param[1] = sval[i0] * U[1][i0]
      param[2] = sval[i1] * U[0][i1]
      param[3] = sval[i2] * U[1][i2]
      #tool.set_rho(param)
      tool.set_rho(rho11, rho00, rhoM1, rho10)
      grad = numpy.array([0,0,0,0], dtype=numpy.float64)
      nll = Double()
      npars = Long(4)
      nll = tool(npars, grad, 4)
      print "nll = ", nll

def compare_costheta(phicut=(-math.pi,math.pi)):
   """
   Plot the costheta distribution for the real data, and superimpose on
   top the Monte Carlo phase space distribution (red error bars) renormalized
   to match the total number of real events, and the PWA fit (blue error bars).
   The interval defined in the optional argument phicut selects a region in
   phi within which the events are selected for inclusion in this plot.
   """
   hreal = tool.hist_real_costheta("real_costheta", phicut[0], phicut[1])
   hmcraw = tool.hist_mc_costheta("mcraw_costheta", 0, phicut[0], phicut[1])
   hmcwgt = tool.hist_mc_costheta("mcwgt_costheta", 1, phicut[0], phicut[1])
   hreal.Draw()
   hmcraw.Scale(hreal.Integral() / hmcraw.Integral())
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def compare_phi(costhetacut=(-1,1)):
   """
   Plot the phi distribution for the real data, and superimpose on
   top the Monte Carlo phase space distribution (red error bars) renormalized
   to match the total number of real events, and the PWA fit (blue error bars).
   The interval defined in the optional argument phicut selects a region in
   costheta within which the events are selected for inclusion in this plot.
   """
   hreal = tool.hist_real_phi("real_phi", costhetacut[0], costhetacut[1])
   hmcraw = tool.hist_mc_phi("mcraw_phi", 0, costhetacut[0], costhetacut[1])
   hmcwgt = tool.hist_mc_phi("mcwgt_phi", 1, costhetacut[0], costhetacut[1])
   hreal.Draw()
   hmcraw.Scale(hreal.Integral() / hmcraw.Integral())
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def test_rho_svd():
   """
   This function contains various mathematical experiments that I did to
   prove to myself that the parameterization I adopted for the SDM makes
   sense. None of this needs to be repeated for new fits, it was just a
   one-time exercise. In particular, I was curious why certain values for
   the SDM matrix elements that lie outside the limits imposed by the Schwarz
   inequality for off-diagonal elements (but not too far) seemed to never
   produce negative W values anywhere in phase space. This turns out to be
   true in the unpolarized case, but probably not true for the more general
   case with a polarized beam. Nevermind, because the SDM still must respect
   the Schwarz inequality on its own, regardless of whether violating it
   does or does not cause W to dip below zero at some point or other in the
   space of decay kinematics for this particular channel.
   """
   rho = TMatrixD(3,3)
   svd = TDecompSVD(rho)
   rgen = TRandom3();
   while True:
      rho11 = rgen.Uniform(0.5)
      rho00 = rgen.Uniform(1)
      scale10 = math.sqrt(rho11 * rho00) * 3
      rho10 = rgen.Uniform(-scale10, scale10)
      scaleM1 = rho11 * 2
      rhoM1 = rgen.Uniform(-scaleM1, scaleM1)
      rho[0][0] = rho11
      rho[1][0] = -rho10
      rho[2][0] = rhoM1
      rho[0][1] = -rho10
      rho[1][1] = rho00
      rho[2][1] = rho10
      rho[0][2] = rhoM1
      rho[1][2] = rho10
      rho[2][2] = rho11
      print "rho:" 
      for i in range(0, 3):
         print "{0:12.7f} {1:12.7f} {2:12.7f}".format(
                 rho[i][0], rho[i][1], rho[i][2])
      tool.set_rho(rho11, rho00, rhoM1, rho10)
      grad = numpy.array([0,0,0,0], dtype=numpy.float64)
      nll = Double()
      npars = Long(4)
      nll = tool(npars, grad, 4)
      if math.isnan(nll):
         if abs(rho10) <= math.sqrt(rho00 * rho11) and abs(rhoM1) <= rho11:
            print "simple boundary check failed!"
         else:
            continue
      else:
         if rho10 * rho10 > rho00 * rho11 or rhoM1 * rhoM1 > rho11 * rho11:
            print "simple boundary check foiled!"
         else:
            continue
      svd.SetMatrix(rho)
      svd.Decompose()
      sval = svd.GetSig()
      U = svd.GetU()
      V = svd.GetV()
      print "svd of rho:"
      for sig in range(0, len(sval)):
         if U[0][sig] * V[0][sig] < 0:
            sval[sig] = -sval[sig]
            V[0][sig] = -V[0][sig]
            V[1][sig] = -V[1][sig]
            V[2][sig] = -V[2][sig]
      for sig in range(0, len(sval)):
         print "{0:12.7f}   {1:10.7f} {2:10.7f} {3:10.7f}" + \
               " {4:10.7f} {5:10.7f} {6:10.7f}".format(
                sval[sig], U[sig][0], U[sig][1], U[sig][2],
                V[sig][0], V[sig][1], V[sig][2])

      resp = raw_input("Press return to continue, e to evaluate: ")
      if len(resp) == 0 or resp[0] != 'e':
         continue
      param = numpy.array([0,0,0,0], dtype=numpy.float64)
      i1 = 0
      for sig in range(0, 3):
         if U[1][sig] == 0:
            i1 = sig
            break
      i2 = (i1 + 1) % 3
      i0 = (i1 + 2) % 3
      param[0] = sval[i0] * U[0][i0]
      param[1] = sval[i0] * U[1][i0]
      param[2] = sval[i1] * U[0][i1]
      param[3] = sval[i2] * U[1][i2]
      #tool.set_rho(param)
      tool.set_rho(rho11, rho00, rhoM1, rho10)
      grad = numpy.array([0,0,0,0], dtype=numpy.float64)
      nll = Double()
      npars = Long(4)
      nll = tool(npars, grad, 4)
      print "nll = ", nll

def fake(nevents=10000000):
   """
   A simple random event generator that was useful for generating fake data
   that could be used for some of the mathematical experiments implement in
   test_rho_svd above. Who knows, it might come in handy in another context.
   """
   global tool
   tool = PWAtool()
   tool.gen_real_events(nevents)
   tool.gen_mc_events(nevents)
