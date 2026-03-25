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
/// \file include/EventAction.hh
/// \brief Definition of the SpeleoMu::EventAction class

#ifndef SpeleoMuEventAction_h
#define SpeleoMuEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

namespace SpeleoMu
{

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// in the detetcor for the Primary Track and for all Tracks:
/// - fEnergyPrm, fEnergyAll, fTrackLPrm, fTrackLAll
/// which are collected step by step via the functions
/// - AddPrmTrk(), AddAllTrk()

class EventAction : public G4UserEventAction
{
  public:
  EventAction() = default;
  ~EventAction() override = default;

  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;
  
  void SetPrmTrk( G4double E, G4double px, G4double py, G4double pz);
  void SetCattivo(G4double E, G4double px, G4double py, G4double pz);
  void SetCavity( G4double E, G4double px, G4double py, G4double pz);
  void SetFiume(  G4double E, G4double px, G4double py, G4double pz);

  void AddPrimaryTrackL(G4double ptl);
  G4double GetPrimaryTrackL();
    
  G4bool DoneCattivo();
  G4bool DoneCavity();
  G4bool DoneFiume();
  
  private:
  G4double fE0   = 0.;
  G4double fp0x  = 0.;
  G4double fp0y  = 0.;
  G4double fp0z  = 0.;
  G4double fTrackLPrm = 0.;
  G4double fEC   = 0.;
  G4double fpCx  = 0.;
  G4double fpCy  = 0.;
  G4double fpCz  = 0.;
  G4double fECv  = 0.;
  G4double fpCvx = 0.;
  G4double fpCvy = 0.;
  G4double fpCvz = 0.;
  G4double fEF   = 0.;
  G4double fpFx  = 0.;
  G4double fpFy  = 0.;
  G4double fpFz  = 0.;

  G4double fDx = 999.;
  G4double fDy = 999.;
  G4double fDz = 999.;

  G4bool fCattivo = false;
  G4bool fCavity  = false;
  G4bool fFiume   = false;
};

// inline functions

  inline void EventAction::SetPrmTrk(G4double E, G4double px, G4double py, G4double pz)
{

  fE0  = E;
  fp0x = px;
  fp0y = py;
  fp0z = pz;

}

inline void EventAction::SetCattivo(G4double E, G4double px, G4double py, G4double pz)
{

  fEC  = E;
  fpCx = px;
  fpCy = py;
  fpCz = pz;
  fCattivo = true;
}

inline void EventAction::SetCavity(G4double E, G4double px, G4double py, G4double pz)
{

  fECv  = E;
  fpCvx = px;
  fpCvy = py;
  fpCvz = pz;
  fCavity = true;
}

  
inline void EventAction::SetFiume(G4double E, G4double px, G4double py, G4double pz)
{

  fEF  = E;
  fpFx = px;
  fpFy = py;
  fpFz = pz;
  fFiume = true;
  
}


inline void EventAction::AddPrimaryTrackL(G4double ptl)
{
  fTrackLPrm+=ptl;
}

inline G4double EventAction::GetPrimaryTrackL()
{
  return fTrackLPrm;
}

  
  inline G4bool EventAction::DoneCattivo(){ return fCattivo; }
  inline G4bool EventAction::DoneCavity(){  return fCavity; }
  inline G4bool EventAction::DoneFiume(){   return fFiume;   } 

}  // namespace SpeleoMu
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
