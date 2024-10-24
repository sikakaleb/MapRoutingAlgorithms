//
// Created by caleb on 24/10/2024.
//
#include "gtest/gtest.h"
#include "Graph.h"

// Test pour vérifier l'ajout de sommets
TEST(GraphTest, AddVertex) {
    Graph graph;

    // Ajouter un sommet
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));

    // Vérifier que le sommet est présent
    std::vector<int> neighbors = graph.getNeighbors(1);
    EXPECT_EQ(neighbors.size(), 0);  // Pas de voisins au départ
}

// Test pour vérifier l'ajout d'arêtes
TEST(GraphTest, AddEdge) {
    Graph graph;

    // Ajouter deux sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));

    // Ajouter une arête entre les deux sommets
    graph.addEdge(1, 2, 5.0);

    // Vérifier que le voisin du sommet 1 est le sommet 2
    std::vector<int> neighbors = graph.getNeighbors(1);
    ASSERT_EQ(neighbors.size(), 1);  // Il devrait y avoir 1 voisin
    EXPECT_EQ(neighbors[0], 2);      // Le voisin devrait être le sommet 2
}

// Test pour vérifier que plusieurs arêtes peuvent être ajoutées
TEST(GraphTest, MultipleEdges) {
    Graph graph;

    // Ajouter trois sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));

    // Ajouter des arêtes entre les sommets
    graph.addEdge(1, 2, 5.0);
    graph.addEdge(1, 3, 7.0);

    // Vérifier que les voisins du sommet 1 sont les sommets 2 et 3
    std::vector<int> neighbors = graph.getNeighbors(1);
    ASSERT_EQ(neighbors.size(), 2);  // Il devrait y avoir 2 voisins
    EXPECT_EQ(neighbors[0], 2);
    EXPECT_EQ(neighbors[1], 3);
}
