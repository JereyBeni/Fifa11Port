cmake_minimum_required(VERSION 3.22.1)
project(Fifa11Port)

# Estándar de C++ moderno
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Librería compartida nativa para Android (.so)
add_library(fifa11_core SHARED
    app/src/main/cpp/main.cpp
)

# Enlazar librerías nativas de Android (OpenGL ES, Log, Android)
find_library(log-lib log)
find_library(gles-lib GLESv3)
find_library(android-lib android)

target_link_libraries(fifa11_core
    ${log-lib}
    ${gles-lib}
    ${android-lib}
)