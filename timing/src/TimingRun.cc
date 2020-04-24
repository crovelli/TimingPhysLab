#include "TimingRun.hh"

TimingRun::TimingRun()
: G4Run(),
  fEdep1(0.), 
  fEdep2(0.)
{} 

TimingRun::~TimingRun()
{} 

void TimingRun::Merge(const G4Run* run)
{
  const TimingRun* localRun = static_cast<const TimingRun*>(run);
  fEdep1 += localRun->fEdep1;
  fEdep2 += localRun->fEdep2;

  G4Run::Merge(run); 
} 

void TimingRun::AddEdep1(G4double edep1)
{
  fEdep1 += edep1;
}

void TimingRun::AddEdep2(G4double edep2)
{
  fEdep2 += edep2;
}
