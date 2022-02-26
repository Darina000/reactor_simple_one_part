#ifndef PHD_CODE_PHYSLIST_HH
#define PHD_CODE_PHYSLIST_HH
#include <CLHEP/Units/SystemOfUnits.h>

#include "globals.hh"
#include "G4ios.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "QGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
class PhysList:  public G4VModularPhysicsList{
public:
    PhysList(){
        int ver = 0;
     //   defaultCutValue = 0.001*CLHEP::mm;
        SetVerboseLevel(ver);

        // EM Physics
       // RegisterPhysics( new G4EmStandardPhysics_option4(ver) );
        RegisterPhysics( new G4EmStandardPhysics(ver) );

        // Synchroton Radiation & GN Physics
       // RegisterPhysics( new G4EmExtraPhysics(ver) );

      //  G4double lowlimit = 50.0*CLHEP::keV;
        G4double lowlimit = 50.0*CLHEP::keV;
        G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowlimit, 100.*CLHEP::GeV);
        
        G4VUserPhysicsList::SetCuts();



        // Decays
      //  RegisterPhysics( new G4DecayPhysics(ver) );

        // Hadron Elastic scattering
     //   RegisterPhysics( new G4HadronElasticPhysics(ver) );

        // Hadron Physics
    //    RegisterPhysics( new G4HadronPhysicsQGSP_BERT(ver));

        // Stopping Physics
     //   RegisterPhysics( new G4StoppingPhysics(ver) );

        // Ion Physics
      //  RegisterPhysics( new G4IonPhysics(ver));

        // Neutron tracking cut
      //  RegisterPhysics( new G4NeutronTrackingCut(ver));
    };
    ~PhysList() override = default;

};


#endif //PHD_CODE_PHYSLIST_HH



