#include "TimingAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "TimingHisto.hh"
#include "G4ProcessTable.hh"
#include "G4RadioactiveDecay.hh"
#include "G4TwoVector.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>

TimingAnalysisManager* TimingAnalysisManager::fManager = 0;

TimingAnalysisManager* TimingAnalysisManager::GetInstance()
{
  if(!fManager) fManager = new TimingAnalysisManager();
  
  return fManager;
}

void TimingAnalysisManager::Dispose()
{
  delete fManager;
  fManager = 0;
}

TimingAnalysisManager::TimingAnalysisManager()
  : fVerbose(0),
    fV1ThresE(20*keV), fV2ThresE(20*keV)
{
  fEdepo.clear();
  fHisto = new TimingHisto();
  BookHisto();
}

TimingAnalysisManager::~TimingAnalysisManager()     
{
  delete fHisto;
}

void TimingAnalysisManager::BookHisto()         
{
  fHistEMax = 2500;
  fHistEMin = 0;
  fHistTMax = 3000000000000000000;
  fHistTMin = 1000000000000000;
  fHistNBin = 100;

  fHisto->Add1D("H0", "Energy deposit (keV) in volume1", fHistNBin,fHistEMin,fHistEMax);
  fHisto->Add1D("H1", "Energy deposit (keV) in volume2", fHistNBin,fHistEMin,fHistEMax);
  fHisto->Add1D("H2", "1st Time deposit (nanosecond) in volume1", fHistNBin,fHistTMin,fHistTMax);
  fHisto->Add1D("H3", "1st Time deposit (nanosecond) in volume2", fHistNBin,fHistTMin,fHistTMax);
  fHisto->Add1D("H4", "Coincidence spectrum (keV) between volume1 and volume2",fHistNBin,fHistEMin,fHistEMax);
  fHisto->Add1D("H5", "Coincidence deltaT between volume1 and volume2",fHistNBin,-0.1,0.1);
  fHisto->Add1D("H6", "Decay emission spectrum (keV)",fHistNBin,fHistEMin,fHistEMax);
}
 
void TimingAnalysisManager::BeginOfRun()  
{
  fHisto->Book();
}

void TimingAnalysisManager::EndOfRun(G4int nevent)    
{
  fHisto->Save();
  G4cout << "TimingAnalysisManager: Histograms have been saved!" << G4endl;
}

void TimingAnalysisManager::BeginOfEvent()    
{
  fEdepo.clear();
}

void TimingAnalysisManager::EndOfEvent()        
{
  if (fEdepo.size()) {

    std::sort(fEdepo.begin(),fEdepo.end());    

    G4double firstTimeV1 = 0;
    G4double firstTimeV2 = 0;
    G4double V1E = 0;
    G4double V2E = 0;

    for (size_t i = 0; i < fEdepo.size(); i++) {
      if ( ((firstTimeV1==0) || (fEdepo[i].GetTime()<firstTimeV1)) && fEdepo[i].GetID() == 1 && fEdepo[i].GetEnergy() > fV1ThresE ) firstTimeV1 = fEdepo[i].GetTime();
      if ( ((firstTimeV2==0) || (fEdepo[i].GetTime()<firstTimeV2)) && fEdepo[i].GetID() == 2 && fabs(fEdepo[i].GetEnergy()) > fV2ThresE ) firstTimeV2 = fEdepo[i].GetTime();
      if ( fEdepo[i].GetID() == 1 ) {
	V1E += fEdepo[i].GetEnergy();
      } else if ( fEdepo[i].GetID() == 2 ) {
	V2E += fEdepo[i].GetEnergy();
      }
    }
    if (firstTimeV1>0) fHisto->FillHisto(2,firstTimeV1,1);      
    if (firstTimeV2>0) fHisto->FillHisto(3,firstTimeV2,1);      
    if (V1E) fHisto->FillHisto(0,V1E,1);        // V1 energy histogram
    if (V2E) fHisto->FillHisto(1,V2E,1);        // V2 energy histogram

    if (V2E >= fV2ThresE && V1E >= fV1ThresE ) {
      G4double minE = V2E;
      if (V1E<V2E) minE = V1E;
      fHisto->FillHisto(4,minE,1); // coincidence histogram, E
      fHisto->FillHisto(5,firstTimeV1-firstTimeV2,1); // coincidence histogram, dT
    }

    // now add zero energy to separate events
    AddEnergy(0,0.,0.,0.);
  }
}

void TimingAnalysisManager::AddEnergy(G4int vid, G4double edep, G4double weight, G4double time) 
{
  TimingEnergyDeposition A(vid,edep,time,weight);
  fEdepo.push_back(A);
}

// energy spectrum for particles emitted in decay 
void TimingAnalysisManager::AddParticle(G4double energy) 
{
  if (energy>0.0) fHisto->FillHisto(6,energy,1);
}


