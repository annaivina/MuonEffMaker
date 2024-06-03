using namespace std;

void ratiosf(TFile *normal, TFile *systematic, int naam)
{

   	gStyle->Reset();
   	SetAtlasStyle();
   	gStyle->SetPalette(1);

    //Let's make the folder and the file to save our ratios
    //                                         0                                1                                   2
    char periodss [6][200];
    //sprintf(periodss [0],"%s_mass",name_datafile[0]);
    sprintf(periodss [0],"%s_mass_up",name_datafile[0]);
    sprintf(periodss [1],"%s_mass_down",name_datafile[0]);
    sprintf(periodss [2],"%s_positive",name_datafile[0]);
    sprintf(periodss [3],"%s_negative",name_datafile[0]); //= {Form("%s_mass",name_datafile[0]),Form("%s_positive",name_datafile[0]),Form("%s_negative",name_datafile[0])};
    TFile *periods;
    //if(naam==1){periods = new TFile(Form("relative/%s.root",periodss[0]),"RECREATE");}
    if(naam==1){periods = new TFile(Form("relative/%s.root",periodss[0]),"RECREATE");}
    if(naam==2){periods = new TFile(Form("relative/%s.root",periodss[1]),"RECREATE");}
    if(naam==3){periods = new TFile(Form("relative/%s.root",periodss[2]),"RECREATE");}
    if(naam==4){periods = new TFile(Form("relative/%s.root",periodss[3]),"RECREATE");}
    //if(period==1 && naam==1){periods[period] = new TFile(Form("relative/period%s.root",periodss[1]),"RECREATE");}
    //if(period==1 && naam==2){periods[period] = new TFile(Form("relative/period%s.root",periodss[3]),"RECREATE");}
    //if(period==1 && naam==3){periods[period] = new TFile(Form("relative/period%s.root",periodss[5]),"RECREATE");}

    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"I am in the ratios. Trying to calculate the relative SF errors..."<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;

    TGraphAsymmErrors *SFnometa[ntrig];//for normal SF
    TGraphAsymmErrors *SFsysteta[ntrig];//for systematic SF

    TGraphAsymmErrors *SFnomphibar[ntrig];//for normal SF
    TGraphAsymmErrors *SFsystphibar[ntrig];//for systematic SF

    TGraphAsymmErrors *SFnomphiend[ntrig];//for normal SF
    TGraphAsymmErrors *SFsystphiend[ntrig];//for systematic SF

    for(int i =0; i<ntrig; ++i)
       {
            //eta
            SFnometa[i] = (TGraphAsymmErrors*)normal->Get(Form("%s",sfeta[i]));
         	SFnometa[i] -> SetName(Form("SF_%s",triggers[i]));
         	SFsysteta[i] = (TGraphAsymmErrors*)systematic->Get(Form("%s",sfeta[i]));
         	//phi barrel
         	SFnomphibar[i] = (TGraphAsymmErrors*)normal->Get(Form("%s",sfphibar[i]));
         	SFnomphibar[i] -> SetName(Form("SFphibar_%s",triggers[i]));
         	SFsystphibar[i] = (TGraphAsymmErrors*)systematic->Get(Form("%s",sfphibar[i]));
         	//phi endcap
         	SFnomphiend[i] = (TGraphAsymmErrors*)normal->Get(Form("%s",sfphiend[i]));
         	SFnomphiend[i] -> SetName(Form("SFphiend_%s",triggers[i]));
         	SFsystphiend[i] = (TGraphAsymmErrors*)systematic->Get(Form("%s",sfphiend[i]));
       }


    const int number  = 2;
    //eta
    TGraphAsymmErrors *ratios[number][ntrig]={{SFnometa[0],SFnometa[1],SFnometa[2]},{SFsysteta[0],SFsysteta[1],SFsysteta[2]}};
    //phi barrel
    TGraphAsymmErrors *ratiosphibar[number][ntrig]={{SFnomphibar[0],SFnomphibar[1],SFnomphibar[2]},{SFsystphibar[0],SFsystphibar[1],SFsystphibar[2]}};
    //phi endcap
    TGraphAsymmErrors *ratiosphiend[number][ntrig]={{SFnomphiend[0],SFnomphiend[1],SFnomphiend[2]},{SFsystphiend[0],SFsystphiend[1],SFsystphiend[2]}};


    TGraphAsymmErrors *ratio [ntrig];
    TGraphAsymmErrors *ratio1 [ntrig];
    TGraphAsymmErrors *ratio2 [ntrig];

    TF1               *fit[ntrig];
    TF1               *fit1[ntrig];
    TF1               *fit2[ntrig];

    TLegend           *leg1[ntrig];
    TLegend           *leg2[ntrig];
    TCanvas           *canvas[ntrig];
    TCanvas           *canvasnew[ntrig];

    cout<<"Calculation the relative ratio for the eta ... "<<endl;

    for (int trig=0;trig<ntrig;++trig)
    	{
        	//canvas[trig]= new TCanvas(Form("canvas_%d",trig),Form("canvas_%d",trig),800,600);//Returns the trig numbers
 	    	//canvas[trig]->cd();

        	ratio[trig] = (TGraphAsymmErrors*)ratios[0][trig]->Clone(Form("ratio_%d",trig));

        	double x1;
    		double y1;
    		double x2;
    		double y2;

        	for(int n=0; n<ratio[trig]->GetN();n++)
           		{
       		 		ratios[0][trig]->GetPoint(n,x1,y1);
       		 		ratios[1][trig]->GetPoint(n,x2,y2);

                    double erryh1 = ratios[0][trig]->GetErrorYhigh(n);
      		        double erryl1 = ratios[0][trig]->GetErrorYlow(n);
        	 		double errxh1 = ratios[0][trig]->GetErrorXhigh(n);
      	     		double errxl1 = ratios[0][trig]->GetErrorXlow(n);
             		double erryh2 = ratios[1][trig]->GetErrorYhigh(n);
             		double erryl2 = ratios[1][trig]->GetErrorYlow(n);

             		double errl = y2/y1 * sqrt(pow(erryh1/y1,2)+pow(erryl2/y2,2));
             		double errh = y2/y1 * sqrt(pow(erryl1/y1,2)+pow(erryh2/y2,2));
             		ratio[trig]->SetPoint(n,x1,y2/y1);
             		ratio[trig]->SetPointError(n,errxl1,errxh1,errl,errh);

            		double r;
            		if(y2/y1>1)r=(y2/y1-1)*100; else if (y2/y1<1)r=(1-y2/y1)*100; else r=0;
            		cout<<"The SF ratio=syst/nominal  is "<<r<<"For the following trigger"<<trig<<endl;
            	}//end for eta


/*
    		ratio[trig]->SetLineColor(kBlack);
 			ratio[trig]->SetMarkerStyle(20);
 			ratio[trig]->SetMarkerColor(kBlack);
 			ratio[trig]->SetTitle(";#eta;Relative uncertaintity");
   			ratio[trig]->Draw("ap");
*/
    		fit[trig] = new TF1(Form("fit_%d",trig),"[0]",-2.5,2.5);
    		fit[trig]->SetParameter(0,1.);
    		fit[trig]->Print();
    		ratio[trig]->Fit(fit[trig],"s","",-2.5,2.5)->Print();
    		//fit[trig]->Draw("same");
/*
			leg1[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg1[trig]->SetBorderSize(0);
			leg1[trig]->SetFillStyle(0);
			leg1[trig]->SetTextSize(0.04);
			leg1[trig]->SetTextFont(42);
			leg1[trig]->AddEntry(ratio[trig],  Form("%s",fnames[trig]),"pl");
			leg1[trig]->Draw();


			canvasnew[trig]= new TCanvas(Form("canvasnew_%d",trig),Form("canvasnew_%d",trig),800,600);//Returns the trig numbers
 			canvasnew[trig]->cd();


    		ratios[0][trig]->SetMarkerColor(kBlue);
    		ratios[0][trig]->SetLineColor(kBlue);
    		ratios[0][trig]->SetTitle(";#eta;SF");
			ratios[0][trig]->Draw("ap0");

			ratios[1][trig]->SetMarkerColor(kRed);
			ratios[1][trig]->SetLineColor(kRed);
			ratios[1][trig]->Draw("p same");


			leg2[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg2[trig]->SetBorderSize(0);
			leg2[trig]->SetFillStyle(0);
			leg2[trig]->SetTextSize(0.04);
			leg2[trig]->SetTextFont(42);
			leg2[trig]->AddEntry(ratios[0][trig],  Form("%s nominal",fnames[trig]),"pl");
			leg2[trig]->AddEntry(ratios[1][trig],  Form("%s #mu negat",fnames[trig]),"pl");
			leg2[trig]->Draw();
*/

    		ratio[trig]->Write();
   		}//end of trigger loop

      cout<<"Calculation the relative ratio for the phi barrel and endcap... "<<endl;
      for (int trig=0;trig<ntrig;++trig)
        {
            ratio1[trig] = (TGraphAsymmErrors*)ratiosphibar[0][trig]->Clone(Form("ratiobar_%d",trig));
            ratio2[trig] = (TGraphAsymmErrors*)ratiosphiend[0][trig]->Clone(Form("ratioend_%d",trig));

            double x1;//for phi barrel
    	    double y1;
            double x2;
    	    double y2;
            double xx1;//for phi endcap
    	    double yy1;
    	    double xx2;
    	    double yy2;

    		for(int n=0; n<ratio1[trig]->GetN();n++)
          		 {
       		 		ratiosphibar[0][trig]->GetPoint(n,x1,y1);
       		 		ratiosphibar[1][trig]->GetPoint(n,x2,y2);

      	 	 		double erryh1 = ratiosphibar[0][trig]->GetErrorYhigh(n);
      		 		double erryl1 = ratiosphibar[0][trig]->GetErrorYlow(n);
        	 		double errxh1 = ratiosphibar[0][trig]->GetErrorXhigh(n);
      	     		double errxl1 = ratiosphibar[0][trig]->GetErrorXlow(n);
             		double erryh2 = ratiosphibar[1][trig]->GetErrorYhigh(n);
             		double erryl2 = ratiosphibar[1][trig]->GetErrorYlow(n);

             		double errl = y2/y1 * sqrt(pow(erryh1/y1,2)+pow(erryl2/y2,2));
             		double errh = y2/y1 * sqrt(pow(erryl1/y1,2)+pow(erryh2/y2,2));
             		ratio1[trig]->SetPoint(n,x1,y2/y1);
             		ratio1[trig]->SetPointError(n,errxl1,errxh1,errl,errh);

             		double r;
             		if(y2/y1>1)r=(y2/y1-1)*100; else if (y2/y1<1)r=(1-y2/y1)*100; else r=0;
             		cout<<"The SF ratio for BARREL =syst/nominal  is "<<r<<"For the following trigger"<<trig<<endl;
            	}//end for phi bar


/*
    		ratio1[trig]->SetLineColor(kBlack);
 			ratio1[trig]->SetMarkerStyle(20);
 			ratio1[trig]->SetMarkerColor(kBlack);
 			ratio1[trig]->SetTitle(";#phi;Relative uncertaintity");
    		ratio1[trig]->Draw("ap");
*/


    		fit1[trig] = new TF1(Form("fit1_%d",trig),"[0]",-2.945243,3.337942);
    		fit1[trig]->SetParameter(0,1.);
    		fit1[trig]->Print();
    		ratio1[trig]->Fit(fit1[trig],"s","",-2.945243,3.337942)->Print();
    		//fit1[trig]->Draw("same");

/*
			leg11[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg11[trig]->SetBorderSize(0);
			leg11[trig]->SetFillStyle(0);
			leg11[trig]->SetTextSize(0.04);
			leg11[trig]->SetTextFont(42);
			leg11[trig]->AddEntry(ratio[trig],  Form("%s",fnames[trig]),"pl");
			leg11[trig]->Draw();


			canvasnew[trig]= new TCanvas(Form("canvasnew_%d",trig),Form("canvasnew_%d",trig),800,600);//Returns the trig numbers
 			canvasnew[trig]->cd();


    		ratios[0][trig]->SetMarkerColor(kBlue);
    		ratios[0][trig]->SetLineColor(kBlue);
    		ratios[0][trig]->SetTitle(";#phi;SF");
			ratios[0][trig]->Draw("ap0");

			ratios[1][trig]->SetMarkerColor(kRed);
			ratios[1][trig]->SetLineColor(kRed);
			ratios[1][trig]->Draw("p same");


			leg2[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg2[trig]->SetBorderSize(0);
			leg2[trig]->SetFillStyle(0);
			leg2[trig]->SetTextSize(0.04);
			leg2[trig]->SetTextFont(42);
			leg2[trig]->AddEntry(ratios[0][trig],  Form("%s nominal",fnames[trig]),"pl");
			leg2[trig]->AddEntry(ratios[1][trig],  Form("%s #Syst",fnames[trig]),"pl");
			leg2[trig]->Draw();
*/
        	ratio1[trig]->Write();


        	///================================================================================///
        	///================================================================================///
        	//FOR THE ENDCAP//////////////////////////////////////////////////////////////////////
        	///================================================================================///
        	///================================================================================///
/*
        	canvass[trig]= new TCanvas(Form("canvass_%d",trig),Form("canvass_%d",trig),800,600);//Returns the trig numbers
 	    	canvass[trig]->cd();
*/


        	for(int n=0; n<ratio2[trig]->GetN();n++)
           		{
       		 		ratiosphiend[0][trig]->GetPoint(n,xx1,yy1);
       		 		ratiosphiend[1][trig]->GetPoint(n,xx2,yy2);

      	 	 		double erryh11 = ratiosphiend[0][trig]->GetErrorYhigh(n);
      		 		double erryl11 = ratiosphiend[0][trig]->GetErrorYlow(n);
        	 		double errxh11 = ratiosphiend[0][trig]->GetErrorXhigh(n);
      	     		double errxl11 = ratiosphiend[0][trig]->GetErrorXlow(n);
             		double erryh22 = ratiosphiend[1][trig]->GetErrorYhigh(n);
             		double erryl22 = ratiosphiend[1][trig]->GetErrorYlow(n);


             		double errll = yy2/yy1 * sqrt(pow(erryh11/yy1,2)+pow(erryl22/yy2,2));
             		double errhh = yy2/yy1 * sqrt(pow(erryl11/yy1,2)+pow(erryh22/yy2,2));
             		ratio2[trig]->SetPoint(n,xx1,yy2/yy1);
             		ratio2[trig]->SetPointError(n,errxl11,errxh11,errll,errhh);

             		double s;
             		if(yy2/yy1>1)s=(yy2/yy1-1)*100; else if (yy2/yy1<1)s=(1-yy2/yy1)*100; else s=0.;
             		cout<<"The SF ratio for ENDCAP =syst/nominal  is "<<s<<"For the following trigger"<<trig<<endl;
            	}//end for phi end


/*
    		ratioo[trig]->SetLineColor(kBlack);
 			ratioo[trig]->SetMarkerStyle(20);
 			ratioo[trig]->SetMarkerColor(kBlack);
 			ratioo[trig]->SetTitle(";#phi;Relative uncertaintity");
    		ratioo[trig]->Draw("ap");
*/

    		fit2[trig] = new TF1(Form("fit2_%d",trig),"[0]",-3.403392,2.879793);
    		fit2[trig]->SetParameter(0,1.);
    		fit2[trig]->Print();
    		ratio2[trig]->Fit(fit2[trig],"s","",-3.403392,2.879793)->Print();
    		//fit2[trig]->Draw("same");

/*
			leg11[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg11[trig]->SetBorderSize(0);
			leg11[trig]->SetFillStyle(0);
			leg11[trig]->SetTextSize(0.04);
			leg11[trig]->SetTextFont(42);
			leg11[trig]->AddEntry(ratioo[trig],  Form("%s",fnames[trig]),"pl");
			leg11[trig]->Draw();



			canvasneww[trig]= new TCanvas(Form("canvasneww_%d",trig),Form("canvasneww_%d",trig),800,600);//Returns the trig numbers
 			canvasneww[trig]->cd();


    		ratioss[0][trig]->SetMarkerColor(kBlue);
    		ratioss[0][trig]->SetLineColor(kBlue);
    		ratioss[0][trig]->SetTitle(";#phi_{end};SF");
			ratioss[0][trig]->Draw("ap0");

			ratioss[1][trig]->SetMarkerColor(kRed);
			ratioss[1][trig]->SetLineColor(kRed);
			ratioss[1][trig]->Draw("p same");


			leg22[trig] = new TLegend(0.6,0.65,0.9,0.9);
			leg22[trig]->SetBorderSize(0);
			leg22[trig]->SetFillStyle(0);
			leg22[trig]->SetTextSize(0.04);
			leg22[trig]->SetTextFont(42);
			leg22[trig]->AddEntry(ratioss[0][trig],  Form("%s nominal",fnames[trig]),"pl");
			leg22[trig]->AddEntry(ratioss[1][trig],  Form("%s #Syst",fnames[trig]),"pl");
			leg22[trig]->Draw();
*/
        	ratio2[trig]->Write();




        }//end for trigger loop

    periods->Write();
}//The end of the story


