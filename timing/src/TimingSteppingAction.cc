#include "TimingSteppingAction.hh"
#include "TimingEventAction.hh"
#include "TimingDetectorConstruction.hh"
#include "TimingAnalysisManager.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

TimingSteppingAction::TimingSteppingAction(TimingEventAction* eventAction)
  : G4UserSteppingAction(),
    fEventAction(eventAction),
    fScoringVolume1(0),
    fScoringVolume2(0)
{}

TimingSteppingAction::~TimingSteppingAction()
{}

void TimingSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* fTrack = step->GetTrack();
  G4int StepNo = fTrack->GetCurrentStepNumber();
  if(StepNo >= 10000) fTrack->SetTrackStatus(fStopAndKill);
  
  // this step
  G4double time   = step->GetPreStepPoint()->GetGlobalTime()/ns;
  G4double weight = step->GetPreStepPoint()->GetWeight();

  TimingAnalysisManager* analysis = TimingAnalysisManager::GetInstance();

  if (StepNo == 1) { //beginning of step                                                                      
    G4double energy = step->GetPreStepPoint()->GetKineticEnergy()/keV;
    G4String partType= fTrack->GetDefinition()->GetParticleType();

    // G4cout << "UserSteppingAction :: StepNo = " << StepNo << ", partType == " << partType << G4endl;
    // if (fTrack->GetTrackID() != 1 ) G4cout << "UserSteppingAction :: process = " << fTrack->GetCreatorProcess()->GetProcessName() << G4endl;
    
    // G4ParticleDefinition* thePartDef = fTrack->GetDefinition();
    // if (( partType == "nucleus") &&  !(thePartDef->GetPDGStable())) 
    // G4cout << "UserSteppingAction :: nucleus, time = " << time << G4endl;
    
    if (fTrack->GetTrackID() != 1 ){
      if (fTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay") {   //Radioactive decay products    

        // all products   
	//G4cout << "UserSteppingAction :: RadioactiveDecay => energy = " << energy/keV << ", time = " << time << ", partType = " << partType << G4endl; 

        // emitted particles except nuclei   
	if ( partType!= "nucleus") analysis->AddParticle(energy);    
      }
    }
  } // 1st step


  // energy deposition in crystal and bar
  if (!fScoringVolume1) { 
    const TimingDetectorConstruction* detectorConstruction
      = static_cast<const TimingDetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();   
  }
  if (!fScoringVolume2) { 
    const TimingDetectorConstruction* detectorConstruction
      = static_cast<const TimingDetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();   
  }
  
  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volumes
  if (volume != fScoringVolume1 && volume != fScoringVolume2) return;

  G4double edepStep = step->GetTotalEnergyDeposit()/keV;
  if (fTrack->GetTrackID() != 1 && edepStep) {
    if (volume == fScoringVolume1) analysis->AddEnergy(1,edepStep,weight,time);  
    if (volume == fScoringVolume2) analysis->AddEnergy(2,edepStep,weight,time);     
    if (volume == fScoringVolume1) fEventAction->AddEdep1(edepStep);  
    if (volume == fScoringVolume2) fEventAction->AddEdep2(edepStep);  
  }
}



