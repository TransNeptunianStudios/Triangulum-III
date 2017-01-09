cd ${TRIANGULUM_HOME}/server && mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE:String=Debug -DENTITYX_BUILD_TESTING=0 -DENTITYX_BUILD_SHARED=0
make
