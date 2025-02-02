#ifndef LAPPDLVFactory_h
#define LAPPDLVFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "VComponentFactory.hh"
#include <set>
class G4LogicalVolume;

//singleton class
class LAPPDLVFactory: public VComponentFactory<G4LogicalVolume>
{
  public:
    static LAPPDLVFactory* GetInstance();
    
    //Singletons should not be cloneable.
    LAPPDLVFactory(const LAPPDLVFactory&) = delete;
    
    //Singletons should not be assignable.
    LAPPDLVFactory& operator=(const LAPPDLVFactory&) = delete;
       
  protected:  
    LAPPDLVFactory();
    virtual ~LAPPDLVFactory();
      
    virtual G4LogicalVolume* Create(const G4String& name) override;
      
  private: 
    static LAPPDLVFactory* mInstance;  
    
    std::set<G4String> mProductsSet;
    G4String mMacrosDirectoryPath;
    G4String mLVName;
               
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
