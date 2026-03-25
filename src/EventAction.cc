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
/// \file src/EventAction.cc
/// \brief Implementation of the SpeleoMu::EventAction class

#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <iomanip>

namespace SpeleoMu
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void EventAction::BeginOfEventAction(const G4Event* event)
{
  // initialisation per event
  G4PrimaryParticle* priPar = event->GetPrimaryVertex()->GetPrimary();
  fE0 = priPar->GetKineticEnergy();
  G4ThreeVector parDir = priPar->GetMomentumDirection();
  fp0x = parDir.getX();
  fp0y = parDir.getY();
  fp0z = parDir.getZ();
  
  fTrackLPrm = 0.;
    
  fEC   = 0.;
  fpCx  = 0.;
  fpCy  = 0.;
  fpCz  = 0.;

  fECv   = 0.;
  fpCvx  = 0.;
  fpCvy  = 0.;
  fpCvz  = 0.;

  fEF   = 0.;
  fpFx  = 0.;
  fpFy  = 0.;
  fpFz  = 0.;

  fDx  = 999.;
  fDy  = 999.;
  fDz  = 999.;

  fCattivo = false;
  fCavity  = false;
  fFiume   = false;
  
  auto eventID = event->GetEventID();  
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ((printModulo > 0) && (eventID % printModulo == 0)) {
    
    G4cout << "   Primary Track: total energy: "       << std::setw(7) << G4BestUnit(fE0, "Energy")
      //           << "            total track length: " << std::setw(7) << G4BestUnit(fTrackLPrm, "Length")
           << G4endl;

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();


  // fill ntuple
  analysisManager->FillNtupleDColumn( 0, fE0  );
  analysisManager->FillNtupleDColumn( 1, fp0x );
  analysisManager->FillNtupleDColumn( 2, fp0y );
  analysisManager->FillNtupleDColumn( 3, fp0z );
  analysisManager->FillNtupleDColumn( 4, fTrackLPrm );
  analysisManager->FillNtupleDColumn( 5, fEC  );
  analysisManager->FillNtupleDColumn( 6, fpCx );
  analysisManager->FillNtupleDColumn( 7, fpCy );
  analysisManager->FillNtupleDColumn( 8, fpCz );
  analysisManager->FillNtupleDColumn( 9, fECv );
  analysisManager->FillNtupleDColumn(10, fpCvx);
  analysisManager->FillNtupleDColumn(11, fpCvy);
  analysisManager->FillNtupleDColumn(12, fpCvz);
  analysisManager->FillNtupleDColumn(13, fEF  );
  analysisManager->FillNtupleDColumn(14, fpFx );
  analysisManager->FillNtupleDColumn(15, fpFy );
  analysisManager->FillNtupleDColumn(16, fpFz );

  analysisManager->AddNtupleRow();

  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();


  G4cout << "----->  Filling Ntuple for Event " << eventID << "  " << fE0 << " " << fEF << " " <<  fTrackLPrm << G4endl;
  if ((printModulo > 0) && (eventID % printModulo == 0)) {
    
    G4cout << "   Primary Track:  total track length: " << std::setw(7) << G4BestUnit(fTrackLPrm, "Length")
           << G4endl;
    G4cout << "--> End of event " << eventID << "\n" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

}  // namespace SpeleoMu
