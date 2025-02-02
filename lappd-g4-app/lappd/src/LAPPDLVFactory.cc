#include "LAPPDLVFactory.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"

#include "LAPPDLVBuilder.hh"
#include "G4NistManager.hh"
#include <set>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVFactory* LAPPDLVFactory::mInstance = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVFactory::LAPPDLVFactory():
VComponentFactory()
{
  mMacrosDirectoryPath = "lappd/macros/lappds/";//relative to CMAKE_BINARY_DIR
  
  //available products in the factory.
  mProductsSet.insert("lappd");
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVFactory::~LAPPDLVFactory()
{  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* LAPPDLVFactory::Create(const G4String& modelName)
{
  mLVName = modelName + "_envelopeLV";
  
  G4LogicalVolume* lv = G4LogicalVolumeStore::GetInstance()->GetVolume(
    mLVName,
    false
    );
    
  if (lv) return lv;
  
  G4String macroFilePath = mMacrosDirectoryPath + modelName + ".mac";
  
  if (mProductsSet.find(modelName) != mProductsSet.end()) 
  {
    LAPPDLVBuilder builder(modelName, macroFilePath);
    return builder.GetProductInAnEnvelope();  
  }
  else // product is not available in the factory!
  {
    return nullptr;  
  }
        
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVFactory* LAPPDLVFactory::GetInstance()
{
  static LAPPDLVFactory instance;
  
  if(mInstance == nullptr)
  {
    mInstance = &instance;
  }
    
  return mInstance;
   
}

