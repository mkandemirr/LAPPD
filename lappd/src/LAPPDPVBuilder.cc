#include "LAPPDPVBuilder.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"

#include "LAPPDLVFactory.hh"
#include "G4NistManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDPVBuilder::LAPPDPVBuilder(const G4String& modelName):
VComponentBuilder(),
mModelName{modelName}
{    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDPVBuilder::~LAPPDPVBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* LAPPDPVBuilder::Build()
{

  G4LogicalVolume* envelopeLV = LAPPDLVFactory::GetInstance()->
                                Get(mModelName);
                                
  G4Box* envelopeSolid = static_cast<G4Box*>(envelopeLV->GetSolid());
  
  G4double gap = 5 * mm;
  //Envelope world
  G4double worldSizeX = 2*envelopeSolid->GetXHalfLength() + gap;
  G4double worldSizeY = 2*envelopeSolid->GetYHalfLength() + gap;
  G4double worldSizeZ = 2*envelopeSolid->GetZHalfLength() + gap;
  
  G4Box* solidWorld = new G4Box(mModelName + "_envelopeWorldSolid", 
                              worldSizeX*0.5, 
                              worldSizeY*0.5, 
                              worldSizeZ*0.5
                              );

  
  auto vis_world = new G4VisAttributes(G4Colour(1.0, 0.9, 0.1, 0.4));
  
  G4Material* worldMat = G4NistManager::Instance()->
                         FindOrBuildMaterial("G4_AIR");
                            
                        
  G4LogicalVolume* worldLV = new G4LogicalVolume(solidWorld, worldMat, 
                                                "WorldLV");
                              
  vis_world->SetForceWireframe(true);
  worldLV->SetVisAttributes(vis_world);



  // 8. Place envelope in world
  auto *envelopePV = new G4PVPlacement(nullptr, 
    G4ThreeVector(0, 0, 0 * mm), 
    envelopeLV, 
    mModelName + "_envelopePV", 
    worldLV, 
    false, 
    0, 
    true);  


  //9. Place world
  G4VPhysicalVolume *worldPV = new G4PVPlacement(nullptr, 
                                G4ThreeVector(), 
                                worldLV, 
                                "WorldPV", 
                                nullptr, 
                                false, 
                                0, 
                                true);    



  return worldPV;
           
}

