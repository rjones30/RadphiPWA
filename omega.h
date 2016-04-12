//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 25 09:27:32 2013 by ROOT version 5.34/03
// from TTree h1/Radphi
// found on file: ntuple.root
//////////////////////////////////////////////////////////

#ifndef omega_h
#define omega_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1D.h>
#include<TH2D.h>
#include <TString.h>
#include <TProfile.h>
#include <TTree.h>
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class omega : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   double angle_diff(double angle1,double angle2);
   double constrain_angle(double x);

  //Declaration of histograms 
  TH1D *amass_1d;
  TH1D *omass_1d;
  TH1D *remass_1d;
  TH1D *remass2_1d;
  TH1D *remass3_1d;
  TH1D *remass4_1d;
  TH1D *remass5_1d;
  TH1D *remass6_1d;
  TH1D *remass7_1d;
  TH1D *remass8_1d;
  TH1D *remass9_1d;
  TH1D *remass10_1d;
  TH1D *remass11_1d;
  TH1D *remass12_1d;
  TH1D *remass13_1d;
  TH1D *remass14_1d;
  TH1D *remass15_1d;
  TH1D *remass16_1d;
  TH1D *remass17_1d;
  TH1D *remass18_1d;
  TH1D *remass19_1d;
  TH1D *remass20_1d;
  TH1D *remass21_1d;
  TH1D *remass22_1d;
  TH1D *remass23_1d;
  TH1D *remass24_1d;
  TH1D *remass25_1d;
  TH1D *remass26_1d;
  TH1D *remass27_1d;
  TH1D *remass28_1d;
  TH1D *remass29_1d;
  TH1D *remass30_1d;
  TH1D *remass31_1d;
  TH1D *remass32_1d;
  TH1D *remass33_1d;
  TH1D *remass34_1d;
  TH1D *remass35_1d;
  TH1D *remass36_1d;
  TH1D *remass37_1d;
  TH1D *remass38_1d;
  TH1D *remass39_1d;
  TH1D *remass40_1d;

  TH1D *mom_trans_1d;
  TH1D *mom_trans1_1d;
  TH1D *mom_trans2_1d;
  TH1D *mom_trans3_1d;
  TH1D *mom_trans4_1d;
  TH1D *mom_trans5_1d;
  TH1D *mom_trans6_1d;
  TH1D *mom_trans7_1d;
  TH1D *mom_trans8_1d;
  TH1D *mom_trans9_1d;
  TH1D *prot_mass_1d;
  TH1D *prot_mass2_1d;



  TH1D *t_mom1;
  TH1D *t_mom2;
  TH1D *t_mom3;
  TH1D *t_mom4;
  TH1D *t_mom5;
  TH1D *t_mom6;
  TH1D *t_mom7;
  TH1D *t_mom8;
  TH1D *t_mom9;
  TH1D *t_mom10;
  TH1D *t_mom11;
  TH1D *t_mom12;
  TH1D *t_mom13;
  TH1D *t_mom14;
  TH1D *t_mom15;
  TH1D *t_mom16;
  TH1D *t_mom17;
  TH1D *t_mom18;
  TH1D *t_mom19;



  TH1D *prot_rf;
  TH1D *prot_cm;
  TH1D *beam_cm;
  TH1D *prot_rf2;
  TH1D *phi_lab;
  TH1D *phi_lab2;
  TH1D *cos_hft1;
  TH1D *cos_hft2;
  TH1D *cos_hft3;
  TH1D *cos_hft4;
  TH1D *cos_hft5;
  TH1D *cos_hft6;
  TH1D *cos_hft7;
  TH1D *cos_hft8;
  TH1D *cos_hft9;
  TH1D *cos_hft10;
  TH1D *cos_hft11;
  TH1D *cos_hft12;
  TH1D *cos_hft13;
  TH1D *cos_hft14;
  TH1D *cos_hft15;
  TH1D *cos_hft16;
  TH1D *cos_hft17;
  TH1D *cos_hft18;
  TH1D *cos_hft19;
  TH1D *cos2_hft1;
  TH1D *cos2_hft2;
  TH1D *cos2_hft3;
  TH1D *cos2_hft4;
  TH1D *cos2_hft5;
  TH1D *cos2_hft6;
  TH1D *cos2_hft7;
  TH1D *cos2_hft8;
  TH1D *cos2_hft9;
  TH1D *cos2_hft10;
  TH1D *cos2_hft11;
  TH1D *cos2_hft12;
  TH1D *cos2_hft13;
  TH1D *cos2_hft14;
  TH1D *cos2_hft15;
  TH1D *cos2_hft16;
  TH1D *cos2_hft17;
  TH1D *cos2_hft18;
  TH1D *cos2_hft19;


  TH1D *cos_gjt1;
  TH1D *cos_gjt2;
  TH1D *cos_gjt3;
  TH1D *cos_gjt4;
  TH1D *cos_gjt5;
  TH1D *cos_gjt6;
  TH1D *cos_gjt7;
  TH1D *cos_gjt8;
  TH1D *cos_gjt9;
  TH1D *cos_gjt10;
  TH1D *cos_gjt11;
  TH1D *cos_gjt12;
  TH1D *cos_gjt13;
  TH1D *cos_gjt14;
  TH1D *cos_gjt15;
  TH1D *cos_gjt16;
  TH1D *cos_gjt17;
  TH1D *cos_gjt18;
  TH1D *cos_gjt19;
  TH1D *cos2_gjt1;
  TH1D *cos2_gjt2;
  TH1D *cos2_gjt3;
  TH1D *cos2_gjt4;
  TH1D *cos2_gjt5;
  TH1D *cos2_gjt6;
  TH1D *cos2_gjt7;
  TH1D *cos2_gjt8;
  TH1D *cos2_gjt9;
  TH1D *cos2_gjt10;
  TH1D *cos2_gjt11;
  TH1D *cos2_gjt12;
  TH1D *cos2_gjt13;
  TH1D *cos2_gjt14;
  TH1D *cos2_gjt15;
  TH1D *cos2_gjt16;
  TH1D *cos2_gjt17;
  TH1D *cos2_gjt18;
  TH1D *cos2_gjt19;
  TH1D *cos2_gjt20;
 

  TH1D *cos3_gjt1;
  TH1D *cos3_gjt2;
  TH1D *cos3_gjt3;
  TH1D *cos3_gjt4;
  TH1D *cos3_gjt5;
  TH1D *cos3_gjt6;
  TH1D *cos3_gjt7;
  TH1D *cos3_gjt8;
  TH1D *cos3_gjt9;
  TH1D *cos3_gjt10;
  TH1D *cos3_gjt11;
  TH1D *cos3_gjt12;
  TH1D *cos3_gjt13;
  TH1D *cos3_gjt14;
  TH1D *cos3_gjt15;
  TH1D *cos3_gjt16;
  TH1D *cos3_gjt17;
  TH1D *cos3_gjt18;
  TH1D *cos3_gjt19;


  TH1D *cos4_gjt1;
  TH1D *cos4_gjt2;
  TH1D *cos4_gjt3;
  TH1D *cos4_gjt4;
  TH1D *cos4_gjt5;
  TH1D *cos4_gjt6;
  TH1D *cos4_gjt7;
  TH1D *cos4_gjt8;
  TH1D *cos4_gjt9;
  TH1D *cos4_gjt10;
  TH1D *cos4_gjt11;
  TH1D *cos4_gjt12;
  TH1D *cos4_gjt13;
  TH1D *cos4_gjt14;
  TH1D *cos4_gjt15;
  TH1D *cos4_gjt16;
  TH1D *cos4_gjt17;
  TH1D *cos4_gjt18;
  TH1D *cos4_gjt19;

 
  TH2D *p_angle;
  TH2D *p_angle1;
  TH2D *p_angle2;
  TH2D *p_angle3;
  TH2D *p_angle4;
  TH2D *p_angle5;
  TH2D *p_angle6;
  TH1D *o_angle;

  TH1D *phi_hf;
  TH1D *phi_hf1;
  TH1D *phi_hf2;
  TH1D *phi_hf3;
  TH1D *phi_hf4;
  TH1D *phi_hf5;
  TH1D *phi_hf6;
  TH1D *phi_hf7;
  TH1D *phi_hf8;
  TH1D *phi_hf9;
  TH1D *phi_hf10;
  TH1D *phi_hf11;
  TH1D *phi_hf12;
  TH1D *phi_hf13;
  TH1D *phi_hf14;
  TH1D *phi_hf15;
  TH1D *phi_hf16;
  TH1D *phi_hf17;
  TH1D *phi_hf18;
  TH1D *phi_hf19;


  TH1D *phi_gj;
  TH1D *phi_gj1;
  TH1D *phi_gj2;
  TH1D *phi_gj3;
  TH1D *phi_gj4;
  TH1D *phi_gj5;
  TH1D *phi_gj6;
  TH1D *phi_gj7;
  TH1D *phi_gj8;
  TH1D *phi_gj9;
  TH1D *phi_gj10;
  TH1D *phi_gj11;
  TH1D *phi_gj12;
  TH1D *phi_gj13;
  TH1D *phi_gj14;
  TH1D *phi_gj15;
  TH1D *phi_gj16;
  TH1D *phi_gj17;
  TH1D *phi_gj18;
  TH1D *phi_gj19;



  TH1D *phigj_2;
  TH1D *phigj_2_1;
  TH1D *phigj_2_2;
  TH1D *phigj_2_3;
  TH1D *phigj_2_4;
  TH1D *phigj_2_5;
  TH1D *phigj_2_6;
  TH1D *phigj_2_7;
  TH1D *phigj_2_8;
  TH1D *phigj_2_9;
  TH1D *phigj_2_10;
  TH1D *phigj_2_11;
  TH1D *phigj_2_12;
  TH1D *phigj_2_13;
  TH1D *phigj_2_14;
  TH1D *phigj_2_15;
  TH1D *phigj_2_16;
  TH1D *phigj_2_17;
  TH1D *phigj_2_18;
  TH1D *phigj_2_19;

  TH1D *phigj_3;
  TH1D *phigj_3_1;
  TH1D *phigj_3_2;
  TH1D *phigj_3_3;
  TH1D *phigj_3_4;
  TH1D *phigj_3_5;
  TH1D *phigj_3_6;
  TH1D *phigj_3_7;
  TH1D *phigj_3_8;
  TH1D *phigj_3_9;
  TH1D *phigj_3_10;
  TH1D *phigj_3_11;
  TH1D *phigj_3_12;
  TH1D *phigj_3_13;
  TH1D *phigj_3_14;
  TH1D *phigj_3_15;
  TH1D *phigj_3_16;
  TH1D *phigj_3_17;
  TH1D *phigj_3_18;
  TH1D *phigj_3_19;


  TH1D *phigj_4;
  TH1D *phigj_4_1;
  TH1D *phigj_4_2;
  TH1D *phigj_4_3;
  TH1D *phigj_4_4;
  TH1D *phigj_4_5;
  TH1D *phigj_4_6;
  TH1D *phigj_4_7;
  TH1D *phigj_4_8;
  TH1D *phigj_4_9;
  TH1D *phigj_4_10;
  TH1D *phigj_4_11;
  TH1D *phigj_4_12;
  TH1D *phigj_4_13;
  TH1D *phigj_4_14;
  TH1D *phigj_4_15;
  TH1D *phigj_4_16;
  TH1D *phigj_4_17;
  TH1D *phigj_4_18;
  TH1D *phigj_4_19;


  TH1D *alph_ang;
  TH1D *alph_ang2;
  TH1D *energy_1d;
  TH1D *delphi_1d;
  TH1D *delphi1_1d;
  TH1D *delphi2_1d;
  TH1D *delphi3_1d;
  TH1D *delphi4_1d;
  TH1D *delphi5_1d;
  TH1D *delphi6_1d;
  TH1D *delphi7_1d;
  TH1D *delphi8_1d;
  TH1D *delphi9_1d;
  TH1D *delphi10_1d;
  TH1D *delphi11_1d;
  TH1D *delphi12_1d;
  TH1D *delphi13_1d;
  TH1D *delphi14_1d;
  TH1D *delphi15_1d;
  TH1D *delphi16_1d;
  TH1D *delphi17_1d;
  TH1D *delphi18_1d;
  TH1D *delphi19_1d;
  TH1D *delphi20_1d;
  TH1D *delphi21_1d;
  TH1D *delphi22_1d;
  TH1D *delphi23_1d;
  TH1D *delphi24_1d;
  TH1D *delphi25_1d;
  TH1D *delphi26_1d;
  TH1D *delphi27_1d;
  TH1D *delphi28_1d;
  TH1D *delphi29_1d;
  TH1D *delphi30_1d;
  TH1D *delphi31_1d;
  TH1D *delphi32_1d;
  TH1D *delphi33_1d;
  TH1D *delphi34_1d;
  TH1D *delphi35_1d;
  TH1D *delphi36_1d;
  TH1D *delphi37_1d;
  TH1D *delphi38_1d;
  TH1D *tagger_1d;
  TH1D *Efrwd_1d;
  TH1D *Efrwd1_1d;
  TH1D *Efrwd2_1d;
  TH1D *Efrwd3_1d;
  TH1D *Efrwd4_1d;
  TH1D *bgvE_1d;

  TH1D *mismass_1d[20];
  TH1D *mismass2_1d[20];
  TH1D *mismass3_1d[20];
  TH1D *mismass4_1d[6];
  TH1D *coener_1d[6];
  TH1D *ener_1d[20];
  TH1D *ener2_1d[20];
  TH1D *ener3_1d[20];
  TH1D *momtrans[20];
  TH1D *momtrans2[20];
  TH1D *momtrans3[20];
  TH1D *momtrans4[20];
  TH1D *E_delphi[20];
  TH1D *ome_azimuth;
  TH1D *ome_azimuth2;
  TH1D *outofplane ;
  TH1D *outofplane1;
   // Declaration of leaf types
   Int_t           runno;
   Int_t           eventno;
   Int_t           ismc;
   Int_t           evtype;
   Int_t           memam;
   Int_t           cmam;
   Int_t           emam;
   Int_t           m2mam;
   Int_t           nbsd;
   Int_t           ibsd[400];   //[nbsd]
   Int_t           absd[400];   //[nbsd]
   Int_t           tbsd[400];   //[nbsd]
   Int_t           nbgv;
   Int_t           ibgv[400];   //[nbgv]
   Int_t           abgv[400];   //[nbgv]
   Int_t           tbgv[400];   //[nbgv]
   Int_t           ncpv;
   Int_t           icpv[250];   //[ncpv]
   Int_t           acpv[250];   //[ncpv]
   Int_t           tcpv[250];   //[ncpv]
   Int_t           nupv;
   Int_t           iupv[100];   //[nupv]
   Int_t           aupv[100];   //[nupv]
   Int_t           tupv[100];   //[nupv]
   Int_t           nlgd;
   Int_t           ilgd[640];   //[nlgd]
   Int_t           jlgd[640];   //[nlgd]
   Int_t           algd[640];   //[nlgd]
   Int_t           ntag;
   Int_t           itag[320];   //[ntag]
   Int_t           ttag[320];   //[ntag]
   Int_t           nhbsd;
   Int_t           chbsd[400];   //[nhbsd]
   Float_t         Ebsd[400];   //[nhbsd]
   Int_t           ntbsd[400];   //[nhbsd]
   Int_t           t1bsd[400];   //[nhbsd]
   Int_t           npix;
   Int_t           ipix[200];   //[npix]
   Int_t           rpix[200];   //[npix]
   Int_t           lpix[200];   //[npix]
   Int_t           spix[200];   //[npix]
   Float_t         zpix[200];   //[npix]
   Float_t         phipix[200];   //[npix]
   Float_t         rpixt[200];   //[npix]
   Float_t         lpixt[200];   //[npix]
   Float_t         spixt[200];   //[npix]
   Float_t         rpixe[200];   //[npix]
   Float_t         lpixe[200];   //[npix]
   Float_t         spixe[200];   //[npix]
   Int_t           nhbgv;
   Int_t           chbgv[400];   //[nhbgv]
   Float_t         Ebgvdwn[400];   //[nhbgv]
   Float_t         Ebgvup[400];   //[nhbgv]
   Int_t           ntbgvdwn[400];   //[nhbgv]
   Int_t           t1bgvdwn[400];   //[nhbgv]
   Int_t           ntbgvup[400];   //[nhbgv]
   Int_t           t1bgvup[400];   //[nhbgv]
   Int_t           nhcpv;
   Int_t           chcpv[250];   //[nhcpv]
   Float_t         Ecpv[250];   //[nhcpv]
   Int_t           ntcpv[250];   //[nhcpv]
   Int_t           t1cpv[250];   //[nhcpv]
   Int_t           nhupv;
   Int_t           chupv[50];   //[nhupv]
   Float_t         Eupv[50];   //[nhupv]
   Int_t           ntupv[50];   //[nhupv]
   Int_t           t1upv[50];   //[nhupv]
   Int_t           nhtag;
   Int_t           chtag[320];   //[nhtag]
   Float_t         Etag0[320];   //[nhtag]
   Float_t         Etag1[320];   //[nhtag]
   Int_t           nttagl[320];   //[nhtag]
   Int_t           nttagr[320];   //[nhtag]
   Int_t           t1tagl[320];   //[nhtag]
   Int_t           t1tagr[320];   //[nhtag]
   Int_t           ntimes;
   Float_t         le[500];   //[ntimes]
   Int_t           nrec;
   Float_t         trec0;
   Float_t         therec[100];   //[nrec]
   Float_t         phirec[100];   //[nrec]
   Float_t         derec[100];   //[nrec]
   Float_t         Erec[100];   //[nrec]
   Float_t         trec[100];   //[nrec]
   Int_t           mrec[100];   //[nrec]
   Int_t           ncoin;
   Int_t           cochan[30];   //[ncoin]
   Float_t         cotime[30];   //[ncoin]
   Float_t         coenergy[30];   //[ncoin]
   Float_t         tagweight[30];   //[ncoin]
   Int_t           nhlgd;
   Int_t           chlgd[640];   //[nhlgd]
   Float_t         Elgd[640];   //[nhlgd]
   Int_t           clust[640];   //[nhlgd]
   Int_t           nphot;
   Int_t           nfrwd;
   Float_t         Efrwd;
   Float_t         pvect[400][4];   //[nphot]
   Int_t           nbcl;
   Float_t         bce[24];   //[nbcl]
   Float_t         bcphi[24];   //[nbcl]
   Float_t         bcz[24];   //[nbcl]
   Float_t         bct[24];   //[nbcl]
   Float_t         bcse[24];   //[nbcl]
   Int_t           nmes;
   Int_t           mtype[500];   //[nmes]
   Float_t         ptot[500][4];   //[nmes]
   Float_t         amass[500];   //[nmes]
   Int_t           idtype[500][2];   //[nmes]
   Int_t           ichild[500][2];   //[nmes]

   // List of branches
   TBranch        *b_runno;   //!
   TBranch        *b_eventno;   //!
   TBranch        *b_ismc;   //!
   TBranch        *b_evtype;   //!
   TBranch        *b_memam;   //!
   TBranch        *b_cmam;   //!
   TBranch        *b_emam;   //!
   TBranch        *b_m2mam;   //!
   TBranch        *b_nbsd;   //!
   TBranch        *b_ibsd;   //!
   TBranch        *b_absd;   //!
   TBranch        *b_tbsd;   //!
   TBranch        *b_nbgv;   //!
   TBranch        *b_ibgv;   //!
   TBranch        *b_abgv;   //!
   TBranch        *b_tbgv;   //!
   TBranch        *b_ncpv;   //!
   TBranch        *b_icpv;   //!
   TBranch        *b_acpv;   //!
   TBranch        *b_tcpv;   //!
   TBranch        *b_nupv;   //!
   TBranch        *b_iupv;   //!
   TBranch        *b_aupv;   //!
   TBranch        *b_tupv;   //!
   TBranch        *b_nlgd;   //!
   TBranch        *b_ilgd;   //!
   TBranch        *b_jlgd;   //!
   TBranch        *b_algd;   //!
   TBranch        *b_ntag;   //!
   TBranch        *b_itag;   //!
   TBranch        *b_ttag;   //!
   TBranch        *b_nhbsd;   //!
   TBranch        *b_chbsd;   //!
   TBranch        *b_Ebsd;   //!
   TBranch        *b_ntbsd;   //!
   TBranch        *b_t1bsd;   //!
   TBranch        *b_npix;   //!
   TBranch        *b_ipix;   //!
   TBranch        *b_rpix;   //!
   TBranch        *b_lpix;   //!
   TBranch        *b_spix;   //!
   TBranch        *b_zpix;   //!
   TBranch        *b_phipix;   //!
   TBranch        *b_rpixt;   //!
   TBranch        *b_lpixt;   //!
   TBranch        *b_spixt;   //!
   TBranch        *b_rpixe;   //!
   TBranch        *b_lpixe;   //!
   TBranch        *b_spixe;   //!
   TBranch        *b_nhbgv;   //!
   TBranch        *b_chbgv;   //!
   TBranch        *b_Ebgvdwn;   //!
   TBranch        *b_Ebgvup;   //!
   TBranch        *b_ntbgvdwn;   //!
   TBranch        *b_t1bgvdwn;   //!
   TBranch        *b_ntbgvup;   //!
   TBranch        *b_t1bgvup;   //!
   TBranch        *b_nhcpv;   //!
   TBranch        *b_chcpv;   //!
   TBranch        *b_Ecpv;   //!
   TBranch        *b_ntcpv;   //!
   TBranch        *b_t1cpv;   //!
   TBranch        *b_nhupv;   //!
   TBranch        *b_chupv;   //!
   TBranch        *b_Eupv;   //!
   TBranch        *b_ntupv;   //!
   TBranch        *b_t1upv;   //!
   TBranch        *b_nhtag;   //!
   TBranch        *b_chtag;   //!
   TBranch        *b_Etag0;   //!
   TBranch        *b_Etag1;   //!
   TBranch        *b_nttagl;   //!
   TBranch        *b_nttagr;   //!
   TBranch        *b_t1tagl;   //!
   TBranch        *b_t1tagr;   //!
   TBranch        *b_ntimes;   //!
   TBranch        *b_le;   //!
   TBranch        *b_nrec;   //!
   TBranch        *b_trec0;   //!
   TBranch        *b_therec;   //!
   TBranch        *b_phirec;   //!
   TBranch        *b_derec;   //!
   TBranch        *b_Erec;   //!
   TBranch        *b_trec;   //!
   TBranch        *b_mrec;   //!
   TBranch        *b_ncoin;   //!
   TBranch        *b_cochan;   //!
   TBranch        *b_cotime;   //!
   TBranch        *b_coenergy;   //!
   TBranch        *b_tagweight;   //!
   TBranch        *b_nhlgd;   //!
   TBranch        *b_chlgd;   //!
   TBranch        *b_Elgd;   //!
   TBranch        *b_clust;   //!
   TBranch        *b_nphot;   //!
   TBranch        *b_nfrwd;   //!
   TBranch        *b_Efrwd;   //!
   TBranch        *b_pvect;   //!
   TBranch        *b_nbcl;   //!
   TBranch        *b_bce;   //!
   TBranch        *b_bcphi;   //!
   TBranch        *b_bcz;   //!
   TBranch        *b_bct;   //!
   TBranch        *b_bcse;   //!
   TBranch        *b_nmes;   //!
   TBranch        *b_mtype;   //!
   TBranch        *b_ptot;   //!
   TBranch        *b_amass;   //!
   TBranch        *b_idtype;   //!
   TBranch        *b_ichild;   //!

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
   } pwa_ntuple;

   TFile *ntoutfile;
   TTree *ntout;

   omega(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~omega() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(omega,0);
};

