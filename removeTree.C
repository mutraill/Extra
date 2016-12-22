#include <string>
#include "TFile.h"
#include <iostream>

void removeTree(){

  std::string file_name="Xicc_reconstructed_noPIDcuts.root";              // enter file name here in parenthesis 
  TFile *file=new TFile((file_name).c_str(),"update");
  std::string object_to_remove="DaVinciAlg.DaVinciMemory;1";         // enter TTree name here

  //the object can be a tree, a histogram, etc, in this case "test1" is a TTree
  //notice the ";1" which means cycle 1; to remove all cycles do ";*"
  //if your object is not at the top directory, but in a directory in the .root file, called foo
  // you do first

  //file->cd("GenXicc_sim09_pKD;1");  // enter directory name here
  //then continue with the Delete command which is only applied to the current gDirectory
  gDirectory->Delete(object_to_remove.c_str());
  file->Close();

  cout << "Done removing the desired TTree" << endl;
}