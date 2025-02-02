#ifndef LAPPDPVBuilder_h
#define LAPPDPVBuilder_h 1

#include "VComponentBuilder.hh"
#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LAPPDPVBuilder : public VComponentBuilder<G4VPhysicalVolume> {

  public:
    LAPPDPVBuilder(const G4String& modelName); 
    ~LAPPDPVBuilder();
    
  protected:  
    virtual G4VPhysicalVolume* Build() override;   
    
  private:
    G4String mModelName; 
};

#endif

