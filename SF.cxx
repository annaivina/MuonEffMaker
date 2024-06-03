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

 //if(period==1 && names==0) {ntuple=new TFile("default/SF_periodC_eta_phi.root","RECREATE");}
 //if(period==1 && names==1) {ntuple=new TFile("mass/SF_periodC_mass.root","RECREATE");}
 //if(period==1 && names==2) {ntuple=new TFile("positive/SF_periodC_mupos.root","RECREATE");}
 //if(period==1 && names==3) {ntuple=new TFile("negative/SF_periodC_muneg.root","RECREATE");}
 //if(period==1 && names==4) {ntuple=new TFile("newbin/SF_periodC_new_eta_phi.root","RECREATE");}


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
 //TH1D *ptbarMC  =(TH1D*)file1->Get("probeptbar");//znamenatel - MC - barrel
// ptbarMC->Sumw2();

 TH1D *ptend  =(TH1D*)file->Get("probeptend");//znamenatel - data - endcap
 ptend->Sumw2();
// TH1D *ptendMC  =(TH1D*)file1->Get("probeptend");//znamenatel - Mc - endcap
// ptendMC->Sumw2();


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
 	    //etaMC[i] = (TH1D*)file1->Get(Form("%s",etaden[i]));
 	    //etaMC[i] ->Sumw2();

 	    phibar[i] = (TH1D*)file->Get(Form("%s",phibarr[i]));
 	    phibar[i] ->Sumw2();
 	    phiend[i] = (TH1D*)file->Get(Form("%s",phiendc[i]));
 	    phiend[i] ->Sumw2();
 	    //phibarMC[i] = (TH1D*)file1->Get(Form("%s",phibarr[i]));
 	    //phibarMC[i] ->Sumw2();
 	    //phiendMC[i] = (TH1D*)file1->Get(Form("%s",phiendc[i]));
 	    //phiendMC[i] ->Sumw2();

 	    //Hislitel
 	    etamu  [i] = (TH1D*)file->Get(Form("%s",etanum[i]));
 		etamu  [i] ->Sumw2();
 	   /// etamuMC[i] = (TH1D*)file1->Get(Form("%s",etanum[i]));
 	   // etamuMC[i] ->Sumw2();

 	    ptbarmu[i] = (TH1D*)file->Get(Form("%s",ptbarr[i]));
 	    ptbarmu[i] ->Sumw2();
 	    ptendmu[i] = (TH1D*)file->Get(Form("%s",ptendc[i]));
 	    ptendmu[i] ->Sumw2();
 	   /// ptendmuMC[i] = (TH1D*)file1->Get(Form("%s",ptendc[i]));
 	   // ptendmuMC[i] ->Sumw2();
 	   // ptbarmuMC[i] = (TH1D*)file1->Get(Form("%s",ptbarr[i]));
 	   // ptbarmuMC[i] ->Sumw2();


 	    phibarmu[i] = (TH1D*)file->Get(Form("%s",phibarrmu[i]));
 	    phibarmu[i] ->Sumw2();
 	    phiendmu[i] = (TH1D*)file->Get(Form("%s",phiendcmu[i]));
 	    phiendmu[i] ->Sumw2();
 	  //  phibarmuMC[i] = (TH1D*)file1->Get(Form("%s",phibarrmu[i]));
 	  //  phibarmuMC[i] ->Sumw2();
 	  //  phiendmuMC[i] = (TH1D*)file1->Get(Form("%s",phiendcmu[i]));
 	   // phiendmuMC[i] ->Sumw2();
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

