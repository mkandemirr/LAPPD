#include "LAPPDMaterialFactory.hh"
#include "G4NistManager.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDMaterialFactory* LAPPDMaterialFactory::fInstance = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDMaterialFactory::LAPPDMaterialFactory():
VComponentFactory(),
mNumComponents{0},
mDensity{0.}
{
  mMacrosDirectoryPath = "lappd/macros/mpt/"; //relative to CMAKE_BINARY_DIR
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDMaterialFactory::~LAPPDMaterialFactory()
{    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::Create(const G4String& name)
{
  G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(name);
  if(mat) return mat;
 
  if (name == "air")
    return CreateAir(name);
  else if (name == "vacuum")
    return G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
  else if (name == "glass")
    return CreateGlass(name);
  else if (name == "rock")
    return CreateRock(name);   
  else if (name == "pmtVacuum")
    return CreatePmtVacuum(name);
  else if (name == "potassium")
    return CreatePotassium(name);
  else if (name == "borosilicateGlass")
    return CreateBorosilicateGlass(name);
  else if (name == "K2NaSb")
    return CreateK2NaSb(name);
 else
    return nullptr;  
       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::CreateAir(const G4String& name)
{
	// --- Air  N=70% O=30% ---------
  mDensity       = 1.29e-3*g/cm3;
  mNumComponents = 2;
  
  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
  mat-> AddElement(GetElement("N"), 70*perCent);
  mat-> AddElement(GetElement("O"), 30*perCent);
  
  MaterialPropertiesTable* mpt = GetMPT(name);
  mpt->DumpTable();
  
  mat->SetMaterialPropertiesTable(mpt);
  
	return mat;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4Material* LAPPDMaterialFactory::CreateGlass(const G4String& name)
{
  mDensity       = 2.2 * g/cm3;
  mNumComponents = 2;

  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
  mat->AddElement(GetElement("Si"), 0.4675);
  mat->AddElement(GetElement("O"), 0.5325);
  
  MaterialPropertiesTable* mpt = GetMPT(name);
  mpt->DumpTable();
  
  mat->SetMaterialPropertiesTable(mpt);

  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4Material* LAPPDMaterialFactory::CreateRock(const G4String& name)
{
  mDensity       = 2.7 * g/cm3;
  mNumComponents = 2;

  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
  mat->AddElement(GetElement("Si"), 0.4675);
  mat->AddElement(GetElement("O"), 0.5325);

  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::CreatePmtVacuum(const G4String& name)
{
  // --- PMT vacuum is very dilute air -------
  mDensity     = 1e-3 * CLHEP::kGasThreshold; //from PhysicalConstants.h
  mNumComponents = 1;
  G4double temperature = CLHEP::STP_Temperature;  //from PhysicalConstants.h
  G4double pressure    = CLHEP::STP_Pressure * mDensity / (1.29e-3*g/cm3);
   
  G4Material* mat = new G4Material(name, 
                                   mDensity, 
                                   mNumComponents, 
                                   kStateGas,
                                   temperature,
                                   pressure
                                   );
  
  mat->AddMaterial(G4NistManager::Instance()->
    FindOrBuildMaterial("G4_AIR"), 1.);                                 
                                   
  MaterialPropertiesTable* mpt = GetMPT(name);
  mpt->DumpTable();
                           
  mat->SetMaterialPropertiesTable(mpt);
  
  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::CreatePotassium(const G4String& name)
{
  // --- Stainless Steel  71% Fe, 19% Cr, 10% Ni ------
  mDensity       = 5.0*g/cm3;
  mNumComponents = 1;
  
  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
  mat-> AddElement(GetElement("K"), 1.0);
   
  return mat;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::CreateBorosilicateGlass(const G4String& name)
{
  G4NistManager* nist = G4NistManager::Instance();
  
  G4Material* K2O    = nist->FindOrBuildMaterial("G4_POTASSIUM_OXIDE");
  G4Material* B2O3   = nist->FindOrBuildMaterial("G4_BORON_OXIDE");
  G4Material* SiO2   = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material* Na2O   = nist->FindOrBuildMaterial("G4_SODIUM_MONOXIDE");
  G4Material* Al2O3  = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  
  mDensity = 2.23*g/cm3;
  mNumComponents = 5;
  // PMT-materials
  // mat
  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
                                            
  mat->AddMaterial(SiO2, 80.6 * perCent);
  mat->AddMaterial(B2O3, 13.0 * perCent);
  mat->AddMaterial(Na2O, 2.   * perCent); // 1/2 of wt% for (Na20+K20)
  mat->AddMaterial(K2O,  2.   * perCent); // 1/2 of wt% for (Na20+K20)
  mat->AddMaterial(Al2O3,2.31 * perCent);
  
  MaterialPropertiesTable* mpt = GetMPT(name);
  mpt->DumpTable();
  
  mat->SetMaterialPropertiesTable(mpt);
  
  return mat;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::CreateK2NaSb(const G4String& name)
{
  mDensity       = 3.2 * g / cm3;
  mNumComponents = 3;
  
  G4NistManager* nist = G4NistManager::Instance();
  G4Element* K = nist->FindOrBuildElement("K");  // Potassium
  G4Element* Na = nist->FindOrBuildElement("Na"); // Sodium
  G4Element* Sb = nist->FindOrBuildElement("Sb"); // Antimony

  // Define the Multi-Alkali material (K2NaSb)
  G4Material* mat = new G4Material(name, mDensity, mNumComponents);
  mat->AddElement(K, 2);  // 2 K atoms
  mat->AddElement(Na, 1); // 1 Na atom
  mat->AddElement(Sb, 1); // 1 Sb atom
  
  return mat; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Element* LAPPDMaterialFactory::GetElement(const G4String &symb, G4bool isotopes)
{
  return G4NistManager::Instance()->FindOrBuildElement(symb,isotopes); 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* LAPPDMaterialFactory::GetMaterial
(
  const G4String &name, 
  G4bool isotopes, 
  G4bool warning
)
{
  return G4NistManager::Instance()->FindOrBuildMaterial(name,isotopes,warning); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesTable* LAPPDMaterialFactory::GetMPT
(
  const G4String& name)
{
  G4String macroFilePath = mMacrosDirectoryPath + name + "_mpt.mac";
  
  MaterialPropertiesTable* mpt = new MaterialPropertiesTable(name);
  G4UImanager::GetUIpointer()->ExecuteMacroFile(macroFilePath);
  return mpt;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDMaterialFactory* LAPPDMaterialFactory::GetInstance()
{
  static LAPPDMaterialFactory instance;
  
  if(fInstance == nullptr)
  {
    fInstance = &instance;
  }
    
  return fInstance;
   
}
