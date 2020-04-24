#ifndef TimingAnalysisManager_h
#define TimingAnalysisManager_h 1

#include "globals.hh"
#include "TimingEnergyDeposition.hh"
#include <vector>

class TimingHisto;

class TimingAnalysisManager
{

public:

  // With description
  static TimingAnalysisManager* GetInstance();
  static void Dispose();
  
private:
  
  TimingAnalysisManager();
  ~TimingAnalysisManager();

public: // Without description

  void BookHisto();

  void BeginOfRun();
  void EndOfRun(G4int);

  void BeginOfEvent();
  void EndOfEvent();

  void AddEnergy(G4double, G4double, G4double);
  void AddParticle(G4double, G4double);

  void SetVerbose(G4int val) {fVerbose = val;};
  G4int GetVerbose() const {return fVerbose;};

private:

  // MEMBERS
  static TimingAnalysisManager* fManager;

  G4int fVerbose;

  G4double fHistEMax;
  G4double fHistEMin;
  G4double fHistTMax;
  G4double fHistTMin;
  G4int fHistNBin;

  G4double fV1ThresE;
  G4double fV2ThresE;

  // energy depositions for an event
  std::vector <TimingEnergyDeposition> fEdepo;
  //
  TimingHisto*  fHisto;  
};

#endif
