using namespace std;

//void SF(TFile *file, TFile *file1,int names)//period (0 or 1), names(0,1,2 or 3), var(0 or 1)
void SF(TFile *file,int names)//period (0 or 1), names(0,1,2 or 3), var(0 or 1)
{
 cout<<"====================================================="<<endl;
 cout<<"Entering the SF.cxx to calculate the efficiency and SF"<<endl;
 cout<<"======================================================"<<endl;
 gStyle->Reset();
 SetAtlasStyle();
 gStyle->SetPalette(1);

 //colours and markers
 int col[4]={kAzure-3, kPink +9, kBlack, kRed};
 int mar[2]={20,34};
 const int datamc = 2;
 const int ratio  = 2;


 /////////////////////////////////////////////////////////////////////
 ///////////////////////////saving the histograms////////////////////
 ////////////////////////////////////////////////////////////////////
 //===================================for ETA==================================
 TFile  *ntuple;
 if(names==0) {ntuple=new TFile(Form("default/SF_%s_eta_phi.root",name_datafile[0]),"RECREATE");}
 //if(names==1) {ntuple=new TFile(Form("mass/SF_%s_mass.root",name_datafile[0]),"RECREATE");}
 if(names==1) {ntuple=new TFile(Form("mass_up/SF_%s_mass_up.root",name_datafile[0]),"RECREATE");}
 if(names==2) {ntuple=new TFile(Form("mass_down/SF_%s_mass_down.root",name_datafile[0]),"RECREATE");}
 if(names==3) {ntuple=new TFile(Form("positive/SF_%s_mupos.root",name_datafile[0]),"RECREATE");}
 if(names==4) {ntuple=new TFile(Form("negative/SF_%s_muneg.root",name_datafile[0]),"RECREATE");}
 if(names==5) {ntuple=new TFile(Form("newbin/SF_%s_new_eta_phi.root",name_datafile[0]),"RECREATE");}


 cout<<"====================================================="<<endl;
 cout<<"~~~~~~~~~~~>Starting with extracting the histograms ....."<<endl;
 cout<<"====================================================="<<endl;

 //The histograms
 //eta
 TH1D *eta[ntrig];//znamenatel -data
 TH1D *etaMC[ntrig];//znamenatel - MC

 TH1D *etamu[ntrig];//hislitel - data
 TH1D *etamuMC[ntrig];//hislitel - MC

 //pt//pt  - barrel
 TH1D *ptbarmu[ntrig];//hislitel - data
 TH1D *ptbarmuMC[ntrig];//hislitel - MC

 TH1D *ptendmu[ntrig];//hislitel - data - endcap
 TH1D *ptendmuMC[ntrig];//hislitel - MC - endcap

 TH1D *ptbar  =(TH1D*)file->Get("probeptbar");//znamenatel - data - barrel
 ptbar->Sumw2();

 TH1D *ptend  =(TH1D*)file->Get("probeptend");//znamenatel - data - endcap
 ptend->Sumw2();


 //phi - barrel
 TH1D *phibar[ntrig];//znamenatel - data - barrel
 TH1D *phibarMC[ntrig];//znamenatel - MC -barrel
 TH1D *phibarmu[ntrig];//hislitel - data - barrel
 TH1D *phibarmuMC[ntrig];//hislitel - MC - barrel
 //phi - endcap
 TH1D *phiend[ntrig];//znamenatel - data - endcap
 TH1D *phiendMC[ntrig];// znamenatel - MC - endcap
 TH1D *phiendmu[ntrig];// hislitel - data - endcap
 TH1D *phiendmuMC[ntrig];//hislitel - MC - endcap


 for(int i = 0; i<ntrig; ++i)
    {
        //Znamenatel
 		eta  [i] = (TH1D*)file->Get(Form("%s",etaden[i]));
 		eta  [i] ->Sumw2();

 	    phibar[i] = (TH1D*)file->Get(Form("%s",phibarr[i]));
 	    phibar[i] ->Sumw2();
 	    phiend[i] = (TH1D*)file->Get(Form("%s",phiendc[i]));
 	    phiend[i] ->Sumw2();

 	    //Hislitel
 	    etamu  [i] = (TH1D*)file->Get(Form("%s",etanum[i]));
 		etamu  [i] ->Sumw2();

 	    ptbarmu[i] = (TH1D*)file->Get(Form("%s",ptbarr[i]));
 	    ptbarmu[i] ->Sumw2();
 	    ptendmu[i] = (TH1D*)file->Get(Form("%s",ptendc[i]));
 	    ptendmu[i] ->Sumw2();

 	    phibarmu[i] = (TH1D*)file->Get(Form("%s",phibarrmu[i]));
 	    phibarmu[i] ->Sumw2();
 	    phiendmu[i] = (TH1D*)file->Get(Form("%s",phiendcmu[i]));
 	    phiendmu[i] ->Sumw2();

    }


 TH1D *etatot[ratio][datamc][ntrig]= {{{etamu[0],etamu[1],etamu[2]},{etamuMC[0],etamuMC[1],etamuMC[2]}},
                                  {{eta[0],eta[1],eta[2]},{etaMC[0],etaMC[1],etaMC[2]}}};


 TGraphAsymmErrors *eff[datamc][ntrig];
 TGraphAsymmErrors *SF [ntrig];
 TCanvas           *canvas[ntrig];
 TPad              *pad1[ntrig];
 TPad              *pad2[ntrig];
 TLegend           *leg[ntrig];
 TLegend           *legA[ntrig];
 TLine             *line1a[ntrig];
 TLine             *line1b[ntrig];


 TGraphAsymmErrors *effptbar[datamc][ntrig];
 TGraphAsymmErrors *SFptbar [ntrig];
 TCanvas           *canvas1[ntrig];
 TPad              *pad11[ntrig];
 TPad              *pad22[ntrig];
 TLegend           *leg2[ntrig];
 TLegend           *legC[ntrig];
 TLine             *line2a[ntrig];
 TLine             *line2b[ntrig];


TGraphAsymmErrors *effptend[datamc][ntrig];
 TGraphAsymmErrors *SFptend [ntrig];
 TCanvas           *canvas4[ntrig];
 TPad              *pad111[ntrig];
 TPad              *pad222[ntrig];
 TLegend           *leg5[ntrig];
 TLegend           *legE[ntrig];
 TLine             *line3a[ntrig];
 TLine             *line3b[ntrig];


 TGraphAsymmErrors *effphibar[datamc][ntrig];
 TGraphAsymmErrors *SFphibar [ntrig];
 TCanvas           *canvas10[ntrig];
 TPad              *pad10[ntrig];
 TPad              *pad20[ntrig];
 TLegend           *leg20[ntrig];
 TLegend           *legC20[ntrig];
 TLine             *line20[ntrig];

  TGraphAsymmErrors *effphiend[datamc][ntrig];
 TGraphAsymmErrors *SFphiend [ntrig];
 TCanvas           *canvas300[ntrig];
 TPad              *pad30[ntrig];
 TPad              *pad40[ntrig];
 TLegend           *leg40[ntrig];
 TLegend           *legC30[ntrig];
 TLine             *line30[ntrig];



 //Loop over the trigger collections
 for(int trig=0;trig<ntrig;++trig)
 {


    //Make the efficiency for both Data and MC for all triggers
    for(int dm=0; dm<datamc;++dm)
       {
         eff[dm][trig] = new TGraphAsymmErrors();
         eff[dm][trig]->BayesDivide(etatot[0][dm][trig],etatot[1][dm][trig]);


         /// HERE
	const int npoints=eff[dm][trig]->GetN();
	for(int b=0;b<npoints;++b)
	{
		double x,y,exl,exh,eyl,eyh;
		eff[dm][trig]->GetPoint(b,x,y);
		eyh=eff[dm][trig]->GetErrorYhigh(b);
		eyl=eff[dm][trig]->GetErrorYlow(b);

		std::cout<<"trigggg "<<trig<<", bin "<<b<<" ; eta="<<x<<"; eff="<<y<<" , "<<eyh<<" "<<eyl<<std::endl;
	}
        }

    //Write
    eff[0][trig]->Write();
    eff[1][trig]->Write();
    SF[trig]->Write();
    ntuple->Write();

}//End of the trigger loop

cout<<"=============================================="<<endl;
cout<<"==============Finished the eta SF============="<<endl;
cout<<"=============================================="<<endl;
//===========================================END of ETA================================//


cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
cout<<"==============Starting to calculate the SF for pT..... BARREL============="<<endl;
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

TH1D *pt_bar[ratio][datamc][ntrig]= {{{ptbarmu[0],ptbarmu[1],ptbarmu[2]},{ptbarmuMC[0],ptbarmuMC[1],ptbarmuMC[2]}},
                                    {{ptbar,ptbar,ptbar},{ptbarMC,ptbarMC,ptbarMC}}};

TH1D *pt_end[ratio][datamc][ntrig]= {{{ptendmu[0],ptendmu[1],ptendmu[2]},{ptendmuMC[0],ptendmuMC[1],ptendmuMC[2]}},
                                    {{ptend,ptend,ptend},{ptendMC,ptendMC,ptendMC}}};


for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         effptbar[dm][trig] = new TGraphAsymmErrors();
         effptbar[dm][trig]->BayesDivide(pt_bar[0][dm][trig],pt_bar[1][dm][trig]);
        }

 	SFptbar[trig] = (TGraphAsymmErrors*)effptbar[0][trig]->Clone(Form("SFptbar_%d",trig));
  	double x1,x2,y1,y2;
  	for(int i=0;i<SFptbar[trig]->GetN();i++)
    	{
     		effptbar[0][trig]->GetPoint(i,x1,y1);
     		effptbar[1][trig]->GetPoint(i,x2,y2);
     		SFptbar[trig]->SetPoint(i,x1,y1/y2);
     		double exh=effptbar[0][trig]->GetErrorXhigh(i);
     		double exl=effptbar[0][trig]->GetErrorXlow(i);

     		double ey1h=effptbar[0][trig]->GetErrorYhigh(i);
     		double ey1l=effptbar[0][trig]->GetErrorYlow(i);

     		double ey2h=effptbar[1][trig]->GetErrorYhigh(i);
     		double ey2l=effptbar[1][trig]->GetErrorYlow(i);

     		double errh = y1/y2 * sqrt(pow(ey1h/y1,2)+pow(ey2l/y2,2));
     		double errl = y1/y2 * sqrt(pow(ey1l/y1,2)+pow(ey2h/y2,2));

     		SFptbar[trig]->SetPointError(i,exl,exh,errl,errh);
		}


     //Write
    effptbar[0][trig]->Write();
    effptbar[1][trig]->Write();
    SFptbar[trig]->Write();
    ntuple->Write();
}

