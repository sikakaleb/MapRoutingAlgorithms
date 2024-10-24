//
// Created by caleb on 24/10/2024.
//
#include "gtest/gtest.h"
#include "Graph.h"
#include "CSVReader.h"

// Test pour vérifier que les sommets sont bien lus à partir du CSV
TEST(CSVReaderTest, CanReadVertices) {
    CSVReader reader("../data/csv/graph_dc_area.2022-03-11.csv"); // Assurez-vous que le chemin est correct
    std::vector<Vertex> vertices = reader.readVertices();

    // Vérifier qu'au moins un sommet a été lu
    ASSERT_GT(vertices.size(), 0);

    // Vérifier les valeurs spécifiques du premier sommet
    EXPECT_EQ(vertices[0].vertexId, 0);
    EXPECT_DOUBLE_EQ(vertices[0].longitude, -76.929192819);
    EXPECT_DOUBLE_EQ(vertices[0].latitude, 38.8924826094);
}

// Test pour vérifier que les sommets et arêtes sont bien ajoutés au graphe
TEST(GraphTest, AddVertexAndEdge) {
    Graph graph;

    // Ajouter deux sommets au graphe
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));

    // Ajouter une arête entre les deux sommets
    graph.addEdge(1, 2, 5.0);

    // Vérifier que les voisins du sommet 1 sont corrects
    std::vector<int> neighbors = graph.getNeighbors(1);
    ASSERT_EQ(neighbors.size(), 1);
    EXPECT_EQ(neighbors[0], 2);
}