#endif

#ifdef omega_cxx
void omega::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("runno", &runno, &b_runno);
   fChain->SetBranchAddress("eventno", &eventno, &b_eventno);
   fChain->SetBranchAddress("ismc", &ismc, &b_ismc);
   fChain->SetBranchAddress("evtype", &evtype, &b_evtype);
# if 0
   fChain->SetBranchAddress("memam", &memam, &b_memam);
   fChain->SetBranchAddress("cmam", &cmam, &b_cmam);
   fChain->SetBranchAddress("emam", &emam, &b_emam);
   fChain->SetBranchAddress("m2mam", &m2mam, &b_m2mam);
   fChain->SetBranchAddress("nbsd", &nbsd, &b_nbsd);
   fChain->SetBranchAddress("ibsd", ibsd, &b_ibsd);
   fChain->SetBranchAddress("absd", absd, &b_absd);
   fChain->SetBranchAddress("tbsd", tbsd, &b_tbsd);
   fChain->SetBranchAddress("nbgv", &nbgv, &b_nbgv);
   fChain->SetBranchAddress("ibgv", ibgv, &b_ibgv);
   fChain->SetBranchAddress("abgv", abgv, &b_abgv);
   fChain->SetBranchAddress("tbgv", tbgv, &b_tbgv);
   fChain->SetBranchAddress("ncpv", &ncpv, &b_ncpv);
   fChain->SetBranchAddress("icpv", icpv, &b_icpv);
   fChain->SetBranchAddress("acpv", acpv, &b_acpv);
   fChain->SetBranchAddress("tcpv", tcpv, &b_tcpv);
   fChain->SetBranchAddress("nupv", &nupv, &b_nupv);
   fChain->SetBranchAddress("iupv", iupv, &b_iupv);
   fChain->SetBranchAddress("aupv", aupv, &b_aupv);
   fChain->SetBranchAddress("tupv", tupv, &b_tupv);
   fChain->SetBranchAddress("nlgd", &nlgd, &b_nlgd);
   fChain->SetBranchAddress("ilgd", ilgd, &b_ilgd);
   fChain->SetBranchAddress("jlgd", jlgd, &b_jlgd);
   fChain->SetBranchAddress("algd", algd, &b_algd);
   fChain->SetBranchAddress("ntag", &ntag, &b_ntag);
   fChain->SetBranchAddress("itag", itag, &b_itag);
   fChain->SetBranchAddress("ttag", ttag, &b_ttag);
   fChain->SetBranchAddress("nhbsd", &nhbsd, &b_nhbsd);
   fChain->SetBranchAddress("chbsd", chbsd, &b_chbsd);
   fChain->SetBranchAddress("Ebsd", Ebsd, &b_Ebsd);
   fChain->SetBranchAddress("ntbsd", ntbsd, &b_ntbsd);
   fChain->SetBranchAddress("t1bsd", t1bsd, &b_t1bsd);
