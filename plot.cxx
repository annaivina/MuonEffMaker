#include<cmath>
#include<cassert>
#include<iostream>


#include"TFile.h"
#include"TH2.h"
#include"TCanvas.h"
#include"TAxis.h"
#include"TROOT.h"
#include"TF1.h"
#include"TMath.h"
#include"TStyle.h"
#include"TBranch.h"
#include"TTree.h"
#include"TColor.h"
#include"TLegend.h"
#include"TArray.h"
#include"AtlasLabels.C"
#include"AtlasStyle.C"
using namespace std;


void plot()
{
    //Mas
    TFile *file1=  new TFile("relative/periodB_mass_up.root");//mass
    TFile *file2=  new TFile("relative/periodB_mass_down.root");//mass
    TFile *file3=  new TFile("relative/periodB_positive.root");//positive
    TFile *file4=  new TFile("relative/periodB_negative.root");//negative


    TGraphAsymmErrors *mass_up = (TGraphAsymmErrors*)file1->Get("ratio_0");
    TGraphAsymmErrors *mass_down = (TGraphAsymmErrors*)file2->Get("ratio_0");
    TGraphAsymmErrors *mass_positive = (TGraphAsymmErrors*)file3->Get("ratio_0");
    TGraphAsymmErrors *mass_neg = (TGraphAsymmErrors*)file4->Get("ratio_0");


    TCanvas *canvas= new TCanvas("canvas","canvas",800,600);//Returns the trig numbers

    double x1,x2,x3,x4,y1,y2,y3,y4;
    for(int i=0;i<mass_up->GetN();i++)
    {
        mass_up->GetPoint(i,x1,y1);
        double errxh1 = mass_up->GetErrorXhigh(i);
      	double errxl1 = mass_up->GetErrorXlow(i);

        double value = fabs(1. - y1);
        mass_up->SetPoint(i,x1,value*100);
        mass_up->SetPointError(i,errxl1,errxh1,10e-20,10e-20);

     }



    for(int i=0;i<mass_up->GetN();i++)
    {
        mass_down->GetPoint(i,x2,y2);
        double errxh1 = mass_down->GetErrorXhigh(i);
      	double errxl1 = mass_down->GetErrorXlow(i);

        double value = fabs(1. - y2);
        mass_down->SetPoint(i,x2,value*100);
        mass_down->SetPointError(i,errxl1,errxh1,10e-20,10e-20);

     }


     for(int i=0;i<mass_up->GetN();i++)
    {
        mass_positive->GetPoint(i,x3,y3);
        double errxh1 = mass_positive->GetErrorXhigh(i);
      	double errxl1 = mass_positive->GetErrorXlow(i);

        double value = fabs(1. - y3);
        mass_positive->SetPoint(i,x3,value*100);
        mass_positive->SetPointError(i,errxl1,errxh1,10e-20,10e-20);

     }

      for(int i=0;i<mass_up->GetN();i++)
    {
        mass_neg->GetPoint(i,x4,y4);
        double errxh1 = mass_neg->GetErrorXhigh(i);
      	double errxl1 = mass_neg->GetErrorXlow(i);

        double value = fabs(1. - y4);
        mass_neg->SetPoint(i,x4,value*100);
        mass_neg->SetPointError(i,errxl1,errxh1,10e-20,10e-20);

     }



    mass_up->SetLineColor(kBlack);
 	mass_up->SetMarkerStyle(20);
 	mass_up->SetMarkerColor(kBlack);
 	mass_up->SetTitle(";#eta;Default/Changed");
 	//mass_rel->GetYaxis()->SetRangeUser(0.,0.05);
    mass_up->Draw();


    mass_down->SetLineColor(kRed);
 	mass_down->SetMarkerStyle(20);
 	mass_down->SetMarkerColor(kRed);
    mass_down->Draw("same");

    mass_positive->SetLineColor(kBlue);
    mass_positive->SetMarkerStyle(20);
 	mass_positive->SetMarkerColor(kBlue);
    mass_positive->Draw("same");

    mass_neg->SetLineColor(kGreen);
    mass_neg->SetMarkerStyle(20);
 	mass_neg->SetMarkerColor(kGreen);
    mass_neg->Draw("same");


 TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
 leg->SetFillStyle(0);
 leg->SetBorderSize(0);//take the box
 leg->SetTextSize(0.045);//set the size of text
 leg->AddEntry(mass_up,"[86,96] GeV mass cut","pe");
 leg->AddEntry(mass_down,"[76,116] GeV mass cut","pe");
 leg->AddEntry(mass_positive, "Positive muons","pe");
 leg->AddEntry(mass_neg, "Negative muons","pe");

 leg->Draw();




}
