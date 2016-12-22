#include <TChain.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <sstream>
#include "math.h"
#include <cstdlib>
#include "TROOT.h"
#include <TRandom.h>

using namespace std;

void printUsage()
{
  cout << "Usage: ./RandomSelection.exe <Input1> <Input2> <Path/to/Tuple1> <Path/toTuple2> <percetange>"  << endl;
}

int main(int argc, char *argv[])
{
  int nargs = argc - 1;
  if (nargs!=5)
  {
  printUsage();
  return 1;
  }

  string inputFilename1 = argv[1];
  string inputFilename2 = argv[2];
  string inputTree1 = argv[3];
  string inputTree2 = argv[4];
  string percentage = argv[5];

  float value = atof(percentage.c_str());
  float perc_value = value/100;
 
  TFile *oldfile1 = new TFile(inputFilename1.c_str());
  TTree *oldtree1 = (TTree*)oldfile1->Get(inputTree1.c_str());
   
  TFile *oldfile2 = new TFile(inputFilename2.c_str());
  TTree *oldtree2 = (TTree*)oldfile2->Get(inputTree2.c_str());

  TChain chain(inputTree1.c_str());

  chain.AddFile(inputFilename1.c_str());
  chain.AddFile(inputFilename2.c_str());

  Double_t nentries = chain.GetEntries();
 
  //string outputName = "/Users/murdotraill/Desktop/Scripts/TMVAStudies/Xicc+2D+K-p/Attempt3/Background_MVA_"; 
  string outputName = inputFilename1.substr(0,inputFilename1.size() - 14);
  outputName += percentage + "%_BothMag" + ".root";
  
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile(outputName.c_str(),"recreate");
  TTree *newtree = chain.CloneTree(0);

   /////////////////////////////////////////////////////////////////////

   for (Long64_t i=0;i<nentries; i++) {
      chain.GetEntry(i);
      
      if(i%100000==0) cout << "Processing event " << i << "..." << endl;
      if (gRandom->Rndm() < perc_value){
	 newtree->Fill();
      }
   }

   newtree->Print();
   newtree->AutoSave();
   delete oldfile1;
   delete oldfile2;
   delete newfile;

   return 0;
}
