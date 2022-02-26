#include"DetectorConstruction.hh"
#include"SensitiveDetector.hh" 
#include<G4NistManager.hh>
#include<G4Box.hh>
#include<G4Tubs.hh>
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include "G4SystemOfUnits.hh"

#include <G4UniformMagField.hh>
#include <G4ClassicalRK4.hh>
#include <G4TransportationManager.hh>
#include <G4EqMagElectricField.hh>
#include "G4EquationOfMotion.hh"
#include "G4ElectroMagneticField.hh"
#include "G4EqEMFieldWithSpin.hh"
#include "G4PropagatorInField.hh"

#include "G4ChargeState.hh"

#include "G4ElectroMagneticField.hh"

using namespace std;

#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x))


World::World(double size_x, double size_y, double size_z,  G4Material *mater_): mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{

    
	//double size05 = size/2;
	solid = new G4Box("world", sizex, sizey, sizez);
	logic = new G4LogicalVolume( solid, mater, "World", 0, 0, 0);
	physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World",
				   0, false, 0);             
}

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    
    G4String name, symbol;
    G4double density, fractionmass;
    G4int nel, ncomponents;
    
    G4NistManager* nist = G4NistManager::Instance();
    G4int nvar = 8;
//fMinStep = 0.001*mm ;
    G4bool isotopes = true;
    
    G4bool checkOverlaps = true;
    auto nistManager = G4NistManager::Instance();
      
    density = 0.413*kg/m3;
    auto AirDensity = nistManager ->BuildMaterialWithNewDensity("AirDensity", "G4_AIR", density);

    
    

    world = new World(0.5*400*m, 0.5*400*m, 0.5*400*m, AirDensity);
    
    
    
    G4Box *solidTgt = new G4Box("solidTgt", 0.5*400*m, 0.5*400*m, 0.5*400*m);
    G4LogicalVolume *logiclTgt = new G4LogicalVolume(solidTgt, AirDensity, "logiclTgt");
    G4PVPlacement *physilTgt = new G4PVPlacement(0, G4ThreeVector(0,0,200*m), logiclTgt,
                             "physilTgt", world->getLogic(), false, 0);
    
    
    
    G4Box *solidDet = new G4Box("solidDet",  0.5*400*m, 0.5*400*m, 0.5*5*m);
    G4LogicalVolume *logicDet = new G4LogicalVolume(solidDet, AirDensity, "logicDet");
    G4PVPlacement *physiDet = new G4PVPlacement(0, G4ThreeVector(0,0,-2.5*m), logicDet,
                            "physiDet", world->getLogic(), false, 0);

    
    
    SensitiveDetector *detector = new SensitiveDetector("hi there");
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(detector);
    logicDet->SetSensitiveDetector(detector);
    
    world->getLogic()->SetVisAttributes (G4VisAttributes::Invisible);
    
    
    
    
    
    
    G4ElectricField* magField_5 = new G4UniformElectricField( G4ThreeVector(0.0,0.0,
                                                                          500*kilovolt/m)); //ускоряем
    G4EqMagElectricField* fEquation1_5 = new G4EqMagElectricField(magField_5);
    G4MagIntegratorStepper* fStepper1_5 = new G4ClassicalRK4( fEquation1_5, nvar );
    G4FieldManager* localFieldMgr1_5
            = new G4FieldManager(magField_5);
    logiclTgt->SetFieldManager(localFieldMgr1_5, true);
    G4MagInt_Driver* fIntgrDriver1_5 = new G4MagInt_Driver(fMinStep,
                                     fStepper1_5,
                                     fStepper1_5->GetNumberOfVariables() );
    G4ChordFinder* fChordFinder1_5 = new G4ChordFinder(fIntgrDriver1_5);
       localFieldMgr1_5->SetChordFinder( fChordFinder1_5 );
    
    
    
    
    
    
    return world->getPhysic();
}
