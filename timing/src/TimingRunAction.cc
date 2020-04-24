#include "TimingRunAction.hh"
#include "TimingAnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include <G4Gamma.hh>

TimingRunAction::TimingRunAction(TimingPrimaryGeneratorAction* kin)
  : G4UserRunAction(),
    fPrimary(kin)
{}

TimingRunAction::~TimingRunAction()
{}

G4Run* TimingRunAction::GenerateRun()  
{
  return new TimingRun;
}

void TimingRunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  
  // Creation of the analysis manager
  TimingAnalysisManager* analysis = TimingAnalysisManager::GetInstance();
  analysis->BeginOfRun();
}

void TimingRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  // Total deposits
  const TimingRun* b1Run = static_cast<const TimingRun*>(run);
  G4double edep1 = b1Run->GetEdep1();
  G4double edep2 = b1Run->GetEdep2();

  // Get the analysis manager
  TimingAnalysisManager* analysis = TimingAnalysisManager::GetInstance();
  analysis->EndOfRun(run->GetNumberOfEvent());  

  // Print
  G4cout << "--------------------End of Run------------------------" << G4endl;
  G4cout << "The run consists of " << nofEvents << " events" << G4endl;
  G4cout << "Total deposited energy in volume1 = "  << edep1 << " [keV]" << G4endl;
  G4cout << "Total deposited energy in volume2 = "  << edep2 << " [keV]" << G4endl;
  G4cout << G4endl;
}

