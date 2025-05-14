#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "PhotonSD.hh"

#include "LAPPDPVBuilder.hh"
#include "DetectorPVBuilder.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction():
G4VUserDetectorConstruction(),
mModel("lappd")
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
  //LAPPDPVBuilder builder(mModel);
  //return builder.GetProduct();

 DetectorPVBuilder builder(mModel);
 return builder.GetProduct();
 

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  PhotonSD* pmt = mPhotonSD.Get();
  if (!pmt)
  {
    PhotonSD* pmt_SD = new PhotonSD("/Det/photonSD");
    mPhotonSD.Put(pmt_SD);
  }
  
  G4SDManager::GetSDMpointer()->AddNewDetector(mPhotonSD.Get());
                       
  G4String sdName = mModel + "_PhotocathodeLV";
  SetSensitiveDetector(sdName, mPhotonSD.Get(), true);

}




