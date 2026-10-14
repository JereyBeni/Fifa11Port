cmake_minimum_required(VERSION 3.22.1)
project("fifa11port")

# Compilar la librería nativa compartida incluyendo el parser de archivos .big
add_library(
    fifa11_core
    SHARED
    app/src/main/cpp/main.cpp
    app/src/main/cpp/BigParser.cpp
)

find_library(
    log-lib
    log
)

target_link_libraries(
    fifa11_core
    ${log-lib}
)