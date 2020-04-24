#ifndef TimingPhysListParticles_h
#define TimingPhysListParticles_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class TimingPhysListParticles : public G4VPhysicsConstructor
{
public: 
  TimingPhysListParticles(const G4String& name = "particles");
  virtual ~TimingPhysListParticles();
  
public: 
  // This method will be invoked in the Construct() method. 
  // each particle type will be instantiated
  virtual void ConstructParticle();
  
  // This method is dummy.
  virtual void ConstructProcess() {};
};

#endif








