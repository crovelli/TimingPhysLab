#ifndef TimingRun_h
#define TimingRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

class TimingRun : public G4Run
{
  public:
    TimingRun();
    virtual ~TimingRun();

    // method from the base class
    virtual void Merge(const G4Run*);
    
    void AddEdep1 (G4double edep1); 
    void AddEdep2 (G4double edep2); 

    // get methods
    G4double GetEdep1() const { return fEdep1; }
    G4double GetEdep2() const { return fEdep2; }

  private:
    G4double  fEdep1;
    G4double  fEdep2;
};

#endif