/*
    //Overall canvas
 	canvas[trig]= new TCanvas(Form("canvas_%d",trig),Form("canvas_%d",trig),800,600);//Returns the trig numbers
 	canvas[trig]->cd();

    //Upper pad                                                      xl  ylow xr  yhigh
 	pad1[trig] = new TPad(Form("pad1_%d",trig), Form("pad1_%d",trig), 0, 0.3, 1, 1.0);//Top
 	pad1[trig]->SetBottomMargin(0.01); // Upper and lower plot are joined
 	pad1[trig]->SetLeftMargin(0.15);
 	pad1[trig]->Range(-3.454024,-657.2018,3.135956,3683.141);
 	pad1[trig]->SetLeftMargin(0.15);
 	pad1[trig]->Draw();             // Draw the upper pad: pad1
 	pad1[trig]->cd();

    //Efficiency for the data
 	eff[0][trig]->SetLineColor(col[0]);
 	eff[0][trig]->SetMarkerStyle(mar[0]);
 	eff[0][trig]->SetMarkerColor(col[0]);
 	eff[0][trig]->SetTitle(";;Efficiency ");
 	eff[0][trig]->GetYaxis()->SetRangeUser(0.001,1.05);
 	eff[0][trig]->Draw("AP");

    //Efficiency for MC
 	eff[1][trig]->SetLineColor(col[1]);
 	eff[1][trig]->SetMarkerStyle(mar[1]);
 	eff[1][trig]->SetMarkerColor(col[1]);
 	eff[1][trig]->SetMarkerSize(1.6);
 	eff[1][trig]->Draw("p same");

    line1a[trig] = new TLine(-3.,1.,3.,1.);
   	line1a[trig]->SetLineColor(kBlack);
    line1a[trig]->SetLineWidth(1);
    line1a[trig]->SetLineStyle(2);
    line1a[trig]->Draw("l4");

 	leg[trig] = new TLegend(0.536,0.109,0.635,0.308);
 	leg[trig]->SetBorderSize(0);
 	leg[trig]->SetFillStyle(0);
 	leg[trig]->SetTextSize(0.04);
    leg[trig]->SetTextFont(42);
    leg[trig]->AddEntry(eff[1][trig],  Form("%s, MC"  ,fnames[trig]),"pl");
    leg[trig]->AddEntry(eff[0][trig],  Form("%s, Data",fnames[trig]),"pl");
 	leg[trig]->Draw();

 	legA[trig] = new TLegend(0.357,0.107,0.507,0.306);
 	legA[trig]->SetBorderSize(0);
 	legA[trig]->SetTextSize(0.04);
 	legA[trig]->SetFillStyle(0);
 	legA[trig]->SetTextAlign(32);
 	legA[trig]->SetTextFont(42);

 	legA[trig]->AddEntry((TObject*)0,"#bf{#it{ATLAS}} Internal","");
 	legA[trig]->AddEntry((TObject*)0,"#sqrt{s_{NN}} = 8.16 TeV","");
 	legA[trig]->AddEntry((TObject*)0,"|#eta| < 2.5","");
 	legA[trig]->Draw();

 	canvas[trig]->cd();
    //Lower pad
 	pad2[trig] = new TPad(Form("pad2_%d",trig), Form("pad2_%d",trig), 0, 0, 1, 0.3); //Bottom
	pad2[trig]->SetTopMargin(0.); // Upper and lower plot are joined
 	pad2[trig]->SetTopMargin(0);
 	pad2[trig]->SetLeftMargin(0.15);
 	pad2[trig]->SetBottomMargin(0.4);
 	pad2[trig]->Range(-3.458,0.7273355,3.128667,1.08939);
 	pad2[trig]->Draw();
 	pad2[trig]->cd();       // pad2 becomes the current pad
*/
/*
    //Let's make the SF
 	SF[trig] = (TGraphAsymmErrors*)eff[0][trig]->Clone(Form("SF_%d",trig));
  	double x1,x2,y1,y2;
  	for(int i=0;i<SF[trig]->GetN();i++)
    	{
     		eff[0][trig]->GetPoint(i,x1,y1);
     		eff[1][trig]->GetPoint(i,x2,y2);
     		SF[trig]->SetPoint(i,x1,y1/y2);
     		double exh=eff[0][trig]->GetErrorXhigh(i);
     		double exl=eff[0][trig]->GetErrorXlow(i);

     		double ey1h=eff[0][trig]->GetErrorYhigh(i);
     		double ey1l=eff[0][trig]->GetErrorYlow(i);

     		double ey2h=eff[1][trig]->GetErrorYhigh(i);
     		double ey2l=eff[1][trig]->GetErrorYlow(i);

     		double errh = y1/y2 * sqrt(pow(ey1h/y1,2)+pow(ey2l/y2,2));
     		double errl = y1/y2 * sqrt(pow(ey1l/y1,2)+pow(ey2h/y2,2));

     		SF[trig]->SetPointError(i,exl,exh,errl,errh);
		}//end of SF loop
*/
/*
    SF[trig]->SetLineColor(col[2]);
 	SF[trig]->SetMarkerStyle(mar[0]);
 	SF[trig]->SetMarkerColor(col[2]);
 	SF[trig]->Draw("AP0");

    SF[trig]->GetYaxis()->SetTitle("Data / MC ");
 	SF[trig]->GetYaxis()->SetNdivisions(505);
   	SF[trig]->GetYaxis()->SetTitleSize(20);
   	SF[trig]->GetXaxis()->SetTickSize(0.07);
   	SF[trig]->GetYaxis()->SetTitleFont(43);
   	SF[trig]->GetYaxis()->SetTitleOffset(2);
   	SF[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SF[trig]->GetYaxis()->SetLabelSize(20);
   	SF[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SF[trig]->GetYaxis()->SetRangeUser(0.7,1.3);

   	// X axis ratio plot settings
   	SF[trig]->GetXaxis()->SetTitle("#eta ");
   	SF[trig]->GetXaxis()->SetTitleSize(20);
   	SF[trig]->GetXaxis()->SetTitleFont(43);
   	SF[trig]->GetXaxis()->SetTitleOffset(5.);
   	SF[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SF[trig]->GetXaxis()->SetLabelSize(20);
   	SF[trig]->GetXaxis()->SetLabelOffset(0.06);


   	line1b[trig] = new TLine(-3.,1.,3.,1.);
   	line1b[trig]->SetLineColor(kBlack);
    line1b[trig]->SetLineWidth(1);
    line1b[trig]->SetLineStyle(2);
    line1b[trig]->Draw("l4");
*/
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



 ////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////PT    efficiency////////////////////////////////////////////////////
 //BARRELL/////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////
 //DENOMIRATOR.....DATA/////////////////////////////////////
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

