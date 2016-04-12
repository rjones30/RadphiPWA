#!/bin/env python
#
# omegatree.py - simple python root macro for running the omega TSelector
#                over a chain of real or Monte Carlo radphi events.
#
# author: richard.t.jones at uconn.edu
# version: april 12, 2016
#

from ROOT import *
import glob

realdir = "/pnfs4/phys.uconn.edu/data/Gluex/radphi/pass-6-2014/"

h1chain = TChain("h1")
for rootfile in glob.iglob(realdir + "r*.root"):
   h1chain.Add(rootfile)

h1chain.Process("omega.C+g")
