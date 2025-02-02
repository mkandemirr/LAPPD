

#ifndef LAPPDLVBuilderMsgr_h
#define LAPPDLVBuilderMsgr_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class LAPPDLVBuilder;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LAPPDLVBuilderMsgr: public G4UImessenger
{
  public:
    LAPPDLVBuilderMsgr(LAPPDLVBuilder* );
   ~LAPPDLVBuilderMsgr();

    virtual void SetNewValue(G4UIcommand*, G4String);

	private:
		void GetAsAVector(const G4String& inputString,
											std::vector<G4double>& vec
		                 );
  
    LAPPDLVBuilder *mBuilder;
    
    G4UIcmdWithABool* mEnableStripsCmd;
   
    G4UIcmdWithADoubleAndUnit *mPhotocathodeSizeXCmd;
    G4UIcmdWithADoubleAndUnit *mPhotocathodeSizeYCmd;
    
    G4UIcmdWithADoubleAndUnit *mHousingWindowSizeXCmd;
    G4UIcmdWithADoubleAndUnit *mHousingWindowSizeYCmd;
    G4UIcmdWithADoubleAndUnit *mHousingWindowThicknessCmd;
    
    G4UIcmdWithADoubleAndUnit *mHousingSizeXCmd;
    G4UIcmdWithADoubleAndUnit *mHousingSizeYCmd;
    G4UIcmdWithADoubleAndUnit *mHousingThicknessCmd;
    
    //z direction
    G4UIcmdWithADoubleAndUnit *mAirGapThicknessCmd;
    G4UIcmdWithADoubleAndUnit *mPhotocathodeWindowThicknessCmd;
    G4UIcmdWithADoubleAndUnit *mPhotocathodeGapThicknessCmd;
    
    G4UIcmdWithAString *mHousingWindowMatNameCmd; 
    G4UIcmdWithAString *mPhotocathodeWindowMatNameCmd; 
    
   
    
    
    
    
    
   
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

