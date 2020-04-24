#ifndef TimingPhysicsList_h
#define TimingPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include <vector>

class G4VPhysicsConstructor;
//class TimingPhysicsListMessenger;
class G4ProductionCuts;

class TimingPhysicsList: public G4VModularPhysicsList
{
public:
  TimingPhysicsList();
  virtual ~TimingPhysicsList();

  virtual void ConstructParticle();

  virtual void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);

  virtual void ConstructProcess();

private:

  // hide assignment operator
  TimingPhysicsList & operator=(const TimingPhysicsList &right);
  TimingPhysicsList(const TimingPhysicsList&);

  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;

  G4VPhysicsConstructor*  fEmPhysicsList;
  G4VPhysicsConstructor*  fRaddecayList;
  G4VPhysicsConstructor*  fParticleList;

  //TimingPhysicsListMessenger* fPMessenger;
};

#endif

