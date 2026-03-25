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
/// \file src/SteppingAction.cc
/// \brief Implementation of the SpeleoMu::SteppingAction class

#include "G4SystemOfUnits.hh"

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "globals.hh"


namespace SpeleoMu
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
                               EventAction* eventAction)
  : fDetConstruction(detConstruction), fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // Collect energy and track length step by step

  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // energy deposit
  //  auto edep = step->GetTotalEnergyDeposit();


  G4double Ek = 0;
  G4ThreeVector parDir; 

  
  // Add Edep and Step Length for primary track
  if (step->GetTrack()-> GetTrackID() == 1 ) {


    if (volume == fDetConstruction->GetMountainPV())
      fEventAction->AddPrimaryTrackL( step->GetStepLength() );

    
    //    G4cout << volume->GetName() << " " << step->GetTrack()->GetKineticEnergy()/GeV << " GeV " << " Total TL " << fEventAction->GetPrimaryTrackL()/m << " m " << G4endl; 
    if (volume == fDetConstruction->GetCattivoPV()  && !fEventAction->DoneCattivo() ) {

      Ek = step->GetTrack()->GetKineticEnergy();
      parDir = step->GetTrack()->GetMomentumDirection();

      fEventAction->SetCattivo(Ek, parDir.getX(), parDir.getY(), parDir.getZ() );

      G4cout << "Cattivo " << Ek/GeV << " " << " GeV" << G4endl;

    }

    if (volume == fDetConstruction->GetCavityPV()  && !fEventAction->DoneCavity() ) {

      Ek = step->GetTrack()->GetKineticEnergy();
      parDir = step->GetTrack()->GetMomentumDirection();

      fEventAction->SetCavity(Ek, parDir.getX(), parDir.getY(), parDir.getZ() );

      G4cout << "Cavity " << Ek/GeV << " " << " GeV" << G4endl;

    }

    if (volume == fDetConstruction->GetFiumePV() && !fEventAction->DoneFiume() ) {

      Ek = step->GetTrack()->GetKineticEnergy();
      parDir = step->GetTrack()->GetMomentumDirection();

      fEventAction->SetFiume(Ek, parDir.getX(), parDir.getY(), parDir.getZ() );

      G4cout << "Fiume " << Ek/GeV << " " << " GeV" << G4endl;
    }

  } else {

    step->GetTrack()->SetTrackStatus(fStopAndKill);

  }


  
 
  
  // Add Edep and Step Length for all tracks
  //fEventAction->AddAllTrk(edep, stepLength);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace SpeleoMu