/*
 	canvas1[trig]= new TCanvas(Form("canvas1_%d",trig),Form("canvas1_%d",trig),800,600);//Returns the trig numbers
 	canvas1[trig]->cd();

 	pad11[trig] = new TPad(Form("pad11_%d",trig), Form("pad11_%d",trig), 0, 0.3, 1, 1.0);//Top
 	pad11[trig]->SetBottomMargin(0.01); // Upper and lower plot are joined
 	pad11[trig]->SetLeftMargin(0.15);
 	pad11[trig]->Range(-3.454024,-657.2018,3.135956,3683.141);
 	pad11[trig]->SetLeftMargin(0.15);
 	pad11[trig]->Draw();             // Draw the upper pad: pad1
 	pad11[trig]->cd();

 	effptbar[0][trig]->SetLineColor(col[0]);
 	effptbar[0][trig]->SetMarkerStyle(mar[0]);
 	effptbar[0][trig]->SetMarkerColor(col[0]);
 	effptbar[0][trig]->SetTitle(";;Efficiency");
 	effptbar[0][trig]->Draw("AP");
 	effptbar[0][trig]->GetYaxis()->SetRangeUser(0.,1.1);

 	effptbar[1][trig]->SetLineColor(col[1]);
 	effptbar[1][trig]->SetMarkerStyle(mar[0]);
 	effptbar[1][trig]->SetMarkerColor(col[1]);
 	effptbar[1][trig]->Draw("p same");

   	line2a[trig] = new TLine(0.,1.,87,1.);
   	line2a[trig]->SetLineColor(kBlack);
    line2a[trig]->SetLineWidth(1);
    line2a[trig]->SetLineStyle(2);
    line2a[trig]->Draw("l4");

 	leg2[trig] = new TLegend(0.5,0.2,0.6,0.4);
 	leg2[trig]->SetBorderSize(0);
 	leg2[trig]->SetFillStyle(0);
 	leg2[trig]->SetTextSize(0.04);
    leg2[trig]->SetTextFont(42);
    leg2[trig]->AddEntry(effptbar[0][trig],  Form("%s, Data",fnames[trig]),"pl");
    leg2[trig]->AddEntry(effptbar[1][trig],  Form("%s, MC"  ,fnames[trig]),"pl");
 	leg2[trig]->Draw();


 	legC[trig] = new TLegend(0.45,0.2,0.3,0.4);
 	legC[trig]->SetBorderSize(0);
 	legC[trig]->SetTextSize(0.04);
 	legC[trig]->SetFillStyle(0);
 	legC[trig]->SetTextAlign(32);
 	legC[trig]->SetTextFont(42);

 	legC[trig]->AddEntry((TObject*)0,"#bf{#it{ATLAS}} Internal","");
 	legC[trig]->AddEntry((TObject*)0,"#sqrt{s_{NN}} = 8.16 TeV","");
 	legC[trig]->AddEntry((TObject*)0,"|#eta| < 1.05","");
 	legC[trig]->AddEntry((TObject*)0,"#bf{Barrel}","");
 	legC[trig]->Draw();


 	canvas1[trig]->cd();
 	pad22[trig] = new TPad(Form("pad22_%d",trig), Form("pad22_%d",trig), 0, 0, 1, 0.3); //Bottom
	pad22[trig]->SetTopMargin(0.); // Upper and lower plot are joined
 	pad22[trig]->SetTopMargin(0);
 	pad22[trig]->SetLeftMargin(0.15);
 	pad22[trig]->SetBottomMargin(0.4);
 	pad22[trig]->Range(-3.458,0.7273355,3.128667,1.08939);
 	pad22[trig]->Draw();
 	pad22[trig]->cd();       // pad2 becomes the current pad

*/
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

/*
 	SFptbar[trig]->SetLineColor(col[2]);
 	SFptbar[trig]->SetMarkerStyle(mar[0]);
 	SFptbar[trig]->SetMarkerColor(col[2]);
 	SFptbar[trig]->Draw("AP");

    // Y axis ratio plot setitng
    SFptbar[trig]->GetYaxis()->SetTitle("Data / MC ");
 	SFptbar[trig]->GetYaxis()->SetNdivisions(505);
   	SFptbar[trig]->GetYaxis()->SetTitleSize(20);
   	SFptbar[trig]->GetYaxis()->SetTitleFont(43);
   	SFptbar[trig]->GetYaxis()->SetTitleOffset(2);
   	SFptbar[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFptbar[trig]->GetYaxis()->SetLabelSize(20);
   	SFptbar[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFptbar[trig]->GetYaxis()->SetRangeUser(0.7,1.1);

   	// X axis ratio plot settings
   	SFptbar[trig]->GetXaxis()->SetTitle("p_{T} ");
   	SFptbar[trig]->GetXaxis()->SetTitleSize(20);
   	SFptbar[trig]->GetXaxis()->SetTitleFont(43);
   	SFptbar[trig]->GetXaxis()->SetTitleOffset(4.);
   	SFptbar[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFptbar[trig]->GetXaxis()->SetLabelSize(20);
   	SFptbar[trig]->GetXaxis()->SetLabelOffset(0.06);

   	line2b[trig] = new TLine(0.,1.,87,1.);
   	line2b[trig]->SetLineColor(kBlack);
    line2b[trig]->SetLineWidth(1);
    line2b[trig]->SetLineStyle(2);
    line2b[trig]->Draw("l4");
*/
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

