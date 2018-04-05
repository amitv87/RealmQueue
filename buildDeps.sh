set -e
set -x

NUM_CPU=$(getconf _NPROCESSORS_ONLN)

ROOT_DIR=$(pwd)

cd $ROOT_DIR/deps/libuv
sh autogen.sh
./configure
make -j$NUM_CPU

cd $ROOT_DIR/deps/realm-object-store
mkdir -p out
cd out
cmake -DCMAKE_BUILD_TYPE=Release -DREALM_CORE_PREFIX=$ROOT_DIR/deps/realm-core -DREALM_PLATFORM=$(uname) ..
make -j$NUM_CPU

cd $ROOT_DIR
