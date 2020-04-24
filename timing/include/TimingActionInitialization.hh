#ifndef TimingActionInitialization_h
#define TimingActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TimingActionInitialization : public G4VUserActionInitialization
{
  public:
    TimingActionInitialization();
    virtual ~TimingActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
