//////////////////////////////////////////////////////////////////////////
// License & Copyright
// ===================
// 
// Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////


#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"

// GEANT4 //
#include "G4LogicalVolume.hh"
#include "G4StepLimiterBuilder.hh"

// BOOST/PYTHON //
#include "boost/python.hpp"
#include "pyublas/numpy.hpp"


using namespace boost::python;


void RegisterParallelWorld(DetectorConstruction* detector, PhysicsList* physics_list) {
    ParallelDetectorConstruction* parallel_detector = new ParallelDetectorConstruction();
    detector->RegisterParallelWorld(parallel_detector);
    detector->SetParallelWorld(parallel_detector);

    physics_list->SetParallelWorldName("parallel world");
}


BOOST_PYTHON_MODULE(libg4) {
    def("RegisterParallelWorld", RegisterParallelWorld);

    class_<DetectorConstruction, DetectorConstruction*,
        bases<G4VUserDetectorConstruction> >
        ("DetectorConstruction", "detector")
        .def("SaveEnergyHistogram", &DetectorConstruction::SaveEnergyHistogram)
        .def("SaveCountsHistogram", &DetectorConstruction::SaveCountsHistogram)
        .def("SetCTDirectory", &DetectorConstruction::SetCTDirectory)
        .def("GetCTOrigin", &DetectorConstruction::GetCTOrigin)

        .def("SetRadius", &DetectorConstruction::SetRadius)
        .def("SetCrystalLength", &DetectorConstruction::SetCrystalLength)
        .def("SetCrystalWidth", &DetectorConstruction::SetCrystalWidth)
        .def("SetNumberOfCrystals", &DetectorConstruction::SetNumberOfCrystals)
        .def("SetNumberOfBlocks", &DetectorConstruction::SetNumberOfBlocks)
        .def("SetNumberOfHeads", &DetectorConstruction::SetNumberOfHeads)

        .def("GetHistogram", &DetectorConstruction::GetHistogram)    
        .def("ZeroHistogram", &DetectorConstruction::ZeroHistogram)    
        ;   // End DetectorConstruction

    class_<PhysicsList, PhysicsList*,
        bases<G4VModularPhysicsList> >
        ("PhysicsList", "physics list")
        ;   // End PhysicsList

    class_<G4StepLimiterBuilder, G4StepLimiterBuilder*,
        bases<G4VPhysicsConstructor>, boost::noncopyable >
        ("StepLimiterBuilder", "step limit builder")
        ;   // End G4StepLimiterBuilder

    class_<EventAction, EventAction*,
        bases<G4UserEventAction>, boost::noncopyable>
        ("EventAction", "EventAction")
        ;   // End EventAction

    class_<SteppingAction, SteppingAction*,
        bases<G4UserSteppingAction>, boost::noncopyable>
        ("SteppingAction", "SteppingAction")
        .def("SaveMomentumHistogram", &SteppingAction::SaveMomentumHistogram)
        .def("SaveStepsHistogram", &SteppingAction::SaveStepsHistogram)
        ;   // End SteppingAction

    class_<PrimaryGeneratorAction, PrimaryGeneratorAction*,
        bases<G4VUserPrimaryGeneratorAction>, boost::noncopyable>
        ("PrimaryGeneratorAction", "PrimaryGeneratorAction")
        .def("LoadActivityData", &PrimaryGeneratorAction::LoadActivityData)
        .def("SetGunPosition", &PrimaryGeneratorAction::SetGunPosition)
        ;   // End PrimaryGeneratorAction
}

