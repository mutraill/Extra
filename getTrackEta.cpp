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
  cout << "Usage: <InputFile> <Path/to/Tuple> <Outfile> <Mother> <Daughter 1> <Daughter 2>"  << endl;
}

int main(int argc, char *argv[])
{
  int nargs = argc - 1;
  if (nargs!=6)
  {
    printUsage();
    return 1;
  }
  
  string inputFilename = argv[1];
  string tupleName = argv[2];
  string outFilename = argv[3];
  TFile* f = TFile::Open(inputFilename.c_str(), "READ");
  f->ls();
  TTree *t = (TTree*)f->Get(tupleName.c_str());
  TTree *lumi = (TTree*)f->Get("GetIntegratedLuminosity/LumiTuple"); //<---- Comment out for MC
  
  TFile *fdp_out = new TFile(outFilename.c_str(), "RECREATE"); 
  TTree *tt_dp_out = t->CloneTree(0);
  //TTree *tt_dp_out2 = lumi->CloneTree(0); //<---- Comment out for MC

  double p_eta, h1_eta, h2_eta;
  double p_pz, p_p;
  double h2_pz, h2_p;
  double h1_pz,  h1_p;

  string mother = argv[4];
  string d1 = argv[5];
  string d2 = argv[6];

  string MPZ = mother + "_PZ";
  string MP = mother + "_P";
  string D1PZ = d1 + "_PZ";
  string D1P = d1 + "_P";
  string D2PZ = d2 + "_PZ";
  string D2P = d2 + "_P";
  string Meta = mother + "_TRACK_Eta";
  string Meta2 = mother + "_TRACK_Eta/D";
  string D1eta = d1 + "_TRACK_Eta";
  string D1eta2 = d1 + "_TRACK_Eta/D";
  string D2eta = d2 + "_TRACK_Eta";
  string D2eta2 = d2 + "_TRACK_Eta/D";

  // CHANGE ME! 
  t->SetBranchAddress(MPZ.c_str(), &p_pz);
  t->SetBranchAddress(MP.c_str(), &p_p);
  t->SetBranchAddress(D1PZ.c_str(), &h1_pz);
  t->SetBranchAddress(D1P.c_str(), &h1_p);
  t->SetBranchAddress(D2PZ.c_str(), &h2_pz);
  t->SetBranchAddress(D2P.c_str(), &h2_p);

  tt_dp_out->Branch(Meta.c_str(), &p_eta, Meta2.c_str());
  tt_dp_out->Branch(D1eta.c_str(), &h1_eta, D1eta2.c_str());
  tt_dp_out->Branch(D2eta.c_str(), &h2_eta, D2eta2.c_str());

  cout << "Checkpoint: branches set." << endl;
  
  for( int ii = 0; ii < t->GetEntries(); ++ii )
  {
    if(ii%10000==0) cout << "Processing event " << ii << "..." << endl;
    t->GetEntry(ii);
    p_eta = 0.5 * log((p_p + p_pz)/(p_p - p_pz));
    h1_eta = 0.5 * log((h1_p + h1_pz)/(h1_p - h1_pz));
    h2_eta = 0.5 * log((h2_p + h2_pz)/(h2_p - h2_pz));
    //    cout << p_eta << endl;
    
    tt_dp_out->Fill();
  }

  //for( int ii = 0; ii < lumi->GetEntries(); ++ii )
  // {
  // if(ii%10000==0) cout << "Processing event " << ii << "..." << endl;
  // lumi->GetEntry(ii);
  // tt_dp_out2->Fill(); // comment out for MC  
  //}

  cout << "Event loop complete. Wrote tree with: " << tt_dp_out->GetEntries() << " entries." << endl;
  
  tt_dp_out->AutoSave();
 // tt_dp_out2->AutoSave(); // comment out for MC
  return 0;
}





    
    
