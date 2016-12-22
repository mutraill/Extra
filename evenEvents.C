
void evenEvents() {
   
   TFile *oldfile = new TFile("Xicc+_DKp_BothMag_2012_10%_presel.root");
   TTree *oldtree = (TTree*)oldfile->Get("DecayTree");
   Double_t nentries = oldtree->GetEntries();
 
   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("Xicc+_DKp_BothMag_2012_1perc_presel_training.root","recreate");
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
   ULong64_t eventNumber;

   oldtree->SetBranchAddress("Xiccp_OWNPV_CHI2",&Xiccp_OWNPV_CHI2);
   oldtree->SetBranchAddress("Xiccp_IPCHI2_OWNPV",&Xiccp_IPCHI2_OWNPV);
   oldtree->SetBranchAddress("Km_PIDK",&Km_PIDK);
   oldtree->SetBranchAddress("Kmsoft_PIDK",&Kmsoft_PIDK);
   oldtree->SetBranchAddress("psoft_PIDp",&psoft_PIDp);
   oldtree->SetBranchAddress("Pip1_PIDK",&Pip1_PIDK);
   oldtree->SetBranchAddress("Pip2_PIDK",&Pip2_PIDK);
   oldtree->SetBranchAddress("eventNumber",&eventNumber);

   /////////////////////////////////////////////////////////////////////

   for (Long64_t i=0;i<nentries; i++) {
     if(i%1000==0) cout << "Processing event " << i << "..." << endl;
      oldtree->GetEntry(i);

      if(eventNumber%2 == 0){newtree->Fill();}
   }

   newtree->Print();
   newtree->AutoSave();
   delete oldfile;
   delete newfile;
}
