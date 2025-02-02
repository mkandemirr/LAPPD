#include "LAPPDLVBuilder.hh"
#include "LAPPDLVBuilderMsgr.hh"

#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"

#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"

#include "LAPPDMaterialFactory.hh"
#include "LAPPDOSFactory.hh"

#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVBuilder::LAPPDLVBuilder(const G4String& pModelName,
                               const G4String& pMacroFilePath):
                           
VComponentBuilder(),
mModelName{pModelName},
mMacroFilePath{pMacroFilePath},
mPrefix{pModelName},
mEnvelopeMat{nullptr}
{
  mMessenger = new LAPPDLVBuilderMsgr(this);
  Initialize(); 
  
  SetInputParametersWithAMacroFile();
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVBuilder::~LAPPDLVBuilder()
{
  delete mMessenger; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetInputParametersWithAMacroFile()
{
  if (mMacroFilePath == "") 
  {
    G4String macrosDirectoryPath = "lappd/macros/lappds/";
    mMacroFilePath = macrosDirectoryPath + mModelName + ".mac";  
  }

  G4UImanager::GetUIpointer()->ExecuteMacroFile(mMacroFilePath);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::Initialize()
{
  //Stripts
  mEnableStrips = false;
  //activeLayer
  mNumberOfActiveLayer = 28; 
  mActiveLayerWidth = 5.2 *mm; //along x
  mActiveLayerThickness = 2*mm; //along z

  //InactiveLayer 
  mNumberOfInactiveLayer = 27;

  mInactiveLayerWidth = 1.7 *mm; //along x
  mInactiveLayerThickness = 2*mm; //along z

  mPhotocathodeHalfSizeZ = 2 * mm;
  
   //FrontSpacer
  mFrontSpacerHalfSizeX = 1 * mm;
  mFrontSpacerHalfSizeY = (95.75 * sqrt(2) - 2) * mm;
  mFrontSpacerHalfSizeZ = 1 * mm; //thickness

  mFrontSpacerPhotocathodeGap = 1 * mm;

  //BackSpacer
  mBackSpacerHalfSizeX = 1 * mm;
  mBackSpacerHalfSizeY = (95.75 * sqrt(2) - 2) * mm;
  mBackSpacerHalfSizeZ = 1 * mm; //thickness

  mBackSpacerFrontSpacerGap = 0 * mm;


  mSpacersGap = 8 * mm; //centre distance

    
  //MCP
  mMcpHalfSizeX = 95. * mm;
  mMcpHalfSizeY = 95. * mm;
  mMcpHalfSizeZ = 1 * mm;

  //****The belows are controlled by UI commands!*******
  
  mHousingWindowHalfSizeX = 95.75 * mm;
  mHousingWindowHalfSizeY = 95.75 * mm;
  mHousingWindowHalfSizeZ = 5 * mm;
  
  // Housing
  mHousingHalfSizeX = 95.75 + 5 * mm;
  mHousingHalfSizeY = 95.75 + 5 * mm;
  mHousingHalfSizeZ = 55 * mm ;
  
  //z direction
  mAirGapHalfSizeZ =  20 * mm;
  mPhotocathodeWindowHalfSizeZ = 0.25 * mm;
  mPhotocathodeGapHalfSizeZ = 0.25 * mm;
  
  // Photocathode
  mPhotocathodeHalfSizeX = 95.75 * mm;
  mPhotocathodeHalfSizeY = 95.75 * mm;
  
  //Materials
  mPhotocathodeWindowMatName = "borosilicateGlass";
  mHousingWindowMatName = "glass";
  
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* LAPPDLVBuilder::GetProductInAnEnvelope(G4Material* pEnvMat)
{
  assert(pEnvMat);
  
  mEnvelopeMat = pEnvMat;
  mUseEnvelope = true;
  return GetProduct();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* LAPPDLVBuilder::Build()
{ 
  G4bool checkOverlaps = true;

  //rock material is used for volumes that are just for visualization,
  //including spacers, mcps and strips
  G4Material* rock = LAPPDMaterialFactory::GetInstance()->
                                Get("rock");
  

  //Dependent parameters should be here! G4InitState
  
  //AirGap
  G4double housingSkinSurfaceTolerance = 0.001 * mm;
  mAirGapHalfSizeX = mHousingHalfSizeX - housingSkinSurfaceTolerance;
  mAirGapHalfSizeY = mHousingHalfSizeY - housingSkinSurfaceTolerance;
  
  // Entrance window/PhotocathodeWindow/LAPPDWindow
  mPhotocathodeWindowHalfSizeX = mPhotocathodeHalfSizeX;
  mPhotocathodeWindowHalfSizeY = mPhotocathodeHalfSizeY;
  
  //PhotocathodeToWindowGap
  mPhotocathodeGapHalfSizeX = mPhotocathodeWindowHalfSizeX;
  mPhotocathodeGapHalfSizeY = mPhotocathodeWindowHalfSizeY;
  
  // Envelope
  mEnvelopeHalfSizeX = mHousingHalfSizeX + 1 * mm;
  mEnvelopeHalfSizeY = mHousingHalfSizeY + 1 * mm;
  mEnvelopeHalfSizeZ = mHousingHalfSizeZ + 1 * mm; 
  
  
  //Define material,solid and logic

  //1. Envelope
  G4Material* envMat = mEnvelopeMat;
  G4Box *envelopeSolid = new G4Box(mPrefix + "_envelopeSolid", 
                                    mEnvelopeHalfSizeX, 
                                    mEnvelopeHalfSizeY,
                                    mEnvelopeHalfSizeZ);
                                  
  auto envelopeLV = new G4LogicalVolume(envelopeSolid, envMat, 
                                        mPrefix + "_envelopeLV");
                             
  
  //2. LAPPDHousing
  G4Material * housingMat = LAPPDMaterialFactory::GetInstance()->Get("air");
  G4Box *housingSolid = new G4Box(mPrefix + "_housingSolid", 
                                      mHousingHalfSizeX, 
                                      mHousingHalfSizeY, 
                                      mHousingHalfSizeZ);
                                      
  auto housingLV = new G4LogicalVolume(housingSolid, 
                            housingMat, 
                            mPrefix + "_housingLV");
                             

    
  //3. HousingWindow
  G4Material *housingWindowMat = LAPPDMaterialFactory::GetInstance()->
                                  Get(mHousingWindowMatName);
  
  G4Box *housingWindowSolid = new G4Box(mPrefix + "_housingWindowSolid", 
                                      mHousingWindowHalfSizeX, 
                                      mHousingWindowHalfSizeY, 
                                      mHousingWindowHalfSizeZ);
                                      
  auto housingWindowLV = new G4LogicalVolume(housingWindowSolid, 
                                          housingWindowMat, 
                                          mPrefix + "_housingWindowLV");
                               
  
  //4. AirGap
  G4Material *airGapMat = LAPPDMaterialFactory::GetInstance()->Get("air");
  G4Box *airGapSolid = new G4Box(mPrefix + "_airGapSolid", 
                                mAirGapHalfSizeX, 
                                mAirGapHalfSizeY, 
                                mAirGapHalfSizeZ);
                                      
  auto airGapLV = new G4LogicalVolume(airGapSolid, 
                            airGapMat, 
                            mPrefix + "_airGapLV");
                             
  
  //5. PhotocathodeWindow or LAPPD window
  G4Material* photocathodeWindowMat = LAPPDMaterialFactory::GetInstance()->
                              Get(mPhotocathodeWindowMatName);
  G4Box *photocathodeWindowSolid = new G4Box(mPrefix + 
                                      "_photocathodeWindowSolid", 
                                      mPhotocathodeWindowHalfSizeX, 
                                      mPhotocathodeWindowHalfSizeY, 
                                      mPhotocathodeWindowHalfSizeZ);
                               
  auto photocathodeWindowLV = new G4LogicalVolume(photocathodeWindowSolid, 
                                  photocathodeWindowMat, 
                                  mPrefix + "_photocathodeWindowLV");
                             
  
  //6. PhotocathodeGap                            
  G4Material* photocathodeGapMat = LAPPDMaterialFactory::GetInstance()->
                                Get("pmtVacuum");
  G4Box * photocathodeGapSolid = new G4Box(mPrefix + "_photocathodeGapSolid",  
                                mPhotocathodeGapHalfSizeX,  
                                mPhotocathodeGapHalfSizeY, 
                                mPhotocathodeGapHalfSizeZ);
                                
  auto  photocathodeGapLV = new G4LogicalVolume( photocathodeGapSolid, 
                               photocathodeGapMat, 
                               mPrefix +"_photocathodeGapLV");
                             
  
  //7. Photocathode                            
  G4Material* photocathodeMat = LAPPDMaterialFactory::GetInstance()->
                                Get("K2NaSb");
  G4Box * photocathodeSolid = new G4Box(mPrefix + "_photocathodeSolid",  
                                mPhotocathodeHalfSizeX,  
                                mPhotocathodeHalfSizeY, 
                                mPhotocathodeHalfSizeZ);
                                
  auto  photocathodeLV = new G4LogicalVolume( photocathodeSolid, 
                           photocathodeMat, 
                           mPrefix +"_photocathodeLV"); //do not change
                                                             //this name!!
                             
  
  
  //PLACEMENT
  
  //1. Place HousingWindow in Housing
  G4double housingWindowPosZ = mHousingHalfSizeZ - mHousingWindowHalfSizeZ;
  
  G4ThreeVector housingWindowPos(0,0,housingWindowPosZ);
  
  auto housingWindowPV = new G4PVPlacement(0, 
    housingWindowPos, 
    housingWindowLV, 
    mPrefix + "_housingWindowPV", 
    housingLV, 
    false, 
    0,
    checkOverlaps); 
    
    
  //2. Place AirGap in Housing
  G4double airGapPosZ = housingWindowPosZ - mHousingWindowHalfSizeZ - 
                          mAirGapHalfSizeZ;
                            
  
  G4ThreeVector airGapPos(0, 0, airGapPosZ);
  
  auto airGapPV = new G4PVPlacement(0, 
    airGapPos, 
    airGapLV, 
    mPrefix + "_airGapPV", 
    housingLV, 
    false, 
    0,
    checkOverlaps);   
   
     
  //3. Place PhotocathodeWindow in Housing
  G4double photocathodeWindowPosZ = airGapPosZ - mAirGapHalfSizeZ - 
                             mPhotocathodeWindowHalfSizeZ;
  
  G4ThreeVector photocathodeWindowPos(0,0,photocathodeWindowPosZ);
  
  auto photocathodeWindowPV = new G4PVPlacement(0, 
    photocathodeWindowPos, 
    photocathodeWindowLV, 
    mPrefix + "_photocathodeWindowPV", 
    housingLV, 
    false, 
    0,
    checkOverlaps);
    
    
  //4. Place PhotocathodeGap in Housing
  G4double photocathodeGapPosZ = photocathodeWindowPosZ - 
                                 mPhotocathodeWindowHalfSizeZ - 
                                 mPhotocathodeGapHalfSizeZ;
  
  G4ThreeVector photocathodeGapPos(0, 0, photocathodeGapPosZ);
  
  auto photocathodeGapPV = new G4PVPlacement(0, 
    photocathodeGapPos, 
    photocathodeGapLV, 
    mPrefix + "_photocathodeGapPV", 
    housingLV, 
    false, 
    0,
    checkOverlaps);
 
  
  //5. Place Photocathode in Housing
  G4double photocathodePosZ = photocathodeGapPosZ - 
                              mPhotocathodeGapHalfSizeZ - 
                              mPhotocathodeHalfSizeZ;                            
  
  G4ThreeVector photocathodePos(0., 0., photocathodePosZ);
  
  auto photocathodePV = new G4PVPlacement(0, 
    photocathodePos, 
     photocathodeLV, 
    mPrefix + "_photocathodePV", 
    housingLV, 
    false, 
    0,
    checkOverlaps);
    


  //Just for visualization!
  
  if (mEnableStrips) 
  {
  

    //FrontSpacer
    G4Box *frontSpacerSolid = new G4Box(mPrefix + "_frontSpacerSolid", 
                                        mFrontSpacerHalfSizeX, 
                                        mFrontSpacerHalfSizeY, 
                                        mFrontSpacerHalfSizeZ);
                                        
    auto frontSpacerLV = new G4LogicalVolume(frontSpacerSolid, 
                              rock, 
                              mPrefix + "_frontSpacerLV");
                               
    
    //BackSpacer
    G4Box *backSpacerSolid = new G4Box(mPrefix + "_backSpacerSolid", 
                                mBackSpacerHalfSizeX, 
                                mBackSpacerHalfSizeY, 
                                mBackSpacerHalfSizeZ
                                );
                                
                                
    auto backSpacerLV = new G4LogicalVolume(backSpacerSolid, rock, 
                                            mPrefix + "_backSpacerLV");
                               
    
    //MCP
    G4Box * mcpSolid = new G4Box(mPrefix + "_mcpSolid",  
                                mMcpHalfSizeX,  
                                mMcpHalfSizeY, 
                                mMcpHalfSizeZ);
    
    auto  mcpLV = new G4LogicalVolume( mcpSolid, rock, 
                                      mPrefix + "_mcpLV");
                               
    
    //Stripts
    G4double activeLayerHalfSizeX =  mActiveLayerWidth*0.5;
    G4double activeLayerHalfSizeY = mPhotocathodeHalfSizeY; 
    G4double activeLayerHalfSizeZ = mActiveLayerThickness*0.5;

    //Active                          
    G4Box* activeLayerSolid = new G4Box(mPrefix + "_activeLayerSolid", 
                                activeLayerHalfSizeX, 
                                activeLayerHalfSizeY, 
                                activeLayerHalfSizeZ);
                                
    G4LogicalVolume* activeLayerLV = new G4LogicalVolume(activeLayerSolid, 
                                      rock, 
                                      mPrefix + "_activeLayerLV");
    
      
    //Inactive 
    G4double inactiveLayerHalfSizeX =  mInactiveLayerWidth*0.5;
    G4double inactiveLayerHalfSizeY =  mPhotocathodeHalfSizeY;
    G4double inactiveLayerHalfSizeZ =  mInactiveLayerThickness*0.5;
                              
    G4Box* inactiveLayerSolid = new G4Box(mPrefix + "_inactiveLayerSolid", 
                                          inactiveLayerHalfSizeX, 
                                          inactiveLayerHalfSizeY, 
                                          inactiveLayerHalfSizeZ);
                                          
    G4LogicalVolume* inactiveLayerLV = new G4LogicalVolume(inactiveLayerSolid, 
                                        rock, 
                                        mPrefix + "_inactiveLayerLV");
       

    //6. Place spacers in housing
    G4double frontSpacerPosZ = photocathodePosZ - mPhotocathodeHalfSizeZ - 
                               mFrontSpacerPhotocathodeGap - 
                               mFrontSpacerHalfSizeZ;
    
    G4ThreeVector frontSpacerPos(0.0, 0.0, frontSpacerPosZ);

    G4RotationMatrix** frontSpacerRot = new G4RotationMatrix*[3];
    
    
   
    G4double backSpacerPosZ = frontSpacerPosZ - mFrontSpacerHalfSizeZ - 
                              mBackSpacerFrontSpacerGap - mBackSpacerHalfSizeZ;
    
    G4ThreeVector backSpacerPos(0.0, 0.0, backSpacerPosZ);

    G4RotationMatrix** backSpacerRot = new G4RotationMatrix*[3];
    
    
    G4double frontSpacerTranslationZ = mFrontSpacerHalfSizeZ + 
                                        2 * mBackSpacerHalfSizeZ + 
                                        mSpacersGap + mFrontSpacerHalfSizeZ; 
    
    G4double backSpacerTranslationZ = mBackSpacerHalfSizeZ + mSpacersGap + 
                                      2 * mFrontSpacerHalfSizeZ + 
                                      mBackSpacerHalfSizeZ;
    
    
    for (int i = 0; i<3; ++i)
    {

      frontSpacerRot[i] = new G4RotationMatrix();
      frontSpacerRot[i]->rotateZ(45*deg);

      new G4PVPlacement(frontSpacerRot[i], 
                        frontSpacerPos, 
                        frontSpacerLV, 
                        mPrefix + "_spacer" + std::to_string(i) + "Front_PV", 
                        housingLV, 
                        false, 
                        0,
                        checkOverlaps);

      backSpacerRot[i] = new G4RotationMatrix();
      backSpacerRot[i]->rotateZ(135*deg);

    


     new G4PVPlacement(backSpacerRot[i], 
                      backSpacerPos,
                      frontSpacerLV, 
                       mPrefix + "_spacer" + std::to_string(i) + "BackPV",  
                      housingLV, 
                      false, 
                      0,
                      checkOverlaps);
      
      frontSpacerPos = frontSpacerPos - G4ThreeVector(0., 0., 
                                        frontSpacerTranslationZ); 
      backSpacerPos = backSpacerPos - G4ThreeVector(0., 0., 
                                      backSpacerTranslationZ);   
      
    }  
     
    // 7. Place two MCPs in housing
    G4double mcp1PosZ = backSpacerPosZ - mBackSpacerHalfSizeZ - mSpacersGap/2.;
    G4ThreeVector mcp1Pos(0,0,mcp1PosZ);
    
    
    new G4PVPlacement(0, 
      mcp1Pos, 
      mcpLV, 
      mPrefix + "_mcp1PV", 
      housingLV, 
      false, 
      0,
      checkOverlaps);

    G4double mcp2PosZ = mcp1PosZ - 2 * mFrontSpacerHalfSizeZ - 
                        2 * mBackSpacerHalfSizeZ - mSpacersGap;   
    
    G4ThreeVector mcp2Pos(0,0,mcp2PosZ);

    new G4PVPlacement(0, 
        mcp2Pos, 
        mcpLV, 
        mPrefix + "_mcp2PV", 
        housingLV, 
        false, 
        0,
        checkOverlaps);
    
       
    // 8 .Place strips in housing
      
    for (int i = 0; i< mNumberOfActiveLayer; ++i)
    {
      G4double x1 = mPhotocathodeHalfSizeX - mActiveLayerWidth*0.5 - 
                    i * (mInactiveLayerWidth + mActiveLayerWidth);
                    
      G4double x2 = mPhotocathodeHalfSizeX - mActiveLayerWidth - 
                    mInactiveLayerWidth * 0.5 - 
                    i * (mInactiveLayerWidth + mActiveLayerWidth);
      
      G4double y = 0.;
      G4double gapStripsAndHousing = 1*mm; //along z
      G4double z = -mHousingHalfSizeZ + mActiveLayerThickness*0.5 + 
                    gapStripsAndHousing;


      new G4PVPlacement(0, 
          G4ThreeVector(x1,y,z), 
          activeLayerLV, 
          mPrefix + "_activeLayerPV_" + std::to_string(i), 
          housingLV, 
          false, 
          0,
          checkOverlaps);

      if (i == (mNumberOfActiveLayer - 1) ) break;

      new G4PVPlacement(0, 
          G4ThreeVector(x2,y,z), 
          inactiveLayerLV, 
          mPrefix + "_inactiveLayerPV_" + std::to_string(i), 
          housingLV, 
          false, 
          0,
          checkOverlaps);

    }
  
  
  
  }
  
  
  
   
  // 9. Place housing in envelope.
  auto *housingPV = new G4PVPlacement(nullptr, 
    G4ThreeVector(0, 0, 0 * mm), 
    housingLV, 
    mPrefix + "_housingPV", 
    envelopeLV, 
    false, 
    0, 
    true);  
    
  
  SetVisAttributes();
   
  BuildPhotocathodeSurface(photocathodePV, photocathodeGapPV);
   
  
  if (mUseEnvelope) 
  {
    //Build optical surfaces!
    BuildHousingSurface(housingLV);
    
    //CreatePmtOpticalPhotonSimulationModel(photocathodeSurface);
    return envelopeLV;
  }
  
  return housingLV;           

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::BuildPhotocathodeSurface
(
  G4PVPlacement* photocathodePV,
  G4PVPlacement* photocathodeGapPV
)
{
  G4OpticalSurface* os = LAPPDOSFactory::GetInstance()->Get("lappd");
  
  G4String mPrefix = "lappd";
  
  new G4LogicalBorderSurface(mPrefix + "_photocathodeSurface2",
                                    photocathodeGapPV, 
                                    photocathodePV,
                                    os
                                    );                                 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::BuildHousingSurface(G4LogicalVolume* housingLV)
{
  const int numEntries = 2;
  G4double energy[numEntries] = { 1.*eV, 6 * eV }; 
  G4double reflectivity[numEntries] = { 0.1, 0.1 };  

  
  G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
  mpt->AddProperty("REFLECTIVITY", energy, reflectivity, numEntries);

  G4OpticalSurface* surface = new G4OpticalSurface("HousingOptSurface");
  surface->SetType(dielectric_metal); 
  surface->SetFinish(ground); 
  surface->SetModel(unified); 

  surface->SetMaterialPropertiesTable(mpt);
  
  new G4LogicalSkinSurface("HousingLogicalSkinSurface", 
                           housingLV, 
                           surface
                           );
                             
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetVisAttributes()
{
  //path relative to CMAKE_BINARY_DIR
  G4String macrosDirectoryPath = "lappd/macros/vis/";
  G4String path = macrosDirectoryPath + mModelName + "_vis.mac";  
  
  G4UImanager::GetUIpointer()->ExecuteMacroFile(path);  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetStripsEnabled(G4bool b)
{
  mEnableStrips = b;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetPhotocathodeSizeX(G4double x)
{
  mPhotocathodeHalfSizeX = x * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetPhotocathodeSizeY(G4double y)
{
  mPhotocathodeHalfSizeY = y * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingSizeX(G4double x)
{
  mHousingHalfSizeX = x * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingSizeY(G4double y)
{
  mHousingHalfSizeY = y * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingThickness(G4double thickness)
{
  mHousingHalfSizeZ = thickness * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingWindowSizeX(G4double x)
{
  mHousingWindowHalfSizeX = x * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingWindowSizeY(G4double y)
{
  mHousingWindowHalfSizeY = y * 0.5;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingWindowThickness(G4double thickness)
{
  mHousingWindowHalfSizeZ = thickness * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetAirGapThickness(G4double thickness)
{
  mAirGapHalfSizeZ = thickness * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetPhotocathodeWindowThickness(G4double thickness)
{
  mPhotocathodeWindowHalfSizeZ = thickness * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetPhotocathodeGapThickness(G4double thickness)
{
  mPhotocathodeGapHalfSizeZ = thickness * 0.5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetHousingWindowMaterialName(const G4String& name)
{
  mHousingWindowMatName = name;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilder::SetPhotocathodeWindowMaterialName(const G4String& name)
{
  mPhotocathodeWindowMatName = name;
}
    

