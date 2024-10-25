cmake_minimum_required(VERSION 3.14)
project(MapRoutingAlgorithms)

set(CMAKE_CXX_STANDARD 17)

# Ajouter le répertoire include pour les fichiers d'en-tête
include_directories(include)

# Inclure les fichiers source du répertoire src (sans inclure main.cpp)
file(GLOB SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")  # Supprimer main.cpp des fichiers sources pour les tests


# Ne pas inclure src/main.cpp dans les tests
add_executable(MapRoutingAlgorithms ${SRC_FILES} src/main.cpp
        include/utils.h)

# --- Partie Google Test ---
include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/third_party")

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
)
# Empêcher Google Test de créer des cibles de test supplémentaires
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Inclure Google Test pour utiliser gtest_discover_tests
include(GoogleTest)

# Ajouter les fichiers de test
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# Créer un exécutable pour chaque fichier de test
# Créer un exécutable pour chaque fichier de test, en excluant main.cpp
foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file} ${SRC_FILES}
            tests/test_mercator_projection.cpp
            tests/test_cross_validation.cpp
            include/utils.h)  # Ne pas inclure src/main.cpp ici

    target_link_libraries(${test_name} GTest::gtest_main)

    # Découverte automatique des tests
    gtest_discover_tests(${test_name})
endforeach()
# foreach(test_file ${TEST_FILES})
#     get_filename_component(test_name ${test_file} NAME_WE)

#     # Créer une liste de fichiers sources nécessaires en fonction du nom du fichier de test
#     if (test_name MATCHES "test_graph")
#         set(SRC_FILES src/Graph.cpp src/Vertex.cpp
#                 src/Edge.cpp)
#     elseif (test_name MATCHES "test_csv_reader")
#         set(SRC_FILES src/CSVReader.cpp src/Vertex.cpp
#                 src/Edge.cpp)
#     else()
#         # Par défaut, inclure tous les fichiers sources pour d'autres tests
#         set(SRC_FILES src/*.cpp)
#     endif()

#     # Créer un exécutable unique pour chaque fichier de test
#     add_executable(${test_name}_exec ${test_file} ${SRC_FILES})

#     # Lier Google Test à chaque exécutable
#     target_link_libraries(${test_name}_exec GTest::gtest_main)

#     # Découverte automatique des tests
#     gtest_discover_tests(${test_name}_exec)
# endforeach()
