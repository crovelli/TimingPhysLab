#ifndef TimingRunAction_h
#define TimingRunAction_h 1

#include "TimingRun.hh"   
#include "TimingPrimaryGeneratorAction.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class TimingRunAction : public G4UserRunAction
{
public:
  TimingRunAction(TimingPrimaryGeneratorAction*);
  virtual ~TimingRunAction();
  
  virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

private:
  TimingPrimaryGeneratorAction* fPrimary;
};

#endif

