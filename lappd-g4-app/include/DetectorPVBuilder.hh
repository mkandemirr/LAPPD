#ifndef DetectorPVBuilder_h
#define DetectorPVBuilder_h 1

#include "VComponentBuilder.hh"
#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorPVBuilder : public VComponentBuilder<G4VPhysicalVolume> {

  public:
    DetectorPVBuilder(const G4String& modelName); 
    ~DetectorPVBuilder();
    
  protected:  
    virtual G4VPhysicalVolume* Build() override;   
    
  private:
    G4String mModelName; 
};

#endif

