//
// Created by caleb on 24/10/2024.
//
#include "gtest/gtest.h"
#include "MercatorProjection.h"
#include "Vertex.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <array>
#include "utils.h"  // Inclure l'en-tête avec la fonction exec()

// Test pour comparer la conversion Mercator avec Python via pyproj
TEST(MercatorProjectionTest, CompareWithPyProj) {
    // Utiliser la projection Mercator avec le centre par défaut
    MercatorProjection projection;

    // Créer un Vertex
    Vertex v(1, 0.0, 51.4779);  // Greenwich

    // Convertir avec la méthode C++
    v.toCartesian(projection);

    // Appeler le script Python pour calculer les coordonnées Mercator via pyproj
    std::string cmd = "python ../scripts/mercator_projection.py 0.0 51.4779";
    std::string output = exec(cmd);

    // Récupérer les valeurs x et y du script Python
    std::istringstream iss(output);
    std::string x_str, y_str;
    getline(iss, x_str, ',');
    getline(iss, y_str, ',');

    double py_x = std::stod(x_str);
    double py_y = std::stod(y_str);

    // Comparer les résultats
    EXPECT_NEAR(v.x, py_x, 1.0);
    EXPECT_NEAR(v.y, py_y, 1.0);
}
