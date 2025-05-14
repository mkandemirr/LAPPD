#include "DetectorPVBuilder.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4VisAttributes.hh"

#include "MaterialFactory.hh"
#include "LAPPDLVFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorPVBuilder::DetectorPVBuilder(const G4String& modelName):
VComponentBuilder(),
mModelName{modelName}
{    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorPVBuilder::~DetectorPVBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorPVBuilder::Build()
{

  //LAPPD
  G4LogicalVolume* lappdEnvelopeLV = LAPPDLVFactory::GetInstance()->
                                      Get(mModelName);

  G4LogicalVolume* lappdHousingLV = lappdEnvelopeLV->GetDaughter(0)->
                                      GetLogicalVolume(); 



  //Detector
  G4double detSizeX = 280*cm;
  G4double detSizeY = 300*cm;
  G4double detSizeZ = 250*cm;

  G4Box* detSolid = new G4Box(mModelName + "DetectorSolid", 
                                detSizeX*0.5, 
                                detSizeY*0.5, 
                                detSizeZ*0.5
                                );

  G4Material* detMat = MaterialFactory::GetInstance()->
                         Get("gdDopedWater");
                            
                        
  G4LogicalVolume* detectorLV = new G4LogicalVolume(detSolid, 
                                                detMat, 
                                                "DetectorLV");
  auto visDet = new G4VisAttributes(G4Colour(1.0, 0.5, 0.4, 0.4));                            
  visDet->SetForceWireframe(true);
  
  detectorLV->SetVisAttributes(visDet);
  
  // 1. Place lappds in detector
  
  G4int numX = 5;  // number of lappd along x
  G4int numY = 6;  // number of lappd along y

  // Boşluk dahil LAPPD aralıkları
  G4double spacingX = 500.0 * mm;  // X yönündeki boşluk dahil toplam aralık
  G4double spacingY = 500.0 * mm;  // Y yönündeki boşluk dahil toplam aralık
  G4double zPos  = 1000 * mm;   // LAPPD'lerin Z konumu


  // Y ekseninde 180 derece döndürme
  G4RotationMatrix* rotY180 = new G4RotationMatrix();
  rotY180->rotateY(180.0 * deg);


  for (G4int i = 0; i < numX; i++) 
  {
    for (G4int j = 0; j < numY; j++) 
    {
      G4double xPos = (i - (numX - 1) / 2.0) * spacingX;
      G4double yPos = (j - (numY - 1) / 2.0) * spacingY;

      // Pozitif Z side
      new G4PVPlacement(rotY180, 
                        G4ThreeVector(xPos, yPos, zPos), 
                        lappdHousingLV, 
                        "LAPPDHousingPV_"+ std::to_string(i * numY + j), 
                        detectorLV, 
                        false, 
                        i * numY + j, 
                        true);

      // Negatif Z side
      new G4PVPlacement(0, 
                        G4ThreeVector(xPos, yPos, -zPos), 
                        lappdHousingLV, 
                        "LAPPDHousingPV_"+ std::to_string(i * numY + j),
                        detectorLV, 
                        false, 
                        i * numY + j + 100,  // Farklı copy number
                        true);
    }
    
  }





  //world
  G4double gap = 3 * cm;
  G4double worldSizeX = detSizeX + gap;
  G4double worldSizeY = detSizeY + gap;
  G4double worldSizeZ = detSizeZ + gap;

  G4Box* solidWorld = new G4Box(mModelName + "WorldSolid", 
                                worldSizeX*0.5, 
                                worldSizeY*0.5, 
                                worldSizeZ*0.5
                                );

  G4Material* worldMat = MaterialFactory::GetInstance()->
                         Get("air");
                            
                        
  G4LogicalVolume* worldLV = new G4LogicalVolume(solidWorld, 
                                                worldMat, 
                                                "WorldLV");
  
  auto visWorld = new G4VisAttributes(G4Colour(1.0, 0.9, 0.1, 0.4));                            
  visWorld->SetForceWireframe(true);
  
  worldLV->SetVisAttributes(visWorld);



  //2. Place detector in world
  G4VPhysicalVolume *detectorPV = new G4PVPlacement(nullptr, 
                                      G4ThreeVector(), 
                                      detectorLV, 
                                      "DetectorPV", 
                                      worldLV, 
                                      false, 
                                      0, 
                                      true);   



  //3. Place world
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

