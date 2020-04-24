#include "TimingActionInitialization.hh"
#include "TimingPrimaryGeneratorAction.hh"
#include "TimingRunAction.hh"
#include "TimingEventAction.hh"
#include "TimingSteppingAction.hh"

TimingActionInitialization::TimingActionInitialization()
 : G4VUserActionInitialization()
{}

TimingActionInitialization::~TimingActionInitialization()
{}

void TimingActionInitialization::BuildForMaster() const
{
  TimingRunAction* runAction = new TimingRunAction(0);
  SetUserAction(runAction);
}

void TimingActionInitialization::Build() const
{
  TimingPrimaryGeneratorAction* primary = new TimingPrimaryGeneratorAction();    
  SetUserAction(primary);

  TimingRunAction* runAction = new TimingRunAction(primary);                     
  SetUserAction(runAction);
  
  TimingEventAction* eventAction = new TimingEventAction();                      
  SetUserAction(eventAction);
  
  SetUserAction(new TimingSteppingAction(eventAction));                   
}  