/*
 	canvas4[trig]= new TCanvas(Form("canvas4_%d",trig),Form("canvas4_%d",trig),800,600);//Returns the trig numbers
 	canvas4[trig]->cd();

 	pad111[trig] = new TPad(Form("pad111_%d",trig), Form("pad111_%d",trig), 0, 0.3, 1, 1.0);//Top
 	pad111[trig]->SetBottomMargin(0.01); // Upper and lower plot are joined
 	pad111[trig]->SetLeftMargin(0.15);
 	pad11[trig]->Range(-3.454024,-657.2018,3.135956,3683.141);
 	pad111[trig]->SetLeftMargin(0.15);
 	pad111[trig]->Draw();             // Draw the upper pad: pad1
 	pad111[trig]->cd();

 	effptend[0][trig]->SetLineColor(col[0]);
 	effptend[0][trig]->SetMarkerStyle(mar[0]);
 	effptend[0][trig]->SetMarkerColor(col[0]);
 	effptend[0][trig]->SetTitle(";;Efficiency");
 	effptend[0][trig]->Draw("ap");
 	effptend[0][trig]->GetYaxis()->SetRangeUser(0.,1.);

 	effptend[1][trig]->SetLineColor(col[1]);
 	effptend[1][trig]->SetMarkerStyle(mar[0]);
 	effptend[1][trig]->SetMarkerColor(col[1]);
 	effptend[1][trig]->Draw("p same");

    line3a[trig] = new TLine(0.,1.,87,1.);
   	line3a[trig]->SetLineColor(kBlack);
    line3a[trig]->SetLineWidth(1);
    line3a[trig]->SetLineStyle(2);
    line3a[trig]->Draw("l4");

 	leg5[trig] = new TLegend(0.5,0.2,0.6,0.4);
 	leg5[trig]->SetBorderSize(0);
 	leg5[trig]->SetFillStyle(0);
 	leg5[trig]->SetTextSize(0.04);
    leg5[trig]->SetTextFont(42);
    leg5[trig]->AddEntry(effptend[0][trig],  Form("%s, Data",fnames[trig]),"pl");
    leg5[trig]->AddEntry(effptend[1][trig],  Form("%s, MC"  ,fnames[trig]),"pl");
 	leg5[trig]->Draw();

 	legE[trig] = new TLegend(0.45,0.2,0.3,0.4);
 	legE[trig]->SetBorderSize(0);
 	legE[trig]->SetTextSize(0.04);
 	legE[trig]->SetFillStyle(0);
 	legE[trig]->SetTextAlign(32);
 	legE[trig]->SetTextFont(42);

 	legE[trig]->AddEntry((TObject*)0,"#bf{#it{ATLAS}} Internal","");
 	legE[trig]->AddEntry((TObject*)0,"#sqrt{s_{NN}} = 8.16 TeV","");
 	legE[trig]->AddEntry((TObject*)0,"1.05<|#eta| < 2.5","");
 	legE[trig]->AddEntry((TObject*)0,"#bf{Endcap}","");
 	legE[trig]->Draw();

 	canvas4[trig]->cd();
 	pad222[trig] = new TPad(Form("pad22_%d",trig), Form("pad22_%d",trig), 0, 0, 1, 0.3); //Bottom
	pad222[trig]->SetTopMargin(0.); // Upper and lower plot are joined
 	pad222[trig]->SetTopMargin(0);
 	pad222[trig]->SetLeftMargin(0.15);
 	pad222[trig]->SetBottomMargin(0.4);
 	pad22[trig]->Range(-3.458,0.7273355,3.128667,1.08939);
 	pad222[trig]->Draw();
 	pad222[trig]->cd();       // pad2 becomes the current pad

*/
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
/*
 	SFptend[trig]->SetLineColor(col[2]);
 	SFptend[trig]->SetMarkerStyle(mar[0]);
 	SFptend[trig]->SetMarkerColor(col[2]);
 	SFptend[trig]->Draw("ap");


    SFptend[trig]->GetYaxis()->SetTitle("Data / MC ");
 	SFptend[trig]->GetYaxis()->SetNdivisions(505);
   	SFptend[trig]->GetYaxis()->SetTitleSize(20);
   	SFptend[trig]->GetYaxis()->SetTitleFont(43);
   	SFptend[trig]->GetYaxis()->SetTitleOffset(2);
   	SFptend[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFptend[trig]->GetYaxis()->SetLabelSize(20);
   	SFptend[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFptend[trig]->GetYaxis()->SetRangeUser(0.7,1.5);

   	// X axis ratio plot settings
   	SFptend[trig]->GetXaxis()->SetTitle("p_{T} ");
   	SFptend[trig]->GetXaxis()->SetTitleSize(20);
   	SFptend[trig]->GetXaxis()->SetTitleFont(43);
   	SFptend[trig]->GetXaxis()->SetTitleOffset(4.);
   	SFptend[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFptend[trig]->GetXaxis()->SetLabelSize(20);
   	SFptend[trig]->GetXaxis()->SetLabelOffset(0.06);

   	line3b[trig] = new TLine(0.,1.,87,1.);
   	line3b[trig]->SetLineColor(kBlack);
    line3b[trig]->SetLineWidth(1);
    line3b[trig]->SetLineStyle(2);
    line3b[trig]->Draw("l4");
*/
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

