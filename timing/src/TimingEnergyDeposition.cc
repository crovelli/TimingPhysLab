#include "TimingEnergyDeposition.hh"

TimingEnergyDeposition::TimingEnergyDeposition()
  : fID(0),fEnergy(0.), fTime(0.),fWeight(1.)
{;}

TimingEnergyDeposition::TimingEnergyDeposition( G4int id, G4double energy, G4double time, G4double weight )
  : fID(id),
    fEnergy(energy),
    fTime(time),
    fWeight(weight)
{;}

TimingEnergyDeposition::TimingEnergyDeposition(const TimingEnergyDeposition &right )
  : fID(right.fID),
    fEnergy(right.fEnergy),
    fTime(right.fTime),
    fWeight(right.fWeight)
{;}
   
TimingEnergyDeposition::~TimingEnergyDeposition() {;}

G4bool TimingEnergyDeposition::operator==
                                          ( const TimingEnergyDeposition &right ) const
{
  if (fID != right.fID)
    return fID == right.fID;
  else
    return fTime == right.fTime;
}

G4bool TimingEnergyDeposition::operator<
                                    ( const TimingEnergyDeposition &right ) const
{
  if (fID != right.fID)
    return fID < right.fID;
  else
    return fTime < right.fTime;
}

G4bool TimingEnergyDeposition::operator<=
                                    ( const TimingEnergyDeposition &right ) const
{
  if (fID != right.fID)
    return fID <= right.fID;
  else
    return fTime <= right.fTime;
}
