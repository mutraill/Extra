//Script to get DIRA angle for MCDecayTreeTuple

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
  cout << "Usage: <InputFile> <Path/to/Tuple> <Outfile> <Mother>"  << endl;
}

int main(int argc, char *argv[])
{
  int nargs = argc - 1;
  if (nargs!=4)
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
  
  TFile *fdp_out = new TFile(outFilename.c_str(), "RECREATE");
  TTree *tt_dp_out = t->CloneTree(0);

  double P_DIRA;
  double P_endx, P_endy, P_endz, P_orix, P_oriy, P_oriz; 
  double P_px, P_py, P_pz;

  string mother = argv[4];

  string MPX = mother + "_TRUEP_X";
  string MPY = mother + "_TRUEP_Y";
  string MPZ = mother + "_TRUEP_Z";

  string MENDX = mother + "_TRUEENDVERTEX_X";  
  string MENDY = mother + "_TRUEENDVERTEX_Y";
  string MENDZ = mother + "_TRUEENDVERTEX_Z";

  string MORIX = mother + "_TRUEORIGINVERTEX_X";
  string MORIY = mother + "_TRUEORIGINVERTEX_Y";
  string MORIZ = mother + "_TRUEORIGINVERTEX_Z";

  string Meta = mother + "_DIRA";
  string Meta2 = mother + "_DIRA/D";

  // CHANGE ME! 
  t->SetBranchAddress(MPX.c_str(), &P_px);
  t->SetBranchAddress(MPY.c_str(), &P_py);
  t->SetBranchAddress(MPZ.c_str(), &P_pz);

  t->SetBranchAddress(MENDX.c_str(), &P_endx);
  t->SetBranchAddress(MENDY.c_str(), &P_endy);
  t->SetBranchAddress(MENDZ.c_str(), &P_endz);

  t->SetBranchAddress(MORIX.c_str(), &P_orix);
  t->SetBranchAddress(MORIY.c_str(), &P_oriy);
  t->SetBranchAddress(MORIZ.c_str(), &P_oriz);

  tt_dp_out->Branch(Meta.c_str(), &P_DIRA, Meta2.c_str());

  cout << "Checkpoint: branches set." << endl;
  
  for( int ii = 0; ii < t->GetEntries(); ++ii )
  {
    if(ii%50000==0) cout << "Processing event " << ii << "..." << endl;
    t->GetEntry(ii);
    P_DIRA = ((P_endx-P_orix)*P_px+(P_endy-P_oriy)*P_py+(P_endz-P_oriz)*P_pz) / sqrt(P_px*P_px+P_py*P_py+P_pz*P_pz) / sqrt( (P_endx-P_orix)*(P_endx-P_orix) + (P_endy-P_oriy)*(P_endy-P_oriy) + (P_endz-P_oriz)*(P_endz-P_oriz)); 
    
    //    cout << P_DIRA << endl;
    
    tt_dp_out->Fill();
    
  }

  cout << "Event loop complete. Wrote tree with: " << tt_dp_out->GetEntries() << " entries." << endl;
  
  tt_dp_out->AutoSave();
  return 0;
}





    
   