set -e
# set -x

NUM_CPU=$(getconf _NPROCESSORS_ONLN)
mkdir -p .build
cd .build
cmake ..
make -j$NUM_CPU

ls -lah realmqueue

./realmqueue
