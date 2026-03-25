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
/// \file src/PrimaryGeneratorAction.cc
/// \brief Implementation of the SpeleoMu4::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "math.h"


namespace SpeleoMu
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("mu-");

  
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  //  fParticleGun->SetParticleEnergy(randomE);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  G4double worldZHalfLength = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;
  if (worldLV) {
    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  }

  if (worldBox) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", JustWarning, msg);
  }


  // Generate random energy between 10 MeV and 50 MeV
  G4double minE =  200.0*GeV;
  G4double maxE = 10000.0*GeV;
  G4double gamma = 2.7;
  
  G4double randomC = G4UniformRand();
  


  G4double randomE = std::pow( 1/(  (1-randomC)*std::pow(minE, -(gamma-1)) +randomC*std::pow(maxE, -(gamma-1)) ), 1/(gamma-1));
    
  //G4double randomE = minE + (maxE - minE) * G4UniformRand(); 
    
  // G4cout << "Primary " << randomE/GeV << " GeV" << G4endl;
  fParticleGun->SetParticleEnergy(randomE);

  G4double randomSin = G4UniformRand()*0.002;  // maximum ZD angle ~10 deg

  G4double zD = std::cos(std::asin(randomSin));
  G4double randomAz = 2*pi*G4UniformRand();
  G4double xyM = std::sqrt(1-zD*zD);
  G4double randomDx = xyM*std::cos(randomAz);
  G4double randomDy = xyM*std::sin(randomAz);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(randomDx, randomDy, -zD));
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
  
  // Set gun position

  //  G4double WS = 200*m;  // 3 * km;
  G4double WS = 1500*randomSin *m;  // 3 * km;
  G4double randomX = -WS/2 + WS*G4UniformRand();
  G4double randomY = -WS/2 + WS*G4UniformRand();

  if( randomX*randomDx > 0)  randomX = -randomX;
  if( randomY*randomDy > 0)  randomY = -randomY;			       
    
  fParticleGun->SetParticlePosition(G4ThreeVector(randomX, randomY, worldZHalfLength));
  //fParticleGun->SetParticlePosition(G4ThreeVector(0., 0. , worldZHalfLength));

  fParticleGun->GeneratePrimaryVertex(event);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace SpeleoMu
