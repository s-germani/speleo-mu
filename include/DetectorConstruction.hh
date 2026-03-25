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
/// \file include/DetectorConstruction.hh
/// \brief Definition of the SpeleoMu::DetectorConstruction class

#ifndef SpeleoMuDetectorConstruction_h
#define SpeleoMuDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "G4Threading.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

namespace SpeleoMu
{

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined
/// via G4GlobalMagFieldMessenger class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

  public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    // get methods
    //
    const G4VPhysicalVolume* GetMountainPV() const;
    const G4VPhysicalVolume* GetCattivoPV()  const;
    const G4VPhysicalVolume* GetCavityPV()   const;
    const G4VPhysicalVolume* GetFiumePV()    const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger;
    // magnetic field messenger

    G4VPhysicalVolume* fMountainPV = nullptr;  // the Mountain Physical Volume
    G4VPhysicalVolume* fCattivoPV  = nullptr;  // the Cattivo  Physical Volume
    G4VPhysicalVolume* fCavityPV   = nullptr;  // the Cavity   Physical Volume
    G4VPhysicalVolume* fFiumePV    = nullptr;  // the Fiume    Physical Volume

    G4bool fCheckOverlaps = true;  // option to activate checking of volumes overlaps
};

// inline functions

  inline const G4VPhysicalVolume* DetectorConstruction::GetMountainPV() const
{
  return fMountainPV;
}

inline const G4VPhysicalVolume* DetectorConstruction::GetCattivoPV() const
{
  return fCattivoPV;
}

inline const G4VPhysicalVolume* DetectorConstruction::GetCavityPV() const
{
  return fCavityPV;
}

  
inline const G4VPhysicalVolume* DetectorConstruction::GetFiumePV() const
{
  return fFiumePV;
}

  
}  // namespace SpeleoMu

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
