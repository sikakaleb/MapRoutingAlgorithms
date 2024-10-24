cmake_minimum_required(VERSION 3.10)
project(MapRoutingAlgorithms)  # Nom du projet

set(CMAKE_CXX_STANDARD 17)

# Inclure les fichiers source du répertoire src
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Créer l'exécutable à partir des fichiers source
add_executable(MapRoutingAlgorithms ${SRC_FILES}
        src/main.cpp)
