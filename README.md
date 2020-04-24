# TimingPhysLab

# Create your area
mkdir TimingLab

cd TimingLab

git clone git@github.com:crovelli/TimingPhysLab.git

cd TimingPhysLab

# Setup environment 
source geant4.sh

# [ Setup environment on lxpus ]
/bin/bash

export LCGENV_PATH=/cvmfs/sft.cern.ch/lcg/releases

/cvmfs/sft.cern.ch/lcg/releases/lcgenv/latest/lcgenv -p LCG_96 --ignore Grid x86_64-centos7-gcc8-opt Geant4 > geant4_lxplus.sh

source geant4_lxplus.sh

# Compile
mkdir timing_build

cd timing_build

cmake3 -DGeant4_DIR=GEANT4__HOME ../timing

make

# Run w/o visualization
./timing run.in

# Run with visualization
./timing visandrun.mac
