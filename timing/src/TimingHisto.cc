#include "TROOT.h"
#include "TApplication.h"
#include "TGClient.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1D.h"

#include "TimingHisto.hh"
#include "G4ParticleTable.hh"

#include "G4Tokenizer.hh"

TimingHisto::TimingHisto()
  :fHistName("Timing"), fHistType("root"),
   fNHisto(0), fVerbose(0),
   fDefaultAct(1)
{
  fROOThisto.clear();

  fActive.clear();
  fBins.clear();
  fXmin.clear();
  fXmax.clear();
  fIds.clear();
  fTitles.clear();
}

TimingHisto::~TimingHisto()
{}

void TimingHisto::Book()
{
  G4String fileNameROOT = fHistName + G4String(".root");
  fHfileROOT = new TFile(fileNameROOT.c_str() ,"RECREATE","ROOT file for Timing");
  G4cout << "Root file for histos: " << fileNameROOT << G4endl;
  for(G4int i=0; i<fNHisto; i++) {
    if(fActive[i]) {
      G4String id = G4String("h")+fIds[i];
      fROOThisto[i] = new TH1D(id, fTitles[i], fBins[i], fXmin[i], fXmax[i]);
      G4cout << "ROOT Histo " << fIds[i] << " " << fTitles[i] << " booked " << G4endl;
    }
  }
} 

void TimingHisto::Save()
{
  G4cout << "ROOT: files writing..." << G4endl;
  fHfileROOT->Write();
  G4cout << "ROOT: files closing..." << G4endl;
  fHfileROOT->Close();
  delete fHfileROOT;
}

void TimingHisto::Add1D(const G4String& id, const G4String& name, G4int nb, G4double x1, G4double x2)
{
  if(fVerbose > 0) {
    G4cout << "New histogram will be booked: #" << id << "  <" << name 
           << "  " << nb << "  " << x1 << "  " << x2 << G4endl;
  }
  fNHisto++;
  fActive.push_back(fDefaultAct);
  fBins.push_back(nb);
  fXmin.push_back(x1);
  fXmax.push_back(x2);
  fIds.push_back(id);
  fTitles.push_back(name);
  fROOThisto.push_back(0);
}

void TimingHisto::SetHisto1D(G4int i, G4int nb, G4double x1, G4double x2, G4double u)
{
  if(i>=0 && i<fNHisto) {
    if(fVerbose > 0) {
      G4cout << "Update histogram: #" << i  
             << "  " << nb << "  " << x1 << "  " << x2 << "  " << u 
             << G4endl;
    }
    fBins[i] = nb;
    fXmin[i] = x1;
    fXmax[i] = x2;
  } else {
    G4cout << "TimingHisto::setTimingHisto1D: WARNING! wrong histogram index "
           << i << G4endl;
  }
}

void TimingHisto::FillHisto(G4int i, G4double x, G4double w)
{
  if(fVerbose > 1) {
    G4cout << "fill histogram: #" << i << " at x= " << x 
           << "  weight= " << w
           << G4endl;   
  }

  if(i>=0 && i<fNHisto) {
    fROOThisto[i]->Fill(x,w);
  } else {
    G4cout << "TimingHisto::fill: WARNING! wrong ROOT histogram index "
           << i << G4endl;
  }
}

void TimingHisto::ScaleHisto(G4int i, G4double x)
{
  if(fVerbose > 0) {
    G4cout << "Scale histogram: #" << i << " by factor " << x << G4endl;   
  }
  if(i>=0 && i<fNHisto) {
    fROOThisto[i]->Scale(x);
  } else {
    G4cout << "TimingHisto::scale: WARNING! wrong ROOT histogram index "
           << i << G4endl;
  }
}

void TimingHisto::SetFileName(const G4String& nam) 
{
  fHistName = nam;
}

const G4String& TimingHisto::GetFileName() const
{
  return fHistName;
}

void TimingHisto::SetFileType(const G4String& nam) 
{
  fHistType = nam;
}

const G4String& TimingHisto::FileType() const
{
  return fHistType;
}

