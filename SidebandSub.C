////////////////////////////////////////////
/// Authur: Murdo Traill 
/// Date: 21/11/16
///////////////////////////////////////////

#include <TLegend.h>
#include <TLatex.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>
#include <TPaveText.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGraph.h>

#include <iomanip>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void printUsage()
{
  cout << "Usage: <Filepathway> <TTreeName> <PlotVariable> <MinValue> <MaxValue>"  << endl;
}
 
int main(int argc, char *argv[])
{

	int nargs = argc - 1;
  if (nargs!=5)
  {
    printUsage();
    return 1;
  }
  ///////////// DEFINE INPUTS ///////////

  string FileName = argv[1];
  string TupleName = argv[2];
  string Variable = argv[3];

  string Min = argv[4];
  string Max = argv[5]; 

  double MIN = atof(Min.c_str());
  double MAX = atof(Max.c_str());

  /////////////////// DATA INPUT HERE //////////////////

  TFile myFile(FileName.c_str(), "READ");                         
  TTree* myTree = (TTree*) myFile.Get(TupleName.c_str());  

  //////////////////////////////////////////////////////////

  int nEntries = myTree->GetEntries();	

  cout << "Original number of events in tree: " << nEntries << endl;

  vector<string> PlotVariables;
  Double_t MVA_Array[0]; 

  PlotVariables.push_back(Variable.c_str());

  for (int i = 0; i < (PlotVariables.size()); ++i) 
  {
  myTree->SetBranchAddress(PlotVariables[i].c_str(),&MVA_Array[i]);   
  }

  Double_t Dplus_M;
  myTree->SetBranchAddress("Dplus_M",&Dplus_M); 

  /////////////////////////////////////////////////////////

  gStyle->SetTitleY(0.97);  
  gStyle->SetTitleX(0.53);
  gStyle->SetCanvasColor(0);
  gStyle->SetOptStat(1110);    
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.85);                 
  //gStyle->SetOptTitle(0);
  gStyle->SetLegendTextSize(0.03);

  TH1F * h1 = new TH1F("h1","h1",100,MIN,MAX);
  TH1F * h2 = new TH1F("h2","h2",100,MIN,MAX);
  TH1F * h3 = new TH1F("h3","h3",100,MIN,MAX);

  TCanvas* c1 = new TCanvas("c1","c1",900,600); 

  float ratio = (1890-1850)/(2*(50));

  for (int i = 0; i<nEntries; i++) { 
       myTree->GetEntry(i);
       if(i%1000 == 0){cout << "Processing event " << i << "..." << endl;}

       if (Dplus_M >1850 && Dplus_M <1890){h1->Fill(-MVA_Array[0]);}
       if (Dplus_M <=1850 || Dplus_M >=1890){h2->Fill(-MVA_Array[0]);}

   }

////////// CONFIFGURE OUTPUT //////////////////

string output3 =  "/Users/murdotraill/Desktop/Data/Real/ControlModes/D+2Kpipi/" + Variable + "_sidebandreduction.root";
TFile *output = new TFile(output3.c_str(), "RECREATE");
cout << "" << endl;
cout << "--> Created root file: " << output3 << endl;   

h3->Add(h1,1.0);
h3->Add(h2,(-1*ratio));

h3->Draw("");

h3->SetTitle("");
  
h3->GetXaxis()->SetTitleOffset(1.2);
//h3->GetXaxis()->CenterTitle();
h3->GetXaxis()->SetTitle("-piplus1_PIDK");
//h3->GetXaxis()->SetTitle(Variable.c_str());

h3->GetYaxis()->SetTitle("Number of Events");
h3->GetYaxis()->SetTitleOffset(1.3);

h3->SetLineColor(kRed); 
h3->SetLineWidth(2);
//h3->GetYaxis()->CenterTitle();
c1->Update();

float maxx = gPad->GetUymax();

//cout << maxx << endl;
h3->GetYaxis()->SetRangeUser(0,maxx); 

TLine *line1 = new TLine(MIN,0,MAX,0);
line1->SetLineColor(1);
line1->SetLineWidth(2);
line1->Draw();

string output1 = "~/Desktop/" + Variable + ".png";
string output2 = "~/Desktop/" + Variable + ".pdf";

c1->Print(output1.c_str());
c1->Print(output2.c_str());

h3->Write();

myFile.Close();

return 0;
}
