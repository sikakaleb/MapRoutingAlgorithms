//
// Created by caleb on 24/10/2024.
//
//
// Created by caleb on 24/10/2024.
//

#include <iostream>

#include "Graph.h"

int main() {
    Graph graph;

    // Ajouter des sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));

    // Ajouter des arêtes
    graph.addEdge(1, 2, 5.0);  // De 1 à 2 avec un poids de 5.0
    graph.addEdge(2, 3, 7.0);  // De 2 à 3 avec un poids de 7.0

    // Afficher le graphe
    graph.printGraph();

    // Afficher les voisins du sommet 1
    std::vector<int> neighbors = graph.getNeighbors(1);
    std::cout << "Neighbors of Vertex 1: ";
    for (int neighbor : neighbors) {
        std::cout << neighbor << " ";
    }
    std::cout << std::endl;

    return 0;
}
