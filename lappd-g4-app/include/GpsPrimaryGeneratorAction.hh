#ifndef GpsPrimaryGeneratorAction_h
#define GpsPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class G4ParticleGun;

class GpsPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GpsPrimaryGeneratorAction();
    ~GpsPrimaryGeneratorAction() override;

    virtual void GeneratePrimaries(G4Event*) override;

  private:
    G4GeneralParticleSource* mGPSGun; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
