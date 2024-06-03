////////////////////////////////////////////////////////////////////////Trigger SF code for the systematcic SF studies//////////////////////////////////////////////////////
//This code will make for you the SF for the muon triggers you like, if you change the trigger name
//Also it will provide for you the systematic uncertainty for the chosen triggers
//In case of not clear understanding what is going on please contact me: anna.ivina@cern.ch
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Some names in the files
//Names of folders for efficiency (data and mc)
//Please specify here the MC and data you want to use
//the root files for data are Data_high_pt_period[x]_v6.root ,periodB,periodC..
//the root files for mc are MC_high_pt_[x]_v6.root, e5366,35367...

//pPb - period B; Pbp - period C;
//period B - e5367;
const int n1=1;
char name_datafile[n1][200]={"periodB"};//for data
const int n2=1;
//char name_mcfile[n2][200]={"e5366"};//for MC
char name_mcfile[n2][200]={"pPb"};//for MC with data overlaid
const int n=2;
char folders[n][200];
//names for the folders for SF
//we choose nd=5 //since we have 3 systematics + one default binning + one binning to reduce the systematic
//const int nd=5;
const int nd=6; //0        1       2          3         4
//char sffolders[nd][200] = {"default","mass","positive","negative","newbin"};
char sffolders[nd][200] = {"default","mass_up","mass_down","positive","negative","newbin"};
//for the ratios
//we use nsfb=3 since we have only 3 systematics
//const int nsfb = 3;
const int nsfb = 4;
char ratiosfb[nsfb][300] ;
//for the total systematics and SF plotting
//we use finalb=3 since we have only 3 systematics
//const int finalb = 3;
const int finalb = 4;
char sfactorsb[finalb][500];

//Here please you see the triggerrs we use
//Names for the triggers(we have 3 triggers)
const int ntrig = 3;
char triggers [ntrig][200]=   {"mu15","mu15_MU10","mu15_MU6"};//for the histograms in the probe.cxx
char fnames   [ntrig][200]  = {"HLT_mu15","HLT_mu15_MU10","HLT_mu15_MU6"};//for the plotting in SF.cxx
char etaden [ntrig]  [200]  = {"probeetacutmu15","probeetacutmu15_MU10","probeetacutmu15_MU6"};//eta - znamenatel
char etanum [ntrig]  [200]  = {"probeetamu15","probeetamu15_MU10","probeetamu15_MU6"};//eta - hislitel

char ptbarr [ntrig]  [200]  = {"probeptbarmu15","probeptbarmu15_MU10","probeptbarmu15_MU6"};//eta - znamenatel
char ptendc [ntrig]  [200]  = {"probeptendmu15","probeptendmu15_MU10","probeptendmu15_MU6"};//eta - hislitel

char phibarr [ntrig] [200]  = {"probephibarcutmu15","probephibarcutmu15_MU10","probephibarcutmu15_MU6"};
char phiendc [ntrig] [200]  = {"probephiendcutmu15","probephiendcutmu15_MU10","probephiendcutmu15_MU6"};

char phibarrmu [ntrig] [200]  = {"probephibarmu15","probephibarmu15_MU10","probephibarmu15_MU6"};
char phiendcmu [ntrig] [200]  = {"probephiendmu15","probephiendmu15_MU10","probephiendmu15_MU6"};

char sfeta[ntrig]   [200] = {"SF_0","SF_1","SF_2"};
char sfphibar[ntrig][200] = {"SFphibar_0","SFphibar_1","SFphibar_2"};
char sfphiend[ntrig][200] = {"SFphiend_0","SFphiend_1","SFphiend_2"};

//include
#include "runall.h"

//Run each file - probe
void runefficiency(int name)
    {
        sprintf(folders[0],"Efficiency_%s",name_mcfile[0]);
        sprintf(folders[1],"Efficiency_%s",name_datafile[0]);
       	system(Form("mkdir -p %s",folders[name]));
    	TFile *file;
    	//if(name==0){file= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/data/MC_high_pt_%s_v6.root",name_mcfile[0]));}//MC
    	//if(name==0){file= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/Ntuple_eff_maker/MC_high_%s.root",name_mcfile[0]));}//MC with data overlaid
    	//if(name==1){file= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/data/Data_high_pt_%s_v6.root",name_datafile[0]));}//Data
    	//call the file
    	if(name==1){file= new TFile(Form("/srv01/cgrp/users/annai/annai/SM_higgs/SF_for_charged/Analysis/HighPt_pPb_%s_v15.root",name_datafile[0]));}//Data version15
    	run(file,name);
	}

