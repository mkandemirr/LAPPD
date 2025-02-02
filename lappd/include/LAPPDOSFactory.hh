#ifndef LAPPDOSFactory_h
#define LAPPDOSFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "VComponentFactory.hh"

class G4OpticalSurface;
class OpticalSurfaceBuilder;

//singleton class
class LAPPDOSFactory: public VComponentFactory<G4OpticalSurface>
{
  public:
    static LAPPDOSFactory* GetInstance();
    
    //Singletons should not be cloneable.
    LAPPDOSFactory(const LAPPDOSFactory&) = delete;
    
    //Singletons should not be assignable.
    LAPPDOSFactory& operator=(const LAPPDOSFactory&) = delete;
     
  protected:  
    LAPPDOSFactory();
    virtual ~LAPPDOSFactory();
      
    virtual G4OpticalSurface* Create(const G4String& name) override;
      
  private: //functions
    G4OpticalSurface* CreateSurface(const G4String& name, G4bool enableMatProp);
  
  private: //data members
    static LAPPDOSFactory* mInstance; //singleton class
    
    std::map<G4String, G4OpticalSurface*> mProductsMap;
    G4String mMacrosDirectoryPath;
                   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
