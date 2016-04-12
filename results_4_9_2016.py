#!/bin/env python
#
# results_4_9_2015.py : fit results created using PWAomega.py
#                       formed into a self-plotting data file.
# usage:
#    $ python
#    >>> import results_4_9_2015
#    >>> results_4_9_2015.plot(0)
#    >>> results_4_9_2015.plot(1)
#    >>> results_4_9_2015.plot(2)
#    >>> results_4_9_2015.plot(3)
#
# actual fit results:
"""
tbins = [0.0, 0.08]
total acceptance-corrected yield = 6777615.65016 +/- 76690.78406
   rho11 =  0.29986 +/-  0.00450
   rho00 =  0.40028 +/-  0.00685
   rhoM1 = -0.29921 +/-  0.00440
Re_rho10 =  0.34626 +/-  0.00194

complete correlation matrix, order as listed above:
   1.000    -0.777    -0.986     0.130
  -0.777     1.000     0.741     0.519
  -0.986     0.741     1.000    -0.185
   0.130     0.519    -0.185     1.000

tbins = [0.08, 0.18]
total acceptance-corrected yield = 2796975.18881 +/- 23658.42024
   rho11 =  0.28703 +/-  0.00318
   rho00 =  0.42594 +/-  0.00558
   rhoM1 = -0.28703 +/-  0.00318
Re_rho10 =  0.34965 +/-  0.00157

complete correlation matrix, order as listed above:
   1.000    -0.735    -1.000     0.161
  -0.735     1.000     0.735     0.551
  -1.000     0.735     1.000    -0.161
   0.161     0.551    -0.161     1.000

tbins = [0.18, 0.30]
total acceptance-corrected yield = 2279114.90158 +/- 22195.03604
   rho11 =  0.29370 +/-  0.00386
   rho00 =  0.41260 +/-  0.00594
   rhoM1 = -0.29370 +/-  0.00386
Re_rho10 =  0.34811 +/-  0.00143

complete correlation matrix, order as listed above:
   1.000    -0.825    -1.000     0.153
  -0.825     1.000     0.825     0.432
  -1.000     0.825     1.000    -0.153
   0.153     0.432    -0.153     1.000

tbins = [0.30, 0.45]
total acceptance-corrected yield = 2401263.24437 +/- 23249.35505
   rho11 =  0.31903 +/-  0.00390
   rho00 =  0.36195 +/-  0.00575
   rhoM1 = -0.31070 +/-  0.00404
Re_rho10 =  0.33543 +/-  0.00174

complete correlation matrix, order as listed above:
   1.000    -0.756    -0.908    -0.003
  -0.756     1.000     0.741     0.591
  -0.908     0.741     1.000    -0.047
  -0.003     0.591    -0.047     1.000

tbins = [0.45, 0.65]
total acceptance-corrected yield = 2565398.43403 +/- 29307.72270
   rho11 =  0.36138 +/-  0.00471
   rho00 =  0.27724 +/-  0.00645
   rhoM1 = -0.35710 +/-  0.00490
Re_rho10 =  0.31484 +/-  0.00254

complete correlation matrix, order as listed above:
   1.000    -0.722    -0.976    -0.204
  -0.722     1.000     0.729     0.816
  -0.976     0.729     1.000     0.209
  -0.204     0.816     0.209     1.000

tbins = [0.65, 0.90]
total acceptance-corrected yield = 3094167.30249 +/- 232249.49297
   rho11 =  0.40653 +/-  0.03599
   rho00 =  0.18695 +/-  0.02130
   rhoM1 = -0.40653 +/-  0.03599
Re_rho10 =  0.27568 +/-  0.00369

complete correlation matrix, order as listed above:
   1.000    -0.996    -1.000    -0.934
  -0.996     1.000     0.996     0.961
  -1.000     0.996     1.000     0.934
  -0.934     0.961     0.934     1.000

tbins = [0.90, 1.20]
total acceptance-corrected yield = 5207985.67069 +/- 125006.66231
   rho11 =  0.45470 +/-  0.01127
   rho00 =  0.09061 +/-  0.00824
   rhoM1 = -0.45424 +/-  0.01131
Re_rho10 =  0.20268 +/-  0.00828

complete correlation matrix, order as listed above:
   1.000    -0.468    -0.999    -0.216
  -0.468     1.000     0.475     0.963
  -0.999     0.475     1.000     0.223
  -0.216     0.963     0.223     1.000
"""

import re
import numpy
from ROOT import *

parnames = ("rho11", "rho00", "rhoM1", "Re_rho10")

def plot(par):
   parname = parnames[par]
   source = open(__file__)
   scanning = 0
   tabs = numpy.ndarray((2, 99), dtype=numpy.float)
   values = numpy.ndarray((99,), dtype=numpy.float)
   errors = numpy.ndarray((99,), dtype=numpy.float)
   maxlim = -1e99
   minlim = +1e99
   points = 0
   for line in source:
      if re.match(r"\"\"\"", line):
         if scanning:
            break
         else:
            scanning = 1
            continue
      elif not scanning:
         continue
      elif re.match(r" *" + parnames[par] + r" .*", line):
         flds = line.split()
         try:
            val = float(flds[2])
            err = float(flds[4])
            values[points] = val
            errors[points] = err
            if val + err > maxlim:
               maxlim = val + err
            if val - err < minlim:
               minlim = val - err
            points += 1
         except ValueError:
            continue
      elif re.match(r"tbins = .*", line):
         flds = line.split()
         try:
            tlower = float(flds[2].strip("[], "))
            tupper = float(flds[3].strip("[], "))
            tabs[0][points] = (tupper + tlower)/2
            tabs[1][points] = (tupper - tlower)/2
         except ValueError:
            continue
   global dataset
   dataset = TGraphErrors(points, tabs[0], values, tabs[1], errors)
   dataset.SetTitle("{0} vs |t|".format(parnames[par]))
   dataset.SetMarkerColor(kBlue)
   dataset.SetMarkerStyle(21)
   dataset.Draw("ALP")
   c1.Update()
