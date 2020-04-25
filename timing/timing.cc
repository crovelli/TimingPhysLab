#include "TimingDetectorConstruction.hh"
#include "TimingPhysicsList.hh"
#include "TimingActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "time.h"


int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  //set random seed with system time
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new TimingDetectorConstruction());       

  // Physics list    
  runManager->SetUserInitialization(new TimingPhysicsList());                
  
  // User action initialization
  runManager->SetUserInitialization(new TimingActionInitialization());
  
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;   
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  delete visManager;
  delete runManager; 
}  
