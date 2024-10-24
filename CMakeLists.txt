cmake_minimum_required(VERSION 3.14)
project(MapRoutingAlgorithms)

set(CMAKE_CXX_STANDARD 17)

# Ajouter le répertoire include pour les fichiers d'en-tête
include_directories(include)

# Inclure les fichiers source du répertoire src
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Créer l'exécutable principal
add_executable(MapRoutingAlgorithms ${SRC_FILES})

# --- Ajouter cette partie pour utiliser FetchContent ---
include(FetchContent)

# Définir le répertoire où les contenus seront téléchargés
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/third_party")

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1  # Vous pouvez spécifier la version souhaitée
)

# Empêcher Google Test de créer des cibles de test supplémentaires
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Ajouter les fichiers de test
file(GLOB_RECURSE TEST_FILES tests/*.cpp)

# Créer un exécutable pour chaque fichier de test
foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file} ${SRC_FILES})
    target_link_libraries(${test_name} GTest::gtest_main)

    # Inclure GoogleTest pour utiliser gtest_discover_tests
    include(GoogleTest)

    gtest_discover_tests(${test_name})
endforeach()
