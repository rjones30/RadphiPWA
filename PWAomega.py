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

def init(check=0, tlim=[0, 99]):
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
   fitter = TMinuit(4)
   tool.SetFCN(fitter)
   err1 = Long()
   fitter.mnparm(0, "a0", 0.3, 0.01, 0, 0, err1)
   err2 = Long()
   fitter.mnparm(1, "c0", 0.3, 0.01, 0, 0, err2)
   err3 = Long()
   fitter.mnparm(2, "a1", 0.3, 0.01, 0, 0, err3)
   err4 = Long()
   fitter.mnparm(3, "c2", 0.3, 0.01, 0, 0, err4)
   if err1 > 0 or err2 > 0 or err3 > 0 or err4 > 0:
      print "fitter.mnparm choked, cannot continue!"
      sys.exit(1)
   if check > 0:
      fitter.Command("set gradient")
   fitter.Command("set gradient 1")

def fit():
   #fitter.Command("set parameter 1 5.55065e-03")
   #fitter.Command("set parameter 2 9.80459e-03")
   #fitter.Command("set parameter 3 -6.03451e-04")
   #fitter.Command("set parameter 4 4.21531e-02")
   fitter.Command("migrad 500")

def report_errors():
   rho11 = tool.get_Re_rho(1,1)
   rho00 = tool.get_Re_rho(0,0)
   rhoM1 = tool.get_Re_rho(-1,1)
   rho10 = tool.get_Re_rho(1,0)
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
   print "   rho11 = {0:8.5f} +/- {1:8.5f}".format(rho11, math.sqrt(covar[0][0]))
   print "   rho00 = {0:8.5f} +/- {1:8.5f}".format(rho00, math.sqrt(covar[1][1]))
   print "   rhoM1 = {0:8.5f} +/- {1:8.5f}".format(rhoM1, math.sqrt(covar[2][2]))
   print "Re_rho10 = {0:8.5f} +/- {1:8.5f}".format(rho10, math.sqrt(covar[3][3]))
   print
   print "complete correlation matrix, order as listed above:"
   for i in range(0, 4):
      print "{0:8.3f}  {1:8.3f}  {2:8.3f}  {3:8.3f}".format(
            covar[i][0] / math.sqrt(covar[i][i] * covar[0][0]),
            covar[i][1] / math.sqrt(covar[i][i] * covar[1][1]),
            covar[i][2] / math.sqrt(covar[i][i] * covar[2][2]),
            covar[i][3] / math.sqrt(covar[i][i] * covar[3][3]))

def compare_costheta(phicut=(-math.pi,math.pi)):
   hreal = tool.hist_real_costheta("real_costheta", phicut[0], phicut[1])
   hmcraw = tool.hist_mc_costheta("mcraw_costheta", 0, phicut[0], phicut[1])
   hmcwgt = tool.hist_mc_costheta("mcwgt_costheta", 1, phicut[0], phicut[1])
   hreal.Draw()
   rawScale = hreal.Integral() / hmcraw.Integral()
   hmcraw.Scale(rawScale)
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   wgtScale = hreal.Integral() / hmcwgt.Integral()
   print "rescale factor for MC fit results is", wgtScale
   hmcwgt.Scale(wgtScale)
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def compare_phi(costhetacut=(-1,1)):
   hreal = tool.hist_real_phi("real_phi", costhetacut[0], costhetacut[1])
   hmcraw = tool.hist_mc_phi("mcraw_phi", 0, costhetacut[0], costhetacut[1])
   hmcwgt = tool.hist_mc_phi("mcwgt_phi", 1, costhetacut[0], costhetacut[1])
   hreal.Draw()
   hmcraw.Scale(hreal.Integral() / hmcraw.Integral())
   hmcraw.SetLineColor(kRed)
   hmcraw.Draw("e,same")
   hmcwgt.Scale(hreal.Integral() / hmcwgt.Integral())
   hmcwgt.SetLineColor(kBlue)
   hmcwgt.Draw("e,same")
   c1.Update

def test_rho_svd():
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
         print "{0:12.7f}   {1:10.7f} {2:10.7f} {3:10.7f} {4:10.7f} {5:10.7f} {6:10.7f}".format(
                sval[sig], U[sig][0], U[sig][1], U[sig][2], V[sig][0], V[sig][1], V[sig][2])

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
   global tool
   tool = PWAtool()
   tool.gen_real_events(nevents)
   tool.gen_mc_events(nevents)
