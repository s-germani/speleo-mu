////////////////////////////////////////////////////////////////////////
//  Macro ROOT per l'analisi dei risultati 
//
//
//  (2026) S. Germani - stefano.germani@unipg.it
//
////////////////////////////////////////////////////////////////////////


#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"


void SpeleoMuPlots(bool savePlots=false){

  gStyle->SetOptStat(0);

  // Open Inpunt file (copyed and renamed)
  TFile *smf = (TFile*) TFile::Open("SpeleoMu_100k.root");

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  //TTree *smtree = (TTree*) smf->Get("SpeleoMu");

  TTree *SpeleoMu;
  smf->GetObject("SpeleoMu", SpeleoMu);

  Double_t  E0 ;
  Double_t  p0x;
  Double_t  p0y;
  Double_t  p0z;
  Double_t  TrackLPrm;
  Double_t  EC ;
  Double_t  pCx;
  Double_t  pCy;
  Double_t  pCz;
  Double_t  ECv;
  Double_t  pCvx;
  Double_t  pCvy;
  Double_t  pCvz;
  Double_t  EF ;
  Double_t  pFx;
  Double_t  pFy;
  Double_t  pFz;  
  
  //------------------------------------------------------------------------
  
  SpeleoMu->SetBranchAddress( "E0",   &E0   );
  SpeleoMu->SetBranchAddress( "p0x",  &p0x  );
  SpeleoMu->SetBranchAddress( "p0y",  &p0y  );
  SpeleoMu->SetBranchAddress( "p0z",  &p0z  );
  SpeleoMu->SetBranchAddress( "TrackLPrm", &TrackLPrm );
  SpeleoMu->SetBranchAddress( "EC",   &EC   );
  SpeleoMu->SetBranchAddress( "pCx",  &pCx  );
  SpeleoMu->SetBranchAddress( "pCy",  &pCy  );
  SpeleoMu->SetBranchAddress( "pCz",  &pCz  );
  SpeleoMu->SetBranchAddress( "ECv",  &ECv  );
  SpeleoMu->SetBranchAddress( "pCvx", &pCvx );
  SpeleoMu->SetBranchAddress( "pCvy", &pCvy );
  SpeleoMu->SetBranchAddress( "pCvz", &pCvz );
  SpeleoMu->SetBranchAddress( "EF",   &EF   );
  SpeleoMu->SetBranchAddress( "pFx",  &pFx  );
  SpeleoMu->SetBranchAddress( "pFy",  &pFy  );
  SpeleoMu->SetBranchAddress( "pFz",  &pFz  );
			   

  ///////////////////////////////////////////////////////////////////////////////////////////////////

  TH1D *hE0   = new TH1D("hE0",   ";log10(E [GeV])", 80, 2, 4);
  TH1D *hE0C  = new TH1D("hE0C",  ";log10(E [GeV])", 80, 2, 4);
  TH1D *hE0Cv = new TH1D("hE0Cv", ";log10(E [GeV])", 80, 2, 4);
  TH1D *hE0F  = new TH1D("hE0F",  ";log10(E [GeV])", 80, 2, 4);


  TH1D *hEC = new TH1D("hEC", ";log10(E [GeV])", 80, 0, 4);




  TH2D *hpxy0    = new TH2D("hpxy0",    ";;", 50, -0.002, 0.002, 50, -0.002, 0.002);
  TH2D *hpxy0C   = new TH2D("hpxy0C",   ";;", 50, -0.002, 0.002, 50, -0.002, 0.002);
  TH2D *hpxy0Cv  = new TH2D("hpxy0Cv",  ";;", 50, -0.002, 0.002, 50, -0.002, 0.002);
  TH2D *hpxy0F   = new TH2D("hpxy0F",   ";;", 50, -0.002, 0.002, 50, -0.002, 0.002);

  TH2D *hpxyC   = new TH2D("hpxyC",   ";;", 50, -0.01, 0.01, 50, -0.01, 0.01);
  TH2D *hpxyCv  = new TH2D("hpxyCv",  ";;", 50, -0.01, 0.01, 50, -0.01, 0.01);
  TH2D *hpxyF   = new TH2D("hpxyF",   ";;", 50, -0.01, 0.01, 50, -0.01, 0.01);

  TH2D *hpxyCvF = new TH2D("hpxyCvF",   ";;", 50, -0.01, 0.01, 50, -0.01, 0.01);


  
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  
  int nentries = SpeleoMu->GetEntries();
  for( int iev=0; iev<nentries; iev++){
    
    SpeleoMu->GetEntry(iev);
    
    //cout << E0 << endl;

    hE0->Fill(log10(E0/1000));
    hpxy0->Fill(p0x, p0y);

    if(EC>0){
      hE0C->Fill(log10(E0/1000));      
      hpxy0C->Fill(p0x, p0y);
      hpxyC->Fill(pCx,  pCy);
    }

    if(ECv>0){
      hE0Cv->Fill(log10(E0/1000));      
      hpxy0Cv->Fill(p0x, p0y);
      hpxyCv->Fill(pCvx,  pCvy);
    }

    if(EF>0){
      hE0F->Fill(log10(E0/1000));      
      hpxy0F->Fill(p0x, p0y);
      hpxyF->Fill(pFx,  pFy);
      if(ECv>0)
	hpxyCvF->Fill(pFx,  pFy);
    }


  }



  //////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *ce = new TCanvas("ce");
  TLegend *le = new TLegend(0.7, 0.7, 0.9,0.9);
  le->SetFillStyle(0);
  le->SetBorderSize(0);

  hE0->SetLineColor(kRed+1);
  hE0->SetLineWidth(3);
  le->AddEntry(hE0, "E0 - All");
  hE0->Draw();

  hE0C->SetLineColor(kOrange+1);
  hE0C->SetLineWidth(3);
  le->AddEntry(hE0C, "E0 - Cattivo");
  hE0C->Draw("same");

  hE0F->SetLineColor(kGreen+1);
  hE0F->SetLineWidth(3);
  le->AddEntry(hE0F, "E0 - Fiume");
  hE0F->Draw("same");

  hE0Cv->SetLineColor(kAzure+1);
  hE0Cv->SetLineWidth(3);
  le->AddEntry(hE0Cv, "E0 - Cavity");
  hE0Cv->Draw("same");

  le->Draw();
  gPad->SetLogy();

  if(savePlots){
    ce->Print("E0.png");
    ce->Print("E0.pdf");
  }

  //////////////////////////////////////////////////////////////////////////////////////


  TCanvas *cp = new TCanvas("cp");
  cp->Divide(2,2);
  
  TLegend *lp = new TLegend(0.7, 0.7, 0.9,0.9);

  cp->cd(1);
  hpxy0->Draw("colz");
  gPad->SetLogz();


  cp->cd(2);
  hpxy0C->Draw("colz");
  gPad->SetLogz();

  cp->cd(3);
  hpxy0Cv->Draw("colz");
  gPad->SetLogz();

  cp->cd(4);
  hpxy0F->Draw("colz");
  gPad->SetLogz();


  TCanvas *cpd = new TCanvas("cpd");
  cpd->Divide(2,2);
  
  //TLegend *lp = new TLegend(0.7, 0.7, 0.9,0.9);

  cpd->cd(1);
  hpxyC->Draw("colz");
  gPad->SetLogz();

  cpd->cd(2);
  hpxyCv->Draw("colz");
  gPad->SetLogz();

  cpd->cd(3);
  hpxyF->Draw("colz");
  gPad->SetLogz();

  cpd->cd(4);
  hpxyCvF->Draw("colz");
  gPad->SetLogz();


  /*
  TCanvas *cpdiff = new TCanvas("cpdiff");

  TH2D *hdiffCF = (TH2D*) hpxyC->Clone("diffCF");
  hdiffCF->Add(hpxyF, -1);

  hdiffCF->Draw("colz");
  gPad->SetLogz();
  */

  TCanvas *cproj = new TCanvas("cproj");

  /*
  TH2D *hdiffCF = (TH2D*) hpxyC->Clone("diffCF");
  hdiffCF->Add(hpxyF, -1);

  TH1D *hdpx = (TH1D*) hdiffCF->ProjectionX("hdpx", 50, 51);
  hdpx->Draw();
  */

  TH1D *hpxF   = (TH1D*) hpxyF->ProjectionX("hpxF", 20, 25);
  TH1D *hpyF   = (TH1D*) hpxyF->ProjectionY("hpyF", 20, 25);
  TH1D *hpxCvF = (TH1D*) hpxyCvF->ProjectionX("hpxCvF", 20, 25);
  TH1D *hpyCvF = (TH1D*) hpxyCvF->ProjectionY("hpyCvF", 20, 25);

  /*
  hpxF->SetLineColor(kRed+1);
  hpxF->Draw();

  hpxCvF->SetLineColor(kGreen+1);
  hpxCvF->Draw("same");
  */

  hpxCvF->Divide(hpxF);
  hpxCvF->Draw();
  //  gPad->SetLogz();
  /*
  TLegend *legl = new TLegend(0.15, 0.7, 0.5, 0.9);
  legl->AddEntry(hLprm, "Primary Track");
  legl->AddEntry(hLall, "All Tracks");
  legl->SetBorderSize(0);
  legl->SetFillStyle(0);
  legl->Draw();
  //gPad->SetLogy();

  if(savePlots){
    cl->Print("EsercizioG4_Tlen.png");
    cl->Print("EsercizioG4_Tlen.pdf");
  }

   */

}
