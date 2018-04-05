cmake_minimum_required(VERSION 2.8)
# set(CMAKE_VERBOSE_MAKEFILE ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  cmake_policy(SET CMP0068 NEW)
  SET(CMAKE_MACOSX_RPATH ON)
  SET(CMAKE_INSTALL_RPATH "@loader_path")
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  SET(PLATFORM_LINKER_FLAGS "-Wl,-dead_strip -framework CoreFoundation")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(PLATFORM_LINKER_FLAGS "-Wl,-rpath,./ -Wl,--gc-sections -Wl,--as-needed")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  
endif()

SET(CMAKE_C_FLAGS "-std=c11")
# -stdlib=libc++ 

SET(LIBUV_DIR "${CMAKE_SOURCE_DIR}/deps/libuv")
SET(LIBUV_INC "${LIBUV_DIR}/include")
SET(LIBUV_STATIC_LIB "${LIBUV_DIR}/.libs/libuv.a")

SET(REALM_CORE_DIR "${CMAKE_SOURCE_DIR}/deps/realm-core")
SET(REALM_CORE_INC "${REALM_CORE_DIR}/src")
SET(REALM_CORE_CFG_INC "${REALM_CORE_DIR}/build.release/src")
SET(REALM_CORE_STATIC_LIB "${REALM_CORE_DIR}/build.release/src/realm/librealm.a")

SET(REALM_OBJECT_STORE_DIR "${CMAKE_SOURCE_DIR}/deps/realm-object-store")
SET(REALM_OBJECT_STORE_INC "${REALM_OBJECT_STORE_DIR}/src")
SET(REALM_OBJECT_STORE_STATIC_LIB "${REALM_OBJECT_STORE_DIR}/.build/src/librealm-object-store.a")

# -I/Users/amitverma/realm/realm-object-store/src \
#  -I/Users/amitverma/realm/realm-object-store/out/CMakeFiles/realm-core-5.4.0/include \
#  -I/Users/amitverma/realm/realm-object-store/external/pegtl \

# SET(HIREDIS_DIR "${CMAKE_SOURCE_DIR}/deps/redis/deps/hiredis")
# SET(HIREDIS_INCLUDES "${HIREDIS_DIR}")
# SET(HIREDIS_STATIC_LIB "${HIREDIS_DIR}/libhiredis.a")

# SET(JSONCPP_DIR "${CMAKE_SOURCE_DIR}/deps/jsoncpp/")
# SET(JSONCPP_INCLUDES "${JSONCPP_DIR}/include")
# SET(JSONCPP_STATIC_LIB "${JSONCPP_DIR}/build/src/lib_json/libjsoncpp.a")

SET(CMAKE_CXX_FLAGS "-std=c++14 -DNDEBUG -DREALM_HAVE_CONFIG -O3 -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath \$<))\"'")

# SET(APP_INCLUDES "include")
# FILE(GLOB_RECURSE udpnative_src "src/*.c" "src/*.cpp")
# ADD_LIBRARY(udpnative_obj OBJECT ${udpnative_src})
# TARGET_INCLUDE_DIRECTORIES(udpnative_obj PUBLIC ${APP_INCLUDES} ${LIBUV_INCLUDES} ${HIREDIS_INCLUDES} ${JSONCPP_INCLUDES})

# ADD_LIBRARY(udpnative_module SHARED $<TARGET_OBJECTS:udpnative_obj>)
# TARGET_LINK_LIBRARIES(udpnative_module ${LIBUV_STATIC_LIB} ${HIREDIS_STATIC_LIB} ${JSONCPP_STATIC_LIB})

# ADD_EXECUTABLE(udpnative_server $<TARGET_OBJECTS:udpnative_obj>)
# TARGET_LINK_LIBRARIES(udpnative_server ${LIBUV_STATIC_LIB} ${HIREDIS_STATIC_LIB} ${JSONCPP_STATIC_LIB})



FILE(GLOB_RECURSE realmqueue_src "src/*.c" "src/*.cpp")
ADD_EXECUTABLE(realmqueue ${realmqueue_src})
TARGET_INCLUDE_DIRECTORIES(realmqueue PUBLIC ${LIBUV_INC} ${REALM_CORE_INC} ${REALM_CORE_CFG_INC} ${REALM_OBJECT_STORE_INC})
TARGET_LINK_LIBRARIES(realmqueue ${LIBUV_STATIC_LIB} ${REALM_CORE_STATIC_LIB} ${REALM_OBJECT_STORE_STATIC_LIB} ${PLATFORM_LINKER_FLAGS})
