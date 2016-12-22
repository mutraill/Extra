
void Random() {
   
   TFile *oldfile = new TFile("Dplus_WC_Subset.root");
   TTree *oldtree = (TTree*)oldfile->Get("DecayTreeTuple/DecayTree");
   Double_t nentries = oldtree->GetEntries();
 
   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("Dplus_WC_random_subset.root","recreate");
   TTree *newtree = oldtree->CloneTree(0);

   //////////// Preselection Variables //////////////////////

   Double_t Xicc_OWNPV_CHI2;
   Double_t Xicc_IPCHI2_OWNPV;
   Double_t Ksoft_PIDK;
   Double_t Kminus_PIDK;
   Double_t pplus_PIDp;
   Double_t piplus1_PIDK;
   Double_t piplus2_PIDK;

   oldtree->SetBranchAddress("Xicc_OWNPV_CHI2",&Xicc_OWNPV_CHI2);
   oldtree->SetBranchAddress("Xicc_IPCHI2_OWNPV",&Xicc_IPCHI2_OWNPV);
   oldtree->SetBranchAddress("Ksoft_PIDK",&Ksoft_PIDK);
   oldtree->SetBranchAddress("Kminus_PIDK",&Kminus_PIDK);
   oldtree->SetBranchAddress("pplus_PIDp",&pplus_PIDp);
   oldtree->SetBranchAddress("piplus1_PIDK",&piplus1_PIDK);
   oldtree->SetBranchAddress("piplus2_PIDK",&piplus2_PIDK);

   /////////////////////////////////////////////////////////////////////

   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);

      if (gRandom->Rndm() < 0.015){
         if(Xicc_OWNPV_CHI2 <= 100 && Xicc_IPCHI2_OWNPV <=100 && Ksoft_PIDK >= 0 && Kminus_PIDK >= 0 && pplus_PIDp >=0 && (-1*piplus1_PIDK) >=0 && (-1*piplus2_PIDK) >=0)
            newtree->Fill();
         
      }
   }

   newtree->Print();
   newtree->AutoSave();
   delete oldfile;
   delete newfile;
}
