#!/bin/env python
#
# o3kine.py - python root functions for playing with the kinematics
#             of gamma,p -> omega,p with omega -> 3gamma.
#
# author: richard.t.jones at uconn.edu
# version: april 11, 2016

from ROOT import *
import math

m_pi0 = 0.135
m_omega = 0.782
m_proton = 0.938
Ebeam = 5.0

random = TRandom3()

c1 = TCanvas("c1", "c1", 5, 10, 550, 500)

Radphi_theta_min = 3.5 # degrees in lab
Radphi_theta_max = 38  # degrees in lab
Radphi_energy_min = 0.08 # GeV
Radphi_thetarec_min = 30 # degrees in lab

def gen_omega(costheta0, phi0, costheta1, phi1):
   """
   omega -> pi0,gamma -> 3gamma;
   where the photons are numbered 0(bachelor), 1(pi0-forward), 2(pi0-backward)
     theta0,phi0 = decay angles of gamma[1] in pi0 rest frame,
     theta1,phi1 = decay angles of gamma[0] in omega rest frame;
   generates global 4-momenta pgamma[0..2] and pomega in omega rest frame.
   """
   global pgamma
   pgamma = [TLorentzVector(), TLorentzVector(), TLorentzVector()]
   q_omega = (m_omega**2 - m_pi0**2) / (2 * m_omega)
   sintheta1 = sqrt(1 - costheta1*costheta1)
   pgamma[0].SetXYZT(q_omega * sintheta1 * math.cos(phi1),
                     q_omega * sintheta1 * math.sin(phi1),
                     q_omega * costheta1, q_omega)
   q_pi0 = m_pi0 / 2
   sintheta0 = sqrt(1 - costheta0**2)
   pgamma[1].SetXYZT(q_pi0 * sintheta0 * math.cos(phi0),
                     q_pi0 * sintheta0 * math.sin(phi0),
                     q_pi0 * costheta0, q_pi0)
   pgamma[2].SetXYZT(-q_pi0 * sintheta0 * math.cos(phi0),
                     -q_pi0 * sintheta0 * math.sin(phi0),
                     -q_pi0 * costheta0, q_pi0)
   beta = pgamma[0].Vect() * (1 / math.sqrt(q_omega**2 + m_pi0**2))
   pgamma[1].Boost(-beta)
   pgamma[2].Boost(-beta)
   global pomega
   pomega = pgamma[0] + pgamma[1] + pgamma[2]
   return pomega

def gen_reaction(tabs):
   """
   gamma,p -> omega,p at fixed s,t where s is a global and t=-tabs;
   computes s and generates global 4-momenta 
      pbeam, 
      ptarg,
      pomega,
      precoil,
      pgamma[0..2]
   all expressed in the lab frame. Uniform random numbers are used
   to generate the decay angles of the omega and pi0 in their
   respective decay rest frames.
   """
   global pbeam
   pbeam = TLorentzVector(0, 0, Ebeam, Ebeam)
   global ptarg
   ptarg = TLorentzVector(0, 0, 0, m_proton)
   pinitial = pbeam + ptarg
   global s
   s = pinitial.Mag2()
   q_in = (s - m_proton**2) / (2 * math.sqrt(s))
   q_cm = math.sqrt((s - m_proton**2 + m_omega**2)**2 / (4 * s) - m_omega**2)
   EomegaCM = math.sqrt(m_omega**2 + q_cm**2)
   EprotonCM = math.sqrt(m_proton**2 + q_cm**2)
   costhetaCM = (2 * q_in * EomegaCM - m_omega**2 - tabs) / (2 * q_in * q_cm)
   if abs(costhetaCM) > 1:
      print "tabs =", tabs, "is out of range, please try another value"
      return 0
   costheta0 = random.Uniform(-1, 1)
   phi0 = random.Uniform(-math.pi, math.pi)
   costheta1 = random.Uniform(-1, 1)
   phi1 = random.Uniform(-math.pi, math.pi)
   pomega = gen_omega(costheta0, phi0, costheta1, phi1)
   sinthetaCM = math.sqrt(1 - costhetaCM**2)
   beta = TVector3(q_cm * sinthetaCM, 0, q_cm * costhetaCM) * (1 / EomegaCM)
   pomega.Boost(beta)
   pgamma[0].Boost(beta)
   pgamma[1].Boost(beta)
   pgamma[2].Boost(beta)
   global precoil
   precoil = TLorentzVector(-q_cm * sinthetaCM, 0, -q_cm * costhetaCM, EprotonCM)
   betaCM = pinitial.Vect() * (1 / pinitial[3])
   pgamma[0].Boost(betaCM)
   pgamma[1].Boost(betaCM)
   pgamma[2].Boost(betaCM)
   pomega.Boost(betaCM)
   precoil.Boost(betaCM)
   return pomega

def GJframe():
   """
   Transforms 4-vectors for the reaction gamma,p -> omega,p, omega -> 3gamma
   into the Gottfried-Jackson frame. The global 4-momenta modified are
      pbeam, 
      ptarg,
      pomega,
      precoil,
      pgamma[0..2]
   """
   beta0 = pomega.Vect() * (1 / pomega[3])
   pomega.Boost(-beta0)
   pbeam.Boost(-beta0)
   ptarg.Boost(-beta0)
   precoil.Boost(-beta0)
   theta0 = pbeam.Theta()
   phi0 = pbeam.Phi()
   pbeam.RotateZ(-phi0)
   ptarg.RotateZ(-phi0)
   precoil.RotateZ(-phi0)
   pbeam.RotateY(-theta0)
   precoil.RotateY(-theta0)
   psi0 = precoil.Phi()
   ptarg.RotateZ(-psi0)
   precoil.RotateZ(-psi0)
   for g in range(0, 3):
      pgamma[g].Boost(-beta0)
      pgamma[g].RotateZ(-phi0)
      pgamma[g].RotateY(-theta0)
      pgamma[g].RotateZ(-psi0)

def hist_costhetaGJ(tabs, nevents=10000):
   """
   Generate a Monte Carlo sample of the reaction phase-space distributed 
   gamma,p -> omega(3gamma),p events at fixed s,t where s is a global
   constant and t=-tabs; total events generated is nevents. The histogram
   of accepted cos(thetaGJ) is plotted and saved in global h1, and a
   second histogram of phiGJ is also saved (but not plotted) as global h2.
   """
   global h1
   h1 = gROOT.FindObject("h1")
   if h1:
      h1.Delete()
   h1 = TH1I("h1", "costheta_GJ", 100, -1, 1)
   global h2
   h2 = gROOT.FindObject("h2")
   if h2:
      h2.Delete()
   h2 = TH1I("h2", "phi_GJ", 100, -math.pi, math.pi)
   for event in range(0, nevents):
      gen_reaction(tabs)
      gbad = 0
      for g in range(0, 3):
         theta = pgamma[g].Theta() * 180/math.pi
         if theta < Radphi_theta_min or theta > Radphi_theta_max:
            gbad += 1
         elif pgamma[g][3] < Radphi_energy_min:
            gbad += 1
         elif precoil.Theta() * 180/math.pi < Radphi_thetarec_min:
            gbad += 1
      if gbad == 0:
         GJframe()
         h1.Fill(math.cos(pgamma[0].Theta()))
         h2.Fill(pgamma[0].Phi())
   h1.Draw()
   c1.Update()
