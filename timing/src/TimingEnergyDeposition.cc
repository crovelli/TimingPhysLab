#include "TimingEnergyDeposition.hh"

TimingEnergyDeposition::TimingEnergyDeposition()
  : fEnergy(0.), fTime(0.),fWeight(1.)
{;}

TimingEnergyDeposition::TimingEnergyDeposition( G4double energy, G4double time, G4double weight )
  : fEnergy(energy),
    fTime(time),
    fWeight(weight)
{;}

TimingEnergyDeposition::TimingEnergyDeposition(const TimingEnergyDeposition &right )
  : fEnergy(right.fEnergy),
    fTime(right.fTime),
    fWeight(right.fWeight)
{;}
   
TimingEnergyDeposition::~TimingEnergyDeposition() {;}

G4bool TimingEnergyDeposition::operator==
                                          ( const TimingEnergyDeposition &right ) const
{
  return fTime == right.fTime;
}

G4bool TimingEnergyDeposition::operator<
                                    ( const TimingEnergyDeposition &right ) const
{
  return fTime < right.fTime;
}

G4bool TimingEnergyDeposition::operator<=
                                    ( const TimingEnergyDeposition &right ) const
{
  return fTime <= right.fTime;
}
