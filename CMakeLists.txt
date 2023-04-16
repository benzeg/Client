cmake_minimum_required(VERSION 3.13)
project(Client_wasm CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/public)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/public)

find_package(ZLIB REQUIRED)

if (true)
  find_library(libindiclient NAMES libindiclient.a PATHS $ENV{EMSDK}/upstream/emscripten/cache/sysroot/lib)
  set(EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten CACHE STRING "Emscripten path")
  set(CMAKE_TOOLCHAIN_FILE ${EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
  set(WEBIDL_BINDER_SCRIPT ${EMSDK}/upstream/emscripten/tools/webidl_binder)

  set(LIBRARY_COMPILE_ARGS
    -g -O0
    -fPIC
    -pthread 
  )

  # libClient
  add_library(Client Client.cpp)
  set_target_properties(Client PROPERTIES COMPILE_OPTIONS  "${LIBRARY_COMPILE_ARGS}")

  # glue code
  set(IDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Client_wasm.idl)
  add_custom_command(
    OUTPUT glue.cpp glue.js
    COMMAND /home/desktop-ubu/dev/emsdk/upstream/emscripten/tools/webidl_binder ${IDL_FILE} glue
    DEPENDS ${IDL_FILE}
    COMMENT "Generating bindings"
    VERBATIM)

  # executable
  set(EXECUTABLE_COMPILE_ARGS
    -g -O0
    -fPIC
    -pthread
    -I${CMAKE_CURRENT_SOURCE_DIR}
    -include${CMAKE_CURRENT_SOURCE_DIR}/Client.h
  )

  set(EXECUTABLE_LINK_FLAGS
    -g -O0 -gsource-map
    -fPIC
    -pthread
    --post-js glue.js
    --source-map-base file://${CMAKE_CURRENT_SOURCE_DIR}/public/
    -sLEGACY_RUNTIME
    -sSTACK_SIZE=5242880
    -sEXPORTED_RUNTIME_METHODS=FS,getValue
    -sEXPORTED_FUNCTIONS=_malloc,_free
    -sINITIAL_MEMORY=65536000
    -sWEBSOCKET_SUBPROTOCOL=binary
  )

  add_executable(Client-wasm glue.cpp)
  add_dependencies(Client-wasm Client)
  target_link_libraries(Client-wasm Client ${libindiclient} ${ZLIB_LIBRARIES})
  set_target_properties(Client-wasm PROPERTIES COMPILE_OPTIONS  "${EXECUTABLE_COMPILE_ARGS}")
  set_target_properties(Client-wasm PROPERTIES LINK_OPTIONS "${EXECUTABLE_LINK_FLAGS}")
  set_target_properties(Client-wasm PROPERTIES SUFFIX ".js")

  install(FILES build/Client-wasm.js build/Client-wasm.wasm build/Client-wasm.wasm.map build/Client-wasm.worker.js DESTINATION ${CMAKE_INSTALL_PREFIX})

else()
  find_library(libindiclient NAMES libindiclient.a PATHS /usr/lib/x86_64-linux-gnu/libindi)
  find_library(libnova NAMES libnova.a PATHS /usr/lib/x86_64-linux-gnu)
  find_package(Threads REQUIRED)

  add_executable(Client Client.cpp)
  set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")
  target_link_libraries(Client ${libindiclient} ${libnova} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif()