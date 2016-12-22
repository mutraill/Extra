#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <sstream>
#include "math.h"
#include <cstdlib>

using namespace std;

void printUsage()
{
  cout << "Usage: ./TruthMatch.exe <InputFile> <Path/to/Tuple> <TruthMatchVariable>"  << endl;
}

int main(int argc, char *argv[])
{
  int nargs = argc - 1;
  if (nargs!=3)
  {
    printUsage();
    return 1;
  }

   string inputFilename = argv[1];
   string tupleName = argv[2];
   string truthvariable = argv[3];
   
   TFile *oldfile = new TFile(inputFilename.c_str());
   TTree *oldtree = (TTree*)oldfile->Get(tupleName.c_str());
   Double_t nentries = oldtree->GetEntries();

   string output = inputFilename.substr(0,inputFilename.size() - 5);
   output += "_basic_truthmatched.root";
 
   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile(output.c_str(),"recreate");
   TTree *newtree = oldtree->CloneTree(0);

   //////////// Preselection Variables //////////////////////

   Int_t Xicc_BKGCAT;
   Int_t Dplus_BKGCAT;

   Int_t Dplus_TRUEID;
   Int_t pplus_TRUEID;
   Int_t Kminus_TRUEID;
   Int_t Ksoft_TRUEID;
   Int_t piplus1_TRUEID;
   Int_t piplus2_TRUEID;
   Double_t Xicc_M;
   Double_t Dplus_M;

   oldtree->SetBranchAddress(truthvariable.c_str(),&Xicc_BKGCAT);

   oldtree->SetBranchAddress("Dplus_BKGCAT",&Dplus_BKGCAT);
   oldtree->SetBranchAddress("Dplus_TRUEID",&Dplus_TRUEID);
   oldtree->SetBranchAddress("pplus_TRUEID",&pplus_TRUEID);
   oldtree->SetBranchAddress("Kminus_TRUEID",&Kminus_TRUEID);
   oldtree->SetBranchAddress("Ksoft_TRUEID",&Ksoft_TRUEID);
   oldtree->SetBranchAddress("piplus1_TRUEID",&piplus1_TRUEID);
   oldtree->SetBranchAddress("piplus2_TRUEID",&piplus2_TRUEID);
   oldtree->SetBranchAddress("Xicc_M",&Xicc_M);
   oldtree->SetBranchAddress("Dplus_M",&Dplus_M);

   /////////////////////////////////////////////////////////////////////

   for (Long64_t i=0;i<nentries; i++) {
     if(i%5000==0) cout << "Processing event " << i << "..." << endl;
      oldtree->GetEntry(i);

      if(Xicc_BKGCAT == 0 && Dplus_BKGCAT == 0) 
	 //&& abs(Dplus_TRUEID)==411 
	 //&& abs(pplus_TRUEID)==2212 
	 //&& abs(Kminus_TRUEID)==321 
	 //&& abs(Ksoft_TRUEID)==321 
	 //&& abs(piplus1_TRUEID)==211 
	 //&& abs(piplus2_TRUEID)==211 
	 //&& Xicc_M > ((0.974473*Dplus_M) + 1745) && Xicc_M < ((0.974473*Dplus_M) + 1800))
         newtree->Fill();
   }

   newtree->Print();
   newtree->AutoSave();
   delete oldfile;
   delete newfile;
}
