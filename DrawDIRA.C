int DrawTau()
{
  // Open the MC files
  TFile fgl("/Users/austin/Work/ntuple/MC/MCDecayTree.root");
  TTree *t2 = (TTree*)fgl.Get("MCDecayTree");
  
  // Define hist boundary
  Int_t Nbin = 100;
  Double_t xmin = 0;
  Double_t xmax = 0;
  
  // Define useful variables
  Double_t mcLcpx   = 0, mcLcpy   = 0, mcLcpz = 0;
  Double_t mcLcorix = 0, mcLcoriy = 0, mcLcoriz = 0;
  Double_t mcLcendx = 0, mcLcendy = 0, mcLcendz = 0;
  Double_t mcLctau = 0;

  // SetBranch
  t2->SetBranchAddress("Lcp_TRUEP_X",     &mcLcpx);
  t2->SetBranchAddress("Lcp_TRUEP_Y",     &mcLcpy);
  t2->SetBranchAddress("Lcp_TRUEP_Z",     &mcLcpz);
  t2->SetBranchAddress("Lcp_TRUEORIGINVERTEX_X", &mcLcorix);
  t2->SetBranchAddress("Lcp_TRUEORIGINVERTEX_Y", &mcLcoriy);
  t2->SetBranchAddress("Lcp_TRUEORIGINVERTEX_Z", &mcLcoriz);
  t2->SetBranchAddress("Lcp_TRUEENDVERTEX_X", &mcLcendx);
  t2->SetBranchAddress("Lcp_TRUEENDVERTEX_Y", &mcLcendy);
  t2->SetBranchAddress("Lcp_TRUEENDVERTEX_Z", &mcLcendz);
  t2->SetBranchAddress("Lcp_TRUETAU",         &mcLctau);
  Int_t N2 = t2->GetEntries(); 

  // Create plots
  TH1D mch1("mch1", "Lcp_FD_ORIVXZ", Nbin, xmin = 0, xmax = 30);
  TH1D mch2("mch2", "Lcp_FD_ORIVXR", Nbin, xmin = 0, xmax = 30);
  TH1D mch3("mch3", "Lcp_TRUETAU", Nbin, 0, 0.001); 
  TH1D mch4("mch4", "Lcp_DIRA_ORIVX", Nbin, xmin = 0.9999, xmax = 1);
  for ( int jentry = 0; jentry < N2; jentry++)
  {
    t2->GetEntry(jentry);
    
    // Fill FD in Z direction
    mch1.Fill(mcLcendz-mcLcoriz);
    
    // Fill FD of vector length
    mch2.Fill(sqrt( (mcLcendx-mcLcorix)*(mcLcendx-mcLcorix) + (mcLcendy-mcLcoriy)*(mcLcendy-mcLcoriy) + (mcLcendz-mcLcoriz)*(mcLcendz-mcLcoriz) ));
    
    // Fill lifetime
    mch3.Fill(mcLctau);

    // Fill DIRA
    mch4.Fill( ((mcLcendx-mcLcorix)*mcLcpx+(mcLcendy-mcLcoriy)*mcLcpy+(mcLcendz-mcLcoriz)*mcLcpz) / sqrt(mcLcpx*mcLcpx+mcLcpy*mcLcpy+mcLcpz*mcLcpz) / sqrt( (mcLcendx-mcLcorix)*(mcLcendx-mcLcorix) + (mcLcendy-mcLcoriy)*(mcLcendy-mcLcoriy) + (mcLcendz-mcLcoriz)*(mcLcendz-mcLcoriz) )  );
  }
  
  cout << mch4.GetEntries() << endl; 
  TCanvas c1("c1", "c1");
  mch4.Draw();
  gStyle->SetOptStat(kFALSE);
  
  // Draw the legend
  Double_t x1 = 0.6;
  Double_t y1 = 0.7;
  Double_t x2 = 0.89;
  Double_t y2 = 0.89;
  TLegend leg1(x1,y1,x2,y2);
  leg1.AddEntry(&mch3, Form("G.L. N = %5.2f", mch4.GetEntries()), "L");
  leg1.SetFillStyle(0);
  leg1.Draw();
  //gPad->SetLogx(1);  
  
  // Save the figure
  c1.SaveAs("./figure/Lcp_TRUETAU.png");
  
  // Close files 
  fgl.Close();
  return 0;
  //gApplication->Terminate();
}
    
  
   