/*
 	canvas10[trig]= new TCanvas(Form("canvas10_%d",trig),Form("canvas10_%d",trig),800,600);//Returns the trig numbers
 	canvas10[trig]->cd();

 	pad10[trig] = new TPad(Form("pad10_%d",trig), Form("pad10_%d",trig), 0, 0.3, 1, 1.0);//Top
 	pad10[trig]->SetBottomMargin(0.01); // Upper and lower plot are joined
 	pad10[trig]->SetLeftMargin(0.15);
 	pad10[trig]->Range(-3.454024,-657.2018,3.135956,3683.141);
 	pad10[trig]->SetLeftMargin(0.15);
 	pad10[trig]->Draw();             // Draw the upper pad: pad1
 	pad10[trig]->cd();


 	effphibar[0][trig]->SetLineColor(col[0]);
 	effphibar[0][trig]->SetMarkerStyle(mar[0]);
 	effphibar[0][trig]->SetMarkerColor(col[0]);
 	effphibar[0][trig]->SetTitle(";#phi;Efficiency");
 	effphibar[0][trig]->Draw("AP");
 	effphibar[0][trig]->GetYaxis()->SetRangeUser(0.,1.);

 	effphibar[1][trig]->SetLineColor(col[1]);
 	effphibar[1][trig]->SetMarkerStyle(mar[1]);
 	effphibar[1][trig]->SetMarkerColor(col[1]);
 	effphibar[1][trig]->Draw("p same");


 	leg20[trig] = new TLegend(0.5,0.2,0.6,0.4);
 	leg20[trig]->SetBorderSize(0);
 	leg20[trig]->SetFillStyle(0);
 	leg20[trig]->SetTextSize(0.04);
    leg20[trig]->SetTextFont(42);
    leg20[trig]->AddEntry(effphibar[0][trig],  Form("%s, Data",fnames[trig]),"pl");
    leg20[trig]->AddEntry(effphibar[1][trig],  Form("%s, MC"  ,fnames[trig]),"pl");
 	leg20[trig]->Draw();

 	legC20[trig] = new TLegend(0.45,0.2,0.3,0.4);
 	legC20[trig]->SetBorderSize(0);
 	legC20[trig]->SetTextSize(0.04);
 	legC20[trig]->SetFillStyle(0);
 	legC20[trig]->SetTextAlign(32);
 	legC20[trig]->SetTextFont(42);

 	legC20[trig]->AddEntry((TObject*)0,"#bf{#it{ATLAS}} Internal","");
 	legC20[trig]->AddEntry((TObject*)0,"#sqrt{s_{NN}} = 8.16 TeV","");
 	legC20[trig]->AddEntry((TObject*)0,"|#eta| < 1.05","");
 	legC20[trig]->AddEntry((TObject*)0,"#bf{Barrel}","");
 	legC20[trig]->Draw();


 	canvas10[trig]->cd();
 	pad20[trig] = new TPad(Form("pad20_%d",trig), Form("pad20_%d",trig), 0, 0, 1, 0.3); //Bottom
	pad20[trig]->SetTopMargin(0.); // Upper and lower plot are joined
 	pad20[trig]->SetTopMargin(0);
 	pad20[trig]->SetLeftMargin(0.15);
 	pad20[trig]->SetBottomMargin(0.4);
 	pad20[trig]->Range(-3.458,0.7273355,3.128667,1.08939);
 	pad20[trig]->Draw();
 	pad20[trig]->cd();       // pad2 becomes the current pad

*/
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
/*
 	SFphibar[trig]->SetLineColor(col[2]);
 	SFphibar[trig]->SetMarkerStyle(mar[0]);
 	SFphibar[trig]->SetMarkerColor(col[2]);
 	SFphibar[trig]->Draw("AP");


    SFphibar[trig]->GetYaxis()->SetTitle("Data / MC ");
 	SFphibar[trig]->GetYaxis()->SetNdivisions(505);
   	SFphibar[trig]->GetYaxis()->SetTitleSize(20);
   	SFphibar[trig]->GetYaxis()->SetTitleFont(43);
   	SFphibar[trig]->GetYaxis()->SetTitleOffset(2);
   	SFphibar[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFphibar[trig]->GetYaxis()->SetLabelSize(20);
   	SFphibar[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFphibar[trig]->GetYaxis()->SetRangeUser(0.7,1.1);

   	// X axis ratio plot settings
   	SFphibar[trig]->GetXaxis()->SetTitle("#phi ");
   	SFphibar[trig]->GetXaxis()->SetTitleSize(20);
   	SFphibar[trig]->GetXaxis()->SetTitleFont(43);
   	SFphibar[trig]->GetXaxis()->SetTitleOffset(4.);
   	SFphibar[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFphibar[trig]->GetXaxis()->SetLabelSize(20);
   	SFphibar[trig]->GetXaxis()->SetLabelOffset(0.06);

   	line20[trig] = new TLine(-3.6,1.,4.,1);
   	line20[trig]->SetLineColor(kBlack);
    line20[trig]->SetLineWidth(1);
    line20[trig]->SetLineStyle(2);
    line20[trig]->Draw("l4");
*/
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
/*
 	canvas300[trig]= new TCanvas(Form("canvas300_%d",trig),Form("canvas300_%d",trig),800,600);//Returns the trig numbers
 	canvas300[trig]->cd();

 	pad30[trig] = new TPad(Form("pad30_%d",trig), Form("pad30_%d",trig), 0, 0.3, 1, 1.0);//Top
 	pad30[trig]->SetBottomMargin(0.01); // Upper and lower plot are joined
 	pad30[trig]->SetLeftMargin(0.15);
 	pad30[trig]->Range(-3.454024,-657.2018,3.135956,3683.141);
 	pad30[trig]->SetLeftMargin(0.15);
 	pad30[trig]->Draw();             // Draw the upper pad: pad1
 	pad30[trig]->cd();

 	effphiend[0][trig]->SetLineColor(col[0]);
 	effphiend[0][trig]->SetMarkerStyle(mar[0]);
 	effphiend[0][trig]->SetMarkerColor(col[0]);
 	effphiend[0][trig]->SetTitle(";#phi;Efficiency");
 	effphiend[0][trig]->Draw("AP");
 	effphiend[0][trig]->GetYaxis()->SetRangeUser(0.39,1.);

 	effphiend[1][trig]->SetLineColor(col[1]);
 	effphiend[1][trig]->SetMarkerStyle(mar[0]);
 	effphiend[1][trig]->SetMarkerColor(col[1]);
 	effphiend[1][trig]->Draw("p same");

 	leg40[trig] = new TLegend(0.5,0.2,0.6,0.4);
 	leg40[trig]->SetBorderSize(0);
 	leg40[trig]->SetFillStyle(0);
 	leg40[trig]->SetTextSize(0.04);
    leg40[trig]->SetTextFont(42);
    leg40[trig]->AddEntry(effphiend[0][trig],  Form("%s, Data",fnames[trig]),"pl");
    leg40[trig]->AddEntry(effphiend[1][trig],  Form("%s, MC"  ,fnames[trig]),"pl");
 	leg40[trig]->Draw();

 	legC30[trig] = new TLegend(0.45,0.2,0.3,0.4);
 	legC30[trig]->SetBorderSize(0);
 	legC30[trig]->SetTextSize(0.04);
 	legC30[trig]->SetFillStyle(0);
 	legC30[trig]->SetTextAlign(32);
 	legC30[trig]->SetTextFont(42);

 	legC30[trig]->AddEntry((TObject*)0,"#bf{#it{ATLAS}} Internal","");
 	legC30[trig]->AddEntry((TObject*)0,"#sqrt{s_{NN}} = 8.16 TeV","");
 	legC30[trig]->AddEntry((TObject*)0,"1.05 <|#eta| < 2.5","");
 	legC30[trig]->AddEntry((TObject*)0,"#bf{Endcap}","");
 	legC30[trig]->Draw();


 	canvas300[trig]->cd();
 	pad40[trig] = new TPad(Form("pad40_%d",trig), Form("pad40_%d",trig), 0, 0, 1, 0.3); //Bottom
	pad40[trig]->SetTopMargin(0.); // Upper and lower plot are joined
 	pad40[trig]->SetTopMargin(0);
 	pad40[trig]->SetLeftMargin(0.15);
 	pad40[trig]->SetBottomMargin(0.4);
 	pad40[trig]->Range(-3.458,0.7273355,3.128667,1.08939);
 	pad40[trig]->Draw();
 	pad40[trig]->cd();       // pad2 becomes the current pad

*/
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
/*
 	SFphiend[trig]->SetLineColor(col[2]);
 	SFphiend[trig]->SetMarkerStyle(mar[0]);
 	SFphiend[trig]->SetMarkerColor(col[2]);
 	SFphiend[trig]->Draw("AP");

    SFphiend[trig]->GetYaxis()->SetTitle("Data / MC ");
 	SFphiend[trig]->GetYaxis()->SetNdivisions(505);
   	SFphiend[trig]->GetYaxis()->SetTitleSize(20);
   	SFphiend[trig]->GetYaxis()->SetTitleFont(43);
   	SFphiend[trig]->GetYaxis()->SetTitleOffset(2);
   	SFphiend[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFphiend[trig]->GetYaxis()->SetLabelSize(20);
   	SFphiend[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFphiend[trig]->GetYaxis()->SetRangeUser(0.8,1.1);

   	// X axis ratio plot settings
   	SFphiend[trig]->GetXaxis()->SetTitle("#phi ");
   	SFphiend[trig]->GetXaxis()->SetTitleSize(20);
   	SFphiend[trig]->GetXaxis()->SetTitleFont(43);
   	SFphiend[trig]->GetXaxis()->SetTitleOffset(4.);
   	SFphiend[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFphiend[trig]->GetXaxis()->SetLabelSize(20);
   	SFphiend[trig]->GetXaxis()->SetLabelOffset(0.06);

   	line30[trig] = new TLine(-4.,1.,3.6,1);
   	line30[trig]->SetLineColor(kBlack);
    line30[trig]->SetLineWidth(1);
    line30[trig]->SetLineStyle(2);
    line30[trig]->Draw("l4");
*/
    //Write
    effphiend[0][trig]-> Write();
    effphiend[0][trig]->Write();
    SFphiend[trig]->Write();
    ntuple->Write();
}


