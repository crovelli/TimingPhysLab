# TimingPhysLab

# Create your area
mkdir TimingLab
cd TimingLab

git clone git@github.com:crovelli/TimingPhysLab.git

cd TimingPhysLab

# Setup environment 
source geant4_lxplus.sh

mkdir timing_build

cd timing_build

# Compile
cmake3 -DGeant4_DIR=GEANT4__HOME ../timing

make

# Run w/o visualization
./timing run.in

# Run with visualization
./timing visandrun.mac
