//
// Created by caleb on 24/10/2024.
//
#include "gtest/gtest.h"
#include "CSVReader.h"
#include <vector>

// Test pour vérifier la lecture des sommets à partir du fichier CSV
/*TEST(CSVReaderTest, CanReadVertices) {
    CSVReader reader("../data/graph_dc_area.2022-03-11.csv");  // Assurez-vous que le chemin est correct
    std::vector<Vertex> vertices = reader.readVertices();

    ASSERT_GT(vertices.size(), 0);  // Vérifier que des sommets ont bien été chargés

    // Exemple de test d'un sommet spécifique
    EXPECT_EQ(vertices[0].vertexId, 0);
    EXPECT_DOUBLE_EQ(vertices[0].longitude, -76.929192819);
    EXPECT_DOUBLE_EQ(vertices[0].latitude, 38.8924826094);
}*/


TEST(CSVReaderTest, CanReadFirst30Vertices) {
    CSVReader reader("../data/graph_dc_area.2022-03-11.csv");  // Assurez-vous que le chemin est correct
    std::vector<Vertex> vertices = reader.readVertices();

    ASSERT_GE(vertices.size(), 10);  // S'assurer que le fichier contient au moins 30 sommets

    // Exemple de données attendues pour les 30 premiers sommets
    std::vector<std::tuple<int, double, double>> expected_vertices = {
        {0, -76.929192819, 38.8924826094},
        {2, -76.9296620544, 38.8925491793},
        {3, -76.981166842, 38.9025611176},
        {13, -76.9806830055, 38.9033419167},
        {14, -76.9796279047, 38.8655023225},
        {16, -76.9796776153, 38.8653335596},
        {17, -77.0189335838, 38.8983222165},
        {19, -77.0194016108, 38.8983187914},
        {20, -77.1014062303, 38.924958382},
        {37, -77.1028559907, 38.9262992178},
        // Ajoutez ici les autres sommets attendus jusqu'à 30
    };

    for (size_t i = 0; i < expected_vertices.size(); ++i) {
        EXPECT_EQ(vertices[i].vertexId, std::get<0>(expected_vertices[i]));
        EXPECT_DOUBLE_EQ(vertices[i].longitude, std::get<1>(expected_vertices[i]));
        EXPECT_DOUBLE_EQ(vertices[i].latitude, std::get<2>(expected_vertices[i]));
    }
}
