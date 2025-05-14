#include "LAPPDLVBuilderMsgr.hh"
#include "LAPPDLVBuilder.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVBuilderMsgr::LAPPDLVBuilderMsgr(LAPPDLVBuilder *builder)
:G4UImessenger(),
mBuilder(builder)
{  
  G4String commandDirectory = "/lappd/";
  
  //-------Command 0----------
  G4String commandName  = "includeStrips";
  G4String commandPath  = commandDirectory+commandName;
  G4String usage        = "[usage] "+ commandPath + " includeStrips";
  
 
 	mEnableStripsCmd = new G4UIcmdWithABool(commandPath, this);
  mEnableStripsCmd->SetGuidance(usage);
  mEnableStripsCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mEnableStripsCmd->SetToBeBroadcasted(false);
 
  //-------Command 1----------
  
  commandName  = "photocathodeSizeX";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " photocathodeSizeX";
  
 
 	mPhotocathodeSizeXCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mPhotocathodeSizeXCmd->SetGuidance(usage);
  mPhotocathodeSizeXCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodeSizeXCmd->SetToBeBroadcasted(false);
  
  //-------Command 2----------
  commandName  = "photocathodeSizeY";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " photocathodeSizeY";
  
 
 	mPhotocathodeSizeYCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mPhotocathodeSizeYCmd->SetGuidance(usage);
  mPhotocathodeSizeYCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodeSizeYCmd->SetToBeBroadcasted(false);
  
  
  //-------Command 3----------
  commandName  = "housingWindowSizeX";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingWindowSizeX";
  
 
 	mHousingWindowSizeXCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingWindowSizeXCmd->SetGuidance(usage);
  mHousingWindowSizeXCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingWindowSizeXCmd->SetToBeBroadcasted(false);
  
  
  //-------Command 4----------
  commandName  = "housingWindowSizeY";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingWindowSizeY";
  
 
 	mHousingWindowSizeYCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingWindowSizeYCmd->SetGuidance(usage);
  mHousingWindowSizeYCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingWindowSizeYCmd->SetToBeBroadcasted(false);
  
  //-------Command 5----------
  commandName  = "housingWindowThickness";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingWindowThickness";
  
 
 	mHousingWindowThicknessCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingWindowThicknessCmd->SetGuidance(usage);
  mHousingWindowThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingWindowThicknessCmd->SetToBeBroadcasted(false);
  
  //-------Command 6----------
  commandName  = "housingSizeX";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingSizeX";
  
 
 	mHousingSizeXCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingSizeXCmd->SetGuidance(usage);
  mHousingSizeXCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingSizeXCmd->SetToBeBroadcasted(false);
  
  //-------Command 7----------
  commandName  = "housingSizeY";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingSizeY";
  
 
 	mHousingSizeYCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingSizeYCmd->SetGuidance(usage);
  mHousingSizeYCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingSizeYCmd->SetToBeBroadcasted(false);
  
  //-------Command 8----------
  commandName  = "housingThickness";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingThickness";
  
 
  mHousingThicknessCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mHousingThicknessCmd->SetGuidance(usage);
  mHousingThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingThicknessCmd->SetToBeBroadcasted(false);
  
  //-------Command 9----------
  commandName  = "photocathodePositionX";
  commandPath  = commandDirectory + commandName;
  usage        = "[usage] "+ commandPath + " photocathodePositionX";
  
 
  mPhotocathodePosXCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mPhotocathodePosXCmd->SetGuidance(usage);
  mPhotocathodePosXCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodePosXCmd->SetToBeBroadcasted(false);
  
  //-------Command 10----------
  commandName  = "photocathodePositionY";
  commandPath  = commandDirectory + commandName;
  usage        = "[usage] "+ commandPath + " photocathodePositionY";
  
 
  mPhotocathodePosYCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mPhotocathodePosYCmd->SetGuidance(usage);
  mPhotocathodePosYCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodePosYCmd->SetToBeBroadcasted(false);
  
  //-------Command 11----------
  commandName  = "airGapThickness";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " airGapThickness";
  
 
 	mAirGapThicknessCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mAirGapThicknessCmd->SetGuidance(usage);
  mAirGapThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mAirGapThicknessCmd->SetToBeBroadcasted(false);
  
  //-------Command 12----------
  commandName  = "photocathodeWindowThickness";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " photocathodeWindowThickness";
  
 
 	mPhotocathodeWindowThicknessCmd = new G4UIcmdWithADoubleAndUnit(commandPath, this);
  mPhotocathodeWindowThicknessCmd->SetGuidance(usage);
  mPhotocathodeWindowThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodeWindowThicknessCmd->SetToBeBroadcasted(false);
  

  
  //-------Command 13----------
  commandName  = "housingWindowMatName";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " housingWindowMatName";
  
 
  mHousingWindowMatNameCmd = new G4UIcmdWithAString(commandPath, this);
  mHousingWindowMatNameCmd->SetGuidance(usage);
  mHousingWindowMatNameCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mHousingWindowMatNameCmd->SetToBeBroadcasted(false);
  
  //-------Command 14----------
  commandName  = "photocathodeWindowMatName";
  commandPath  = commandDirectory+commandName;
  usage        = "[usage] "+ commandPath + " photocathodeWindowMatName";
  
 
  mPhotocathodeWindowMatNameCmd = new G4UIcmdWithAString(commandPath, this);
  mPhotocathodeWindowMatNameCmd->SetGuidance(usage);
  mPhotocathodeWindowMatNameCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mPhotocathodeWindowMatNameCmd->SetToBeBroadcasted(false);
  
  
 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LAPPDLVBuilderMsgr::~LAPPDLVBuilderMsgr()
{
  //delete mDir;  
   delete mEnableStripsCmd;
   delete mPhotocathodeSizeXCmd; 
   delete mPhotocathodeSizeYCmd;
   delete mHousingSizeXCmd;
   delete mHousingSizeYCmd;
   delete mHousingThicknessCmd;
   delete mHousingWindowSizeXCmd;
   delete mHousingWindowSizeYCmd;
   delete mPhotocathodePosXCmd;
   delete mPhotocathodePosYCmd;
   delete mHousingWindowThicknessCmd;
   delete mAirGapThicknessCmd;
   delete mPhotocathodeWindowThicknessCmd;
   

   delete mHousingWindowMatNameCmd;
   delete mPhotocathodeWindowMatNameCmd;
 	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LAPPDLVBuilderMsgr::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == mEnableStripsCmd )
	{
		mBuilder->SetStripsEnabled(mEnableStripsCmd->
		                              GetNewBoolValue(newValue) );
	}else if( command == mPhotocathodeSizeXCmd )
	{
		mBuilder->SetPhotocathodeSizeX(mPhotocathodeSizeXCmd->
		                              GetNewDoubleValue(newValue) );
	}else if( command == mPhotocathodeSizeYCmd )
	{
	  mBuilder->SetPhotocathodeSizeY(mPhotocathodeSizeYCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mHousingSizeXCmd )
	{
	  mBuilder->SetHousingSizeX(mHousingSizeXCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mHousingSizeYCmd )
	{
	  mBuilder->SetHousingSizeY(mHousingSizeYCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mHousingThicknessCmd )
	{
	  mBuilder->SetHousingThickness(mHousingThicknessCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}
	
	else if( command == mHousingWindowSizeXCmd )
	{
	  mBuilder->SetHousingWindowSizeX(mHousingWindowSizeXCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mHousingWindowSizeYCmd )
	{
	  mBuilder->SetHousingWindowSizeY(mHousingWindowSizeYCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mPhotocathodePosXCmd )
	{
	  mBuilder->SetPhotocathodePositionX(mPhotocathodePosXCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mPhotocathodePosYCmd )
	{
	  mBuilder->SetPhotocathodePositionY(mPhotocathodePosYCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}
	
	else if( command == mHousingWindowThicknessCmd )
	{
	  mBuilder->SetHousingWindowThickness(mHousingWindowThicknessCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}
	
	else if( command == mAirGapThicknessCmd )
	{
	  mBuilder->SetAirGaphickness(mAirGapThicknessCmd->
		                              GetNewDoubleValue(newValue) );
	  
	}else if( command == mPhotocathodeWindowThicknessCmd )
	{
	  mBuilder->SetPhotocathodeWindowThickness(mPhotocathodeWindowThicknessCmd->
		                                         GetNewDoubleValue(newValue) );
	  
	}else if( command == mHousingWindowMatNameCmd  )
	{
	  mBuilder->SetHousingWindowMaterialName(newValue );
	  
	}
	
	else if( command == mPhotocathodeWindowMatNameCmd  )
	{
	  mBuilder->SetPhotocathodeWindowMaterialName(newValue );
	  
	}
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
