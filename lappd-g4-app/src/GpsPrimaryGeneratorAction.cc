#include "GpsPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GpsPrimaryGeneratorAction::GpsPrimaryGeneratorAction():
G4VUserPrimaryGeneratorAction(),
mGPSGun{nullptr}
{
  mGPSGun = new G4GeneralParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GpsPrimaryGeneratorAction::~GpsPrimaryGeneratorAction()
{
  delete mGPSGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GpsPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  mGPSGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
