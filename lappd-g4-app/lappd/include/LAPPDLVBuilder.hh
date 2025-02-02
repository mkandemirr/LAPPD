#ifndef LAPPDLVBuilder_h
#define LAPPDLVBuilder_h 1

#include "VComponentBuilder.hh"
#include "G4VPhysicalVolume.hh"

#include "G4NistManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4PVPlacement;
class LAPPDLVBuilderMsgr;
class G4LogicalVolume;
class G4PVPlacement;

class LAPPDLVBuilder : public VComponentBuilder<G4LogicalVolume> {

  public:
    LAPPDLVBuilder(const G4String& pModelName, 
                   const G4String& pMacroFilePath = ""); 
    ~LAPPDLVBuilder();
    
    G4LogicalVolume* GetProductInAnEnvelope(G4Material* pEnvMat = 
    G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"));
    
  protected:  
    virtual G4LogicalVolume* Build() override;   
    
  private:
    void Initialize();
   
    void SetInputParametersWithAMacroFile();
    void SetVisAttributes();
    void BuildPhotocathodeSurface(
      G4PVPlacement* photoCathodePV,
      G4PVPlacement* photocathodeGapPV
      );
      
    void BuildHousingSurface(G4LogicalVolume* housingLV);
  
  public:
    //UI commands
    void SetStripsEnabled(G4bool b);
    void SetPhotocathodeSizeX(G4double x);
    void SetPhotocathodeSizeY(G4double y);
    
    void SetHousingWindowSizeX(G4double x);
    void SetHousingWindowSizeY(G4double y);
    void SetHousingWindowThickness(G4double thickness);
    
    void SetHousingSizeX(G4double x);
    void SetHousingSizeY(G4double y);
    void SetHousingThickness(G4double thickness);
    
    
    void SetAirGapThickness(G4double thickness);
    void SetPhotocathodeWindowThickness(G4double thickness);
    void SetPhotocathodeGapThickness(G4double thickness);
  
    void SetHousingWindowMaterialName(const G4String& name);
    void SetPhotocathodeWindowMaterialName(const G4String& name);
    
  private:
    LAPPDLVBuilderMsgr *mMessenger;
    
    G4String mModelName;
    G4String mMacroFilePath;
    G4String mPrefix;
    G4bool mUseEnvelope;
    G4bool mEnableStrips;
    
    G4Material* mEnvelopeMat; 
    
    G4String mHousingWindowMatName;
    G4String mPhotocathodeWindowMatName; 
      
    // Envelope
    G4double mEnvelopeHalfSizeX;
    G4double mEnvelopeHalfSizeY;
    G4double mEnvelopeHalfSizeZ;
    
    // Housing
    G4double mHousingHalfSizeX;
    G4double mHousingHalfSizeY;
    G4double mHousingHalfSizeZ;

    //HousingWindow
    G4double mHousingWindowHalfSizeX;
    G4double mHousingWindowHalfSizeY;
    G4double mHousingWindowHalfSizeZ;
    
    //AirGap
    G4double mAirGapHalfSizeX;
    G4double mAirGapHalfSizeY;
    G4double mAirGapHalfSizeZ;
    
    // PhotocathodeWindow
    G4double mPhotocathodeWindowHalfSizeX;
    G4double mPhotocathodeWindowHalfSizeY;
    G4double mPhotocathodeWindowHalfSizeZ;
    
    // PhotocathodeGap
    G4double mPhotocathodeGapHalfSizeX;
    G4double mPhotocathodeGapHalfSizeY;
    G4double mPhotocathodeGapHalfSizeZ;

    // Photocathode
    G4double mPhotocathodeHalfSizeX;
    G4double mPhotocathodeHalfSizeY;
    G4double mPhotocathodeHalfSizeZ;

    
    //FrontSpacer
    G4double mFrontSpacerHalfSizeX;
    G4double mFrontSpacerHalfSizeY;
    G4double mFrontSpacerHalfSizeZ;

    G4double mFrontSpacerPhotocathodeGap;

    //BackSpacer
    G4double mBackSpacerHalfSizeX;
    G4double mBackSpacerHalfSizeY;
    G4double mBackSpacerHalfSizeZ;


    G4double mBackSpacerFrontSpacerGap;

    G4double mSpacersGap; //centre distance

    //MCP.bundan ikitane olacak
    G4double mMcpHalfSizeX;
    G4double  mMcpHalfSizeY;
    G4double  mMcpHalfSizeZ;

    //ActiveLAyer
    G4int mNumberOfActiveLayer;

    
    G4double mActiveLayerWidth; //along x
    G4double mActiveLayerThickness; //along z

    //InactiveLayerLV
    G4int mNumberOfInactiveLayer;
    G4double mInactiveLayerWidth;

    G4double mInactiveLayerThickness; //along z

};

#endif

