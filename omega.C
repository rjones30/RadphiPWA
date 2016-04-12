#if RTJ
This code has been commented by RTJ on April 9, 2016.
To look for all comments, search for string RTJ.
#endif
#define omega_cxx
// The class definition in omega.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("omega.C")
// Root > T->Process("omega.C","some options")
// Root > T->Process("omega.C+")
//

#include "omega.h"
#include <TH2.h>
#include <TStyle.h>
#include <TVector3.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TProofServ.h>
#include <TF1.h>

#include <vector>
#include <cmath>
#include <iostream>



char pwa_ntuple_form[] = "tabs/D:"
                         "Ebeam/D:"
                         "omegaphi/D:"
                         "gjcosthe/D:"
                         "gjthe/D:"
                         "gjphi/D:"
                         "helcosthe/D:"
                         "helthe/D:"
                         "helphi/D:"
                         "wgt[8]/D:"
                         "Ewgt1[7]/D:"
                         "Ewgt2[7]/D:"
                         "Ewgt3[7]/D:"
                         "Ewgt4[7]/D";


#define MIN_TOTAL_ENERGY  3.0
#define MIN_TOTAL_ENERGY_1  2.5
#define MIN_TOTAL_ENERG_2  3.50
#define LGD_CLUSTERS  3
#define CPV_REC_LOW  -3.0
#define CPV_REC_HIGH  +3.0
#define TRIG_TAG_WIN  20
#define TAG_MIN_ENERGY 4
#define PI 3.14159265
#define sqr(x) ((x)*(x))
#define min2(a,b) ((a)<(b)?(a):(b))
#define min(a,b,c) (min2(min2((a),(b)),(c)))
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