#endif
   fChain->SetBranchAddress("npix", &npix, &b_npix);
   fChain->SetBranchAddress("ipix", ipix, &b_ipix);
   fChain->SetBranchAddress("rpix", rpix, &b_rpix);
   fChain->SetBranchAddress("lpix", lpix, &b_lpix);
   fChain->SetBranchAddress("spix", spix, &b_spix);
   fChain->SetBranchAddress("zpix", zpix, &b_zpix);
   fChain->SetBranchAddress("phipix", phipix, &b_phipix);
   fChain->SetBranchAddress("rpixt", rpixt, &b_rpixt);
   fChain->SetBranchAddress("lpixt", lpixt, &b_lpixt);
   fChain->SetBranchAddress("spixt", spixt, &b_spixt);
   fChain->SetBranchAddress("rpixe", rpixe, &b_rpixe);
   fChain->SetBranchAddress("lpixe", lpixe, &b_lpixe);
   fChain->SetBranchAddress("spixe", spixe, &b_spixe);

   fChain->SetBranchAddress("nhbgv", &nhbgv, &b_nhbgv);
   fChain->SetBranchAddress("chbgv", chbgv, &b_chbgv);
   fChain->SetBranchAddress("Ebgvdwn", Ebgvdwn, &b_Ebgvdwn);
   fChain->SetBranchAddress("Ebgvup", Ebgvup, &b_Ebgvup);
   fChain->SetBranchAddress("ntbgvdwn", ntbgvdwn, &b_ntbgvdwn);
   fChain->SetBranchAddress("t1bgvdwn", t1bgvdwn, &b_t1bgvdwn);
   fChain->SetBranchAddress("ntbgvup", ntbgvup, &b_ntbgvup);
   fChain->SetBranchAddress("t1bgvup", t1bgvup, &b_t1bgvup);
   fChain->SetBranchAddress("nhcpv", &nhcpv, &b_nhcpv);
   fChain->SetBranchAddress("chcpv", chcpv, &b_chcpv);
   fChain->SetBranchAddress("Ecpv", Ecpv, &b_Ecpv);
   fChain->SetBranchAddress("ntcpv", ntcpv, &b_ntcpv);
   fChain->SetBranchAddress("t1cpv", t1cpv, &b_t1cpv);
