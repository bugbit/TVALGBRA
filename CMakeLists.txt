# CMakeList.txt: proyecto de CMake para TVALGBRA, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

project ("TVALGBRA")

# Agregue un origen al ejecutable de este proyecto.
add_executable (TVALGBRA "src/TVALGBRA.cpp" "src/TVALGBRA.h" "src/GADGETS.cpp" "src/GADGETS.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
add_subdirectory(tvision) # Assuming Turbo Vision is in the 'tvision' directory.
target_link_libraries(TVALGBRA tvision)