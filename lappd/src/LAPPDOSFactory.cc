#include "LAPPDOSFactory.hh"
#include "G4OpticalSurface.hh"
#include "OpticalSurfaceBuilder.hh"

LAPPDOSFactory* LAPPDOSFactory::mInstance = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDOSFactory::LAPPDOSFactory():
  VComponentFactory()
{
  mMacrosDirectoryPath = "lappd/macros/os/"; //relative to CMAKE_BINARY_DIR
  
  //These are photoCathode surface
  mProductsMap.insert(std::make_pair("lappd", nullptr)); 
   
  //These are private surface 
  mProductsMap.insert(std::make_pair("mirror", nullptr)); 
  mProductsMap.insert(std::make_pair("stainlessSteel", nullptr)); 
  mProductsMap.insert(std::make_pair("pvcWhite", nullptr)); 
  mProductsMap.insert(std::make_pair("pvcBlack", nullptr));
  mProductsMap.insert(std::make_pair("polyethyleneBlack", nullptr)); 
  mProductsMap.insert(std::make_pair("tyvek", nullptr));
  
  
  
  
}  
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDOSFactory::~LAPPDOSFactory()
{   
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4OpticalSurface* LAPPDOSFactory::Create(const G4String& name)
{
  //Because there is no a container class for G4OpticalSurface objects(
  //like a G4LogicalVolumeStore for G4LogicalVolume objects),
  //we can not check whether an optical surface created before. So,
  //we create a map. Now, a product will only be created once.
  
  if (mProductsMap.find(name) != mProductsMap.end() ) 
  {
    if (mProductsMap.at(name) != nullptr)
      return mProductsMap.at(name); 
    
    mProductsMap.at(name) = CreateSurface(name, true);
    return mProductsMap.at(name);
  }else //not found
  {
    return nullptr;
  }
      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDOSFactory* LAPPDOSFactory::GetInstance()
{
  static LAPPDOSFactory instance;
  
  if (mInstance == nullptr)
  {
    mInstance = &instance;
  }
    
  return mInstance;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4OpticalSurface* LAPPDOSFactory::CreateSurface
(
  const G4String& name, 
  G4bool enableMatProp
)
{
  G4String macroFileName = name + "_os.mac";
  G4String macroFilePath = mMacrosDirectoryPath + macroFileName; 
  
  OpticalSurfaceBuilder builder(name, macroFilePath, enableMatProp);
  return builder.GetProduct();  
}