#if 0
   fChain->SetBranchAddress("nhupv", &nhupv, &b_nhupv);
   fChain->SetBranchAddress("chupv", chupv, &b_chupv);
   fChain->SetBranchAddress("Eupv", Eupv, &b_Eupv);
   fChain->SetBranchAddress("ntupv", ntupv, &b_ntupv);
   fChain->SetBranchAddress("t1upv", t1upv, &b_t1upv);
#endif
   fChain->SetBranchAddress("nhtag", &nhtag, &b_nhtag);
   fChain->SetBranchAddress("chtag", chtag, &b_chtag);
   fChain->SetBranchAddress("Etag0", Etag0, &b_Etag0);
   fChain->SetBranchAddress("Etag1", Etag1, &b_Etag1);
   fChain->SetBranchAddress("nttagl", nttagl, &b_nttagl);
   fChain->SetBranchAddress("nttagr", nttagr, &b_nttagr);
   fChain->SetBranchAddress("t1tagl", t1tagl, &b_t1tagl);
   fChain->SetBranchAddress("t1tagr", t1tagr, &b_t1tagr);
   fChain->SetBranchAddress("ntimes", &ntimes, &b_ntimes);
   fChain->SetBranchAddress("le", le, &b_le);
   fChain->SetBranchAddress("nrec", &nrec, &b_nrec);
   fChain->SetBranchAddress("trec0", &trec0, &b_trec0);
   fChain->SetBranchAddress("therec", therec, &b_therec);
   fChain->SetBranchAddress("phirec", phirec, &b_phirec);
   fChain->SetBranchAddress("derec", derec, &b_derec);
   fChain->SetBranchAddress("Erec", Erec, &b_Erec);
   fChain->SetBranchAddress("trec", trec, &b_trec);
   fChain->SetBranchAddress("mrec", mrec, &b_mrec);
   fChain->SetBranchAddress("ncoin", &ncoin, &b_ncoin);
   fChain->SetBranchAddress("cochan", cochan, &b_cochan);
   fChain->SetBranchAddress("cotime", cotime, &b_cotime);
   fChain->SetBranchAddress("coenergy", coenergy, &b_coenergy);
   fChain->SetBranchAddress("tagweight", tagweight, &b_tagweight);
   fChain->SetBranchAddress("nhlgd", &nhlgd, &b_nhlgd);
   fChain->SetBranchAddress("chlgd", chlgd, &b_chlgd);
   fChain->SetBranchAddress("Elgd", Elgd, &b_Elgd);
   fChain->SetBranchAddress("clust", clust, &b_clust);
   fChain->SetBranchAddress("nphot", &nphot, &b_nphot);
   fChain->SetBranchAddress("nfrwd", &nfrwd, &b_nfrwd);
   fChain->SetBranchAddress("Efrwd", &Efrwd, &b_Efrwd);
   fChain->SetBranchAddress("pvect", pvect, &b_pvect);
#if 0
   fChain->SetBranchAddress("nbcl", &nbcl, &b_nbcl);
   fChain->SetBranchAddress("bce", bce, &b_bce);
   fChain->SetBranchAddress("bcphi", bcphi, &b_bcphi);
   fChain->SetBranchAddress("bcz", bcz, &b_bcz);
   fChain->SetBranchAddress("bct", bct, &b_bct);
   fChain->SetBranchAddress("bcse", bcse, &b_bcse);
   fChain->SetBranchAddress("nmes", &nmes, &b_nmes);
   fChain->SetBranchAddress("mtype", mtype, &b_mtype);
   fChain->SetBranchAddress("ptot", ptot, &b_ptot);
   fChain->SetBranchAddress("amass", amass, &b_amass);
   fChain->SetBranchAddress("idtype", idtype, &b_idtype);
   fChain->SetBranchAddress("ichild", ichild, &b_ichild);
#endif
}

Bool_t omega::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef omega_cxx
