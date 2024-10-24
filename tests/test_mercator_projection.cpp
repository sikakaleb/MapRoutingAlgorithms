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

// Fonction pour exécuter un script Python et récupérer les résultats
std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("Erreur lors de l'exécution du script Python");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

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
