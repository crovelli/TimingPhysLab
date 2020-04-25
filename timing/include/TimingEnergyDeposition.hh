#ifndef TimingEnergyDeposition_h
#define TimingEnergyDeposition_h 1

#include "globals.hh"

class TimingEnergyDeposition
{
public:   
  TimingEnergyDeposition();
  TimingEnergyDeposition( const TimingEnergyDeposition &right );
  TimingEnergyDeposition( G4int, G4double, G4double, G4double );
  virtual ~TimingEnergyDeposition();

  G4bool operator==(const TimingEnergyDeposition &right) const ;
  G4bool operator< (const TimingEnergyDeposition &right) const ;
  G4bool operator<=(const TimingEnergyDeposition &right) const ;

  G4double GetEnergy() {return fEnergy;};
  G4double GetTime() {return fTime;};
  G4double GetWeight() {return fWeight;};
  G4double GetID() {return fID;};
  
private:
  G4int    fID;
  G4double fEnergy;  
  G4double fTime;    
  G4double fWeight;
};

#endif
