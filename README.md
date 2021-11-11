# demo_vsomeip
demo envirment for vsomeip for pc



demo_vsomeip$ mkdir vsome/build
demo_vsomeip$ cd vsome/build/

cmake -DCMAKE_INSTALL_PREFIX=../../out/vsome -DENABLE_SIGNAL_HANDLING=1 .. 

demo_vsomeip/vsome/build$ make -j4
demo_vsomeip/vsome/build$ make install





demo_vsomeip/vsome/build$ cmake --build . --target hello_world
demo_vsomeip/vsome/build$ cmake --build . --target response-sample
demo_vsomeip/vsome/build$ cmake --build . --target subscribe-sample
demo_vsomeip/vsome/build$ cmake --build . --target response-sample
demo_vsomeip/vsome/build$ cmake --build . --target notify-sample
demo_vsomeip/vsome/build$ cd examples/
demo_vsomeip/vsome/build/examples$ make -j4


export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/mygithub/demo_vsomeip/vsome/build

env VSOMEIP_CONFIGURATION=vsomeip-tcp-service.json  build/hello_world_service


env VSOMEIP_CONFIGURATION=vsomeip-tcp-client.json  build/hello_world_client






