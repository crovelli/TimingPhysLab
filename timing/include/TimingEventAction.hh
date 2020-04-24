#ifndef TimingEventAction_h
#define TimingEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
class TimingEventAction : public G4UserEventAction
{
public:
  TimingEventAction();
  virtual ~TimingEventAction();
  
  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);
  
  void AddEdep1(G4double edep1) { fEdep1 += edep1; }
  void AddEdep2(G4double edep2) { fEdep2 += edep2; }
  
private:
  G4double     fEdep1;
  G4double     fEdep2;
};

#endif

    
