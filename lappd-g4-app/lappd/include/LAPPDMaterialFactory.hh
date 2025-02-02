#ifndef LAPPDMaterialFactory_h
#define LAPPDMaterialFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "VComponentFactory.hh"

class MaterialPropertiesTable;

//singleton class
class LAPPDMaterialFactory: public VComponentFactory<G4Material>
{
  public:
    static LAPPDMaterialFactory* GetInstance();
    
    //Singletons should not be cloneable.
    LAPPDMaterialFactory(const LAPPDMaterialFactory&) = delete;
    
    //Singletons should not be assignable.
    LAPPDMaterialFactory& operator=(const LAPPDMaterialFactory&) = delete;
     
  protected:  
    LAPPDMaterialFactory();
    virtual ~LAPPDMaterialFactory();
      
    virtual G4Material* Create(const G4String& name) override;
      
  private:
    G4Material* CreateAir(const G4String& name); 
    G4Material* CreateGlass(const G4String& name);
    G4Material* CreateRock(const G4String& name);
    G4Material* CreatePmtVacuum(const G4String& name);
    G4Material* CreatePotassium(const G4String& name);
    G4Material* CreateBorosilicateGlass(const G4String& name);
    G4Material* CreateK2NaSb(const G4String& name);
    
    
    MaterialPropertiesTable* GetMPT(const G4String& name);

    G4Element* GetElement(const G4String &symb, G4bool isotopes=true);
    G4Material* GetMaterial(
      const G4String &name, 
      G4bool isotopes = true, 
      G4bool warning = false
      );
      
  private: //members
    static LAPPDMaterialFactory* fInstance;  //singleton class
    
    G4String mMacrosDirectoryPath;

    G4int mNumComponents;
    G4double mDensity;
                   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
