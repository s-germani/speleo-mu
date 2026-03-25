//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file src/DetectorConstruction.cc
/// \brief Implementation of the SpeleoMu::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4AutoDelete.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Polyhedra.hh"
#include "G4UnionSolid.hh"
#include "G4Colour.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

namespace SpeleoMu
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{


  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;

  
  // NIST Manager
  auto nistManager = G4NistManager::Instance();

  
  // Water material defined using NIST Manager
  G4Material* H2O = nistManager->FindOrBuildMaterial("G4_WATER");

  // Air  material defined using NIST Manager
  G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");

  //Silicon Detector Material
  G4Material* Si = nistManager->FindOrBuildMaterial("G4_Si");

  // Standard Rock Definition
  G4Element* elO  = nistManager->FindOrBuildElement("O");
  G4Element* elCa = nistManager->FindOrBuildElement("Ca");
  G4Element* elC  = nistManager->FindOrBuildElement("C");
  G4Element* elMg = nistManager->FindOrBuildElement("Mg");

  density = 2.65 * g/cm3;
  G4Material* standardRock = new G4Material("StandardRock", density, 4);
  standardRock->AddElement(elO,  0.52);
  standardRock->AddElement(elCa, 0.27);
  standardRock->AddElement(elC,  0.12);
  standardRock->AddElement(elMg, 0.09);
  
 
  // Vacuum
  new G4Material("Galactic", z = 1., a = 1.01 * g / mole, density = universe_mean_density,
                 kStateGas, 2.73 * kelvin, 3.e-18 * pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  
  //  G4double watertankRadius = 5. * m;
  //  G4double watertankHeight = 5. * m;

  auto worldSizeXZ = 3 * km;
  auto worldSizeY  = 1 * km;

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto SiMaterial      = G4Material::GetMaterial("G4_Si");
  auto waterMaterial   = G4Material::GetMaterial("G4_WATER");
  auto rockMaterial    = G4Material::GetMaterial("StandardRock");

    

  if (!defaultMaterial || !waterMaterial || !rockMaterial || !waterMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()", "MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  auto worldS = new G4Box("World",  // its name
                          worldSizeXZ / 2, worldSizeY / 2, worldSizeXZ / 2);  // its size

  auto worldLV = new G4LogicalVolume(worldS,  // its solid
                                     defaultMaterial,  // its material
                                     "World");  // its name

  auto worldPV = new G4PVPlacement(nullptr,  // no rotation
                                   G4ThreeVector(),  // at (0,0,0)
                                   worldLV,  // its logical volume
                                   "World",  // its name
                                   nullptr,  // its mother  volume
                                   false,  // no boolean operation
                                   0,  // copy number
                                   fCheckOverlaps);  // checking overlaps

  //
  // 
  // Mountain --> Cone / Trapezoid
  /*
  G4EllipticalCone(const G4String& pName,
                        G4double  xSemiAxis,
                        G4double  ySemiAxis,
                        G4double  zHeight,
                        G4double  zTopCut)


G4Trd(const G4String& pName,
             G4double  dx1,
             G4double  dx2,
             G4double  dy1,
             G4double  dy2,
             G4double  dz)
  */



  /*******************************


******************************************/
  G4double mountainHeight =  930 *m;
  G4double mountainH1     =  650 *m;
  G4double mountainLeft   =  600 *m;
  G4double mountainRight  = 1050 *m;

  G4double cattivo_top    =  380 *m;
  G4double fiume_cattivo  =  330 *m;
  G4double cattivoH       =  mountainHeight-cattivo_top;
  G4double fiumeH         =  mountainHeight-cattivo_top-fiume_cattivo;

  
  G4double mountainSide   = 2*mountainLeft+mountainRight+20*m;



  G4double zPlane[] = { 0,  mountainLeft, 2*mountainLeft, 2*mountainLeft+mountainRight, mountainSide};
  G4double rInner[] = { 0,             0,              0,                           0,             0};
  G4double rOuter[] = {fiumeH,   mountainH1, mountainHeight,                  mountainH1,        fiumeH};
  
  /***  
  auto mountainS = new G4Polyhedra("Mountain",
				  -1/2*pi,            // phiStart
				   1/2*pi,         // phiTotal
				   4,     // numSide,         
				   5,   //   numZPlanes,
				   zPlane,
				   rInner,
				   rOuter );
    
  **/


  
  auto mountainTrd1 = new G4Trd("Mountain1",
			     mountainSide/2,                         // dx1
			     (mountainLeft+mountainRight)/2,	     // dx2
			     mountainSide/2,	                     // dy1
			     (mountainLeft+mountainRight)/2,	     // dy2
			     mountainH1/2);	                     // dz


  auto mountainTrd2 = new G4Trd("Mountain2",
				(mountainLeft+mountainRight)/2,      // dx1
				0,                            	     // dx2
				(mountainLeft+mountainRight)/2,	     // dy1
				0,	                             // dy2
				(mountainHeight-mountainH1)/2);	     // dz


              
	      
  //G4RotationMatrix* noRot = new G4RotationMatrix;  
  G4ThreeVector zTrans(0, 0, mountainHeight/2);
  
  G4UnionSolid* mountainS =
    new G4UnionSolid("Mountain", mountainTrd1, mountainTrd2, nullptr, zTrans);
              
  
  auto mountainLV = new G4LogicalVolume(mountainS,      // its solid
					rockMaterial,   // its material
					"Mountain");    // its name


  //Create a Rotation Matrix
  G4RotationMatrix* MountainRotation = new G4RotationMatrix();
  MountainRotation->rotateX(-90*deg);
  MountainRotation->rotateY(  0*deg);
  MountainRotation->rotateZ(  0*deg);

  /*
  new G4PVPlacement(MountainRotation,  // no rotation
                    G4ThreeVector(-mountainSide/2, 0, -mountainHeight/2),   // at (0,0,0) --> positioned at the world's center
                    mountainLV,        // its logical volume
                    "Mountain",        // its name
                    worldLV,           // its mother  volume
                    false,             // no boolean operation
                    0,                 // copy number
                    fCheckOverlaps);   // checking overlaps
  */
  fMountainPV = new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(0, 0 , 0),   // at (0,0,0) --> positioned at the world's center
                    mountainLV,        // its logical volume
                    "Mountain",        // its name
                    worldLV,           // its mother  volume
                    false,             // no boolean operation
                    0,                 // copy number
                    fCheckOverlaps);   // checking overlaps


  //
  // Caves (Cattivo , Fiume, Cavity) --> Box
  /*
    G4Box(const G4String& pName,
             G4double  pX,
             G4double  pY,
             G4double  pZ)
  */


  G4double cattivoDZ    =   5*m;
  G4double cattivoSide1 =  10*m;
  G4double cattivoSide2 = 100*m;
  
  G4double fiumeDZ   =  5*m;
  G4double fiumeSide =  5*m;
 
  G4double cavityDZ  = 5*m;
  G4double cavityDX  = 1*m;
  G4double cavityDY  = 2*m;
 

  auto cattivoS = new G4Box("Cattivo",
			    cattivoSide1/2,
			    cattivoSide2/2,
			    cattivoDZ/2    );


  auto cattivoLV = new G4LogicalVolume(cattivoS,      // its solid
				       defaultMaterial,   // its material
				       "Cattivo");    // its name


  fCattivoPV = new G4PVPlacement(nullptr,  // no rotation
				 //G4ThreeVector(0, cattivoH,  zPlane[2] ),    // at (0,0,0) --> positioned at the world's center
				 G4ThreeVector(0, 0, -mountainHeight/2+cattivoH ),    // at (0,0,0) --> positioned at the world's center
				 cattivoLV,          // its logical volume
				 "Cattivo",          // its name
				 mountainLV,         // its mother  volume
				 false,              // no boolean operation
				 0,                  // copy number
				 fCheckOverlaps);    // checking overlaps

  auto fiumeS = new G4Box("Fiume",
			  fiumeSide/2,
			  fiumeSide/2,
			  fiumeDZ/2    );



  auto fiumeLV = new G4LogicalVolume(fiumeS,      // its solid
				     defaultMaterial,   // its material
				     "Fiume");    // its name


  fFiumePV = new G4PVPlacement(nullptr,  // no rotation
			       //G4ThreeVector(0, fiumeH, zPlane[2]),    // at (0,0,0) --> positioned at the world's center
			       G4ThreeVector(0, 10, -mountainHeight/2+fiumeH),    // at (0,0,0) --> positioned at the world's center
			       fiumeLV,          // its logical volume
			       "Fiume",          // its name
			       mountainLV,         // its mother  volume
			       false,              // no boolean operation
			       0,                  // copy number
			       fCheckOverlaps);    // checking overlaps

  
  auto cavityS = new G4Box("Cavity",
			    cavityDX/2,
			    cavityDY/2,
			    cavityDZ/2    );


  
  auto cavityLV = new G4LogicalVolume(cavityS,      // its solid
				     defaultMaterial,   // its material
				     "Cavity");    // its name


  G4double cavityH = (fiumeH+cattivoH)/2;
  fCavityPV = new G4PVPlacement(nullptr,  // no rotation
                    //G4ThreeVector(0, cavityH,   zPlane[2]),    // at (0,0,0) --> positioned at the world's center
		    G4ThreeVector(30, 0, -mountainHeight/2+cavityH),    // at (0,0,0) --> positioned at the world's center
                    cavityLV,          // its logical volume
                    "Cavity",          // its name
                    mountainLV,         // its mother  volume
                    false,              // no boolean operation
                    0,                  // copy number
                    fCheckOverlaps);    // checking overlaps

  
  //
  // print parameters
  //
  G4cout << G4endl << "------------------------------------------------------------" << G4endl
         << "---> The Mountain  (Side:  " << mountainSide / m << "  -  Height:  " << mountainHeight / m
         << "m of " << rockMaterial->GetName() << " ) " << G4endl
         << "------------------------------------------------------------" << G4endl;

  //
  // Visualization attributes
  //
  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());
  mountainLV->SetVisAttributes(G4VisAttributes(G4Colour::White()));

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace SpeleoMu
