
void BranchChange() {
   
   TFile *oldfile = new TFile("26165057_BothMag_Stripped_noPIDs_truthmatched_presel.root");
   TTree *oldtree = (TTree*)oldfile->Get("DecayTree");
   Double_t nentries = oldtree->GetEntries();
 
   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("26165057_BothMag_Stripped_noPIDs_truthmatched_presel_final.root","recreate");
   TTree *newtree = oldtree->CloneTree(0);

   //////////// Preselection Variables //////////////////////

   Double_t Xiccp_OWNPV_CHI2;
   Double_t Xiccp_IPCHI2_OWNPV;
   Double_t Km_PIDK;
   Double_t Kmsoft_PIDK;
   Double_t psoft_PIDp;
   Double_t Pip1_PIDK;
   Double_t Pip2_PIDK;
   Int_t Xicc_BKGCAT;

   oldtree->SetBranchAddress("Xiccp_OWNPV_CHI2",&Xiccp_OWNPV_CHI2);
   oldtree->SetBranchAddress("Xiccp_IPCHI2_OWNPV",&Xiccp_IPCHI2_OWNPV);
   oldtree->SetBranchAddress("Km_PIDK",&Km_PIDK);
   oldtree->SetBranchAddress("Kmsoft_PIDK",&Kmsoft_PIDK);
   oldtree->SetBranchAddress("psoft_PIDp",&psoft_PIDp);
   oldtree->SetBranchAddress("Pip1_PIDK",&Pip1_PIDK);
   oldtree->SetBranchAddress("Pip2_PIDK",&Pip2_PIDK);
   //oldtree->SetBranchAddress("eventNumber",&eventNumber);

   oldtree->SetAlias("Xiccp_MAXDOCA","Xicc_MAXDOCA");
   /////////////////////////////////////////////////////////////////////

   for (Long64_t i=0;i<nentries; i++) {
     if(i%1000==0) cout << "Processing event " << i << "..." << endl;
      oldtree->GetEntry(i);

      if(Xiccp_OWNPV_CHI2 <= 100 && Xiccp_IPCHI2_OWNPV <=100 && Km_PIDK >= 0 && Kmsoft_PIDK >= 0 && psoft_PIDp >=0 && (-1*Pip1_PIDK) >=0 && (-1*Pip2_PIDK) >=0)
         newtree->Fill();
         
   }

   newtree->Print();
   newtree->AutoSave();
   delete oldfile;
   delete newfile;
}
