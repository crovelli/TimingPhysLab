#ifndef TimingDetectorConstruction_h
#define TimingDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class TimingDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  TimingDetectorConstruction();
  virtual ~TimingDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetScoringVolume1() const { return fScoringVolume1; }
  G4LogicalVolume* GetScoringVolume2() const { return fScoringVolume2; }
  
protected:
  G4LogicalVolume*  fScoringVolume1;
  G4LogicalVolume*  fScoringVolume2;
  
private:
  void DefineMaterials();
};

#endif

