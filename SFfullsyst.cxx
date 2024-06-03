using namespace std;

void SFfullsyst(TFile *file, TFile *file1, TFile *error0,TFile *error1, TFile *error2, TFile *error3)//period (0 or 1), names(0,1,2 or 3), var(0 or 1)
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
 TH1D *ptbarMC  =(TH1D*)file1->Get("probeptbar");//znamenatel - MC - barrel
 ptbarMC->Sumw2();

 TH1D *ptend  =(TH1D*)file->Get("probeptend");//znamenatel - data - endcap
 ptend->Sumw2();
 TH1D *ptendMC  =(TH1D*)file1->Get("probeptend");//znamenatel - Mc - endcap
 ptendMC->Sumw2();


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
 	    etaMC[i] = (TH1D*)file1->Get(Form("%s",etaden[i]));
 	    etaMC[i] ->Sumw2();

 	    phibar[i] = (TH1D*)file->Get(Form("%s",phibarr[i]));
 	    phibar[i] ->Sumw2();
 	    phiend[i] = (TH1D*)file->Get(Form("%s",phiendc[i]));
 	    phiend[i] ->Sumw2();
 	    phibarMC[i] = (TH1D*)file1->Get(Form("%s",phibarr[i]));
 	    phibarMC[i] ->Sumw2();
 	    phiendMC[i] = (TH1D*)file1->Get(Form("%s",phiendc[i]));
 	    phiendMC[i] ->Sumw2();

 	    //Hislitel
 	    etamu  [i] = (TH1D*)file->Get(Form("%s",etanum[i]));
 		etamu  [i] ->Sumw2();
 	    etamuMC[i] = (TH1D*)file1->Get(Form("%s",etanum[i]));
 	    etamuMC[i] ->Sumw2();

 	    ptbarmu[i] = (TH1D*)file->Get(Form("%s",ptbarr[i]));
 	    ptbarmu[i] ->Sumw2();
 	    ptendmu[i] = (TH1D*)file->Get(Form("%s",ptendc[i]));
 	    ptendmu[i] ->Sumw2();
 	    ptendmuMC[i] = (TH1D*)file1->Get(Form("%s",ptendc[i]));
 	    ptendmuMC[i] ->Sumw2();
 	    ptbarmuMC[i] = (TH1D*)file1->Get(Form("%s",ptbarr[i]));
 	    ptbarmuMC[i] ->Sumw2();


 	    phibarmu[i] = (TH1D*)file->Get(Form("%s",phibarrmu[i]));
 	    phibarmu[i] ->Sumw2();
 	    phiendmu[i] = (TH1D*)file->Get(Form("%s",phiendcmu[i]));
 	    phiendmu[i] ->Sumw2();
 	    phibarmuMC[i] = (TH1D*)file1->Get(Form("%s",phibarrmu[i]));
 	    phibarmuMC[i] ->Sumw2();
 	    phiendmuMC[i] = (TH1D*)file1->Get(Form("%s",phiendcmu[i]));
 	    phiendmuMC[i] ->Sumw2();
    }


 TGraphAsymmErrors *eff[datamc][ntrig];
 TGraphAsymmErrors *SF [ntrig];
 TCanvas           *canvas[ntrig];
 TPad              *pad1[ntrig];
 TPad              *pad2[ntrig];
 TLegend           *leg[ntrig];
 TLegend           *legA[ntrig];
 TLine             *line1a[ntrig];
 TLine             *line1b[ntrig];
 TGraphAsymmErrors *err0[ntrig];
 TGraphAsymmErrors *err1[ntrig];
 TGraphAsymmErrors *err2[ntrig];
 TGraphAsymmErrors *err3[ntrig];
 TGraphAsymmErrors *errTot[ntrig];
 TGraphAsymmErrors *SFTot[ntrig];


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
 TGraphAsymmErrors *err1_bar[ntrig];
 TGraphAsymmErrors *err2_bar[ntrig];
 TGraphAsymmErrors *err3_bar[ntrig];
 TGraphAsymmErrors *errTot_bar[ntrig];
 TGraphAsymmErrors *SFTot_bar[ntrig];



  TGraphAsymmErrors *effphiend[datamc][ntrig];
 TGraphAsymmErrors *SFphiend [ntrig];
 TCanvas           *canvas300[ntrig];
 TPad              *pad30[ntrig];
 TPad              *pad40[ntrig];
 TLegend           *leg40[ntrig];
 TLegend           *legC30[ntrig];
 TLine             *line30[ntrig];
 TGraphAsymmErrors *err1_end[ntrig];
 TGraphAsymmErrors *err2_end[ntrig];
 TGraphAsymmErrors *err3_end[ntrig];
 TGraphAsymmErrors *errTot_end[ntrig];
 TGraphAsymmErrors *SFTot_end[ntrig];


 TH1D *etatot[ratio][datamc][ntrig]= {{{etamu[0],etamu[1],etamu[2]},{etamuMC[0],etamuMC[1],etamuMC[2]}},
                                  {{eta[0],eta[1],eta[2]},{etaMC[0],etaMC[1],etaMC[2]}}};
 //Loop over the trigger collection
 for(int trig=0;trig<ntrig;++trig)
 {


    //Make the efficiency for both Data and MC for all triggers
    for(int dm=0; dm<datamc;++dm)
       {
         eff[dm][trig] = new TGraphAsymmErrors();
         eff[dm][trig]->BayesDivide(etatot[0][dm][trig],etatot[1][dm][trig]);
        }


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


    //Now lets try to calculate the systematics
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    err0[trig]    = (TGraphAsymmErrors*)error0->Get(Form("ratio_%d",trig));
    err1[trig]    = (TGraphAsymmErrors*)error1->Get(Form("ratio_%d",trig));
    err2[trig]    = (TGraphAsymmErrors*)error2->Get(Form("ratio_%d",trig));
    err3[trig]    = (TGraphAsymmErrors*)error3->Get(Form("ratio_%d",trig));
	errTot[trig]  = (TGraphAsymmErrors*)err3[trig]->Clone(Form("ratioTot_%d",trig)); //Clone one of the err with bigger bins
    SFTot[trig]   = (TGraphAsymmErrors*)SF[trig]->Clone(Form("SFTot_%d",trig));//Clone the SF trig to store there the new syst error

    double xx0,xx1,xx2,xx3;
    double sig0,sig1,sig2,sig3;
    double sigma0,sigma1,sigma2,sigma3;

     for(int n=0; n<err1[trig]->GetN();n++)
         {
            err0[trig]->GetPoint(n,xx0,sig0); if(sig0<1) sigma0=1-sig0; else if(sig0>1)sigma0=sig0-1; else sigma0=0;
            err1[trig]->GetPoint(n,xx1,sig1); if(sig1<1) sigma1=1-sig1; else if(sig1>1)sigma1=sig1-1; else sigma1=0;
            err2[trig]->GetPoint(n,xx2,sig2); if(sig2<1) sigma2=1-sig2; else if(sig2>1)sigma2=sig2-1; else sigma2=0;
            err3[trig]->GetPoint(n,xx3,sig3); if(sig3<1) sigma3=1-sig3; else if(sig3>1)sigma3=sig3-1; else sigma3=0;

            //double sigma = sqrt(pow(sigma1,2)+pow(sigma2,2)+pow(sigma3,2));
            double sigma_mu = (sigma2 + sigma3)/2;
            cout<<"The sigma other is "<<sigma_mu<<endl;
            double sigma_mass = (sigma0 + sigma1)/2;
            cout<<"The sigma mass is "<<sigma_mass<<endl;
            double total = sqrt(pow(sigma_mu,2)+pow(sigma_mass,2));
            //errTot[trig]->SetPoint(n,xx1,sigma); //Saving the points in new TGraph
            errTot[trig]->SetPoint(n,xx1,total); //Saving the points in new TGraph
            cout<<"The error in this bin is "<<total<<"For this trigger "<<trig<<endl;

         }

	int lookhere[28]={0,0,1,1,1,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8};   //-->search for each bin in the new bin with bigger binning..
     //Loop over the bins
    double xxx1,yyy1;
    for(int n=0;n<SFTot[trig]->GetN();n++)
        {

            double exh=SFTot[trig]->GetErrorXhigh(n);
     		double exl=SFTot[trig]->GetErrorXlow(n);

     		errTot[trig]->GetPoint(lookhere[n],xxx1,yyy1);
            SFTot[trig]->SetPointError(n,exl,exh,yyy1,yyy1);

            double result = yyy1*100;
            cout<<"The error in this bin for SF is  "<<result<<"For this trigger "<<trig<<endl;

        }

 	SFTot[trig]->GetYaxis()->SetNdivisions(505);
   	SFTot[trig]->GetYaxis()->SetTitleSize(20);
   	SFTot[trig]->GetYaxis()->SetTitleFont(43);
   	SFTot[trig]->GetYaxis()->SetTitleOffset(2);
   	SFTot[trig]->GetYaxis()->SetLabelFont(40); // Absolute font size in pixel (precision 3)
   	SFTot[trig]->GetYaxis()->SetLabelSize(20);
   	SFTot[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFTot[trig]->GetYaxis()->SetRangeUser(0.7,1.3);

   	SFTot[trig]->GetXaxis()->SetTitleSize(20);
   	SFTot[trig]->GetXaxis()->SetTitleFont(43);
   	SFTot[trig]->GetXaxis()->SetTitleOffset(5.);
   	SFTot[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFTot[trig]->GetXaxis()->SetLabelSize(20);
   	SFTot[trig]->GetXaxis()->SetLabelOffset(0.06);
   	SFTot[trig]->SetTitle(";#eta ;Data/MC");

    SFTot[trig]->SetFillColor(kViolet-2);
    //SFTot[trig]->SetFillStyle(3001);
    SFTot[trig]->Draw("a2");

 	SF[trig]->SetLineColor(col[2]);
 	SF[trig]->SetMarkerStyle(mar[0]);
 	SF[trig]->SetMarkerColor(col[2]);
 	SF[trig]->Draw("p same");

   	line1b[trig] = new TLine(-3.,1.,3.,1.);
   	line1b[trig]->SetLineColor(kBlack);
    line1b[trig]->SetLineWidth(1);
    line1b[trig]->SetLineStyle(2);
    line1b[trig]->Draw("l4");

    //canvas[trig]->Print(".pdf");
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

     //Write
   // effptbar[0][trig]->Write();
   // effptbar[1][trig]->Write();
   // SFptbar[trig]->Write();
  //  ntuple->Write();
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

    //Write
  //  effptend[0][trig]->Write();
  //  effptend[1][trig]->Write();
  //  SFptend[trig]->Write();
  //  ntuple->Write();
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


     //Now lets try to calculate the systematics
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    err1_bar[trig]    = (TGraphAsymmErrors*)error1->Get(Form("ratiobar_%d",trig));
    err2_bar[trig]    = (TGraphAsymmErrors*)error2->Get(Form("ratiobar_%d",trig));
    err3_bar[trig]    = (TGraphAsymmErrors*)error3->Get(Form("ratiobar_%d",trig));
	errTot_bar[trig]  = (TGraphAsymmErrors*)err3_bar[trig]->Clone(Form("ratioTot_%d",trig)); //Clone one of the err with bigger bins
    SFTot_bar[trig]   = (TGraphAsymmErrors*)SFphibar[trig]->Clone(Form("SFTotbar_%d",trig));//Clone the SF trig to store there the new syst error

    double xx1,xx2,xx3;
    double sig1,sig2,sig3;
    double sigma1,sigma2,sigma3;

     for(int n=0; n<err1_bar[trig]->GetN();n++)
         {
            err1_bar[trig]->GetPoint(n,xx1,sig1); if(sig1<1) sigma1=1-sig1; else if(sig1>1)sigma1=sig1-1; else sigma1=0;
            err2_bar[trig]->GetPoint(n,xx2,sig2); if(sig2<1) sigma2=1-sig2; else if(sig2>1)sigma2=sig2-1; else sigma2=0;
            err3_bar[trig]->GetPoint(n,xx3,sig3); if(sig3<1) sigma3=1-sig3; else if(sig3>1)sigma3=sig3-1; else sigma3=0;

            double sigma = sqrt(pow(sigma1,2)+pow(sigma2,2)+pow(sigma3,2));
            errTot_bar[trig]->SetPoint(n,xx1,sigma); //Saving the points in new TGraph
            cout<<"The error in this bin is "<<sigma<<"For this trigger "<<trig<<endl;

         }

     int lookhere[16]={0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7}; //-->search for each bin in the new bin with bigger binning..

    //Loop over the bins
    double xxx1,yyy1;
    for(int n=0;n<SFTot_bar[trig]->GetN();n++)
        {

            double exh=SFTot_bar[trig]->GetErrorXhigh(n);
     		double exl=SFTot_bar[trig]->GetErrorXlow(n);

     		errTot_bar[trig]->GetPoint(lookhere[n],xxx1,yyy1);
            SFTot_bar[trig]->SetPointError(n,exl,exh,yyy1,yyy1);

            double result = yyy1*100;
            cout<<"The error in this bin for SF is  "<<result<<"For this trigger "<<trig<<endl;

        }

 	SFTot_bar[trig]->GetYaxis()->SetNdivisions(505);
   	SFTot_bar[trig]->GetYaxis()->SetTitleSize(20);
   	SFTot_bar[trig]->GetYaxis()->SetTitleFont(43);
   	SFTot_bar[trig]->GetYaxis()->SetTitleOffset(2);
   	SFTot_bar[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFTot_bar[trig]->GetYaxis()->SetLabelSize(20);
   	SFTot_bar[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFTot_bar[trig]->GetYaxis()->SetRangeUser(0.7,1.3);

   	SFTot_bar[trig]->GetXaxis()->SetTitleSize(20);
   	SFTot_bar[trig]->GetXaxis()->SetTitleFont(43);
   	SFTot_bar[trig]->GetXaxis()->SetTitleOffset(5.);
   	SFTot_bar[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFTot_bar[trig]->GetXaxis()->SetLabelSize(20);
   	SFTot_bar[trig]->GetXaxis()->SetLabelOffset(0.06);
   	SFTot_bar[trig]->SetTitle(";#phi ;Data/MC");

    SFTot_bar[trig]->SetFillColor(kViolet-2);
    //SFTot[trig]->SetFillStyle(3001);
    SFTot_bar[trig]->Draw("a2");

   	line1b[trig] = new TLine(-3.,1.,3.,1.);
   	line1b[trig]->SetLineColor(kBlack);
    line1b[trig]->SetLineWidth(1);
    line1b[trig]->SetLineStyle(2);
    line1b[trig]->Draw("l4");


    SFphibar[trig]->SetLineColor(col[2]);
 	SFphibar[trig]->SetMarkerStyle(mar[0]);
 	SFphibar[trig]->SetMarkerColor(col[2]);
 	SFphibar[trig]->Draw("P same");



   	line20[trig] = new TLine(-3.6,1.,4.,1);
   	line20[trig]->SetLineColor(kBlack);
    line20[trig]->SetLineWidth(1);
    line20[trig]->SetLineStyle(2);
    line20[trig]->Draw("l4");

    //Write
    //effphibar[0][trig]->Write();
    //effphibar[1][trig]->Write();
    ///SFphibar[trig]->Write();
    //ntuple->Write();
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



     //Now lets try to calculate the systematics
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    err1_end[trig]    = (TGraphAsymmErrors*)error1->Get(Form("ratioend_%d",trig));
    err2_end[trig]    = (TGraphAsymmErrors*)error2->Get(Form("ratioend_%d",trig));
    err3_end[trig]    = (TGraphAsymmErrors*)error3->Get(Form("ratioend_%d",trig));
	errTot_end[trig]  = (TGraphAsymmErrors*)err3_end[trig]->Clone(Form("ratioTot_%d",trig)); //Clone one of the err with bigger bins
    SFTot_end[trig]   = (TGraphAsymmErrors*)SFphiend[trig]->Clone(Form("SFTotend_%d",trig));//Clone the SF trig to store there the new syst error

    double xx1,xx2,xx3;
    double sig1,sig2,sig3;
    double sigma1,sigma2,sigma3;

     for(int n=0; n<err1_end[trig]->GetN();n++)
         {
            err1_end[trig]->GetPoint(n,xx1,sig1); if(sig1<1) sigma1=1-sig1; else if(sig1>1)sigma1=sig1-1; else sigma1=0;
            err2_end[trig]->GetPoint(n,xx2,sig2); if(sig2<1) sigma2=1-sig2; else if(sig2>1)sigma2=sig2-1; else sigma2=0;
            err3_end[trig]->GetPoint(n,xx3,sig3); if(sig3<1) sigma3=1-sig3; else if(sig3>1)sigma3=sig3-1; else sigma3=0;

            double sigma = sqrt(pow(sigma1,2)+pow(sigma2,2)+pow(sigma3,2));
            errTot_end[trig]->SetPoint(n,xx1,sigma); //Saving the points in new TGraph
            cout<<"The error in this bin is "<<sigma<<"For this trigger "<<trig<<endl;

         }

     int lookhere[16]={0,0,1,1,2,2,3,3,4,4,5,5}; //-->search for each bin in the new bin with bigger binning..

    //Loop over the bins
    double xxx1,yyy1;
    for(int n=0;n<SFTot_end[trig]->GetN();n++)
        {

            double exh=SFTot_end[trig]->GetErrorXhigh(n);
     		double exl=SFTot_end[trig]->GetErrorXlow(n);

     		errTot_end[trig]->GetPoint(lookhere[n],xxx1,yyy1);
            SFTot_end[trig]->SetPointError(n,exl,exh,yyy1,yyy1);

            double result = yyy1*100;
            cout<<"The error in this bin for SF is  "<<result<<"For this trigger "<<trig<<endl;

        }

 	SFTot_end[trig]->GetYaxis()->SetNdivisions(505);
   	SFTot_end[trig]->GetYaxis()->SetTitleSize(20);
   	SFTot_end[trig]->GetYaxis()->SetTitleFont(43);
   	SFTot_end[trig]->GetYaxis()->SetTitleOffset(2);
   	SFTot_end[trig]->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFTot_end[trig]->GetYaxis()->SetLabelSize(20);
   	SFTot_end[trig]->GetYaxis()->SetLabelOffset(0.02);
   	SFTot_end[trig]->GetYaxis()->SetRangeUser(0.7,1.3);

   	SFTot_end[trig]->GetXaxis()->SetTitleSize(20);
   	SFTot_end[trig]->GetXaxis()->SetTitleFont(43);
   	SFTot_end[trig]->GetXaxis()->SetTitleOffset(5.);
   	SFTot_end[trig]->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   	SFTot_end[trig]->GetXaxis()->SetLabelSize(20);
   	SFTot_end[trig]->GetXaxis()->SetLabelOffset(0.06);
   	SFTot_end[trig]->SetTitle(";#phi ;Data/MC");

    SFTot_end[trig]->SetFillColor(kViolet-2);
    //SFTot[trig]->SetFillStyle(3001);
    SFTot_end[trig]->Draw("a2");

    SFphiend[trig]->SetLineColor(col[2]);
 	SFphiend[trig]->SetMarkerStyle(mar[0]);
 	SFphiend[trig]->SetMarkerColor(col[2]);
 	SFphiend[trig]->Draw("p same");

   	line30[trig] = new TLine(-4.,1.,3.6,1);
   	line30[trig]->SetLineColor(kBlack);
    line30[trig]->SetLineWidth(1);
    line30[trig]->SetLineStyle(2);
    line30[trig]->Draw("l4");

    //Write
    //effphiend[0][trig]-> Write();
    //effphiend[0][trig]->Write();
    //SFphiend[trig]->Write();
    //ntuple->Write();
}



}//The end of the story






