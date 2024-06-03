using namespace std;

void probe(TFile *file, int iscut, int name)//will open the file you have specified in runall.cxx
{
  cout<<"================================================"<<endl;
  cout<<"Entering the probe.cxx to fill in the histograms"<<endl;
  time_t     now;
  struct tm  *ts;
  char       buf[80];

  //Extraction of information
  TTree         *treee=(TTree*)file->Get("pairs");

  //PT bins
  int const nptbins=11;
  double  binspt[nptbins]={4.,7.2,10.5,15.5,19.0,25.0,30.0,35.0,40.0,50.0,80.0};


  //ETA bins
   int const netabins=29; //All together
  double binseta[netabins]={-2.5,-2.4,-1.918,-1.623,-1.348,-1.2329,-1.1479,-1.05,-0.908,-0.791,-0.652,-0.476,-0.324,
                            -0.132,0.0,+0.132,+0.324,+0.476,+0.652,+0.791,+0.908,+1.05,+1.1479,+1.2329,+1.348,+1.623,+1.918,+2.4,+2.5};


  int const netabinss=10; //for systematic
  double binsetas[netabinss]={-2.5,-1.918,-1.2329,-0.908,-0.324,+0.324,+0.908,+1.2329,+1.918,+2.5};

  //int const netabinss=10; //for systematic
  //double binsetas[netabinss]={-2.5,-1.918,-1.2329,-0.908,-0.476,+0.476,+0.908,+1.2329,+1.918,+2.5};
  // int const netabinss=10; //for systematic
  //double binsetas[netabinss]={-2.5,-1.918,-1.623,-0.908,-0.476,+0.476,+0.908,+1.623,+1.918,+2.5};


  //ETA-PHI map bins
  //Eta and phi for the eta-phi distribution
  int const nbinsetabar=15;
  double etabinsbar[nbinsetabar]={-1.05,-0.908,-0.791,-0.652,-0.476,-0.324,-0.132,0.0,+0.132,+0.324,+0.476,+0.652,+0.791,+0.908,+1.05};

  int const nbinsetaend=16;
  double etabinsend[nbinsetaend]={-2.5,-2.4,-1.918,-1.623,-1.348,-1.2329,-1.1479,-1.05,+1.05,+1.1479,+1.2329,+1.348,+1.623,+1.918,+2.4,+2.5};

/*
  //Lets define what we need
  bool is_default  = (iscut==0);
  bool is_mass     = (iscut==1);
  bool is_positive = (iscut==2);
  bool is_negative = (iscut==3);
  bool is_newbin   = (iscut==4);
*/
   //Lets define what we need
  bool is_default       = (iscut==0);
  bool is_mass_up       = (iscut==1);
  bool is_mass_down     = (iscut==2);
  bool is_positive      = (iscut==3);
  bool is_negative      = (iscut==4);
  bool is_newbin        = (iscut==5);


  //Define the histogramm
  TH1D *probeetacutmu15;
  TH1D *probeetacutmu15_MU10;
  TH1D *probeetacutmu15_MU6;

  TH1D *probeetamu15;
  TH1D *probeetamu15_MU10;
  TH1D *probeetamu15_MU6;


  TH1D *probephibarcutmu15;
  TH1D *probephibarcutmu15_MU10;
  TH1D *probephibarcutmu15_MU6;

  TH1D *probephibarmu15;
  TH1D *probephibarmu15_MU10;
  TH1D *probephibarmu15_MU6;

  TH1D *probephiendcutmu15;
  TH1D *probephiendcutmu15_MU10;
  TH1D *probephiendcutmu15_MU6;

  TH1D *probephiendmu15;
  TH1D *probephiendmu15_MU10;
  TH1D *probephiendmu15_MU6;


  TH1D *probeptbar;
  TH1D *probeptend;
  TH1D *probeptbarmu15;
  TH1D *probeptbarmu15_MU10;
  TH1D *probeptbarmu15_MU6;

  TH1D *probeptendmu15;
  TH1D *probeptendmu15_MU10;
  TH1D *probeptendmu15_MU6;

/*
  TFile *out_default;
  if(is_default){out_default = new TFile(Form("%s/default.root",folders[name]),"RECREATE");}
  TFile *out_sys1;
  if(is_mass){out_sys1 = new TFile(Form("%s/mass.root",folders[name]),"RECREATE");}
  TFile *out_sys2;
  if(is_positive){out_sys2 = new TFile(Form("%s/positive.root",folders[name]),"RECREATE");}
  TFile *out_sys3;
  if(is_negative){out_sys3 = new TFile(Form("%s/negative.root",folders[name]),"RECREATE");}
  TFile *out_newbin;
  if(is_newbin){out_newbin = new TFile(Form("%s/newbin.root",folders[name]),"RECREATE");}
*/

  TFile *out_default;
  if(is_default){out_default = new TFile(Form("%s/default.root",folders[name]),"RECREATE");}
  TFile *out_sys1;
  if(is_mass_up){out_sys1 = new TFile(Form("%s/mass_up.root",folders[name]),"RECREATE");}
   TFile *out_sys2;
  if(is_mass_down){out_sys2 = new TFile(Form("%s/mass_down.root",folders[name]),"RECREATE");}
  TFile *out_sys3;
  if(is_positive){out_sys3 = new TFile(Form("%s/positive.root",folders[name]),"RECREATE");}
  TFile *out_sys4;
  if(is_negative){out_sys4 = new TFile(Form("%s/negative.root",folders[name]),"RECREATE");}
  TFile *out_newbin;
  if(is_newbin){out_newbin = new TFile(Form("%s/newbin.root",folders[name]),"RECREATE");}

   if(is_default)
    {
        cout<<"I am fillin the default"<<endl;
      	//All probes
  		probeetacutmu15     =new TH1D("probeetacutmu15","probeetacut15",netabins-1,binseta);
  		probeetacutmu15_MU10 =new TH1D("probeetacutmu15_MU10","probeetacut15_MU10",netabins-1,binseta);
  		probeetacutmu15_MU6  =new TH1D("probeetacutmu15_MU6","probeetacut15_MU6",netabins-1,binseta);


  		//Matched to ntrigger
  		probeetamu15=new TH1D("probeetamu15","probeetamu15",netabins-1,binseta);
  		probeetamu15_MU10=new TH1D("probeetamu15_MU10","probeetamu15_MU10",netabins-1,binseta);
  		probeetamu15_MU6=new TH1D("probeetamu15_MU6","probeetamu15_MU6",netabins-1,binseta);
  		////////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////////////////////
  		//PHI///////////////////////////////////////////////////////////////////////////////////////////////
  		//BARRELL----------------------------------------------------------------------------------------------------------------------
  		//All probes
  		probephibarcutmu15=new TH1D("probephibarcutmu15","Probe muon #phi distribution for barrel region",16,-2.945243,3.337942);//probe phi barrel
  		probephibarcutmu15_MU10=new TH1D("probephibarcutmu15_MU10","Probe muon #phi distribution for barrel region",16,-2.945243,3.337942);//probe phi barrel
  		probephibarcutmu15_MU6=new TH1D("probephibarcutmu15_MU6","Probe muon #phi distribution for barrel region",16,-2.945243,3.337942);//probe phi barrel

  		//matched to ntrigger
  		probephibarmu15=new TH1D("probephibarmu15","probephibarmu15",16,-2.945243,3.337942);
  		probephibarmu15_MU10=new TH1D("probephibarmu15_MU10","probephibarmu15MU15",16,-2.945243,3.337942);
  		probephibarmu15_MU6=new TH1D("probephibarmu15_MU6","probephibarmu15_MU6",16,-2.945243,3.337942);


   		//ENDCUP----------------------------------------------------------------------------------------------------------------------
   		//All probes
  		probephiendcutmu15=new TH1D("probephiendcutmu15","Probe muon #phi distribution for endcap region",12,-3.403392,2.879793);//probe phi endcap
  		probephiendcutmu15_MU10=new TH1D("probephiendcutmu15_MU10","Probe muon #phi distribution for endcap region",12,-3.403392,2.879793);//probe phi endcap
  		probephiendcutmu15_MU6=new TH1D("probephiendcutmu15_MU6","Probe muon #phi distribution for endcap region",12,-3.403392,2.879793);//probe phi endcap


  		//Matched to the ntrigger
  		probephiendmu15=new TH1D("probephiendmu15","probephiendmu15",12,-3.403392,2.879793);
  		probephiendmu15_MU10=new TH1D("probephiendmu15_MU10","probephiendmu15_MU10",12,-3.403392,2.879793);
  		probephiendmu15_MU6=new TH1D("probephiendmu15_MU6","probephiendmu15_MU6",12,-3.403392,2.879793);
  		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    }

    if(is_mass_up || is_mass_down || is_positive || is_negative || is_newbin)
    {    cout<<"I am fillin with "<<iscut<<endl;
      	//All probes
  		probeetacutmu15     =new TH1D("probeetacutmu15","probeetacut15",netabinss-1,binsetas);
  		probeetacutmu15_MU10 =new TH1D("probeetacutmu15_MU10","probeetacut15_MU10",netabinss-1,binsetas);
  		probeetacutmu15_MU6  =new TH1D("probeetacutmu15_MU6","probeetacut15_MU6",netabinss-1,binsetas);


  		//Matched to ntrigger
  		probeetamu15=new TH1D("probeetamu15","probeetamu15",netabinss-1,binsetas);
  		probeetamu15_MU10=new TH1D("probeetamu15_MU10","probeetamu15_MU10",netabinss-1,binsetas);
  		probeetamu15_MU6=new TH1D("probeetamu15_MU6","probeetamu15_MU6",netabinss-1,binsetas);
  		////////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////////////////////
  		//PHI///////////////////////////////////////////////////////////////////////////////////////////////
  		//BARRELL----------------------------------------------------------------------------------------------------------------------
  		//All probes
  		probephibarcutmu15=new TH1D("probephibarcutmu15","Probe muon #phi distribution for barrel region",8,-2.945243,3.337942);//probe phi barrel
  		probephibarcutmu15_MU10=new TH1D("probephibarcutmu15_MU10","Probe muon #phi distribution for barrel region",8,-2.945243,3.337942);//probe phi barrel
  		probephibarcutmu15_MU6=new TH1D("probephibarcutmu15_MU6","Probe muon #phi distribution for barrel region",8,-2.945243,3.337942);//probe phi barrel

  		//matched to ntrigger
  		probephibarmu15=new TH1D("probephibarmu15","probephibarmu15",8,-2.945243,3.337942);
  		probephibarmu15_MU10=new TH1D("probephibarmu15_MU10","probephibarmu15MU15",8,-2.945243,3.337942);
  		probephibarmu15_MU6=new TH1D("probephibarmu15_MU6","probephibarmu15_MU6",8,-2.945243,3.337942);


   		//ENDCUP----------------------------------------------------------------------------------------------------------------------
   		//All probes
  		probephiendcutmu15=new TH1D("probephiendcutmu15","Probe muon #phi distribution for endcap region",6,-3.403392,2.879793);//probe phi endcap
  		probephiendcutmu15_MU10=new TH1D("probephiendcutmu15_MU10","Probe muon #phi distribution for endcap region",6,-3.403392,2.879793);//probe phi endcap
  		probephiendcutmu15_MU6=new TH1D("probephiendcutmu15_MU6","Probe muon #phi distribution for endcap region",6,-3.403392,2.879793);//probe phi endcap


  		//Matched to the ntrigger
  		probephiendmu15=new TH1D("probephiendmu15","probephiendmu15",6,-3.403392,2.879793);
  		probephiendmu15_MU10=new TH1D("probephiendmu15_MU10","probephiendmu15_MU10",6,-3.403392,2.879793);
  		probephiendmu15_MU6=new TH1D("probephiendmu15_MU6","probephiendmu15_MU10",6,-3.403392,2.879793);
  		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //PT/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //All probes
  probeptbar = new TH1D("probeptbar","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  probeptend = new TH1D("probeptend","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt

  //matched to the ntrigger --BARREL
  probeptbarmu15 = new TH1D("probeptbarmu15","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  probeptbarmu15_MU10=new TH1D("probeptbarmu15_MU10","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  probeptbarmu15_MU6=new TH1D("probeptbarmu15_MU6","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt


  //matched to the ntrigger --ENDCAP
  probeptendmu15=new TH1D("probeptendmu15","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  probeptendmu15_MU10=new TH1D("probeptendmu15_MU10","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  probeptendmu15_MU6=new TH1D("probeptendmu15_MU6","Probe muon p_{T} distribution [GeV]",nptbins-1,binspt); //Ptobe pt
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 /*
  //Number of vertices ALL - BARREL
  TH1D *probeverbartcut8=new TH1D("probeverbartcut8","probevertcut8",9,1.5,10.5);
  TH1D *probeverbartcut15=new TH1D("probeverbartcut15","probevertcut155",9,1.5,10.5);
  TH1D *probeverbartcut15_MU10=new TH1D("probeverbartcut15_MU10","probevertcut15_MU10",9,1.5,10.5);
  TH1D *probeverbartcut15_MU6=new TH1D("probeverbartcut15_MU6","probevertcut15_MU6",9,1.5,10.5);
  TH1D *probeverbartcut10MU6=new TH1D("probeverbartcut10MU6","probevertcut10MU6",9,1.5,10.5);


   //Number of vertices matched to the ntrigger - BARREL

  TH1D *probeverbartmu8=new TH1D("probeverbartmu8","probevertmu80",9,1.5,10.5);
  TH1D *probeverbartmu15=new TH1D("probeverbartmu15","probevertmu15",9,1.5,10.5);
  TH1D *probeverbartmu15_MU10=new TH1D("probeverbartmu15_MU10","probevertmu15_MU10",9,1.5,10.5);
  TH1D *probeverbartmu15_MU6=new TH1D("probeverbartmu15_MU6","probevertmu15_MU6",9,1.5,10.5);
  TH1D *probeverbartmu10MU6=new TH1D("probeverbartmu10MU6","probevertmu10MU6",9,1.5,10.5);
  ////////////////////////////////////////////////////////////////////////////////////////////////////


   //Number of vertices ALL - ENDCAP
  TH1D *probeverendtcut8=new TH1D("probeverendtcut8","probevertcut8",9,1.5,10.5);
  TH1D *probeverendtcut15=new TH1D("probeverendtcut15","probevertcut155",9,1.5,10.5);
  TH1D *probeverendtcut15_MU10=new TH1D("probeverendtcut15_MU10","probevertcut15_MU10",9,1.5,10.5);
  TH1D *probeverendtcut15_MU6=new TH1D("probeverendtcut15_MU6","probevertcut15_MU6",9,1.5,10.5);
  TH1D *probeverendtcut10MU6=new TH1D("probeverendtcut10MU6","probevertcut10MU6",9,1.5,10.5);


   //Number of vertices matched to the ntrigger - ENDCAP

  TH1D *probeverendtmu8=new TH1D("probeverendtmu8","probevertmu80",9,1.5,10.5);
  TH1D *probeverendtmu15=new TH1D("probeverendtmu15","probevertmu15",9,1.5,10.5);
  TH1D *probeverendtmu15_MU10=new TH1D("probeverendtmu15_MU10","probevertmu15_MU10",9,1.5,10.5);
  TH1D *probeverendtmu15_MU6=new TH1D("probeverendtmu15_MU6","probevertmu15_MU6",9,1.5,10.5);
  TH1D *probeverendtmu10MU6=new TH1D("probeverendtmu10MU6","probevertmu10MU6",9,1.5,10.5);
*/



/*
   /////////////////////////////////////////////////////////////////////////////////////////////////////////
  //ETA PHI map:////////////////////////////////////////////////////////////////////////////////////////////
  //BARRELL

  TH2D *etaphibar15 = new TH2D("etaphibar15","Eta-phi probe mu",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibar15_MU10 = new TH2D("etaphibar15_MU10","Eta-phi probe mu",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibar15_MU6  = new TH2D("etaphibar15_MU6","Eta-phi probe mu",nbinsetabar-1,etabinsbar,8,-3.14,3.14);



  //ENDCAUP
  TH2D *etaphiend8  = new TH2D("etaphiend8", "Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  //TH2D *etaphiend10 = new TH2D("etaphiend10","Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiend15 = new TH2D("etaphiend15","Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiend15_MU10 = new TH2D("etaphiend15_MU10","Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiend15_MU6  = new TH2D("etaphiend15_MU6","Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiend10MU6  = new TH2D("etaphiend10MU6","Eta-phi probe mu",nbinsetaend-1,etabinsend,12,-3.14,3.14);

  //BARREL triggers
  TH2D *etaphibarmu8  = new TH2D("etaphibarmu8","Eta-phi probe mu8",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  //TH2D *etaphibarmu10 = new TH2D("etaphibarmu10","Eta-phi probe mu10",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibarmu15 = new TH2D("etaphibarmu15","Eta-phi probe mu15",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibarmu15_MU10 = new TH2D("etaphibarmu15_MU10","Eta-phi probe mu15",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibarmu15_MU6  = new TH2D("etaphibarmu15_MU6","Eta-phi probe mu15",nbinsetabar-1,etabinsbar,8,-3.14,3.14);
  TH2D *etaphibarmu10MU6  = new TH2D("etaphibarmu10MU6","Eta-phi probe mu15",nbinsetabar-1,etabinsbar,8,-3.14,3.14);


  //ENDCAP triggers
  TH2D *etaphiendmu8  = new TH2D("etaphiendmu8", "Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  //TH2D *etaphiendmu10 = new TH2D("etaphiendmu10","Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiendmu15 = new TH2D("etaphiendmu15","Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiendmu15_MU10 = new TH2D("etaphiendmu15_MU10","Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiendmu15_MU6  = new TH2D("etaphiendmu15_MU6","Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  TH2D *etaphiendmu10MU6  = new TH2D("etaphiendmu10MU6","Eta-phi probe mu8",nbinsetaend-1,etabinsend,12,-3.14,3.14);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

  //define the parameters
  //const int ntrig = 3;
  //char triggers [ntrig][200]= {"mu15","mu15_MU10","mu15_MU6"};
  //eta~~~~~~~~~~~~
  char  names_eta_all [ntrig][200];
  char  names_eta_ntrig[ntrig][200];
  //pt~~~~~~~~~~~~~~
  char  names_pt_bar_all[200] = {"mu_pt_probe>>probeptbar"};
  char  names_pt_end_all[200] = {"mu_pt_probe>>probeptend"};
  char  names_pt_bar_ntrig[ntrig][200];
  char  names_pt_end_ntrig[ntrig][200];
  //phi~~~~~~~~~~~~~
  char  names_phi_bar_all[ntrig][200];
  char  names_phi_end_all[ntrig][200];
  char  names_phi_bar_ntrig[ntrig][200];
  char  names_phi_end_ntrig[ntrig][200];

  //The sets of cuts for the histos
  //eta/////-----------------------
  char cut_def_eta_all[2000]  = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101."};
  //char cut_mas_eta_all[2000]    = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_up_eta_all[2000]    = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_down_eta_all[2000]  = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>76. && pairm<116."};
  char cut_pos_eta_all[2000]  = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe>0."};
  char cut_neg_eta_all[2000]  = {"mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe<0."};

  char cut_def_eta_ntrig[ntrig][3000];
  //char cut_mas_eta_ntrig[ntrig][3000];
  char cut_mas_up_eta_ntrig[ntrig][3000];
  char cut_mas_down_eta_ntrig[ntrig][3000];
  char cut_pos_eta_ntrig[ntrig][3000];
  char cut_neg_eta_ntrig[ntrig][3000];

  //cuts for phi ///------------------
  char cut_def_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101."};
  //char cut_mas_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_up_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_down_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>76. && pairm<116."};
  char cut_pos_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe>0."};
  char cut_neg_phi_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe<0."};


  char cut_def_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101."};
  //char cut_mas_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_up_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_mas_down_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>76. && pairm<116."};
  char cut_pos_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe>0."};
  char cut_neg_phi_end_all[3000]  = {"abs(mu_eta_probe)>=1.05  && abs(mu_eta_probe)<=2.5 && mu_pt_probe>17 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe<0."};


  char cut_def_phi_bar_ntrig[ntrig][3000];
  //char cut_mas_phi_bar_ntrig[ntrig][3000];
  char cut_mas_up_phi_bar_ntrig[ntrig][3000];
  char cut_mas_down_phi_bar_ntrig[ntrig][3000];
  char cut_neg_phi_bar_ntrig[ntrig][3000];
  char cut_pos_phi_bar_ntrig[ntrig][3000];

  char cut_def_phi_end_ntrig[ntrig][3000];
  //char cut_mas_phi_end_ntrig[ntrig][3000];
  char cut_mas_up_phi_end_ntrig[ntrig][3000];
  char cut_mas_down_phi_end_ntrig[ntrig][3000];
  char cut_neg_phi_end_ntrig[ntrig][3000];
  char cut_pos_phi_end_ntrig[ntrig][3000];

  //cuts for pt//////--------------------
  char cut_def_pt_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101."};
  char cut_mas_pt_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_pos_pt_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe>0."};
  char cut_neg_pt_bar_all[2000]  = {"abs(mu_eta_probe)<=1.05 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe<0."};


  char cut_def_pt_end_all[200]  = {"abs(mu_eta_probe)>=1.05 && abs(mu_eta_probe)<=2.5 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101."};
  char cut_mas_pt_end_all[2000]  = {"abs(mu_eta_probe)>=1.05 && abs(mu_eta_probe)<=2.5 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>86. && pairm<96."};
  char cut_pos_pt_end_all[2000]  = {"abs(mu_eta_probe)>=1.05 && abs(mu_eta_probe)<=2.5 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe>0."};
  char cut_neg_pt_end_all[2000]  = {"abs(mu_eta_probe)>=1.05 && abs(mu_eta_probe)<=2.5 && mu_medium_tag ==1 && mu_medium_probe ==1 && pairm>81. && pairm<101. && mu_q_probe<0."};


  char cut_def_pt_bar_ntrig[ntrig][3000];
  char cut_mas_pt_bar_ntrig[ntrig][3000];
  char cut_neg_pt_bar_ntrig[ntrig][3000];
  char cut_pos_pt_bar_ntrig[ntrig][3000];

  char cut_def_pt_end_ntrig[ntrig][3000];
  char cut_mas_pt_end_ntrig[ntrig][3000];
  char cut_neg_pt_end_ntrig[ntrig][3000];
  char cut_pos_pt_end_ntrig[ntrig][3000];

  for(int i = 0; i<ntrig; ++i)
    {
        //those are the first parameters in the tree filling
        sprintf(names_eta_all[i],"mu_eta_probe>>probeetacut%s",triggers[i]);//all probes this will give me mu_eta_probe>>probeetacutmu15 for different ntriggerd
        sprintf(names_eta_ntrig[i],"mu_eta_probe>>probeeta%s",triggers[i]);//matched probes

        sprintf(names_pt_bar_ntrig[i],"mu_pt_probe>>probeptbar%s",triggers[i]);//matched barrel probes
        sprintf(names_pt_end_ntrig[i],"mu_pt_probe>>probeptend%s",triggers[i]);//matched endcap probes

        sprintf(names_phi_bar_all[i],"mu_phi_probe>>probephibarcut%s",triggers[i]);//all barrel probes
        sprintf(names_phi_end_all[i],"mu_phi_probe>>probephiendcut%s",triggers[i]);//all barrel probes

        sprintf(names_phi_bar_ntrig[i],"mu_phi_probe>>probephibar%s",triggers[i]);//matched barrel probes
        sprintf(names_phi_end_ntrig[i],"mu_phi_probe>>probephiend%s",triggers[i]);//matched barrel probes

        //second parameters in the treee
        //eta
        sprintf(cut_def_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_def_eta_all,triggers[i]); //at the end it will give me all the cuts plus the cut on the ntrigger//for the default
        //sprintf(cut_mas_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_eta_all,triggers[i]); //for the mass syst
        sprintf(cut_mas_up_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_up_eta_all,triggers[i]); //for the mass syst
        sprintf(cut_mas_down_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_down_eta_all,triggers[i]); //for the mass syst
        sprintf(cut_pos_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_pos_eta_all,triggers[i]); //for the positive syst
        sprintf(cut_neg_eta_ntrig[i],"%s && muon_probe_%s<=0.01",cut_neg_eta_all,triggers[i]); //for the negative syst

        //phi
        sprintf(cut_def_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_def_phi_bar_all,triggers[i]);
        //sprintf(cut_mas_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_phi_bar_all,triggers[i]);
        sprintf(cut_mas_up_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_up_phi_bar_all,triggers[i]);
        sprintf(cut_mas_down_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_down_phi_bar_all,triggers[i]);
        sprintf(cut_pos_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_pos_phi_bar_all,triggers[i]);
        sprintf(cut_neg_phi_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_neg_phi_bar_all,triggers[i]);

        sprintf(cut_def_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_def_phi_end_all,triggers[i]);
        //sprintf(cut_mas_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_phi_end_all,triggers[i]);
        sprintf(cut_mas_up_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_up_phi_end_all,triggers[i]);
        sprintf(cut_mas_down_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_down_phi_end_all,triggers[i]);
        sprintf(cut_pos_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_pos_phi_end_all,triggers[i]);
        sprintf(cut_neg_phi_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_neg_phi_end_all,triggers[i]);

        //pt
        sprintf(cut_def_pt_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_def_pt_bar_all,triggers[i]);
        sprintf(cut_mas_pt_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_pt_bar_all,triggers[i]);
        sprintf(cut_pos_pt_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_pos_pt_bar_all,triggers[i]);
        sprintf(cut_neg_pt_bar_ntrig[i],"%s && muon_probe_%s<=0.01",cut_neg_pt_bar_all,triggers[i]);

        sprintf(cut_def_pt_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_def_pt_end_all,triggers[i]);
        sprintf(cut_mas_pt_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_mas_pt_end_all,triggers[i]);
        sprintf(cut_pos_pt_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_pos_pt_end_all,triggers[i]);
        sprintf(cut_neg_pt_end_ntrig[i],"%s && muon_probe_%s<=0.01",cut_neg_pt_end_all,triggers[i]);
    }
    //filling the default histo with the right binning
    if(is_default)
       {    //loop over all triggers
            for(int i = 0; i<ntrig; ++i)
               	{
             		//fill the histograms from the tree
             		//eta------
             		treee->Draw(names_eta_all[i],cut_def_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_def_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_def_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_def_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_def_phi_bar_ntrig[i]);//for matched probes
             		treee->Draw(names_phi_end_ntrig[i],cut_def_phi_end_ntrig[i]);//for matched probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_def_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_def_pt_end_ntrig[i]);
             	}
            //pt denominator
            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the default tree//////////////////////////
            out_default->Write();
            out_default->Close();
        }

        // the tree with the new bins but the same default cuts
       if(is_newbin)
       {
            for(int i = 0; i<ntrig; ++i)
               	{
             		//eta------
             		treee->Draw(names_eta_all[i],cut_def_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_def_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_def_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_def_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_def_phi_bar_ntrig[i]);//for matched probes
             		treee->Draw(names_phi_end_ntrig[i],cut_def_phi_end_ntrig[i]);//for matched probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_def_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_def_pt_end_ntrig[i]);
             	}

            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the newbins tree//////////////////////////
            out_newbin->Write();
            out_newbin->Close();
        }

    //filling the mass cut
    if(is_mass_up)
        {
            for(int i = 0; i<ntrig; ++i)
             	{
             		//eta------
             		treee->Draw(names_eta_all[i],cut_mas_up_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_mas_up_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_mas_up_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_mas_up_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_mas_up_phi_bar_ntrig[i]);//for all probes
             		treee->Draw(names_phi_end_ntrig[i],cut_mas_up_phi_end_ntrig[i]);//for all probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_mas_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_mas_pt_end_ntrig[i]);
              	}

            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the mass tree//////////////////////////
            out_sys1->Write();
            out_sys1->Close();
        }


    //filling the mass cut
    if(is_mass_down)
        {
            for(int i = 0; i<ntrig; ++i)
             	{
             		//eta------
             		treee->Draw(names_eta_all[i],cut_mas_down_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_mas_down_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_mas_down_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_mas_down_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_mas_down_phi_bar_ntrig[i]);//for all probes
             		treee->Draw(names_phi_end_ntrig[i],cut_mas_down_phi_end_ntrig[i]);//for all probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_mas_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_mas_pt_end_ntrig[i]);
              	}

            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the mass tree//////////////////////////
            out_sys2->Write();
            out_sys2->Close();
        }
     //filling with the positive
    if(is_positive)
        {
            for(int i = 0; i<ntrig; ++i)
             	{
             		//eta------
             		treee->Draw(names_eta_all[i],cut_pos_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_pos_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_pos_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_pos_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_pos_phi_bar_ntrig[i]);//for all probes
             		treee->Draw(names_phi_end_ntrig[i],cut_pos_phi_end_ntrig[i]);//for all probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_pos_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_pos_pt_end_ntrig[i]);
             	}
            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the positive muons tree//////////////////////////
            out_sys3->Write();
            out_sys3->Close();
        }
    //filling with the negative
    if(is_negative)
        {
            for(int i = 0; i<ntrig; ++i)
             	{
             		//eta------
             		treee->Draw(names_eta_all[i],cut_neg_eta_all);//for all probes
             		treee->Draw(names_eta_ntrig[i],cut_neg_eta_ntrig[i]);//for matched probes

             		//phi------
             		treee->Draw(names_phi_bar_all[i],cut_neg_phi_bar_all);//for all probes
             		treee->Draw(names_phi_end_all[i],cut_neg_phi_end_all);//for all probes

             		treee->Draw(names_phi_bar_ntrig[i],cut_neg_phi_bar_ntrig[i]);//for all probes
             		treee->Draw(names_phi_end_ntrig[i],cut_neg_phi_end_ntrig[i]);//for all probes

             		//pt-------
             		treee->Draw(names_pt_bar_ntrig[i],cut_neg_pt_bar_ntrig[i]);
             		treee->Draw(names_pt_end_ntrig[i],cut_neg_pt_end_ntrig[i]);
             	}

            treee->Draw(names_pt_bar_all,cut_def_pt_bar_all);
     	    treee->Draw(names_pt_end_all,cut_def_pt_end_all);
            ////////////////////////////fill in the negative tree//////////////////////////
            out_sys4->Write();
            out_sys4->Close();
        }

}

//run over all names and over the all files
void run(TFile *file, int n)//will open the file you have specified in runall.cxx
{
  probe(file,0,n);
  probe(file,1,n);
  probe(file,2,n);
  probe(file,3,n);
  probe(file,4,n);
  probe(file,5,n);
}