/////////////////////////////ENDCAP///////////////////////////////////
/////////////////////////////////////////////////////////////////////
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
cout<<"==============Starting to calculate the SF for pT..... ENDCAP============="<<endl;
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         effptend[dm][trig] = new TGraphAsymmErrors();
         effptend[dm][trig]->BayesDivide(pt_end[0][dm][trig],pt_end[1][dm][trig]);
        }


 	SFptend[trig] = (TGraphAsymmErrors*)effptend[0][trig]->Clone(Form("SFptend_%d",trig));
  	double x1,x2,y1,y2;
  	for(int i=0;i<SFptend[trig]->GetN();i++)
    	{
     		effptend[0][trig]->GetPoint(i,x1,y1);
     		effptend[1][trig]->GetPoint(i,x2,y2);
     		SFptend[trig]->SetPoint(i,x1,y1/y2);
     		double exh=effptend[0][trig]->GetErrorXhigh(i);
     		double exl=effptend[0][trig]->GetErrorXlow(i);

     		double ey1h=effptend[0][trig]->GetErrorYhigh(i);
     		double ey1l=effptend[0][trig]->GetErrorYlow(i);

     		double ey2h=effptend[1][trig]->GetErrorYhigh(i);
     		double ey2l=effptend[1][trig]->GetErrorYlow(i);

     		double errh = y1/y2 * sqrt(pow(ey1h/y1,2)+pow(ey2l/y2,2));
     		double errl = y1/y2 * sqrt(pow(ey1l/y1,2)+pow(ey2h/y2,2));

     		SFptend[trig]->SetPointError(i,exl,exh,errl,errh);
		}

    //Write
    effptend[0][trig]->Write();
    effptend[1][trig]->Write();
    SFptend[trig]->Write();
    ntuple->Write();
}




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
 //EFFICIENCY FOR PHI