void omega::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void omega::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   TString option = GetOption();
   TString title;
   TString name;
   TString outfilename;
   outfilename.Form("pwa_tree_%d.root", 0);//gProofServ->GetGroupId());
   ntoutfile = new TFile(outfilename, "recreate");
   ntout = new TTree("pwa_tree", "omega pwa data tree");
   ntout->Branch("pwa_ntuple", &pwa_ntuple, pwa_ntuple_form);

   amass_1d = new TH1D("two_gamma "," ", 100, 0, 1.0);
   amass_1d->Sumw2();
   GetOutputList()->Add(amass_1d);
   omass_1d = new TH1D("two_gamma_cut","", 100, 0.,1.0);
   omass_1d->Sumw2();
   GetOutputList()->Add(omass_1d);
   remass_1d = new TH1D("remass","  ",150,0, 1.5);
   remass_1d->Sumw2();
   GetOutputList()->Add(remass_1d);
   remass2_1d = new TH1D("remass2"," mass ",150,0, 1.5);
   remass2_1d->Sumw2();
   GetOutputList()->Add(remass2_1d);
   remass3_1d = new TH1D("remass3"," mass ", 150 ,0.0,1.5);
   remass3_1d->Sumw2();
   GetOutputList()->Add(remass3_1d);
   remass4_1d = new TH1D("remass4"," mass ",150,0.0, 1.5);
   remass4_1d->Sumw2();
   GetOutputList()->Add(remass4_1d);
   remass5_1d = new TH1D("remass5","mass ", 100, 0.0, 1.5);
   remass5_1d->Sumw2();
   GetOutputList()->Add(remass5_1d);
   remass6_1d = new TH1D("remass6"," mass ",100,0.0, 1.5);
   remass6_1d->Sumw2();
   GetOutputList()->Add(remass6_1d);
   remass7_1d = new TH1D("remass7"," mass ",100,0.0, 1.5);
   remass7_1d->Sumw2();
   GetOutputList()->Add(remass7_1d);
   remass8_1d = new TH1D("remass8"," mass ",100,0.0, 1.5);
   remass8_1d->Sumw2();
   GetOutputList()->Add(remass8_1d);
   remass9_1d = new TH1D("remass9"," mass ",100,0.0, 1.5);
   remass9_1d->Sumw2();
   GetOutputList()->Add(remass9_1d);
   remass10_1d = new TH1D("remass10"," mass ",100,0.0, 1.5);
   remass10_1d->Sumw2();
   GetOutputList()->Add(remass10_1d);
   remass11_1d = new TH1D("remass11"," mass ",100,0.0, 1.5);
   remass11_1d->Sumw2();
   GetOutputList()->Add(remass11_1d);
   remass12_1d = new TH1D("remass12"," mass ",100,0.0, 1.5);
   remass12_1d->Sumw2();
   GetOutputList()->Add(remass12_1d);
   remass13_1d = new TH1D("remass13"," mass ",100,0.0, 1.5);
   remass13_1d->Sumw2();
   GetOutputList()->Add(remass13_1d);
   remass14_1d = new TH1D("remass14"," mass ",100,0.0, 1.5);
   remass14_1d->Sumw2();
   GetOutputList()->Add(remass14_1d);
   remass15_1d = new TH1D("remass15"," mass ",100,0.0, 1.5);
   remass15_1d->Sumw2();
   GetOutputList()->Add(remass15_1d);
   remass16_1d = new TH1D("remass16"," mass ",100,0.0, 1.5);
   remass16_1d->Sumw2();
   GetOutputList()->Add(remass16_1d);
   remass17_1d = new TH1D("remass17"," mass ",100,0.0, 1.5);
   remass17_1d->Sumw2();
   GetOutputList()->Add(remass17_1d);
   remass18_1d = new TH1D("remass18"," mass ",100,0.0, 1.5);
   remass18_1d->Sumw2();
   GetOutputList()->Add(remass18_1d);
   remass19_1d = new TH1D("remass19"," mass ",100,0.0, 1.5);
   remass19_1d->Sumw2();
   GetOutputList()->Add(remass19_1d);
   remass20_1d = new TH1D("remass20"," mass ",100,0.0, 1.5);
   remass20_1d->Sumw2();
   GetOutputList()->Add(remass20_1d);
   remass21_1d = new TH1D("remass21"," mass ",100,0.0, 1.5);
   remass21_1d->Sumw2();
   GetOutputList()->Add(remass21_1d);
   remass22_1d = new TH1D("remass22"," mass ",100,0.0, 1.5);
   remass22_1d->Sumw2();
   GetOutputList()->Add(remass22_1d);
   remass23_1d = new TH1D("remass23"," mass ",100,0.0, 1.5);
   remass23_1d->Sumw2();
   GetOutputList()->Add(remass23_1d);
   remass24_1d = new TH1D("remass24"," mass ",100,0.0, 1.5);
   remass24_1d->Sumw2();
   GetOutputList()->Add(remass24_1d);
   remass25_1d = new TH1D("remass25"," mass ",100,0.0, 1.5);
   remass25_1d->Sumw2();
   GetOutputList()->Add(remass25_1d);
   remass26_1d = new TH1D("remass26"," mass ",100,0.0, 1.5);
   remass26_1d->Sumw2();
   GetOutputList()->Add(remass26_1d);
   remass27_1d = new TH1D("remass27"," mass ",100,0.0, 1.5);
   remass27_1d->Sumw2();
   GetOutputList()->Add(remass27_1d);
   remass28_1d = new TH1D("remass28"," mass ",100,0.0, 1.5);
   remass28_1d->Sumw2();
   GetOutputList()->Add(remass28_1d);
   remass29_1d = new TH1D("remass29"," mass ",100,0.0, 1.5);
   remass29_1d->Sumw2();
   GetOutputList()->Add(remass29_1d);
   remass30_1d = new TH1D("remass30"," mass ",100,0.0, 1.5);
   remass30_1d->Sumw2();
   GetOutputList()->Add(remass30_1d);
   remass31_1d = new TH1D("remass31"," mass ",100,0.0, 1.5);
   remass31_1d->Sumw2();
   GetOutputList()->Add(remass31_1d);
   remass32_1d = new TH1D("remass32"," mass ",100,0.0, 1.5);
   remass32_1d->Sumw2();
   GetOutputList()->Add(remass32_1d);
   remass33_1d = new TH1D("remass33"," mass ",100,0.0, 1.5);
   remass33_1d->Sumw2();
   GetOutputList()->Add(remass33_1d);
   remass34_1d = new TH1D("remass34"," mass ",100,0.0, 1.5);
   remass34_1d->Sumw2();
   GetOutputList()->Add(remass34_1d);
   remass35_1d = new TH1D("remass35"," mass ",100,0.0, 1.5);
   remass35_1d->Sumw2();
   GetOutputList()->Add(remass35_1d);
   remass36_1d = new TH1D("remass36"," mass ",100,0.0, 1.5);
   remass36_1d->Sumw2();
   GetOutputList()->Add(remass36_1d);
   remass37_1d = new TH1D("remass37"," mass ",100,0.0, 1.5);
   remass37_1d->Sumw2();
   GetOutputList()->Add(remass37_1d);
   remass38_1d = new TH1D("remass38"," mass ",100,0.0, 1.5);
   remass38_1d->Sumw2();
   GetOutputList()->Add(remass38_1d);
   remass39_1d = new TH1D("remass39"," mass ",100,0.0, 1.5);
   remass39_1d->Sumw2();
   GetOutputList()->Add(remass39_1d);
   remass40_1d = new TH1D("remass40"," mass ",100,0.0, 1.5);
   remass40_1d->Sumw2();
   GetOutputList()->Add(remass40_1d);


   p_angle = new TH2D("pangle"," ",100,-1.0,1.0,100,-180.0,180.0);
   p_angle->Sumw2();
   GetOutputList()->Add(p_angle);
   p_angle1 = new TH2D("pangle1"," ",100,-1.0,1.0,100,-180.0,180);
   p_angle1->Sumw2();
   GetOutputList()->Add(p_angle1);
   p_angle2 = new TH2D("pangle2"," ",100,-1.0,1.0,100,-180.0,180.0);
   p_angle2->Sumw2();
   GetOutputList()->Add(p_angle2);
   p_angle3 = new TH2D("pangle3"," ",100,-1.0,1.0,100,-180.0,180.0);
   p_angle3->Sumw2();
   GetOutputList()->Add(p_angle3);
   p_angle4 = new TH2D("pangle4"," ",100,-1.0,1.0,100,-180.0,180);
   p_angle4->Sumw2();
   GetOutputList()->Add(p_angle4);
   p_angle5 = new TH2D("pangle5"," ",100,-1.0,1.0,100,-180.0,180.0);
   p_angle5->Sumw2();
   GetOutputList()->Add(p_angle5);
   p_angle6 = new TH2D("pangle6"," ",100,-1.0,1.0,100,-180.0,180.0);
   p_angle6->Sumw2();
   GetOutputList()->Add(p_angle6);
   o_angle = new TH1D("oangle"," ",90,0.0,180);
   o_angle->Sumw2();
   GetOutputList()->Add(o_angle);


   Efrwd_1d = new TH1D("Efrwd"," energy  in the LGD", 30, 0, 30);
   GetOutputList()->Add(Efrwd_1d);
   Efrwd1_1d = new TH1D("Efrwd1"," energy  in the LGD", 100, -2.0, 2.0);
   GetOutputList()->Add(Efrwd1_1d);
   Efrwd2_1d = new TH1D("Efrwd2"," energy  in the LGD", 100, -2.0, 2.0);
   GetOutputList()->Add(Efrwd2_1d);
   Efrwd3_1d = new TH1D("Efrwd3"," energy  in the LGD", 100, -2.0, 2.0);
   GetOutputList()->Add(Efrwd3_1d);
   Efrwd4_1d = new TH1D("Efrwd4"," energy  in the LGD", 100, -2.0, 2.0);
   GetOutputList()->Add(Efrwd4_1d);



   mom_trans_1d = new TH1D("mom_trans"," -t dist_low sb ",100,0, 2.0);
   mom_trans_1d->Sumw2();
   GetOutputList()->Add(mom_trans_1d);
   mom_trans1_1d = new TH1D("mom_trans1"," -t dist_high sb",100,0, 2.0);
   mom_trans1_1d->Sumw2();
   GetOutputList()->Add(mom_trans1_1d);
   mom_trans2_1d = new TH1D("mom_trans2"," -t distribution ",100,0, 2.0);
   mom_trans2_1d->Sumw2();
   GetOutputList()->Add(mom_trans2_1d);
   mom_trans3_1d = new TH1D("mom_trans3"," -t distribution ",100,0, 2.0);
   mom_trans3_1d->Sumw2();
   GetOutputList()->Add(mom_trans3_1d);
   mom_trans4_1d = new TH1D("mom_trans4"," -t distribution ",100,0, 2.0);
   mom_trans4_1d->Sumw2();
   GetOutputList()->Add(mom_trans4_1d);
   mom_trans5_1d = new TH1D("mom_trans5"," -t distribution ",100,0, 2.0);
   mom_trans5_1d->Sumw2();
   GetOutputList()->Add(mom_trans5_1d);
   mom_trans6_1d = new TH1D("mom_trans6"," -t distribution ",100,0, 2.0);
   mom_trans6_1d->Sumw2();
   GetOutputList()->Add(mom_trans6_1d);
   mom_trans7_1d = new TH1D("mom_trans7"," -t distribution ",100,0, 2.0);
   mom_trans7_1d->Sumw2();
   GetOutputList()->Add(mom_trans7_1d);
   mom_trans8_1d = new TH1D("mom_trans8"," -t distribution ",100,0, 2.0);
   mom_trans8_1d->Sumw2();
   GetOutputList()->Add(mom_trans8_1d);
   mom_trans9_1d = new TH1D("mom_trans9"," -t distribution ",100,0, 2.0);
   mom_trans9_1d->Sumw2();
   GetOutputList()->Add(mom_trans9_1d);
   prot_mass_1d = new TH1D("prot_mass"," prot_mass=friends ",100,0, 6.0);
   prot_mass_1d->Sumw2();
   GetOutputList()->Add(prot_mass_1d);
   prot_mass2_1d = new TH1D("prot_mass2","proton mass-friends",100,0, 2.0);
   prot_mass2_1d->Sumw2();
   GetOutputList()->Add(prot_mass2_1d);
   prot_rf = new TH1D("protrf"," ",100,0, 10);
   GetOutputList()->Add(prot_rf);
   phi_lab = new TH1D("philab"," ",180,-180, 180);
   phi_lab->Sumw2();
   GetOutputList()->Add(phi_lab);
   phi_lab2 = new TH1D("philab2"," ",180,-180, 180);
   phi_lab2->Sumw2();
   GetOutputList()->Add(phi_lab2);




   phi_hf = new TH1D("phihf0"," ",180,-180, 180);
   phi_hf->Sumw2();
   GetOutputList()->Add(phi_hf);
   phi_hf1 = new TH1D("phihf1"," ",180,-180, 180);
   phi_hf1->Sumw2();
   GetOutputList()->Add(phi_hf1);
   phi_hf2 = new TH1D("phihf2"," ",180,-180, 180);
   phi_hf2->Sumw2();
   GetOutputList()->Add(phi_hf2);
   phi_hf3 = new TH1D("phihf3"," ",180,-180, 180);
   phi_hf3->Sumw2();
   GetOutputList()->Add(phi_hf3);
   phi_hf4 = new TH1D("phihf4"," ",180,-180, 180);
   phi_hf4->Sumw2();
   GetOutputList()->Add(phi_hf4);
   phi_hf5 = new TH1D("phihf5"," ",180,-180, 180);
   phi_hf5->Sumw2();
   GetOutputList()->Add(phi_hf5);
   phi_hf6 = new TH1D("phihf6"," ",180,-180, 180);
   phi_hf6->Sumw2();
   GetOutputList()->Add(phi_hf6);
   phi_hf7 = new TH1D("phihf7"," ",180,-180, 180);
   phi_hf7->Sumw2();
   GetOutputList()->Add(phi_hf7);
   phi_hf8 = new TH1D("phihf8"," ",180,-180, 180);
   phi_hf8->Sumw2();
   GetOutputList()->Add(phi_hf8);
   phi_hf9 = new TH1D("phihf9"," ",180,-180, 180);
   phi_hf9->Sumw2();
   GetOutputList()->Add(phi_hf9);
   phi_hf10 = new TH1D("phihf10"," ",180,-180, 180);
   phi_hf10->Sumw2();
   GetOutputList()->Add(phi_hf10);
   phi_hf11 = new TH1D("phihf11"," ",180,-180, 180);
   phi_hf11->Sumw2();
   GetOutputList()->Add(phi_hf11);
   phi_hf12 = new TH1D("phihf12"," ",180,-180, 180);
   phi_hf12->Sumw2();
   GetOutputList()->Add(phi_hf12);
   phi_hf13 = new TH1D("phihf13"," ",180,-180, 180);
   phi_hf13->Sumw2();
   GetOutputList()->Add(phi_hf13);
   phi_hf14 = new TH1D("phihf14"," ",180,-180, 180);
   phi_hf14->Sumw2();
   GetOutputList()->Add(phi_hf14);
   phi_hf15 = new TH1D("phihf15"," ",180,-180, 180);
   phi_hf15->Sumw2();
   GetOutputList()->Add(phi_hf15);
   phi_hf16 = new TH1D("phihf16"," ",180,-180, 180);
   phi_hf16->Sumw2();
   GetOutputList()->Add(phi_hf16);
   phi_hf17 = new TH1D("phihf17"," ",180,-180, 180);
   phi_hf17->Sumw2();
   GetOutputList()->Add(phi_hf17);
   phi_hf18 = new TH1D("phihf18"," ",180,-180, 180);
   phi_hf18->Sumw2();
   GetOutputList()->Add(phi_hf18);
   phi_hf19 = new TH1D("phihf19"," ",180,-180, 180);
   phi_hf19->Sumw2();
   GetOutputList()->Add(phi_hf19);



   phi_gj = new TH1D("phigj0"," ",30,-180, 180);
   phi_gj->Sumw2();
   GetOutputList()->Add(phi_gj);
   phi_gj1 = new TH1D("phigj1"," ",30,-180, 180);
   phi_gj1->Sumw2();
   GetOutputList()->Add(phi_gj1);
   phi_gj2 = new TH1D("phigj2"," ",30,-180, 180);
   phi_gj2->Sumw2();
   GetOutputList()->Add(phi_gj2);
   phi_gj3 = new TH1D("phigj3"," ",30,-180, 180);
   phi_gj3->Sumw2();
   GetOutputList()->Add(phi_gj3);
   phi_gj4 = new TH1D("phigj4"," ",30,-180, 180);
   phi_gj4->Sumw2();
   GetOutputList()->Add(phi_gj4);
   phi_gj5 = new TH1D("phigj5"," ",30,-180, 180);
   phi_gj5->Sumw2();
   GetOutputList()->Add(phi_gj5);
   phi_gj6 = new TH1D("phigj6"," ",30,-180, 180);
   phi_gj6->Sumw2();
   GetOutputList()->Add(phi_gj6);
   phi_gj7 = new TH1D("phigj7"," ",30,-180, 180);
   phi_gj7->Sumw2();
   GetOutputList()->Add(phi_gj7);
   phi_gj8 = new TH1D("phigj8"," ",90,-180, 180);
   phi_gj8->Sumw2();
   GetOutputList()->Add(phi_gj8);
   phi_gj9 = new TH1D("phigj9"," ",90,-180, 180);
   phi_gj9->Sumw2();
   GetOutputList()->Add(phi_gj9);
   phi_gj10 = new TH1D("phigj10"," ",90,-180, 180);
   phi_gj10->Sumw2();
   GetOutputList()->Add(phi_gj10);
   phi_gj11 = new TH1D("phigj11"," ",180,-180, 180);
   phi_gj11->Sumw2();
   GetOutputList()->Add(phi_gj11);
   phi_gj12 = new TH1D("phigj12"," ",180,-180, 180);
   phi_gj12->Sumw2();
   GetOutputList()->Add(phi_gj12);
   phi_gj13 = new TH1D("phigj13"," ",180,-180, 180);
   phi_gj13->Sumw2();
   GetOutputList()->Add(phi_gj13);
   phi_gj14 = new TH1D("phigj14"," ",180,-180, 180);
   phi_gj14->Sumw2();
   GetOutputList()->Add(phi_gj14);
   phi_gj15 = new TH1D("phigj15"," ",180,-180, 180);
   phi_gj15->Sumw2();
   GetOutputList()->Add(phi_gj15);
   phi_gj16 = new TH1D("phigj16"," ",180,-180, 180);
   phi_gj16->Sumw2();
   GetOutputList()->Add(phi_gj16);
   phi_gj17 = new TH1D("phigj17"," ",180,-180, 180);
   phi_gj17->Sumw2();
   GetOutputList()->Add(phi_gj17);
   phi_gj18 = new TH1D("phigj18"," ",180,-180, 180);
   phi_gj18->Sumw2();
   GetOutputList()->Add(phi_gj18);
   phi_gj19 = new TH1D("phigj19"," ",180,-180, 180);
   phi_gj19->Sumw2();
   GetOutputList()->Add(phi_gj19);

   
   phigj_2 = new TH1D("phigj2_0"," ",90,-180, 180);
   phigj_2->Sumw2();
   GetOutputList()->Add(phigj_2);
   phigj_2_1 = new TH1D("phigj2_1"," ",90,-180, 180);
   phigj_2_1->Sumw2();
   GetOutputList()->Add(phigj_2_1);
   phigj_2_2 = new TH1D("phigj2_2"," ",90,-180, 180);
   phigj_2_2->Sumw2();
   GetOutputList()->Add(phigj_2_2);
   phigj_2_3 = new TH1D("phigj2_3"," ",90,-180, 180);
   phigj_2_3->Sumw2();
   GetOutputList()->Add(phigj_2_3);
   phigj_2_4 = new TH1D("phigj2_4"," ",90,-180, 180);
   phigj_2_4->Sumw2();
   GetOutputList()->Add(phigj_2_4);
   phigj_2_5 = new TH1D("phigj2_5"," ",90,-180, 180);
   phigj_2_5->Sumw2();
   GetOutputList()->Add(phigj_2_5);
   phigj_2_6 = new TH1D("phigj2_6"," ",90,-180, 180);
   phigj_2_6->Sumw2();
   GetOutputList()->Add(phigj_2_6);
   phigj_2_7 = new TH1D("phigj2_7"," ",90,-180, 180);
   phigj_2_7->Sumw2();
   GetOutputList()->Add(phigj_2_7);
   phigj_2_8 = new TH1D("phigj2_8"," ",90,-180, 180);
   phigj_2_8->Sumw2();
   GetOutputList()->Add(phigj_2_8);
   phigj_2_9 = new TH1D("phigj2_9"," ",90,-180, 180);
   phigj_2_9->Sumw2();
   GetOutputList()->Add(phigj_2_9);
   phigj_2_10 = new TH1D("phigj2_10"," ",90,-180, 180);
   phigj_2_10->Sumw2();
   GetOutputList()->Add(phigj_2_10);
   phigj_2_11 = new TH1D("phigj2_11"," ",180,-180, 180);
   phigj_2_11->Sumw2();
   GetOutputList()->Add(phigj_2_11);
   phigj_2_12 = new TH1D("phigj2_12"," ",180,-180, 180);
   phigj_2_12->Sumw2();
   GetOutputList()->Add(phigj_2_12);
   phigj_2_13 = new TH1D("phigj2_13"," ",180,-180, 180);
   phigj_2_13->Sumw2();
   GetOutputList()->Add(phigj_2_13);
   phigj_2_14 = new TH1D("phigj2_14"," ",180,-180, 180);
   phigj_2_14->Sumw2();
   GetOutputList()->Add(phigj_2_14);
   phigj_2_15 = new TH1D("phigj2_15"," ",180,-180, 180);
   phigj_2_15->Sumw2();
   GetOutputList()->Add(phigj_2_15);
   phigj_2_16 = new TH1D("phigj2_16"," ",180,-180, 180);
   phigj_2_16->Sumw2();
   GetOutputList()->Add(phigj_2_16);
   phigj_2_17 = new TH1D("phigj2_17"," ",180,-180, 180);
   phigj_2_17->Sumw2();
   GetOutputList()->Add(phigj_2_17);
   phigj_2_18 = new TH1D("phigj2_18"," ",180,-180, 180);
   phigj_2_18->Sumw2();
   GetOutputList()->Add(phigj_2_18);
   phigj_2_19 = new TH1D("phigj2_19"," ",180,-180, 180);
   phigj_2_19->Sumw2();
   GetOutputList()->Add(phigj_2_19);



   phigj_3 = new TH1D("phigj3_0"," ",90,-180, 180);
   phigj_3->Sumw2();
   GetOutputList()->Add(phigj_3);
   phigj_3_1 = new TH1D("phigj3_1"," ",90,-180, 180);
   phigj_3_1->Sumw2();
   GetOutputList()->Add(phigj_3_1);
   phigj_3_2 = new TH1D("phigj3_2"," ",90,-180, 180);
   phigj_3_2->Sumw2();
   GetOutputList()->Add(phigj_3_2);
   phigj_3_3 = new TH1D("phigj3_3"," ",90,-180, 180);
   phigj_3_3->Sumw2();
   GetOutputList()->Add(phigj_3_3);
   phigj_3_4 = new TH1D("phigj3_4"," ",90,-180, 180);
   phigj_3_4->Sumw2();
   GetOutputList()->Add(phigj_3_4);
   phigj_3_5 = new TH1D("phigj3_5"," ",90,-180, 180);
   phigj_3_5->Sumw2();
   GetOutputList()->Add(phigj_3_5);
   phigj_3_6 = new TH1D("phigj3_6"," ",90,-180, 180);
   phigj_3_6->Sumw2();
   GetOutputList()->Add(phigj_3_6);
   phigj_3_7 = new TH1D("phigj3_7"," ",90,-180, 180);
   phigj_3_7->Sumw2();
   GetOutputList()->Add(phigj_3_7);
   phigj_3_8 = new TH1D("phigj3_8"," ",90,-180, 180);
   phigj_3_8->Sumw2();
   GetOutputList()->Add(phigj_3_8);
   phigj_3_9 = new TH1D("phigj3_9"," ",90,-180, 180);
   phigj_3_9->Sumw2();
   GetOutputList()->Add(phigj_3_9);
   phigj_3_10 = new TH1D("phigj3_10"," ",90,-180, 180);
   phigj_3_10->Sumw2();
   GetOutputList()->Add(phigj_3_10);
   phigj_3_11 = new TH1D("phigj3_11"," ",90,-180, 180);
   phigj_3_11->Sumw2();
   GetOutputList()->Add(phigj_3_11);
   phigj_3_12 = new TH1D("phigj3_12"," ",180,-180, 180);
   phigj_3_12->Sumw2();
   GetOutputList()->Add(phigj_3_12);
   phigj_3_13 = new TH1D("phigj3_13"," ",180,-180, 180);
   phigj_3_13->Sumw2();
   GetOutputList()->Add(phigj_3_13);
   phigj_3_14 = new TH1D("phigj3_14"," ",180,-180, 180);
   phigj_3_14->Sumw2();
   GetOutputList()->Add(phigj_3_14);
   phigj_3_15 = new TH1D("phigj3_15"," ",180,-180, 180);
   phigj_3_15->Sumw2();
   GetOutputList()->Add(phigj_3_15);
   phigj_3_16 = new TH1D("phigj3_16"," ",180,-180, 180);
   phigj_3_16->Sumw2();
   GetOutputList()->Add(phigj_3_16);
   phigj_3_17 = new TH1D("phigj3_17"," ",180,-180, 180);
   phigj_3_17->Sumw2();
   GetOutputList()->Add(phigj_3_17);
   phigj_3_18 = new TH1D("phigj3_18"," ",180,-180, 180);
   phigj_3_18->Sumw2();
   GetOutputList()->Add(phigj_3_18);
   phigj_3_19 = new TH1D("phigj3_19"," ",180,-180, 180);
   phigj_3_19->Sumw2();
   GetOutputList()->Add(phigj_3_19);




   phigj_4 = new TH1D("phigj4_0"," ",90,-180, 180);
   phigj_4->Sumw2();
   GetOutputList()->Add(phigj_4);
   phigj_4_1 = new TH1D("phigj4_1"," ",90,-180, 180);
   phigj_4_1->Sumw2();
   GetOutputList()->Add(phigj_4_1);
   phigj_4_2 = new TH1D("phigj4_2"," ",90,-180, 180);
   phigj_4_2->Sumw2();
   GetOutputList()->Add(phigj_4_2);
   phigj_4_3 = new TH1D("phigj4_3"," ",90,-180, 180);
   phigj_4_3->Sumw2();
   GetOutputList()->Add(phigj_4_3);
   phigj_4_4 = new TH1D("phigj4_4"," ",90,-180, 180);
   phigj_4_4->Sumw2();
   GetOutputList()->Add(phigj_4_4);
   phigj_4_5 = new TH1D("phigj4_5"," ",90,-180, 180);
   phigj_4_5->Sumw2();
   GetOutputList()->Add(phigj_4_5);
   phigj_4_6 = new TH1D("phigj4_6"," ",90,-180, 180);
   phigj_4_6->Sumw2();
   GetOutputList()->Add(phigj_4_6);
   phigj_4_7 = new TH1D("phigj4_7"," ",90,-180, 180);
   phigj_4_7->Sumw2();
   GetOutputList()->Add(phigj_4_7);
   phigj_4_8 = new TH1D("phigj4_8"," ",90,-180, 180);
   phigj_4_8->Sumw2();
   GetOutputList()->Add(phigj_4_8);
   phigj_4_9 = new TH1D("phigj4_9"," ",90,-180, 180);
   phigj_4_9->Sumw2();
   GetOutputList()->Add(phigj_4_9);
   phigj_4_10 = new TH1D("phigj4_10"," ",90,-180, 180);
   phigj_4_10->Sumw2();
   GetOutputList()->Add(phigj_4_10);
   phigj_4_11 = new TH1D("phigj4_11"," ",90,-180, 180);
   phigj_4_11->Sumw2();
   GetOutputList()->Add(phigj_4_11);
   phigj_4_12 = new TH1D("phigj4_12"," ",90,-180, 180);
   phigj_4_12->Sumw2();
   GetOutputList()->Add(phigj_4_12);
   phigj_4_13 = new TH1D("phigj4_13"," ",180,-180, 180);
   phigj_4_13->Sumw2();
   GetOutputList()->Add(phigj_4_13);
   phigj_4_14 = new TH1D("phigj4_14"," ",180,-180, 180);
   phigj_4_14->Sumw2();
   GetOutputList()->Add(phigj_4_14);
   phigj_4_15 = new TH1D("phigj4_15"," ",180,-180, 180);
   phigj_4_15->Sumw2();
   GetOutputList()->Add(phigj_4_15);
   phigj_4_16 = new TH1D("phigj4_16"," ",180,-180, 180);
   phigj_4_16->Sumw2();
   GetOutputList()->Add(phigj_4_16);
   phigj_4_17 = new TH1D("phigj4_17"," ",180,-180, 180);
   phigj_4_17->Sumw2();
   GetOutputList()->Add(phigj_4_17);
   phigj_4_18 = new TH1D("phigj4_18"," ",180,-180, 180);
   phigj_4_18->Sumw2();
   GetOutputList()->Add(phigj_4_18);
   phigj_4_19 = new TH1D("phigj4_19"," ",180,-180, 180);
   phigj_4_19->Sumw2();
   GetOutputList()->Add(phigj_4_19);




   t_mom1 = new TH1D("tmom1","0.0 < t< 0.08 ",100,0, 2.0);
   t_mom1->Sumw2();
   GetOutputList()->Add(t_mom1);
   t_mom2 = new TH1D("tmom2","0.08 < t 0.18 ",100,0, 2.0);
   t_mom2->Sumw2();
   GetOutputList()->Add(t_mom2);
   t_mom3 = new TH1D("tmom3","0.18 < t < 0.30 ",100,0, 2.0);
   t_mom3->Sumw2();
   GetOutputList()->Add(t_mom3);
   t_mom4 = new TH1D("tmom4","0.30 < t < 0.45",100,0, 2.0);
   t_mom4->Sumw2();
   GetOutputList()->Add(t_mom4);
   t_mom5 = new TH1D("tmom5","0.45 < t < 0.65 ",100,0, 2.0);
   t_mom5->Sumw2();
   GetOutputList()->Add(t_mom5);
   t_mom6 = new TH1D("tmom6","0.65 < t < 0.90 ",100,0, 2.0);
   t_mom6->Sumw2();
   GetOutputList()->Add(t_mom6);
   t_mom7 = new TH1D("tmom7","0.90 < t < 1.20 ",100,0, 2.0);
   t_mom7->Sumw2();
   GetOutputList()->Add(t_mom7);
   t_mom8 = new TH1D("tmom8","0.56 < t < 0.64 ",100,0, 2.0);
   t_mom8->Sumw2();
   GetOutputList()->Add(t_mom8);
   t_mom9 = new TH1D("tmom9","0.64 < t < 0.72 ",100,0, 2.0);
   t_mom9->Sumw2();
   GetOutputList()->Add(t_mom9);
   t_mom10 = new TH1D("tmom10","0.72 < t < 0.80 ",100,0, 2.0);
   t_mom10->Sumw2();
   GetOutputList()->Add(t_mom10);
   t_mom11 = new TH1D("tmom11","0.80 < t < 0.88 ",100,0, 2.0);
   t_mom11->Sumw2();
   GetOutputList()->Add(t_mom11);
   t_mom12 = new TH1D("tmom12","0.88 < t < 0.96 ",100,0, 2.0);
   t_mom12->Sumw2();
   GetOutputList()->Add(t_mom12);
   t_mom13 = new TH1D("tmom13","0.96 < t < 1.04 ",100,0, 2.0);
   t_mom13->Sumw2();
   GetOutputList()->Add(t_mom13);
   t_mom14 = new TH1D("tmom14","1.04 < t < 1.12 ",100,0, 2.0);
   t_mom14->Sumw2();
   GetOutputList()->Add(t_mom14);
   t_mom15 = new TH1D("tmom15","1.12 < t < 1.20 ",100,0, 2.0);
   t_mom15->Sumw2();
   GetOutputList()->Add(t_mom15);
   t_mom16 = new TH1D("tmom16","1.20 < t < 1.28 ",100,0, 2.0);
   t_mom16->Sumw2();
   GetOutputList()->Add(t_mom16);
   t_mom17 = new TH1D("tmom17","1.28 < t < 1.36 ",100,0, 2.0);
   t_mom17->Sumw2();
   GetOutputList()->Add(t_mom17);
   t_mom18 = new TH1D("tmom18","1.36 < t < 1.44 ",100,0, 2.0);
   t_mom18->Sumw2();
   GetOutputList()->Add(t_mom18);
   t_mom19 = new TH1D("tmom19","1.44 < t < 1.52 ",100,0, 2.0);
   t_mom19->Sumw2();
   GetOutputList()->Add(t_mom19);









   cos_hft1 = new TH1D("coshft1","0.0 < t< 0.08 ",50,-1.0, 1.0);
   cos_hft1->Sumw2();
   GetOutputList()->Add(cos_hft1);
   cos_hft2 = new TH1D("coshft2","0.08 < t 0.16 ",50,-1.0, 1.0);
   cos_hft2->Sumw2();
   GetOutputList()->Add(cos_hft2);
   cos_hft3 = new TH1D("coshft3","0.16 < t < 0.24 ",50,-1.0, 1.0);
   cos_hft3->Sumw2();
   GetOutputList()->Add(cos_hft3);
   cos_hft4 = new TH1D("coshft4","0.24 < t < 0.32",50,-1.0, 1.0);
   cos_hft4->Sumw2();
   GetOutputList()->Add(cos_hft4);
   cos_hft5 = new TH1D("coshft5","0.32 < t < 0.40 ",50,-1.0, 1.0);
   cos_hft5->Sumw2();
   GetOutputList()->Add(cos_hft5);
   cos_hft6 = new TH1D("coshft6","0.40 < t < 0.48 ",50,-1.0, 1.0);
   cos_hft6->Sumw2();
   GetOutputList()->Add(cos_hft6);
   cos_hft7 = new TH1D("coshft7","0.48 < t < 0.56 ",50,-1.0, 1.0);
   cos_hft7->Sumw2();
   GetOutputList()->Add(cos_hft7);
   cos_hft8 = new TH1D("coshft8","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos_hft8->Sumw2();
   GetOutputList()->Add(cos_hft8);
   cos_hft9 = new TH1D("coshft9","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos_hft9->Sumw2();
   GetOutputList()->Add(cos_hft9);
   cos_hft10 = new TH1D("coshft10","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos_hft10->Sumw2();
   GetOutputList()->Add(cos_hft10);
   cos_hft11 = new TH1D("coshft11","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos_hft11->Sumw2();
   GetOutputList()->Add(cos_hft11);
   cos_hft12 = new TH1D("coshft12","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos_hft12->Sumw2();
   GetOutputList()->Add(cos_hft12);
   cos_hft13 = new TH1D("coshft13","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos_hft13->Sumw2();
   GetOutputList()->Add(cos_hft13);
   cos_hft14 = new TH1D("coshft14","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos_hft14->Sumw2();
   GetOutputList()->Add(cos_hft14);
   cos_hft15 = new TH1D("coshft15","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos_hft15->Sumw2();
   GetOutputList()->Add(cos_hft15);
   cos_hft16 = new TH1D("coshft16","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos_hft16->Sumw2();
   GetOutputList()->Add(cos_hft16);
   cos_hft17 = new TH1D("coshft17","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos_hft17->Sumw2();
   GetOutputList()->Add(cos_hft17);
   cos_hft18 = new TH1D("coshft18","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos_hft18->Sumw2();
   GetOutputList()->Add(cos_hft18);
   cos_hft19 = new TH1D("coshft19","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos_hft19->Sumw2();
   GetOutputList()->Add(cos_hft19);

   cos2_hft1 = new TH1D("coshft1_2","0.0 < t< 0.08 ",50,-1.0, 1.0);
   cos2_hft1->Sumw2();
   GetOutputList()->Add(cos2_hft1);
   cos2_hft2 = new TH1D("coshft2_2","0.08 < t 0.16 ",50,-1.0, 1.0);
   cos2_hft2->Sumw2();
   GetOutputList()->Add(cos2_hft2);
   cos2_hft3 = new TH1D("coshft3_2","0.16 < t < 0.24 ",50,-1.0, 1.0);
   cos2_hft3->Sumw2();
   GetOutputList()->Add(cos2_hft3);
   cos2_hft4 = new TH1D("coshft4_2","0.24 < t < 0.32",50,-1.0, 1.0);
   cos2_hft4->Sumw2();
   GetOutputList()->Add(cos2_hft4);
   cos2_hft5 = new TH1D("coshft5_2","0.32 < t < 0.40 ",50,-1.0, 1.0);
   cos2_hft5->Sumw2();
   GetOutputList()->Add(cos2_hft5);
   cos2_hft6 = new TH1D("coshft6_2","0.40 < t < 0.48 ",50,-1.0, 1.0);
   cos2_hft6->Sumw2();
   GetOutputList()->Add(cos2_hft6);
   cos2_hft7 = new TH1D("coshft7_2","0.48 < t < 0.56 ",50,-1.0, 1.0);
   cos2_hft7->Sumw2();
   GetOutputList()->Add(cos2_hft7);
   cos2_hft8 = new TH1D("coshft8_2","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos2_hft8->Sumw2();
   GetOutputList()->Add(cos2_hft8);
   cos2_hft9 = new TH1D("coshft9_2","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos2_hft9->Sumw2();
   GetOutputList()->Add(cos2_hft9);
   cos2_hft10 = new TH1D("coshft10_2","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos2_hft10->Sumw2();
   GetOutputList()->Add(cos2_hft10);
   cos2_hft11 = new TH1D("coshft11_2","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos2_hft11->Sumw2();
   GetOutputList()->Add(cos2_hft11);
   cos2_hft12 = new TH1D("coshft12_2","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos2_hft12->Sumw2();
   GetOutputList()->Add(cos2_hft12);
   cos2_hft13 = new TH1D("coshft13_2","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos2_hft13->Sumw2();
   GetOutputList()->Add(cos2_hft13);
   cos2_hft14 = new TH1D("coshft14_2","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos2_hft14->Sumw2();
   GetOutputList()->Add(cos2_hft14);
   cos2_hft15 = new TH1D("coshft15_2","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos2_hft15->Sumw2();
   GetOutputList()->Add(cos2_hft15);
   cos2_hft16 = new TH1D("coshft16_2","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos2_hft16->Sumw2();
   GetOutputList()->Add(cos2_hft16);
   cos2_hft17 = new TH1D("coshft17_2","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos2_hft17->Sumw2();
   GetOutputList()->Add(cos2_hft17);
   cos2_hft18 = new TH1D("coshft18_2","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos2_hft18->Sumw2();
   GetOutputList()->Add(cos2_hft18);
   cos2_hft19 = new TH1D("coshft19_2","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos2_hft19->Sumw2();
   GetOutputList()->Add(cos2_hft19);


   cos_gjt1 = new TH1D("cosgjt1","0.0 < t< 0.08 ",20,-1.0, 1.0);
   cos_gjt1->Sumw2();
   GetOutputList()->Add(cos_gjt1);
   cos_gjt2 = new TH1D("cosgjt2","0.08 < t 0.16 ",20,-1.0, 1.0);
   cos_gjt2->Sumw2();
   GetOutputList()->Add(cos_gjt2);
   cos_gjt3 = new TH1D("cosgjt3","0.16 < t < 0.24 ",20,-1.0, 1.0);
   cos_gjt3->Sumw2();
   GetOutputList()->Add(cos_gjt3);
   cos_gjt4 = new TH1D("cosgjt4","0.24 < t < 0.32",20,-1.0, 1.0);
   cos_gjt4->Sumw2();
   GetOutputList()->Add(cos_gjt4);
   cos_gjt5 = new TH1D("cosgjt5","0.32 < t < 0.40 ",20,-1.0, 1.0);
   cos_gjt5->Sumw2();
   GetOutputList()->Add(cos_gjt5);
   cos_gjt6 = new TH1D("cosgjt6","0.40 < t < 0.48 ",20,-1.0, 1.0);
   cos_gjt6->Sumw2();
   GetOutputList()->Add(cos_gjt6);
   cos_gjt7 = new TH1D("cosgjt7","0.48 < t < 0.56 ",20,-1.0, 1.0);
   cos_gjt7->Sumw2();
   GetOutputList()->Add(cos_gjt7);
   cos_gjt8 = new TH1D("cosgjt8","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos_gjt8->Sumw2();
   GetOutputList()->Add(cos_gjt8);
   cos_gjt9 = new TH1D("cosgjt9","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos_gjt9->Sumw2();
   GetOutputList()->Add(cos_gjt9);
   cos_gjt10 = new TH1D("cosgjt10","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos_gjt10->Sumw2();
   GetOutputList()->Add(cos_gjt10);
   cos_gjt11 = new TH1D("cosgjt11","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos_gjt11->Sumw2();
   GetOutputList()->Add(cos_gjt11);
   cos_gjt12 = new TH1D("cosgjt12","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos_gjt12->Sumw2();
   GetOutputList()->Add(cos_gjt12);
   cos_gjt13 = new TH1D("cosgjt13","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos_gjt13->Sumw2();
   GetOutputList()->Add(cos_gjt13);
   cos_gjt14 = new TH1D("cosgjt14","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos_gjt14->Sumw2();
   GetOutputList()->Add(cos_gjt14);
   cos_gjt15 = new TH1D("cosgjt15","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos_gjt15->Sumw2();
   GetOutputList()->Add(cos_gjt15);
   cos_gjt16 = new TH1D("cosgjt16","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos_gjt16->Sumw2();
   GetOutputList()->Add(cos_gjt16);
   cos_gjt17 = new TH1D("cosgjt17","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos_gjt17->Sumw2();
   GetOutputList()->Add(cos_gjt17);
   cos_gjt18 = new TH1D("cosgjt18","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos_gjt18->Sumw2();
   GetOutputList()->Add(cos_gjt18);
   cos_gjt19 = new TH1D("cosgjt19","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos_gjt19->Sumw2();
   GetOutputList()->Add(cos_gjt19);

   cos2_gjt1 = new TH1D("cosgjt1_2","0.0 < t< 0.08 ",50,-1.0, 1.0);
   cos2_gjt1->Sumw2();
   GetOutputList()->Add(cos2_gjt1);
   cos2_gjt2 = new TH1D("cosgjt2_2","0.08 < t 0.16 ",50,-1.0, 1.0);
   cos2_gjt2->Sumw2();
   GetOutputList()->Add(cos2_gjt2);
   cos2_gjt3 = new TH1D("cosgjt3_2","0.16 < t < 0.24 ",50,-1.0, 1.0);
   cos2_gjt3->Sumw2();
   GetOutputList()->Add(cos2_gjt3);
   cos2_gjt4 = new TH1D("cosgjt4_2","0.24 < t < 0.32",50,-1.0, 1.0);
   cos2_gjt4->Sumw2();
   GetOutputList()->Add(cos2_gjt4);
   cos2_gjt5 = new TH1D("cosgjt5_2","0.32 < t < 0.40 ",50,-1.0, 1.0);
   cos2_gjt5->Sumw2();
   GetOutputList()->Add(cos2_gjt5);
   cos2_gjt6 = new TH1D("cosgjt6_2","0.40 < t < 0.48 ",50,-1.0, 1.0);
   cos2_gjt6->Sumw2();
   GetOutputList()->Add(cos2_gjt6);
   cos2_gjt7 = new TH1D("cosgjt7_2","0.48 < t < 0.56 ",50,-1.0, 1.0);
   cos2_gjt7->Sumw2();
   GetOutputList()->Add(cos2_gjt7);
   cos2_gjt8 = new TH1D("cosgjt8_2","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos2_gjt8->Sumw2();
   GetOutputList()->Add(cos2_gjt8);
   cos2_gjt9 = new TH1D("cosgjt9_2","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos2_gjt9->Sumw2();
   GetOutputList()->Add(cos2_gjt9);
   cos2_gjt10 = new TH1D("cosgjt10_2","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos2_gjt10->Sumw2();
   GetOutputList()->Add(cos2_gjt10);
   cos2_gjt11 = new TH1D("cosgjt11_2","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos2_gjt11->Sumw2();
   GetOutputList()->Add(cos2_gjt11);
   cos2_gjt12 = new TH1D("cosgjt12_2","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos2_gjt12->Sumw2();
   GetOutputList()->Add(cos2_gjt12);
   cos2_gjt13 = new TH1D("cosgjt13_2","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos2_gjt13->Sumw2();
   GetOutputList()->Add(cos2_gjt13);
   cos2_gjt14 = new TH1D("cosgjt14_2","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos2_gjt14->Sumw2();
   GetOutputList()->Add(cos2_gjt14);
   cos2_gjt15 = new TH1D("cosgjt15_2","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos2_gjt15->Sumw2();
   GetOutputList()->Add(cos2_gjt15);
   cos2_gjt16 = new TH1D("cosgjt16_2","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos2_gjt16->Sumw2();
   GetOutputList()->Add(cos2_gjt16);
   cos2_gjt17 = new TH1D("cosgjt17_2","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos2_gjt17->Sumw2();
   GetOutputList()->Add(cos2_gjt17);
   cos2_gjt18 = new TH1D("cosgjt18_2","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos2_gjt18->Sumw2();
   GetOutputList()->Add(cos2_gjt18);
   cos2_gjt19 = new TH1D("cosgjt19_2","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos2_gjt19->Sumw2();
   GetOutputList()->Add(cos2_gjt19);
   cos2_gjt20 = new TH1D("cosgjt20_2","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos2_gjt20->Sumw2();
   GetOutputList()->Add(cos2_gjt20);



   cos3_gjt1 = new TH1D("cosgjt1_3","0.0 < t< 0.08 ",50,-1.0, 1.0);
   cos3_gjt1->Sumw2();
   GetOutputList()->Add(cos3_gjt1);
   cos3_gjt2 = new TH1D("cosgjt2_3","0.08 < t 0.16 ",50,-1.0, 1.0);
   cos3_gjt2->Sumw2();
   GetOutputList()->Add(cos3_gjt2);
   cos3_gjt3 = new TH1D("cosgjt3_3","0.16 < t < 0.24 ",50,-1.0, 1.0);
   cos3_gjt3->Sumw2();
   GetOutputList()->Add(cos3_gjt3);
   cos3_gjt4 = new TH1D("cosgjt4_3","0.24 < t < 0.32",50,-1.0, 1.0);
   cos3_gjt4->Sumw2();
   GetOutputList()->Add(cos3_gjt4);
   cos3_gjt5 = new TH1D("cosgjt5_3","0.32 < t < 0.40 ",50,-1.0, 1.0);
   cos3_gjt5->Sumw2();
   GetOutputList()->Add(cos3_gjt5);
   cos3_gjt6 = new TH1D("cosgjt6_3","0.40 < t < 0.48 ",50,-1.0, 1.0);
   cos3_gjt6->Sumw2();
   GetOutputList()->Add(cos3_gjt6);
   cos3_gjt7 = new TH1D("cosgjt7_3","0.48 < t < 0.56 ",50,-1.0, 1.0);
   cos3_gjt7->Sumw2();
   GetOutputList()->Add(cos3_gjt7);
   cos3_gjt8 = new TH1D("cosgjt8_3","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos3_gjt8->Sumw2();
   GetOutputList()->Add(cos3_gjt8);
   cos3_gjt9 = new TH1D("cosgjt9_3","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos3_gjt9->Sumw2();
   GetOutputList()->Add(cos3_gjt9);
   cos3_gjt10 = new TH1D("cosgjt10_3","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos3_gjt10->Sumw2();
   GetOutputList()->Add(cos3_gjt10);
   cos3_gjt11 = new TH1D("cosgjt11_3","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos3_gjt11->Sumw2();
   GetOutputList()->Add(cos3_gjt11);
   cos3_gjt12 = new TH1D("cosgjt12_3","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos3_gjt12->Sumw2();
   GetOutputList()->Add(cos3_gjt12);
   cos3_gjt13 = new TH1D("cosgjt13_3","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos3_gjt13->Sumw2();
   GetOutputList()->Add(cos3_gjt13);
   cos3_gjt14 = new TH1D("cosgjt14_3","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos3_gjt14->Sumw2();
   GetOutputList()->Add(cos3_gjt14);
   cos3_gjt15 = new TH1D("cosgjt15_3","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos3_gjt15->Sumw2();
   GetOutputList()->Add(cos3_gjt15);
   cos3_gjt16 = new TH1D("cosgjt16_3","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos3_gjt16->Sumw2();
   GetOutputList()->Add(cos3_gjt16);
   cos3_gjt17 = new TH1D("cosgjt17_3","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos3_gjt17->Sumw2();
   GetOutputList()->Add(cos3_gjt17);
   cos3_gjt18 = new TH1D("cosgjt18_3","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos3_gjt18->Sumw2();
   GetOutputList()->Add(cos3_gjt18);
   cos3_gjt19 = new TH1D("cosgjt19_3","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos3_gjt19->Sumw2();
   GetOutputList()->Add(cos3_gjt19);
  



   cos4_gjt1 = new TH1D("cosgjt1_4","0.0 < t< 0.08 ",50,-1.0, 1.0);
   cos4_gjt1->Sumw2();
   GetOutputList()->Add(cos4_gjt1);
   cos4_gjt2 = new TH1D("cosgjt2_4","0.08 < t 0.16 ",50,-1.0, 1.0);
   cos4_gjt2->Sumw2();
   GetOutputList()->Add(cos4_gjt2);
   cos4_gjt3 = new TH1D("cosgjt3_4","0.16 < t < 0.24 ",50,-1.0, 1.0);
   cos4_gjt3->Sumw2();
   GetOutputList()->Add(cos4_gjt3);
   cos4_gjt4 = new TH1D("cosgjt4_4","0.24 < t < 0.32",50,-1.0, 1.0);
   cos4_gjt4->Sumw2();
   GetOutputList()->Add(cos4_gjt4);
   cos4_gjt5 = new TH1D("cosgjt5_4","0.32 < t < 0.40 ",50,-1.0, 1.0);
   cos4_gjt5->Sumw2();
   GetOutputList()->Add(cos4_gjt5);
   cos4_gjt6 = new TH1D("cosgjt6_4","0.40 < t < 0.48 ",50,-1.0, 1.0);
   cos4_gjt6->Sumw2();
   GetOutputList()->Add(cos4_gjt6);
   cos4_gjt7 = new TH1D("cosgjt7_4","0.48 < t < 0.56 ",50,-1.0, 1.0);
   cos4_gjt7->Sumw2();
   GetOutputList()->Add(cos4_gjt7);
   cos4_gjt8 = new TH1D("cosgjt8_4","0.56 < t < 0.64 ",50,-1.0, 1.0);
   cos4_gjt8->Sumw2();
   GetOutputList()->Add(cos4_gjt8);
   cos4_gjt9 = new TH1D("cosgjt9_4","0.64 < t < 0.72 ",50,-1.0, 1.0);
   cos4_gjt9->Sumw2();
   GetOutputList()->Add(cos4_gjt9);
   cos4_gjt10 = new TH1D("cosgjt10_4","0.72 < t < 0.80 ",50,-1.0, 1.0);
   cos4_gjt10->Sumw2();
   GetOutputList()->Add(cos4_gjt10);
   cos4_gjt11 = new TH1D("cosgjt11_4","0.80 < t < 0.88 ",50,-1.0, 1.0);
   cos4_gjt11->Sumw2();
   GetOutputList()->Add(cos4_gjt11);
   cos4_gjt12 = new TH1D("cosgjt12_4","0.88 < t < 0.96 ",50,-1.0, 1.0);
   cos4_gjt12->Sumw2();
   GetOutputList()->Add(cos4_gjt12);
   cos4_gjt13 = new TH1D("cosgjt13_4","0.96 < t < 1.04 ",50,-1.0, 1.0);
   cos4_gjt13->Sumw2();
   GetOutputList()->Add(cos4_gjt13);
   cos4_gjt14 = new TH1D("cosgjt14_4","1.04 < t < 1.12 ",50,-1.0, 1.0);
   cos4_gjt14->Sumw2();
   GetOutputList()->Add(cos4_gjt14);
   cos4_gjt15 = new TH1D("cosgjt15_4","1.12 < t < 1.20 ",50,-1.0, 1.0);
   cos4_gjt15->Sumw2();
   GetOutputList()->Add(cos4_gjt15);
   cos4_gjt16 = new TH1D("cosgjt16_4","1.20 < t < 1.28 ",50,-1.0, 1.0);
   cos4_gjt16->Sumw2();
   GetOutputList()->Add(cos4_gjt16);
   cos4_gjt17 = new TH1D("cosgjt17_4","1.28 < t < 1.36 ",50,-1.0, 1.0);
   cos4_gjt17->Sumw2();
   GetOutputList()->Add(cos4_gjt17);
   cos4_gjt18 = new TH1D("cosgjt18_4","1.36 < t < 1.44 ",50,-1.0, 1.0);
   cos4_gjt18->Sumw2();
   GetOutputList()->Add(cos4_gjt18);
   cos4_gjt19 = new TH1D("cosgjt19_4","1.44 < t < 1.52 ",50,-1.0, 1.0);
   cos4_gjt19->Sumw2();
   GetOutputList()->Add(cos4_gjt19);
 

   alph_ang = new TH1D("alph"," ",100,0, 180);
   GetOutputList()->Add(alph_ang);
   alph_ang2 = new TH1D("alph2"," ",100,0, 180);
   GetOutputList()->Add(alph_ang2);

   energy_1d = new TH1D("energy"," ",25,4.4, 5.6);
   GetOutputList()->Add(energy_1d);
   delphi_1d = new TH1D("delphi"," ",180,-180, 180);
   delphi_1d->Sumw2();
   GetOutputList()->Add(delphi_1d);
   delphi1_1d = new TH1D("delphi1"," ",180,-180, 180);
   delphi1_1d->Sumw2();
   GetOutputList()->Add(delphi1_1d);
   delphi2_1d = new TH1D("delphi2"," ",180,-180, 180);
   delphi2_1d->Sumw2();
   GetOutputList()->Add(delphi2_1d);
   delphi3_1d = new TH1D("delphi3"," ", 180,-180, 180);
   delphi3_1d->Sumw2();
   GetOutputList()->Add(delphi3_1d);
   delphi4_1d = new TH1D("delphi4"," ", 180,-180, 180);
   delphi4_1d->Sumw2();
   GetOutputList()->Add(delphi4_1d);
   delphi5_1d = new TH1D("delphi5"," ", 180,-180, 180);
   delphi5_1d->Sumw2();
   GetOutputList()->Add(delphi5_1d);
   delphi6_1d = new TH1D("delphi6"," ", 180,-180, 180);
   delphi6_1d->Sumw2();
   GetOutputList()->Add(delphi6_1d);
   delphi7_1d = new TH1D("delphi7"," ", 180,-180, 180);
   delphi7_1d->Sumw2();
   GetOutputList()->Add(delphi7_1d);
   delphi8_1d = new TH1D("delphi8"," ", 180,-180, 180);
   delphi8_1d->Sumw2();
   GetOutputList()->Add(delphi8_1d);
   delphi9_1d = new TH1D("delphi9"," ", 180,-180, 180);
   delphi9_1d->Sumw2();
   GetOutputList()->Add(delphi9_1d);
   delphi10_1d = new TH1D("delphi10"," ", 180,-180, 180);
   delphi10_1d->Sumw2();
   GetOutputList()->Add(delphi10_1d);
   delphi11_1d = new TH1D("delphi11"," ", 180,-180, 180);
   delphi11_1d->Sumw2();
   GetOutputList()->Add(delphi11_1d);
   delphi12_1d = new TH1D("delphi12"," ", 180,-180, 180);
   delphi12_1d->Sumw2();
   GetOutputList()->Add(delphi12_1d);
   delphi13_1d = new TH1D("delphi13"," ", 180,-180, 180);
   delphi13_1d->Sumw2();
   GetOutputList()->Add(delphi13_1d);
   delphi14_1d = new TH1D("delphi14"," ", 180,-180, 180);
   delphi14_1d->Sumw2();
   GetOutputList()->Add(delphi14_1d);
   delphi15_1d = new TH1D("delphi15"," ", 180,-180, 180);
   delphi15_1d->Sumw2();
   GetOutputList()->Add(delphi15_1d);
   delphi16_1d = new TH1D("delphi16"," ", 180,-180, 180);
   delphi16_1d->Sumw2();
   GetOutputList()->Add(delphi16_1d);
   delphi17_1d = new TH1D("delphi17"," ", 180,-180, 180);
   delphi17_1d->Sumw2();
   GetOutputList()->Add(delphi17_1d);
   delphi18_1d = new TH1D("delphi18"," ", 180,-180, 180);
   delphi18_1d->Sumw2();
   GetOutputList()->Add(delphi18_1d);
   delphi19_1d = new TH1D("delphi19"," ", 180,-180, 180);
   delphi19_1d->Sumw2();
   GetOutputList()->Add(delphi19_1d);
   delphi20_1d = new TH1D("delphi20"," ", 180,-180, 180);
   delphi20_1d->Sumw2();
   GetOutputList()->Add(delphi20_1d);
   delphi21_1d = new TH1D("delphi21"," ", 180,-180, 180);
   delphi21_1d->Sumw2();
   GetOutputList()->Add(delphi21_1d);
   delphi22_1d = new TH1D("delphi22"," ", 180,-180, 180);
   delphi22_1d->Sumw2();
   GetOutputList()->Add(delphi22_1d);
   delphi23_1d = new TH1D("delphi23"," ", 180,-180, 180);
   delphi23_1d->Sumw2();
   GetOutputList()->Add(delphi23_1d);
   delphi24_1d = new TH1D("delphi24"," ", 180,-180, 180);
   delphi24_1d->Sumw2();
   GetOutputList()->Add(delphi24_1d);
   delphi25_1d = new TH1D("delphi25"," ", 180,-180, 180);
   delphi25_1d->Sumw2();
   GetOutputList()->Add(delphi25_1d);
   delphi26_1d = new TH1D("delphi26"," ", 180,-180, 180);
   delphi26_1d->Sumw2();
   GetOutputList()->Add(delphi26_1d);
   delphi27_1d = new TH1D("delphi27"," ", 180,-180, 180);
   delphi27_1d->Sumw2();
   GetOutputList()->Add(delphi27_1d);
   delphi28_1d = new TH1D("delphi28"," ", 180,-180, 180);
   delphi28_1d->Sumw2();
   GetOutputList()->Add(delphi28_1d);
   delphi29_1d = new TH1D("delphi29"," ", 180,-180, 180);
   delphi29_1d->Sumw2();
   GetOutputList()->Add(delphi29_1d);
   delphi30_1d = new TH1D("delphi30"," ", 180,-180, 180);
   delphi30_1d->Sumw2();
   GetOutputList()->Add(delphi30_1d);
   delphi31_1d = new TH1D("delphi31"," ", 180,-180, 180);
   delphi31_1d->Sumw2();
   GetOutputList()->Add(delphi31_1d);
   delphi32_1d = new TH1D("delphi32"," ", 180,-180, 180);
   delphi32_1d->Sumw2();
   GetOutputList()->Add(delphi32_1d);
   delphi33_1d = new TH1D("delphi33"," ", 180,-180, 180);
   delphi33_1d->Sumw2();
   GetOutputList()->Add(delphi33_1d);
   delphi34_1d = new TH1D("delphi34"," ", 180,-180, 180);
   delphi34_1d->Sumw2();
   GetOutputList()->Add(delphi34_1d);
   delphi35_1d = new TH1D("delphi35"," ", 180,-180, 180);
   delphi35_1d->Sumw2();
   GetOutputList()->Add(delphi35_1d);
   delphi36_1d = new TH1D("delphi36"," ", 180,-180, 180);
   delphi36_1d->Sumw2();
   GetOutputList()->Add(delphi36_1d);
   delphi37_1d = new TH1D("delphi37"," ", 180,-180, 180);
   delphi37_1d->Sumw2();
   GetOutputList()->Add(delphi37_1d);
   delphi38_1d = new TH1D("delphi38"," ", 180,-180, 180);
   delphi38_1d->Sumw2();
   GetOutputList()->Add(delphi38_1d);
   tagger_1d = new TH1D("tagger"," ", 100,-5.0, 5.0);
   GetOutputList()->Add(tagger_1d);
   bgvE_1d = new TH1D("Ebgvup","BGV Energy spectrum ", 100, 0, 5.0);
   GetOutputList()->Add(bgvE_1d);
   
   ome_azimuth = new TH1D("azimuthal","",180,-180,180);
   GetOutputList()->Add(ome_azimuth);
   ome_azimuth2 = new TH1D("azimuthal2","",180,-180,180);
   GetOutputList()->Add(ome_azimuth2);
   outofplane = new TH1D("out_plane","",150,-1.5,1.5);
   GetOutputList()->Add(outofplane);
   outofplane1 = new TH1D("out_plane1","",150,-1.5,1.5);
   GetOutputList()->Add(outofplane1);
  for (int tag =0; tag < 6; ++tag){
       name.Form("missing_mass4_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       mismass4_1d[tag] = new TH1D(name,title,50, 0.0,2.0);
       mismass4_1d[tag]->Sumw2();
       GetOutputList()->Add(mismass4_1d[tag]);
       name.Form("energy_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       coener_1d[tag] = new TH1D(name,title,19, 4.2,5.6);
       coener_1d[tag]->Sumw2();
       GetOutputList()->Add(coener_1d[tag]);
  }
  for (int tag =0; tag < 4; ++tag){
       name.Form("delphi_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       E_delphi[tag] = new TH1D(name,title,100, 0.00,1.50);
       E_delphi[tag]->Sumw2();
       GetOutputList()->Add(E_delphi[tag]);
     }
  for (int tag =0; tag < 20; ++tag){
       name.Form("missing_mass_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       mismass_1d[tag] = new TH1D(name,title,75, 0.0,1.5);
       mismass_1d[tag]->Sumw2();
       GetOutputList()->Add(mismass_1d[tag]);
       name.Form("mass2_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       mismass2_1d[tag] = new TH1D(name,title,75, 0,1.5);
       mismass2_1d[tag]->Sumw2();
       GetOutputList()->Add(mismass2_1d[tag]);
       name.Form("missing_mass3_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       mismass3_1d[tag] = new TH1D(name,title,19, 4.2,5.6);
       mismass3_1d[tag]->Sumw2();
       GetOutputList()->Add(mismass3_1d[tag]);
       name.Form("momentum_transfer_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       momtrans[tag] = new TH1D(name,title,150, 0,2.0);
       momtrans[tag]->Sumw2();
       GetOutputList()->Add(momtrans[tag]);
       name.Form("momentum_transfer2_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       momtrans2[tag] = new TH1D(name,title,150, 0,2.0);
       momtrans2[tag]->Sumw2();
       GetOutputList()->Add(momtrans2[tag]);
       name.Form("momentum_transfer3_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       momtrans3[tag] = new TH1D(name,title,150, 0,2.0);
       momtrans3[tag]->Sumw2();
       GetOutputList()->Add(momtrans3[tag]);
       name.Form("momentum_transfer4_%d",tag);
       title.Form("tagger energy counter %d ",tag);
       momtrans4[tag] = new TH1D(name,title,150, 0,2.0);
       momtrans4[tag]->Sumw2();
       GetOutputList()->Add(momtrans4[tag]);
       name.Form("ener_frwd_%d",tag);
       title.Form("tagger counter_ %d",tag);
       ener_1d[tag] = new TH1D(name,title,100, 0,10.0);
       GetOutputList()->Add(ener_1d[tag]);
       name.Form("ener2_frwd_%d",tag);
       title.Form("tagger counter_ %d",tag);
       ener2_1d[tag] = new TH1D(name,title,100, 0,10.0);
       GetOutputList()->Add(ener2_1d[tag]);
       name.Form("ener3_frwd_%d",tag);
       title.Form("tagger counter_ %d",tag);
       ener3_1d[tag] = new TH1D(name,title,100, 0,10.0);
       GetOutputList()->Add(ener3_1d[tag]);
      }
}

Bool_t omega::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either omega::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   GetEntry(entry);
   if (nrec !=1){
       return kFALSE;
   }     
   if (nfrwd !=3) {
       return kFALSE;
   }     
   double wgt = 0; 
   int  channels1; 
   int  channels2; 
   int  channels3; 
   int  channels4;
   double ewgt1 =0; 
   double ewgt2 =0; 
   double ewgt3 =0; 
   double ewgt4 =0; 
   double wgt_1[20] ; 
   double cwgt[4] ; 
   int chans[4] = {0,0,0,0}; 
   int len = ARRAY_SIZE(tagweight);
#if RTJ
BUG: some of these variables/arrays look to be redundant, please prune them
wgt = the tagger weight summed over all 19 channels
ewgt1..4 = the tagger weight summed over quarters of the tagger energy range
#endif
   for (int h_tag = 0; h_tag < ncoin; ++h_tag) {
       wgt += tagweight[h_tag];
   }
      for ( int j = 0; j < ncoin ; ++j){
         if(coenergy[j] > 4.39 && coenergy[j] < 4.60){
           ewgt1 += tagweight[j];
         }
         if(coenergy[j] > 4.60 && coenergy[j] < 4.90){
           ewgt2 += tagweight[j];
         }
         if(coenergy[j] > 4.90 && coenergy[j] < 5.15){
           ewgt3 += tagweight[j];
         }
         if(coenergy[j] > 5.15 && coenergy[j] < 5.40){
           ewgt4 += tagweight[j];
         }
      }
 
#if RTJ
Emin = energy of the least-energy reconstructed photon among the first 3
       photons in the event;
BUG: where does the count of 3 come from? should stop at nphot. Possible
     answer is that this sample is assumed to be nphot=3,4 and the fourth
     photon (ordered from largest to smallest energy) is ignored if present.
#endif
   double Emin=100;
   double E=0;
   for (int m=0; m < 3; ++m) {
       E = pvect[m][0];
       if (E < Emin) {
          Emin=E;
       }
   }
   int neut_bgv = 0;
   int wgt_cpv2 = 0;
   if (trec0 != 0) {
       double t_bgvdwn_rec=0;
       double t_bgvup_rec=0;
       for (int hbgv =0; hbgv < nhbgv; ++hbgv) {
           for (int tubgv =0; tubgv < ntbgvup[hbgv]; ++tubgv) {
               for (int tdbgv =0; tdbgv < ntbgvdwn[hbgv]; ++tdbgv) {
                   t_bgvup_rec = trec0 -le[t1bgvup[hbgv]+tubgv];
                   t_bgvdwn_rec = trec0 - le[t1bgvdwn[hbgv]+tdbgv] ;
                   if (((t_bgvup_rec > -10. && t_bgvup_rec < +10.) &&
                       (t_bgvdwn_rec > -10. && t_bgvdwn_rec < +10.)) &&
                       (Ebgvup[hbgv] > 0 && Ebgvdwn[hbgv] > 0))
                   {
                       ++neut_bgv;
		       int S1=0;
		       int S2=0; 
#if RTJ
neut_bgv = count of bgv hits with both upstream and downstream energy
           and time values, that does not align with a bsd pixel in phi.
BUG: multiple pixels could align with one bgv counter, leading to a
     value for neut_bgv that is smaller than intended, or even negative.
IMPROVEMENT: implement this as 2 loops, not nested
#endif
                       for (int hbsd =0; hbsd < npix; ++hbsd) {
                           S1=(spix[hbsd]-22)%24;
                           S2=(spix[hbsd]-23)%24;
                           if ((chbgv[hbgv] == S1) || (chbgv[hbgv] == S2)) {
                               --neut_bgv;
                           } 
                       }  
                   }
               }   
           }   
       }
   
       for (int hcpv = 0; hcpv < nhcpv; ++hcpv) {
           for (int hc_iter = 0; hc_iter < ntcpv[hcpv]; ++hc_iter) {
               double t_cpv = 0;
               double dtc_tag = 0;
               double dt_tag2 = 0;
               double dt_cpv_rec = 0;
               t_cpv = le[hc_iter+t1cpv[hcpv]];
               dt_cpv_rec = t_cpv -trec0;
               if ((dt_cpv_rec > -3.) && (dt_cpv_rec < 3.)) {
                   ++wgt_cpv2;
               }
           }
       }
   }
#if RTJ
wgt_cpv2 = number of cpv hits within the [-3,3]ns window.
BUG: not sure why this is called a "wgt" because it is not a weight
     for anything, cpv multiplicity labels the event type, not its weight.
     However, it does not seem to be used anywhere!
#endif
           
   double P[4]={0,0,0,0};
   double p_1 =0;
   double p_2 =0;
   double p_3 =0;
   double e_w =0;
   double missing_mass,del_mom=0,mass=0,ome_phi=0,t=0,del_ener=0,rec_mass=0;
   double ew_lab=0,pw1_lab=0,pw2_lab=0,pw3_lab=0;
   double ew_rf=0, pw1_rf=0,pw2_rf=0, pw3_rf=0;
#if RTJ
see comment above under Emin, regarding fixed sum 0..3
BUG: these variables are redundant -- why so many (3) that are the same?
#endif
   for (int m =0; m < 3 ; ++m) {
       P[0] += pvect[m][0];
       P[1] += pvect[m][1];
       P[2] += pvect[m][2];
       P[3] += pvect[m][3];
 
       e_w += pvect[m][0];
       p_1 += pvect[m][1];
       p_2 += pvect[m][2];
       p_3 += pvect[m][3]; 
   }
#if RTJ
BUG: set to zero, then overwrite? this code looks faulty
#endif
   double E_l =0;
   double Px_l =0;
   double Py_l =0;
   double Pz_l =0;
   E_l = P[0];
   Px_l = P[1];
   Py_l = P[2];
   Pz_l = P[3];
 
   mass = sqrt(sqr(e_w)-sqr(p_1)-sqr(p_2)-sqr(p_3));
   TLorentzVector prot_lab;
   TLorentzVector recprot_lab;
   TLorentzVector w_lab(0,0,0,0);
   TLorentzVector Pi_lab;
   TLorentzVector Pi_lab2;
   TLorentzVector gamma_lab;
   TLorentzVector B_lab;

   //calculate delta phi and pty 
#if RTJ
BUG: this loop overwrites these variables -- why loop? 
#endif
   double pTy=0,costheta=0,pt=0,rec_phi=0,phi_rec=0,del_phi=0;
   for (int b=0;b <nrec; ++b){
       phi_rec = (phirec[b])*180/PI; 
       rec_phi = constrain_angle(phi_rec);
       pTy = -(sin(phirec[b])*P[1])+cos(phirec[b])*P[2];
   }
   pt = sqrt(sqr(P[1]) + sqr(P[2]));

   //recoil proton  and incident beam
   double pi_lab[4]={0,0,0,0};
   double rcprot[4]={0,0,0,0};
   double s  = 0;
   double be_lab=0,be_rf=0;

   double recprot_1 = 0;
   double recprot_2 = 0;
   double recprot_3 = 0;
   double recprot_4 =0;
   double t_region1 =0;
   double t_region2 =0;
   double t_region3 =0;
   double t_sideb =0;
   double t_new1 =0;
   double n_energy[6] ;
   int n_channel[6] ;
   //boost to cm fr/ame 

  // calculate  missing mass, and t //
   for (int h_tag = 0; h_tag < ncoin; ++h_tag){
       recprot_1 = coenergy[h_tag] + 0.938 - P[0];  
       recprot_2 = 0 - P[1];
       recprot_3 = 0- P[2];
       recprot_4 = coenergy[h_tag] - P[3];
       B_lab.SetPxPyPzE(0,0,coenergy[h_tag],coenergy[h_tag]);
       del_ener = coenergy[h_tag] - P[0];
#if RTJ
BUG: you overwrite this, and keep only the last tag. why loop?
     In actual fact, it may be that the difference in t from one end of the
     tagger to the other might be negligible, should be checked.
BUG: why compute the same formula twice?
IMPROVEMENT: everything below including thetaGJ and thetaHel, phiGJ, phiHel, etc
     depends on what you take for the beam photon energy, so you need to repeat
     everything below again for each tagcoin, keeping that tag's weight for that
     row of your pwa_tree.
#endif
       t = -(sqr(mass)-2*(coenergy[h_tag]*(P[0]- P[3])));
       pwa_ntuple.tabs = -(sqr(mass)-2*(coenergy[h_tag]*(P[0]- P[3])));
       pwa_ntuple.Ebeam = coenergy[h_tag];
   }
   double stsbnd = 1.021;
#if RTJ
BUG: t_sideb starts out as 0 and remains 0 forever, and this t_new1 = t
     neither of which ever get used!
#endif
   t_sideb  = t_sideb *stsbnd;
   t_new1 = t - t_sideb;
   prot_lab.SetPxPyPzE(0,0,0,0.938);
   w_lab.SetPxPyPzE(Px_l,Py_l,Pz_l,E_l);
   recprot_lab.SetPxPyPzE(recprot_2,recprot_3,recprot_4,recprot_1);
   // calculate mOmega,mrecoilproton,phi_omega.

   missing_mass = (B_lab + prot_lab - w_lab).M();
   ome_phi = w_lab.Phi()*180/PI;
   del_phi = angle_diff(ome_phi,rec_phi);

    //calculate mandelstam variables s,t
   s = sqrt(sqr((B_lab + prot_lab)));

 

   //pion 

   TLorentzVector  photon_1;
   TLorentzVector  photon_2;
   TLorentzVector  photon_3;
   double mass_12=0;
   double mass_13=0;
   double pmass=0;
   double photon1[4] = {0,0,0,0};
   double photon2[4] = {0,0,0,0};
   double photon3[4] = {0,0,0,0};
#if RTJ
BUG: this looks like throw-away code, pmass is overwritten, never used
#endif
   for (int i =0; i < 2; ++i){
      for (int j = i+1;j < 3; ++j){
           pmass = sqrt(sqr((pvect[i][0]+pvect[j][0]))-sqr((pvect[i][1]+pvect[j][1]))-
                        sqr((pvect[i][2]+pvect[j][2]))-sqr((pvect[i][3]+pvect[j][3])));
      }
   }
   photon1[0] = pvect[0][0];
   photon1[1] = pvect[0][1];
   photon1[2] = pvect[0][2];
   photon1[3] = pvect[0][3];
   photon_1.SetPxPyPzE(photon1[1],photon1[2],photon1[3],photon1[0]);
   photon2[0] = pvect[1][0];
   photon2[1] = pvect[1][1];
   photon2[2] = pvect[1][2];
   photon2[3] = pvect[1][3];
   photon_2.SetPxPyPzE(photon2[1],photon2[2],photon2[3],photon2[0]);
   photon3[0] = pvect[2][0];
   photon3[1] = pvect[2][1];
   photon3[2] = pvect[2][2];
   photon3[3] = pvect[2][3];
   photon_3.SetPxPyPzE(photon3[1],photon3[2],photon3[3],photon3[0]);
   
   TLorentzVector  Pi1;
   TLorentzVector  Pi2;
   TLorentzVector  Pi3;
   TLorentzVector  P123;
   Pi1 =  photon_1 + photon_2; 
   Pi2 =  photon_1 + photon_3; 
   Pi3 =  photon_2 + photon_3;
   P123 =  photon_1 + photon_2 + photon_3;
   if ( Pi1.M() < Pi2.M() && Pi1.M() < Pi3.M()){
       Pi_lab = Pi1;
       Pi_lab2 = Pi1;
       gamma_lab = photon_3;
   } 
   if ( Pi2.M() < Pi1.M() && Pi2.M() < Pi3.M()){
       Pi_lab = Pi2;
       Pi_lab2 = Pi2;
       gamma_lab = photon_2;
   } 
   if ( Pi3.M() < Pi1.M() && Pi3.M() < Pi2.M()){
       Pi_lab = Pi3;
       Pi_lab2 = Pi3;
       gamma_lab = photon_1;
   } 
  
#if RTJ
BUG: you already called this P123, code is confused
#endif
   mass_13 = (Pi_lab+gamma_lab).M();
   // Boosting to center of mass frame 
   TVector3 cmboost;
   double bcm = 0 ;
   bcm = B_lab.E()/(B_lab.E() + prot_lab.M()); 
   cmboost.SetXYZ(0,0,bcm);

#if RTJ
BUG: these names are no longer valid, once you boost them into the cm.
     This makes the code confusing: when is w_lab not a lab momentum??
#endif
   B_lab.Boost(-cmboost);
   recprot_lab.Boost(-cmboost);
   prot_lab.Boost(-cmboost);
   w_lab.Boost(-cmboost);
   gamma_lab.Boost(-cmboost);
   Pi_lab.Boost(-cmboost);
  
   
   TLorentzVector recprot_cm;
   TLorentzVector B_cm;
   TLorentzVector prot_cm;
   TLorentzVector w_cm;
   TLorentzVector Pi_cm;
   TLorentzVector gamma_cm;

   prot_cm = prot_lab;
   B_cm = B_lab;
   recprot_cm = recprot_lab;
   w_cm = w_lab;
   Pi_cm = Pi_lab;
   gamma_cm = gamma_lab;

   double t_min =0;
   double t_new  =0;
   double w_theta =0;
   double w_theta_2 =0;
   TVector3 p1;
   TVector3 p2;
   p1.SetXYZ(B_cm.Px(),B_cm.Py(),B_cm.Pz());
   p2.SetXYZ(w_cm.Px(),w_cm.Py(),w_cm.Pz());
   w_theta = p1.Angle(p2);
   w_theta_2 = w_theta/2;
#if RTJ
BUG: This formula does not yield tmin, but this is unused code.
     The code for t_new yields -t = |t| but never used either.
#endif
   t_min = (sqr(B_cm.E() + w_cm.E()) - sqr(p1-p2));
   t_new = -(sqr(B_cm.E()-w_cm.E())-sqr(p1-p2));
   // opening angle between pion and bachelor photon in cm frame    
   TVector3 pion;
   TVector3 b_gamma;
   double open_angle =0;
   pion.SetXYZ(Pi_cm.Px(),Pi_cm.Py(),Pi_cm.Pz());
   b_gamma.SetXYZ(gamma_cm.Px(),gamma_cm.Py(),gamma_cm.Pz());
   open_angle = (pion.Angle(b_gamma))*180/PI;
   double p_ome_cm = 0;
   p_ome_cm = sqrt(sqr(w_cm.Px()) +sqr(w_cm.Py()) +sqr(w_cm.Pz()));
   double open_a =0;
   open_a = acos((sqr(mass)-sqr(Pi_cm.M())-2*Pi_cm.E()*gamma_cm.E())/(2*pion.Mag()*b_gamma.Mag()))*180/PI;
#if RTJ
there is so much throw-away code in here, it is difficult to follow
#endif
 
   double thetacm = 0;
   double phicm = 0;

   thetacm = w_cm.Theta();
   phicm = w_cm.Phi();

 /*rotate  about the z axis by phicm*/
   Pi_cm.RotateZ(-phicm);
   w_cm.RotateZ(-phicm);
   prot_cm.RotateZ(-phicm);
   recprot_cm.RotateZ(-phicm);
   B_cm.RotateZ(-phicm);
   gamma_cm.RotateZ(-phicm);
  /* rotate about the y axis by the polar angle */

   B_cm.RotateY(-thetacm);
   recprot_cm.RotateY(-thetacm);
   Pi_cm.RotateY(-thetacm);
   w_cm.RotateY(-thetacm);
   prot_cm.RotateY(-thetacm);
   gamma_cm.RotateY(-thetacm);
  
   TLorentzVector B_rf;
   TLorentzVector prot_rf;
   TLorentzVector recprot_rf;
   TLorentzVector w_rf;
   TLorentzVector Pi_rf;
   TLorentzVector gamma_rf;

   B_rf = B_cm;
   prot_rf = prot_cm;
   recprot_rf = recprot_cm;
   w_rf  = w_cm;
   gamma_rf = gamma_cm;
   Pi_rf = Pi_cm;

   
   /*Now boost to omega rest frame*/ 

   double w_rest = w_rf.Pz()/w_rf.E();

   TVector3 rfboost;
   rfboost.SetXYZ(0,0,w_rest);

   Pi_rf.Boost(-rfboost);
   w_rf.Boost(-rfboost);
   prot_rf.Boost(-rfboost);
   recprot_rf.Boost(-rfboost);
   B_rf.Boost(-rfboost);
   gamma_rf.Boost(-rfboost);

   TLorentzVector B_hf;
   TLorentzVector prot_hf;
   TLorentzVector recprot_hf;
   TLorentzVector w_hf;
   TLorentzVector Pi_hf;
   TLorentzVector gamma_hf;

   B_hf = B_rf;
   prot_hf = prot_rf;
   recprot_hf = recprot_rf;
   Pi_hf = Pi_rf;
   w_hf = w_rf;
   gamma_hf = gamma_rf;

   // we are now in helicity frame, calculate costheta and phi

   pwa_ntuple.helcosthe = Pi_hf.CosTheta();
   pwa_ntuple.helphi = (Pi_hf.Phi());
   pwa_ntuple.helthe = (Pi_hf.Theta());
   double hfcos = 0 ;
   hfcos = Pi_hf.CosTheta();

   double hfphi; 
   hfphi = (Pi_hf.Phi())*180/PI;

   
  
   //calculate alpha angle, angle the beam makes with the z axis (theta in      helicity frame)

   double alpha = 0;
   alpha = B_hf.Theta();

   B_hf.RotateY(alpha);    
   w_hf.RotateY(alpha);    
   Pi_hf.RotateY(alpha);    
   prot_hf.RotateY(alpha);    
   recprot_hf.RotateY(alpha);    
   gamma_hf.RotateY(alpha);

   TLorentzVector B_gj;
   TLorentzVector prot_gj;
   TLorentzVector gamma_gj;
   TLorentzVector recprot_gj;
   TLorentzVector w_gj;
   TLorentzVector Pi_gj;

   B_gj = B_hf;
   Pi_gj = Pi_hf;
   recprot_gj = recprot_hf;
   prot_gj = prot_hf;
   w_gj = w_hf;
   gamma_gj = gamma_hf;


   pwa_ntuple.gjcosthe = Pi_gj.CosTheta();
   pwa_ntuple.gjphi = Pi_gj.Phi();
   pwa_ntuple.gjthe = Pi_gj.Theta();
   double gjcos = 0 ;
   double gjphi = 0 ;
   gjcos = Pi_gj.CosTheta();
   gjphi = (Pi_gj.Phi())*180/PI;

   double Ener = 0,theta=0;
   double Px = 0,Py=0,Pz=0,Pt=0;
   for (int m=0; m <3 ; ++m){
       Ener = pvect[m][0];
       Px = pvect[m][1];
       Py = pvect[m][2];
       Pz = pvect[m][3];
       Pt = sqrt(sqr(pvect[m][1])+
                 sqr(pvect[m][2]));
       theta = atan2(Pt,Pz)*180/PI;
   }
   double wgt1 = 0;
   double wgt2 = 0;
   double wgt3 = 0;
   double wgt4 = 0;
   double wgt5 = 0;
   double wgt6 = 0;
   double wgt7 = 0;
   double wgt8 = 0;

  
   double dwgt1 = 0;
   double dwgt2 = 0;
   double dwgt3 = 0;
   double dwgt4 = 0;
   double dwgt5 = 0;
   double dwgt6 = 0;
   double dwgt7 = 0;
   double dwgt8 = 0;

   double sb1 = -0.162;
   double sg1 = +1;
   double sb2 = - 0.112;
   double dsb1 = -0.104;
   double dsg1 = +1;
   double dsb2 = -0.103;

//1
   double tsb2 = -0.066;
   double tsg2 = +1;
   double t2sb1 = - 0.051;
   double dsb1t1 = -0.206;
   double dsgt1 = +1;
   double dsb2t1 = - 0.202;
//2
   double tsb3 = -0.086;
   double tsg3 = +1;
   double t2sb2 = - 0.057;
   double dsb1t2 = -0.1045;
   double dsgt2 = +1;
   double dsb2t2 = - 0.103;
//3
   double tsb4 = -0.125;
   double tsg4 = +1;
   double t2sb3 = - 0.0814;
   double dsb1t3 = -0.0711;
   double dsgt3 = +1;
   double dsb2t3 = - 0.0697;
//4
   double tsb5 = -0.146;
   double tsg5 = +1;
   double t2sb4 = - 0.100;
   double dsb1t4 = -0.0474;
   double dsgt4 = +1;
   double dsb2t4 = - 0.0467;
//5
   double tsb6 = -0.246;
   double tsg6 = +1;
   double t2sb5 = - 0.163;
   double dsb1t5 = -0.0554;
   double dsgt5 = +1;
   double dsb2t5 = - 0.0544;
//6
   double tsb7 = -0.2998;
   double tsg7 = +1;
   double t2sb6 = - 0.1925;
   double dsb1t6 = -0.0552;
   double dsgt6 = +1;
   double dsb2t6 = - 0.0537;
//7
   double tsb8 = -0.342;
   double tsg8 = +1;
   double t2sb7 = - 0.202;
   double dsb1t7 = -0.0502;
   double dsgt7 = +1;
   double dsb2t7 = - 0.0487;


   int t_sb1 =0;
   int t_signal = 0;
   int d_sb1 =0;
   int d_signal = 0;


   int t_sb2 =0;
   int t2_signal = 0;
   int d_sb2 =0;
   int d2_signal = 0;

   int t_sb3 =0;
   int t3_signal = 0;
   int d_sb3 =0;
   int d3_signal = 0;

   int t_sb4 =0;
   int t4_signal = 0;
   int d_sb4 =0;
   int d4_signal = 0;

   int t_sb5 =0;
   int t5_signal = 0;
   int d_sb5 =0;
   int d5_signal = 0;

   int t_sb6 =0;
   int t6_signal = 0;
   int d_sb6 =0;
   int d6_signal = 0;

   int t_sb7 =0;
   int t7_signal = 0;
   int d_sb7 =0;
   int d7_signal = 0;

   int t_sb8 =0;
   int t8_signal = 0;
   int d_sb8 =0;
   int d8_signal = 0;

   if ((mass > 0.6 && mass < 0.7)||(mass > 0.9 && mass < 1.0)){
       ++t_sb1;
       ++t_sb2;
       ++t_sb3;
       ++t_sb4;
       ++t_sb5;
       ++t_sb6;
       ++t_sb7;
       ++t_sb8;
   }  
    if (mass > 0.7 && mass < 0.9){
       ++t_signal;
       ++t2_signal;
       ++t3_signal;
       ++t4_signal;
       ++t5_signal;
       ++t6_signal;
       ++t7_signal;
       ++t8_signal;
   }  
    //if (mass > 0.9 && mass < 1.0){
      // ++ t_sb2;
   //}  
   if ((del_phi > -100 && del_phi < -50)||(del_phi > 50 && del_phi < 100)){
       ++d_sb1;
       ++d_sb2;
       ++d_sb3;
       ++d_sb4;
       ++d_sb5;
       ++d_sb6;
       ++d_sb7;
       ++d_sb8;
   }  
   if (del_phi > -50 && del_phi < 50){
       ++d_signal;
       ++d2_signal;
       ++d3_signal;
       ++d4_signal;
       ++d5_signal;
       ++d6_signal;
       ++d7_signal;
       ++d8_signal;
   }  
  // if (del_phi > 50 && del_phi < 100){
    //   ++ d_sb2;
   //}
   //Invariant mass signal to sideband ratio multiplicative ratio
   double e_sbrat1[7] = {1.024,0.9181,1.0145,1.022,1.0466,
                         1.03836,1.0265}; 
   double e_sbrat2[7] = {0.951,0.965,1.01233,1.006,1.004,
                         1.014,1.01966}; 
   double e_sbrat3[7] = {1.02566,0.926,1.0068,1.0213,1.0358,
                         0.956,1.0322}; 
   double e_sbrat4[7] = {1.0963,1.022,0.997,1.0159,1.007,
                         1.0202,1.0337};
   //delta phi signal to sideband ratio used for sideband subtraction 
  


   double de_sbrt1[7] = {1.0965,1.4395,1.428,1.424,1.662,
                         1.505,1.662};
   double de_sbrt2[7] = {1.4696,1.5281,1.4591,1.422,1.6623,
                         1.6615,1.5000};
   double de_sbrt3[7] = {1.4084,1.4075,1.4225,1.454,1.6621,
                         1.5908,1.37588};
   double de_sbrt4[7] = {1.4885,1.2825,1.528,1.464,1.6624,
                         1.662,1.54};
                          

   double e_wgt1[7] = {0,0,0,0,0,0,0,};
   double e_wgt2[7] = {0,0,0,0,0,0,0,};
   double e_wgt3[7] = {0,0,0,0,0,0,0,};
   double e_wgt4[7] = {0,0,0,0,0,0,0,};
 
   for (int i = 0; i < 7; ++i){
      e_wgt1[i] = ewgt1*(t_signal - e_sbrat1[i]*t_sb1);
      e_wgt2[i] = ewgt2*(t_signal - e_sbrat2[i]*t_sb1);
      e_wgt3[i] = ewgt3*(t_signal - e_sbrat3[i]*t_sb1);
      e_wgt4[i] = ewgt4*(t_signal - e_sbrat4[i]*t_sb1);
   }   
   for (int i = 0; i < 7; ++i){
      pwa_ntuple.Ewgt1[i]  = e_wgt1[i]*(d_signal - de_sbrt1[i]*d_sb1);
      pwa_ntuple.Ewgt2[i]  = e_wgt2[i]*(d_signal - de_sbrt2[i]*d_sb1);
      pwa_ntuple.Ewgt3[i]  = e_wgt3[i]*(d_signal - de_sbrt3[i]*d_sb1);
      pwa_ntuple.Ewgt4[i]  = e_wgt4[i]*(d_signal - de_sbrt4[i]*d_sb1);
   } 


   wgt1 = t_signal - ((1.0219*t_sb1));
   dwgt1 = d_signal - ((1.59*d_sb1));
   wgt2 = t2_signal - ((1.035*t_sb2));
   dwgt2 = d2_signal - ((1.58*d_sb2));
   wgt3 = t3_signal - ((0.956*t_sb3));
   dwgt3 = d3_signal - ((1.51*d_sb3));
   wgt4 = t4_signal - ((1.003*t_sb4));
   dwgt4 = d4_signal - ((1.673*d_sb4));
   wgt5 = t5_signal - ((1.021*t_sb5));
   dwgt5 = d5_signal - ((1.39*d_sb5));
   wgt6 = t6_signal - ((1.045*t_sb6));
   dwgt6 = d6_signal - ((1.505*d_sb6));
   wgt7 = t7_signal - ((1.043*t_sb7));
   dwgt7 = d7_signal - ((1.551*d_sb7));
   wgt8 = t8_signal - ((1.005*t_sb8));
   dwgt8 = d8_signal - ((1.569*d_sb8));

   double n_wgt =   wgt * wgt1 * dwgt1; 
   double nt_wgt1 = wgt * wgt2 * dwgt2; 
   double nt_wgt2 = wgt * wgt3 * dwgt3; 
   double nt_wgt3 = wgt * wgt4 * dwgt4; 
   double nt_wgt4 = wgt * wgt5 * dwgt5; 
   double nt_wgt5 = wgt * wgt6 * dwgt6; 
   double nt_wgt6 = wgt * wgt7 * dwgt7; 
   double nt_wgt7 = wgt * wgt8 * dwgt8;
 
   pwa_ntuple.wgt[0] = wgt * wgt1 * dwgt1; 
   pwa_ntuple.wgt[1] = wgt * wgt2 * dwgt2; 
   pwa_ntuple.wgt[2] = wgt * wgt3 * dwgt3; 
   pwa_ntuple.wgt[3] = wgt * wgt4 * dwgt4; 
   pwa_ntuple.wgt[4] = wgt * wgt5 * dwgt5; 
   pwa_ntuple.wgt[5] = wgt * wgt6 * dwgt6; 
   pwa_ntuple.wgt[6] = wgt * wgt7 * dwgt7; 
   pwa_ntuple.wgt[7] = wgt * wgt8 * dwgt8;





 
   if (Efrwd > 3.0){
   if ( Emin > 0.05){
   if (neut_bgv ==0){
   
       //remass_1d->Fill(mass,wgt);
       if ((theta > (7.95-(Ener * 7.69)))){
	 //  remass2_1d->Fill(mass,wgt);
	   if (Pi_lab.M() > 0.1 && Pi_lab.M() < 0.18)
	   {
              for (int i =0; i < 4 ; ++i){
                 E_delphi[i]->Fill(mass,cwgt[i]);
              }
	   //    remass4_1d->Fill(mass,wgt);
	     //  remass5_1d->Fill(mass,wgt1);
	       if (t > 0.0 && t < 0.08){
		   remass6_1d->Fill(mass,wgt);
	       }
	       if (t > 0.08 && t < 0.18){
		   remass7_1d->Fill(mass,wgt);
	       }
	       if (t > 0.18 && t < 0.30){
		   remass8_1d->Fill(mass,wgt);
	       }
	       if (t > 0.30 && t < 0.45){
		   remass9_1d->Fill(mass,wgt);
	       }
	       if (t > 0.45 && t < 0.65){
		   remass10_1d->Fill(mass,wgt);
	       }
	       if (t > 0.65 && t < 0.90){
		   remass11_1d->Fill(mass,wgt);
	       }
	       if (t > 0.90 && t < 1.2){
		   remass12_1d->Fill(mass,wgt);
	       }
      // Invariant mass plots binned in |t| and also E_gamma ,for each sqrt(s) we do 7 |t| bins
      //      bin 1 
            for(int h_tag =0; h_tag < ncoin; ++h_tag){ 
              if (coenergy[h_tag] > 4.39  && coenergy[h_tag] < 4.60){
		       if (t > 0.00 && t < 0.08){
			   remass13_1d->Fill(mass,e_wgt1[0]);
		       }
		       if (t > 0.08 && t < 0.18){
			   remass14_1d->Fill(mass,e_wgt1[1]);
		       }
		       if (t > 0.18 && t < 0.30){
			   remass15_1d->Fill(mass,e_wgt1[2]);
		       }
		       if (t > 0.30 && t < 0.45){
			   remass16_1d->Fill(mass,e_wgt1[3]);
		       }
		       if (t > 0.45 && t < 0.65){
			   remass17_1d->Fill(mass,e_wgt1[4]);
		       }
		       if (t > 0.65 && t < 0.90){
			   remass18_1d->Fill(mass,e_wgt1[5]);
		       }
		       if (t > 0.90 && t < 1.2){
			   remass19_1d->Fill(mass,e_wgt1[6]);
		       }
                }
              //bin2
              if (coenergy[h_tag] > 4.60  && coenergy[h_tag] < 4.90){
		   if (t > 0.00 && t < 0.08){
		   remass20_1d->Fill(mass,e_wgt2[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		   remass21_1d->Fill(mass,e_wgt2[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		   remass22_1d->Fill(mass,e_wgt2[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		   remass23_1d->Fill(mass,e_wgt2[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		   remass24_1d->Fill(mass,e_wgt2[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		   remass25_1d->Fill(mass,e_wgt2[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		   remass26_1d->Fill(mass,e_wgt2[6]);
		   }
               }
      // Invariant mass plots binned in |t| and also E_gamma ,for each Ebin we do 7 |t| bins 
               //bin3
               if (coenergy[h_tag] > 4.90  && coenergy[h_tag] < 5.15){
		   if (t > 0.00 && t < 0.08){
		   remass27_1d->Fill(mass,e_wgt3[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		   remass28_1d->Fill(mass,e_wgt3[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		   remass29_1d->Fill(mass,e_wgt3[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		   remass30_1d->Fill(mass,e_wgt3[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		   remass31_1d->Fill(mass,e_wgt3[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		   remass32_1d->Fill(mass,e_wgt3[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		   remass33_1d->Fill(mass,e_wgt3[6]);
		   }
               }
      // Invar	      iant mass plots binned in |t| and also E_gamma ,for each Ebin we do 7 |t| bins 
     //        bin4 
               if (coenergy[h_tag] > 5.15  && coenergy[h_tag] < 5.40){
		   if (t > 0.00 && t < 0.08){
		   remass34_1d->Fill(mass,e_wgt4[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		   remass35_1d->Fill(mass,e_wgt4[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		   remass36_1d->Fill(mass,e_wgt4[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		   remass37_1d->Fill(mass,e_wgt4[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		   remass38_1d->Fill(mass,e_wgt4[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		   remass39_1d->Fill(mass,e_wgt4[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		   remass40_1d->Fill(mass,e_wgt4[6]);
		   }
      
             }
         } 
	       for (int j=0;  j< ncoin;++j ){
		   mismass_1d[cochan[j]]->Fill(mass,tagweight[j]);         
	       }
               if (del_ener < 0.5){ 
                  ntout->Fill();
	          delphi_1d->Fill(del_phi,wgt1);
		   if (t > 0.0 && t < 0.08){
		       delphi3_1d->Fill(del_phi,wgt2);
		   }
		   if (t > 0.08 && t < 0.18){
		       delphi4_1d->Fill(del_phi,wgt3);
		   }
		   if (t > 0.18 && t < 0.30){
		       delphi5_1d->Fill(del_phi,wgt4);
		   }
		   if (t > 0.30 && t < 0.45){
		       delphi6_1d->Fill(del_phi,wgt5);
		   }
		   if (t > 0.45 && t < 0.65){
		       delphi7_1d->Fill(del_phi,wgt6);
		   }
		   if (t > 0.65 && t < 0.90){
		       delphi8_1d->Fill(del_phi,wgt7);
		   }
		   if (t > 0.90 && t < 1.2){
		       delphi9_1d->Fill(del_phi,wgt8);
		   }
            for(int h_tag =0; h_tag < ncoin; ++h_tag){ 
              if (coenergy[h_tag] > 4.39  && 
                  coenergy[h_tag] < 4.60){

		   if (t > 0.0 && t < 0.08){
		       delphi11_1d->Fill(del_phi,e_wgt1[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		       delphi12_1d->Fill(del_phi,e_wgt1[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		       delphi13_1d->Fill(del_phi,e_wgt1[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		       delphi14_1d->Fill(del_phi,e_wgt1[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		       delphi15_1d->Fill(del_phi,e_wgt1[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		       delphi16_1d->Fill(del_phi,e_wgt1[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		       delphi17_1d->Fill(del_phi,e_wgt1[6]);
		   }
		}
                         
              if (coenergy[h_tag] > 4.60  && coenergy[h_tag] < 4.90){
		   if (t > 0.0 && t < 0.08){
		       delphi18_1d->Fill(del_phi,e_wgt2[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		       delphi19_1d->Fill(del_phi,e_wgt2[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		       delphi20_1d->Fill(del_phi,e_wgt2[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		       delphi21_1d->Fill(del_phi,e_wgt2[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		       delphi22_1d->Fill(del_phi,e_wgt2[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		       delphi23_1d->Fill(del_phi,e_wgt2[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		       delphi24_1d->Fill(del_phi,e_wgt2[6]);
		   }
                  }
              if (coenergy[h_tag] > 4.90  && coenergy[h_tag] < 5.15){
		   if (t > 0.0 && t < 0.08){
		       delphi25_1d->Fill(del_phi,e_wgt3[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		       delphi26_1d->Fill(del_phi,e_wgt3[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		       delphi27_1d->Fill(del_phi,e_wgt3[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		       delphi28_1d->Fill(del_phi,e_wgt3[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		       delphi29_1d->Fill(del_phi,e_wgt3[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		       delphi30_1d->Fill(del_phi,e_wgt3[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		       delphi31_1d->Fill(del_phi,e_wgt3[6]);
		   }
                  }
              if (coenergy[h_tag] > 5.15  && coenergy[h_tag] < 5.40){
		   if (t > 0.0 && t < 0.08){
		       delphi32_1d->Fill(del_phi,e_wgt4[0]);
		   }
		   if (t > 0.08 && t < 0.18){
		       delphi33_1d->Fill(del_phi,e_wgt4[1]);
		   }
		   if (t > 0.18 && t < 0.30){
		       delphi34_1d->Fill(del_phi,e_wgt4[2]);
		   }
		   if (t > 0.30 && t < 0.45){
		       delphi35_1d->Fill(del_phi,e_wgt4[3]);
		   }
		   if (t > 0.45 && t < 0.65){
		       delphi36_1d->Fill(del_phi,e_wgt4[4]);
		   }
		   if (t > 0.65 && t < 0.90){
		       delphi37_1d->Fill(del_phi,e_wgt4[5]);
		   }
		   if (t > 0.90 && t < 1.2){
		       delphi38_1d->Fill(del_phi,e_wgt4[6]);
		   }
                  }
		}
                   
		  mom_trans1_1d->Fill(t_region1,n_wgt);
		  mom_trans_1d->Fill(t,n_wgt);
               if(mass > 0.7 && mass < 0.9){       
		delphi2_1d->Fill(del_phi,wgt);
	       }
               if(mass > 0.6 && mass < 1.0){       
		   if(del_phi > -100 && del_phi  < 100){
		       mom_trans2_1d->Fill(t,wgt);
		       for (int n = 0; n<ncoin;++n){
		           momtrans[cochan[n]]->Fill(t,tagweight[n]);
		       }  
		   }
		   if(del_phi > -50 && del_phi  < 50){
		       mom_trans3_1d->Fill(t,wgt);
		       for (int l = 0; l<ncoin;++l){
		           momtrans2[cochan[l]]->Fill(t,tagweight[l]);
		       }
		   }
               }
               if(mass > 0.7 && mass < 0.9){       
		   if(del_phi > -100 && del_phi  < 100){
		       mom_trans4_1d->Fill(t,wgt);
		       for (int l = 0; l<ncoin;++l){
		           momtrans3[cochan[l]]->Fill(t,tagweight[l]);
		       }
		   }
		   if(del_phi > -50 && del_phi  < 50){
		       mom_trans5_1d->Fill(t,wgt);
		       mom_trans6_1d->Fill(t,wgt);
		       for (int l = 0; l<ncoin;++l){
		           momtrans4[cochan[l]]->Fill(t,tagweight[l]);
		       }
		   }
               }
               if(mass > 0.6 && mass < 1.0){       
		   if(del_phi > -120 && del_phi  < 120){
		   }
		   if(del_phi > -60 && del_phi  < 60){
		       mom_trans7_1d->Fill(t,wgt);
		   }
	      }
               if(mass > 0.7 && mass < 0.9){       
		   if(del_phi > -100 && del_phi  < 100){
		       mom_trans8_1d->Fill(t,wgt);
		   }
		   if(del_phi > -50 && del_phi  < 50){
		       mom_trans9_1d->Fill(t,wgt);
		   }
	      }


	       for (int j=0;  j< ncoin;++j ){
		   mismass2_1d[cochan[j]]->Fill(mass,tagweight[j]);         
		   mismass3_1d[cochan[j]]->Fill(coenergy[j]);         
	        }      
		       delphi10_1d->Fill(del_phi,wgt);
		       ome_azimuth2->Fill(ome_phi,wgt);
		       alph_ang2->Fill(alpha,wgt);
		       alph_ang->Fill(thetacm,wgt);
		   if (t > 0.0 && t < 0.08){
                       p_angle->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt1->Fill(gjcos,nt_wgt1);
		       cos_hft1->Fill(hfcos,nt_wgt1);
		       phi_gj1->Fill(gjphi,nt_wgt1);
		   }
		   if (t > 0.08 && t < 0.18){
                       p_angle1->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt2->Fill(gjcos,nt_wgt2);
		       cos_hft2->Fill(hfcos,nt_wgt2);
		       phi_gj2->Fill(gjphi,nt_wgt2);
		   }
		   if (t > 0.18 && t < 0.30){
                       p_angle2->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt3->Fill(gjcos,nt_wgt3);
		       cos_hft3->Fill(hfcos,nt_wgt3);
		       phi_gj3->Fill(gjphi,nt_wgt3);
		   }
		   if (t > 0.30 && t < 0.45){
                       p_angle3->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt4->Fill(gjcos,nt_wgt4);
		       cos_hft4->Fill(hfcos,nt_wgt4);
		       phi_gj4->Fill(gjphi,nt_wgt4);
		   }
		   if (t > 0.45 && t < 0.65){
                       p_angle4->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt5->Fill(gjcos,nt_wgt5);
		       cos_hft5->Fill(hfcos,nt_wgt5);
		       phi_gj5->Fill(gjphi,nt_wgt5);
		   }
		   if (t > 0.65 && t < 0.90){
                       p_angle5->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt6->Fill(gjcos,nt_wgt6);
		       cos_hft6->Fill(hfcos,nt_wgt6);
		       phi_gj6->Fill(gjphi,nt_wgt6);
		   }
		   if (t > 0.90 && t < 1.2){
                       p_angle6->Fill(hfcos,hfphi,nt_wgt1);
		       cos_gjt7->Fill(gjcos,nt_wgt7);
		       cos_hft7->Fill(hfcos,nt_wgt7);
		       phi_gj7->Fill(gjphi,nt_wgt7);
		   }

# if 0
		   if (mass > 0.6  && mass < 1.0){
		   if(del_phi > -50 && del_phi  < 50){
		   if (t > 0.0 && t < 0.08){
		       cos2_gjt1->Fill(gjcos,wgt);
		       phigj_2_1->Fill(gjphi,wgt);
		   }
		   if (t > 0.08 && t < 0.18){
		       cos2_gjt2->Fill(gjcos,wgt);
		       phigj_2_2->Fill(gjphi,wgt);
		   }
		   if (t > 0.18 && t < 0.30){
		       cos2_gjt3->Fill(gjcos,wgt);
		       phigj_2_3->Fill(gjphi,wgt);
		   }
		   if (t > 0.30 && t < 0.45){
		       cos2_gjt4->Fill(gjcos,wgt);
		       phigj_2_4->Fill(gjphi,wgt);
		   }
		   if (t > 0.45 && t < 0.65){
		       cos2_gjt5->Fill(gjcos,wgt);
		       phigj_2_5->Fill(gjphi,wgt);
		   }
		   if (t > 0.65 && t < 0.90){
		       cos2_gjt6->Fill(gjcos,wgt);
		       phigj_2_6->Fill(gjphi,wgt);
		   }
		   if (t > 0.90 && t < 1.20){
		       cos2_gjt7->Fill(gjcos,wgt);
		       phigj_2_7->Fill(gjphi,wgt);
		   }
	       }
	       }

	       if (mass > 0.7 && mass < 0.9)
	       {
                   //filling the t resolution plots
		   if(del_phi > -100 && del_phi  < 100){
		       
		       if (t > 0.0 && t < 0.08){
			   cos3_gjt1->Fill(gjcos,wgt);
			   phigj_3_1->Fill(gjphi,wgt);
		       }
		       if (t > 0.08 && t < 0.18){
			   cos3_gjt2->Fill(gjcos,wgt);
			   phigj_3_2->Fill(gjphi,wgt);
		       }
		       if (t > 0.18 && t < 0.30){
			   cos3_gjt3->Fill(gjcos,wgt);
			   phigj_3_3->Fill(gjphi,wgt);
		       }
		       if (t > 0.30 && t < 0.45){
			   cos3_gjt4->Fill(gjcos,wgt);
			   phigj_3_4->Fill(gjphi,wgt);
		       }
		       if (t > 0.45 && t < 0.65){
			   cos3_gjt5->Fill(gjcos,wgt);
			   phigj_3_5->Fill(gjphi,wgt);
		       }
		       if (t > 0.65 && t < 0.90){
			   cos3_gjt6->Fill(gjcos,wgt);
			   phigj_3_6->Fill(gjphi,wgt);
		       }
		       if (t > 0.90 && t < 1.20){
			   cos3_gjt7->Fill(gjcos,wgt);
			   phigj_3_7->Fill(gjphi,wgt);
		       }
	           }
		   if(del_phi > -50 && del_phi  < 50){
		       if (t > 0.0 && t < 0.08){
			   cos4_gjt1->Fill(gjcos,wgt);
			   phigj_4_1->Fill(gjphi,wgt);
		       }
		       if (t > 0.08 && t < 0.18){
			   cos4_gjt2->Fill(gjcos,wgt);
			   phigj_4_2->Fill(gjphi,wgt);
		       }
		       if (t > 0.18 && t < 0.30){
			   cos4_gjt3->Fill(gjcos,wgt);
			   phigj_4_3->Fill(gjphi,wgt);
		       }
		       if (t > 0.30 && t < 0.45){
			   cos4_gjt4->Fill(gjcos,wgt);
			   phigj_4_4->Fill(gjphi,wgt);
		       }
		       if (t > 0.45 && t < 0.65){
			   cos4_gjt5->Fill(gjcos,wgt);
			   phigj_4_5->Fill(gjphi,wgt);
		       }
		       if (t > 0.65 && t < 0.90){
			   cos4_gjt6->Fill(gjcos,wgt);
			   phigj_4_6->Fill(gjphi,wgt);
		       }
		       if (t > 0.90 && t < 1.20){
			   cos4_gjt7->Fill(gjcos,wgt);
			   phigj_4_7->Fill(gjphi,wgt);
		       }
	           }
	           }
# endif
	       }
	     }
           }
       }
     }
   }



return kTRUE;
}

void omega::SlaveTerminate()
{  
//The SlaveTerminate() function is called after all entries or objects
// have been processed. When running with PROOF SlaveTerminate() is called
// on each slave server.
   ntoutfile->cd();
   ntout->Write();
   TString oldpath = ntoutfile->GetName();
   delete ntoutfile;
   TString newpath = "/home/proof/mokaya/" + oldpath;
   rename(oldpath, newpath);
   ntoutfile = 0;
   ntout = 0;
}            
	    
void omega::Terminate()
{
// The Terminate() function is the last function to be called during
// a query. It always runs on the client, it can be used to present
// the results graphically or save the results to file.
//TFile *ofile =  new TFile ("massprof.root", "recreate");
TFile *ofile =  new TFile ("massprof.root", "recreate");
//TFile *ofile =  new TFile ("montecarlo.root", "recreate");
TIter iter(GetOutputList());
TH1D *hist;
while ((hist = (TH1D*)iter())){
   hist->Write();
}
delete ofile;   
}


double omega::constrain_angle(double x){
   x =remainder(x,360.0);
   if(x<0)
       x+=360;
   return x-180;
}
double omega::angle_diff(double angle1,double angle2)
{
   double diff = angle1-angle2;
       while(diff < -180){
          diff +=360;
       }
       while(diff > 180){
          diff -=360;
       }
       return diff;
}
