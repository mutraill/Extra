#include <TLegend.h>
#include <TLatex.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFile.h>
#include <TLorentzVector.h>

//----- Add C++ Header Files ----//

#include <iomanip>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void AddBranch()
{

 TFile myFile("/Users/murdotraill/Desktop/Data/Real/WrongChargeLines/Xicc+2D+K-p/latest2/Xicc+2DKp_MagDown_BKG_Preselection_withEta_cutonEta.root", "READ");                         
 TTree* myTree = (TTree*) myFile.Get("DecayTree");

 TFile* outFile  =new TFile("/Users/murdotraill/Desktop/Data/Real/WrongChargeLines/Xicc+2D+K-p/latest2/Xicc+2DKp_MagDown_BKG_Preselection_withEta_cutonEta_Eff.root","RECREATE");
 TTree* outTree = myTree->CloneTree(-1);

 int nEntries = outTree->GetEntries();

 cout << "Number of events: " << nEntries << endl; 

 Float_t i_pplus_PIDCalibEffWeight;
 Float_t i_Ksoft_PIDCalibEffWeight;
 Float_t i_Kminus_PIDCalibEffWeight;
 Float_t i_piplus1_PIDCalibEffWeight;
 Float_t i_piplus2_PIDCalibEffWeight;
 Float_t i_Event_PIDCalibEffWeight;
 
 TBranch* pplus_PIDCalibEffWeight = outTree->Branch("pplus_PIDCalibEffWeight", &i_pplus_PIDCalibEffWeight, "pplus_PIDCalibEffWeight/F");
 TBranch* Ksoft_PIDCalibEffWeight = outTree->Branch("Ksoft_PIDCalibEffWeight", &i_Ksoft_PIDCalibEffWeight, "Ksoft_PIDCalibEffWeight/F");
 TBranch* Kminus_PIDCalibEffWeight = outTree->Branch("Kminus_PIDCalibEffWeight", &i_Kminus_PIDCalibEffWeight, "kminus_PIDCalibEffWeight/F");
 TBranch* piplus1_PIDCalibEffWeight = outTree->Branch("piplus1_PIDCalibEffWeight", &i_piplus1_PIDCalibEffWeight, "piplus1_PIDCalibEffWeight/F");
 TBranch* piplus2_PIDCalibEffWeight = outTree->Branch("piplus2_PIDCalibEffWeight", &i_piplus2_PIDCalibEffWeight, "piplus2_PIDCalibEffWeight/F");
 TBranch* Event_PIDCalibEffWeight = outTree->Branch("Event_PIDCalibEffWeight", &i_Event_PIDCalibEffWeight, "Event_PIDCalibEffWeight/F");

 for (Int_t i = 0; i<nEntries; i++) {
    outTree->GetEntry(i); 

    if(i%10000 == 0){cout << "Processing event " << i << "..." << endl;}

    i_pplus_PIDCalibEffWeight = 0.;
    pplus_PIDCalibEffWeight->Fill();

    i_Ksoft_PIDCalibEffWeight = 0.;
    Ksoft_PIDCalibEffWeight->Fill();

    i_Kminus_PIDCalibEffWeight = 0.;
    Kminus_PIDCalibEffWeight->Fill();

    i_piplus1_PIDCalibEffWeight = 0.;
    piplus1_PIDCalibEffWeight->Fill();

    i_piplus2_PIDCalibEffWeight = 0.;
    piplus2_PIDCalibEffWeight->Fill();

    i_Event_PIDCalibEffWeight = 0.;
    Event_PIDCalibEffWeight->Fill();

	}	

 outTree->Write();
 outFile->Close(); 

 return;

}