cout<<"///////////////////////////////////////////////////////////////////////////"<<endl;
cout<<"==============Starting to calculate the SF for phi..... BARREL============="<<endl;
cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
TH1D *phi_bar[ratio][datamc][ntrig]= {{{phibarmu[0],phibarmu[1],phibarmu[2]},{phibarmuMC[0],phibarmuMC[1],phibarmuMC[2]}},
                                     {{phibar[0],phibar[1],phibar[2]},{phibarMC[0],phibarMC[1],phibarMC[2]}}};

TH1D *phi_end[ratio][datamc][ntrig]= {{{phiendmu[0],phiendmu[1],phiendmu[2]},{phiendmuMC[0],phiendmuMC[1],phiendmuMC[2]}},
                                     {{phiend[0],phiend[1],phiend[2]},{phiendMC[0],phiendMC[1],phiendMC[2]}}};

for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         effphibar[dm][trig] = new TGraphAsymmErrors();
         effphibar[dm][trig]->BayesDivide(phi_bar[0][dm][trig],phi_bar[1][dm][trig]);
        }


 	SFphibar[trig] = (TGraphAsymmErrors*)effphibar[0][trig]->Clone(Form("SFphibar_%d",trig));
  	double x1,x2,y1,y2;
  	for(int i=0;i<SFphibar[trig]->GetN();i++)
    	{
     		effphibar[0][trig]->GetPoint(i,x1,y1);
     		effphibar[1][trig]->GetPoint(i,x2,y2);
     		SFphibar[trig]->SetPoint(i,x1,y1/y2);
     		double exh=effphibar[0][trig]->GetErrorXhigh(i);
     		double exl=effphibar[0][trig]->GetErrorXlow(i);

     		double ey1h=effphibar[0][trig]->GetErrorYhigh(i);
     		double ey1l=effphibar[0][trig]->GetErrorYlow(i);

     		double ey2h=effphibar[1][trig]->GetErrorYhigh(i);
     		double ey2l=effphibar[1][trig]->GetErrorYlow(i);

     		double errh = y1/y2 * sqrt(pow(ey1h/y1,2)+pow(ey2l/y2,2));
     		double errl = y1/y2 * sqrt(pow(ey1l/y1,2)+pow(ey2h/y2,2));

     		SFphibar[trig]->SetPointError(i,exl,exh,errl,errh);
		}

    //Write
    effphibar[0][trig]->Write();
    effphibar[1][trig]->Write();
    SFphibar[trig]->Write();
    ntuple->Write();
}