/*

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//ETA-PHI MAP/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

//DENuMERATOR
//mu8
 TH2D *etaphibarm8    =(TH2D*)file  ->Get("etaphibar8");
 TH2D *etaphibarm8MC  =(TH2D*)file1 ->Get("etaphibar8");

 //mu15
 TH2D *etaphibarm15   =(TH2D*)file  ->Get("etaphibar15");
 TH2D *etaphibarm15MC =(TH2D*)file1 ->Get("etaphibar15");


 //mu15mu10
 TH2D *etaphibarm15MU10   =(TH2D*)file  ->Get("etaphibar15MU10");
 TH2D *etaphibarm15MU10MC =(TH2D*)file1 ->Get("etaphibar15MU10");


 //mu15mu6
 TH2D *etaphibarm15MU6   =(TH2D*)file  ->Get("etaphibar15MU6");
 TH2D *etaphibarm15MU6MC =(TH2D*)file1 ->Get("etaphibar15MU6");


 //mu10mu6
 TH2D *etaphibarm10MU6   =(TH2D*)file  ->Get("etaphibar10MU6");
 TH2D *etaphibarm10MU6MC =(TH2D*)file1 ->Get("etaphibar10MU6");




 //NUMERATOR
 //mu8
 TH2D *etaphimub8   =(TH2D*)file->Get("etaphibarmu8");
 TH2D *etaphimub8MC =(TH2D*)file1->Get("etaphibarmu8");


 //mu15
 TH2D *etaphimub15   =(TH2D*)file->Get("etaphibarmu15");
 TH2D *etaphimub15MC =(TH2D*)file1->Get("etaphibarmu15");

 //mumu10
 TH2D *etaphimub15MU10   =(TH2D*)file->Get("etaphibarmu15MU10");
 TH2D *etaphimub15MU10MC =(TH2D*)file1->Get("etaphibarmu15MU10");

 //mu15mu6
 TH2D *etaphimub15MU6   =(TH2D*)file->Get("etaphibarmu15MU6");
 TH2D *etaphimub15MU6MC =(TH2D*)file1->Get("etaphibarmu15MU6");

 //mu10mu6
 TH2D *etaphimub10MU6   =(TH2D*)file->Get("etaphibarmu10MU6");
 TH2D *etaphimub10MU6MC =(TH2D*)file1->Get("etaphibarmu10MU6");





  //endcap//////////////////////////////////////////
  //Denumerator
  //mu8
 TH2D *etaphiendm8    =(TH2D*)file  ->Get("etaphiend8");
 TH2D *etaphiendm8MC  =(TH2D*)file1 ->Get("etaphiend8");

 //mu15
 TH2D *etaphiendm15   =(TH2D*)file  ->Get("etaphiend15");
 TH2D *etaphiendm15MC =(TH2D*)file1 ->Get("etaphiend15");


 //mu15mu10
 TH2D *etaphiendm15MU10   =(TH2D*)file  ->Get("etaphiend15MU10");
 TH2D *etaphiendm15MU10MC =(TH2D*)file1 ->Get("etaphiend15MU10");


 TH2D *etaphiendm15MU6   =(TH2D*)file  ->Get("etaphiend15MU6");
 TH2D *etaphiendm15MU6MC =(TH2D*)file1 ->Get("etaphiend15MU6");


 TH2D *etaphiendm10MU6   =(TH2D*)file  ->Get("etaphiend10MU6");
 TH2D *etaphiendm10MU6MC =(TH2D*)file1 ->Get("etaphiend10MU6");




 //Numerator
 //mu8
 TH2D *etaphimue8   =(TH2D*)file ->Get("etaphiendmu8");
 TH2D *etaphimue8MC =(TH2D*)file1->Get("etaphiendmu8");


 //mu15
 TH2D *etaphimue15  =(TH2D*)file ->Get("etaphiendmu15");
 TH2D *etaphimue15MC=(TH2D*)file1->Get("etaphiendmu15");


 //mu15mu10
 TH2D *etaphimue15MU10  =(TH2D*)file ->Get("etaphiendmu15MU10");
 TH2D *etaphimue15MU10MC=(TH2D*)file1->Get("etaphiendmu15MU10");


 //mu15mu6
 TH2D *etaphimue15MU6  =(TH2D*)file ->Get("etaphiendmu15MU6");
 TH2D *etaphimue15MU6MC=(TH2D*)file1->Get("etaphiendmu15MU6");


 //mu10mu6
 TH2D *etaphimue10MU6  =(TH2D*)file ->Get("etaphiendmu10MU6");
 TH2D *etaphimue10MU6MC=(TH2D*)file1->Get("etaphiendmu10MU6");


 TH2D *etaphi_end[ratio][datamc][ntrig]= {{{etaphimue8,etaphimue15,etaphimue15MU10,etaphimue15MU6,etaphimue10MU6},{etaphimue8MC,etaphimue15MC,etaphimue15MU10MC,etaphimue15MU6MC,etaphimue10MU6MC}},
                                         {{etaphiendm8,etaphiendm15,etaphiendm15MU10,etaphiendm15MU6,etaphiendm10MU6},{etaphiendm8MC,etaphiendm15MC,etaphiendm15MU10MC,etaphiendm15MU6MC,etaphiendm10MU6MC}}};

 //TH2D *etaphi_bar[ratio][datamc][ntrig]= {{{etaphimub8,etaphimub15,etaphimub15MU10,etaphimub15MU6,etaphimub10MU6},{etaphimub8MC,etaphimub15MC,etaphimub15MU10MC,etaphimub15MU6MC,etaphimub10MU6MC}},
 //                                    {{etaphibarm8,etaphibarm15,etaphibarm15MU10,etaphibarm15MU6,etaphibarm10MU6},{etaphibarm8MC,etaphibarm15MC,etaphibarm15MU10MC,etaphibarm15MU6MC,etaphibarm10MU6MC}}};





 TH2D *effetaphibar[datamc][ntrig];
 TH2D              *SFetaphibar [ntrig];
 TCanvas           *canvas100[ntrig];
 TPad              *pad100[ntrig];
 TPad              *pad200[ntrig];
 TLegend           *leg200[ntrig];
 TLegend           *legC200[ntrig];
 TLine             *line200[ntrig];




for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         //effetaphibar[dm][trig] = new TGraphAsymmErrors();
         effetaphibar[dm][trig] = (TH2D*)etaphi_bar[0][dm][trig]->Clone(Form("effetaphibar_%d_%d",trig,dm));
         effetaphibar[dm][trig]->Divide(etaphi_bar[0][dm][trig],etaphi_bar[1][dm][trig]);
        }


 	canvas100[trig]= new TCanvas(Form("canvas100_%d",trig),Form("canvas100_%d",trig),600,800);//Returns the trig numbers
 	canvas100[trig]->cd();






    int const nbinsetabar=15;

    double etabinsbar[nbinsetabar]={-1.05,-0.908,-0.791,-0.652,-0.476,-0.324,-0.132,0.0,+0.132,+0.324,+0.476,+0.652,+0.791,+0.908,+1.05};


    SFetaphibar[trig] = (TH2D*)effetaphibar[0][trig]->Clone(Form("SFetaphibar_%d",trig));
    SFetaphibar[trig]->Divide(effetaphibar[0][trig],effetaphibar[1][trig]);
    gStyle->SetPaintTextFormat("4.2f");
    gStyle->SetPalette(kRainBow);
    SFetaphibar[trig]->GetZaxis()->SetRangeUser(0.,1.2);
    //SFetaphibar[trig]->SetTitle(";#eta;#phi");
 	SFetaphibar[trig]->Draw("col text");

 	leg200[trig] = new TLegend(0.5,0.2,0.6,0.4);
    leg200[trig]->SetBorderSize(0);
 	leg200[trig]->SetFillStyle(0);
 	leg200[trig]->SetTextSize(0.04);
    leg200[trig]->SetTextFont(42);
    leg200[trig]->AddEntry(SFetaphibar[trig], Form("%s",fnames[trig]),"pl");
 	leg200[trig]->Draw();




//}



 TH2D              *effetaphiend[datamc][ntrig];
 TH2D              *SFetaphiend [ntrig];
 TCanvas           *canvas200[ntrig];
 TPad              *pad100[ntrig];
 TPad              *pad200[ntrig];
 TLegend           *leg300[ntrig];
 TLegend           *legC200[ntrig];
 TLine             *line200[ntrig];




for(int trig=0;trig<ntrig;++trig)
 {

    for(int dm=0; dm<datamc;++dm)
       {
         //effetaphibar[dm][trig] = new TGraphAsymmErrors();
         effetaphiend[dm][trig] = (TH2D*)etaphi_end[0][dm][trig]->Clone(Form("effetaphiend_%d_%d",trig,dm));
         effetaphiend[dm][trig]->Divide(etaphi_end[0][dm][trig],etaphi_end[1][dm][trig]);
        }


 	canvas200[trig]= new TCanvas(Form("canvas200_%d",trig),Form("canvas200_%d",trig),1000,800);//Returns the trig numbers
 	canvas200[trig]->cd();

    canvas200[trig]->SetTopMargin(0.1);
    canvas200[trig]->SetBottomMargin(0.2);
    canvas200[trig]->SetLeftMargin(0.1);
    canvas200[trig]->SetRightMargin(0.1);

    canvas200[trig]->Draw();






    int const nbinsetaend=16;
    double etabinsend[nbinsetaend]={-2.5,-2.4,-1.918,-1.623,-1.348,-1.2329,-1.1479,-1.05,+1.05,+1.1479,+1.2329,+1.348,+1.623,+1.918,+2.4,+2.5};


    SFetaphiend[trig] = (TH2D*)effetaphiend[0][trig]->Clone(Form("SFetaphiend_%d",trig));
    SFetaphiend[trig]->Divide(effetaphiend[0][trig],effetaphiend[1][trig]);
    gStyle->SetPaintTextFormat("4.2f");
    gStyle->SetPalette(kRainBow);
    SFetaphiend[trig]->GetZaxis()->SetRangeUser(0.,1.2);
    SFetaphiend[trig]->SetTitle(";#eta;#phi");
    SFetaphiend[trig]->GetYaxis()->SetTitleOffset(0.8);
 	SFetaphiend[trig]->Draw("colz text");

 	leg300[trig] = new TLegend(0.5,0.2,0.6,0.4);
    leg300[trig]->SetBorderSize(0);
 	leg300[trig]->SetFillStyle(0);
 	leg300[trig]->SetTextSize(0.04);
    leg300[trig]->SetTextFont(42);
    leg300[trig]->AddEntry(SFetaphiend[trig], Form("%s",fnames[trig]),"pl");
 	leg300[trig]->Draw();
 }
*/



}//The end of the story






