# RadphiPWA - tools for doing PWA of all-neutrals meson photoproduction data taken with the Radphi detector

## Authors

* Richard Jones, University of Connecticut, Storrs, CT

## Description

The UConn group has the complete Radphi dataset stored on disk on the local cluster. The analysis of these data is essentially complete, with large numbers (several million) events in exclusive all-neutral decay channels for a number of prominent mesons. Decay samples from a number of these channels have already been looked at by students in preparation for their theses (pi0, eta, omega, phi, a0, b1) but none of these results have been published as of yet. I would like to dust off these results and extract some of the best signals for further study and eventual publication. The first of these is the omega, the largest all-neutral decay channel seen in the data (total sample size several million). The decay angular distributions provide information about the spin density matrix of the omega in exclusive vector photoproduction. The following tools in this repository were written to allow the extraction of the SDM from omega decays to pi0,gamma.

1. **PWAtool.h,cc** - a general C++ class that wraps capabilities needed to support a PWA: gathering lists of real and Monte Carlo events, parameterizing the SDM so that it obeys constraints from positivity and parity conservation for all values of the input parameters, computing the negative-log-likelihood function and its gradient, and various utility methods for extracting and plotting results.
2. **PWAomega.py** - a suite of python helper functions that set up and perform a PWA using the PWAtool class, and extract results and errors, and make plots of the output.
3. **makerootlibs.C** - root macro used to build the PWAtool shared library.
4. **Makefile** - make file which automates the running of makerootlibs.

## History

This library was developed for use with the root ntuples containing listings of Radphi real events and simulated events for the gamma,p -> omega,p reaction that were constructed by Fridah Mokaya. Fridah estimates the omega component within the complete p,pi0,gamma sample by means of several subtractions (tagging accidentals, omega invariant mass sidebands, and delta-phi side bands) using weights. Each event in both the real data and Monte Carlo samples is listed together with a weight factor which must be used whenever the event is selected for inclusion in a histogram. In the extended likelihood fit implemented in PWAtool.cc and PWAomega.py, the weight is affixed as a multiplier to the log(W) for each real event, and as a multiplier to W for each Monte Carlo event. 

## Release history

Initial release on April 8, 2016.

## Usage synopsis

 $ make [check that this works, fix any errors in the build]
 $ python
 >>> import PWAomega
 >>> PWAomega.init(1, [0, 0.08])
 >>> PWAomega.fit()
 >>> PWAomega.compare_costheta()
 >>> PWAomega.compare_phi()
 >>> PWAomega.report_errors()

## Dependencies

This package depends on having the gnu c/c++ compiler suite installed, together with the python interpreter, and the ROOT data analysis package from CERN. It was developed and tested with g++ version 4.4.9, python 2.6, and root v5.34.32.

## Building instructions

Simply cd to the top-level project directory and type "make".

## Documentation

Just this README.

## Troubleshooting

You are on your own here, but a good place to start in case of problems would be to read the comments in the code.

## Bugs

Please report to the author richard.t.jones at uconn.edu in case of problems.

## How to contribute

Build out support for more decay channels. Additional help with Radphi analysis would always be appreciated.

## Contact the authors

Contact the author richard.t.jones at uconn.edu for more information.
