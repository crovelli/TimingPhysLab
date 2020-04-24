#ifndef TimingSteppingAction_h
#define TimingSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class TimingEventAction;

class G4LogicalVolume;

class TimingSteppingAction : public G4UserSteppingAction
{
  public:
    TimingSteppingAction(TimingEventAction* eventAction);
    virtual ~TimingSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    TimingEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume1;
    G4LogicalVolume* fScoringVolume2;
};

#endif