//Scale factors - SF.cxx
void runSF()
	{
    	TFile *file1;//data
    	TFile *file2;//mc
    	for(int i=0;i<nd;i++)
    		{
    		    system(Form("mkdir -p %s",sffolders[i]));
        		file1= new TFile(Form("/srv01/cgrp/users/annai/annai/SM_higgs/SF_for_charged/Analysis/NewNtuples_Hight_pT/%s/%s.root",folders[1],sffolders[i]));
                //file2= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/%s/%s.root",folders[0],sffolders[i]));
        		//SF(file1,file2,i);
        		SF(file1,i);
        		cout<<"I am in "<<i<<endl;
    		}
	}
/*
//ratios -- ratiosf.cxx
void runratios()
   {    //sprintf(ratiosfb[0],"SF_%s_mass.root",name_datafile[0]);
        sprintf(ratiosfb[0],"SF_%s_mass_up.root",name_datafile[0]);
        sprintf(ratiosfb[1],"SF_%s_mass_down.root",name_datafile[0]);
        sprintf(ratiosfb[2],"SF_%s_mupos.root",name_datafile[0]);
        sprintf(ratiosfb[3],"SF_%s_muneg.root",name_datafile[0]);
    	TFile *file1;//default_new_bin
    	TFile *file2;//systematic
    	system("mkdir -p relative");
    	for(int i=1;i<nd-1;++i)
    		{																																				//folred4 if only mass
        		file1 = new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/%s/SF_%s_new_eta_phi.root",sffolders[5],name_datafile[0]));
                file2 = new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/%s/%s",sffolders[i],ratiosfb[i-1]));
                ratiosf(file1,file2,i);
    		}
	}


//Scale factors including systematic - SFfullsyst.cxx
void runfullsyst()
    {
        //sprintf(sfactorsb[0],"%s_mass.root",name_datafile[0]);
        sprintf(sfactorsb[0],"%s_mass_up.root",name_datafile[0]);
        sprintf(sfactorsb[1],"%s_mass_down.root",name_datafile[0]);
        sprintf(sfactorsb[2],"%s_positive.root",name_datafile[0]);
        sprintf(sfactorsb[3],"%s_negative.root",name_datafile[0]);
        TFile *file1;//data
    	TFile *file2;//mc
        TFile *file3;//system period B or C
        TFile *file4;
        TFile *file5;
        TFile *file6;
        //char version [300]= {"From14Jan"};
        //system(Form("mkdir -p plots_%s",version));
        //system(Form("mkdir -p %s",vers.c_str()));
        file1= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/%s/%s.root",folders[1],sffolders[0]));
        file2= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/%s/%s.root",folders[0],sffolders[0]));
        //file3= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/relative/%s",sfactorsb[0]));//mass
        file3= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/relative/%s",sfactorsb[0]));//mass
        file4= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/relative/%s",sfactorsb[1]));//mass
        file5= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/relative/%s",sfactorsb[2]));//negative
        file6= new TFile(Form("/srv01/cgrp/users/annai/annai/Scale_Factors/Analysis_ZmumuMC2016/NewNtuples_Hight_pT/relative/%s",sfactorsb[3]));//positive
        SFfullsyst(file1,file2,file3,file4,file5,file6);
    }
*/
//Run all of them together for different periods and so on
//probe.xx
void runallefficiencyfiles()
	{
    	//runefficiency(0);
        runefficiency(1);

    	cout<<"================================================"<<endl;
    	cout<<"/////////I am done with the histograms//////////"<<endl;
    	cout<<"================================================"<<endl;

    }

//SF
void runallsffiles()
	{
    	runSF();
    	//runSF(1);

    	cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    	cout<<"///////////////////////////I am done with the SF////////////////////"<<endl;
    	cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
	}
/*
void runallratios()
	{
    	runratios();


    	cout<<"#####################################################################################"<<endl;
    	cout<<"///////////////////////////I am done with  estimating systematics////////////////////"<<endl;
    	cout<<"#####################################################################################"<<endl;
	}

void runfullsystematics()
    {
        runfullsyst();


    }
*/

void runall()
{
    runallefficiencyfiles();
     runallsffiles();
   //runallratios();
    //runfullsystematics();
    cout<<"######################################################################"<<endl;
    cout<<"///////////////////////////The worker has finished////////////////////"<<endl;
    cout<<"######################################################################"<<endl;
}

