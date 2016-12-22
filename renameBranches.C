#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include <vector>
using namespace std;

     /*************************************************************/
    /*Program to rename branches for use in Charge Cong Mass Fits*/
   /*                         Cameron Dean                      */
  /*                      University of Glasgow                */
 /*                            08/01/2016                     */
/*************************************************************/

void renameBranches(string fileName = "26165057_BothMag_Stripped_noPIDs_truthmatched_presel_renamed_renamed.root",
				    string particle1 = "Km",
  				  string particle2 = "Pip1",
            string particle3 = "Pip2",
            string particle4 = "psoft",
            string particle5 = "Kmsoft"){


  TFile* dataFile = new TFile(fileName.c_str());
  TTree* dataTree = (TTree*)dataFile->Get("DecayTree");

  string outputName = fileName.substr(0,fileName.size() - 5);
  outputName += "_renamed.root";
  TFile* outFile  =new TFile(outputName.c_str(),"RECREATE");
  TTree*  outTree = dataTree->CloneTree(-1); //copying and cloning the input tree

  vector<string> trailers,p1,p2,p3,p4,p5,p6,p7; 
  vector<string> out_p1,out_p2,out_p3,out_p4,out_p5,out_p6,out_p7;

  trailers.push_back("_PIDK");
  trailers.push_back("_PIDp");
  trailers.push_back("_PIDe");
  trailers.push_back("_PIDmu");
  trailers.push_back("_P");
  trailers.push_back("_PT");
  //trailers.push_back("_M");
  //trailers.push_back("_MMERR");
  trailers.push_back("_PX");
  //trailers.push_back("_MAXDOCA");
  trailers.push_back("_PY");
  trailers.push_back("_PZ");
  trailers.push_back("_PE");
  
  //trailers.push_back("_IPCHI2_OWNPV");
  //trailers.push_back("_IP_OWNPV");
  //trailers.push_back("_ENDVERTEX_CHI2");
  //trailers.push_back("_ConsDplus_chi2");
  //trailers.push_back("_FDCHI2_OWNPV");

for (unsigned int i = 0; i < trailers.size(); ++i)
{
	p1.push_back(particle1 + trailers[i]);
	p2.push_back(particle2 + trailers[i]);
  p3.push_back(particle3 + trailers[i]);
  p4.push_back(particle4 + trailers[i]);
  p5.push_back(particle5 + trailers[i]);

	out_p1.push_back("Kminus" + trailers[i]);
	out_p2.push_back("piplus1" + trailers[i]);
  out_p3.push_back("piplus2" + trailers[i]);
  out_p4.push_back("pplus" + trailers[i]);
  out_p5.push_back("Ksoft" + trailers[i]);

	outTree->GetBranch(p1[i].c_str())->SetName(out_p1[i].c_str());
	outTree->GetBranch(p2[i].c_str())->SetName(out_p2[i].c_str());
  outTree->GetBranch(p3[i].c_str())->SetName(out_p3[i].c_str());
  outTree->GetBranch(p4[i].c_str())->SetName(out_p4[i].c_str());
  outTree->GetBranch(p5[i].c_str())->SetName(out_p5[i].c_str());

	outTree->GetLeaf(p1[i].c_str())->SetName(out_p1[i].c_str());
	outTree->GetLeaf(p2[i].c_str())->SetName(out_p2[i].c_str());
  outTree->GetLeaf(p3[i].c_str())->SetName(out_p3[i].c_str());
  outTree->GetLeaf(p4[i].c_str())->SetName(out_p4[i].c_str());
  outTree->GetLeaf(p5[i].c_str())->SetName(out_p5[i].c_str());
} 

  outTree->Write();
  outFile->Close();     

}