//Calculation for the endcap
cout<<"///////////////////////////////////////////////////////////////////////////"<<endl;
cout<<"==============Starting to calculate the SF for phi..... ENDCAP============="<<endl;
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         effphiend[dm][trig] = new TGraphAsymmErrors();
         effphiend[dm][trig]->BayesDivide(phi_end[0][dm][trig],phi_end[1][dm][trig]);
        }

 	SFphiend[trig] = (TGraphAsymmErrors*)effphiend[0][trig]->Clone(Form("SFphiend_%d",trig));
  	double x1,x2,y1,y2;
  	for(int i=0;i<SFphiend[trig]->GetN();i++)
    	{
     		effphiend[0][trig]->GetPoint(i,x1,y1);
     		effphiend[1][trig]->GetPoint(i,x2,y2);
     		SFphiend[trig]->SetPoint(i,x1,y1/y2);
     		double exh=effphiend[0][trig]->GetErrorXhigh(i);
     		double exl=effphiend[0][trig]->GetErrorXlow(i);

     		double ey1h=effphiend[0][trig]->GetErrorYhigh(i);
     		double ey1l=effphiend[0][trig]->GetErrorYlow(i);

     		double ey2h=effphiend[1][trig]->GetErrorYhigh(i);
     		double ey2l=effphiend[1][trig]->GetErrorYlow(i);

     		double errh = y1/y2 * sqrt(pow(ey1h/y1,2)+pow(ey2l/y2,2));
     		double errl = y1/y2 * sqrt(pow(ey1l/y1,2)+pow(ey2h/y2,2));

     		SFphiend[trig]->SetPointError(i,exl,exh,errl,errh);
		}

    //Write
    effphiend[0][trig]-> Write();
    effphiend[0][trig]->Write();
    SFphiend[trig]->Write();
    ntuple->Write();
 }


}//The end of the story






