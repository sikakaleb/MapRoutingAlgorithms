//
// Created by caleb on 24/10/2024.
//

// include/Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Edge.h"

class Graph {
public:
    // Ajout de sommets et d'arêtes
    void addVertex(const Vertex& vertex);
    void addEdge(int sourceId, int destId, double weight);

    // Récupérer les voisins d'un sommet donné
    std::vector<int> getNeighbors(int vertexId) const;

    // Pour afficher les informations du graphe (sommets et arêtes)
    void printGraph() const;

private:
    std::vector<Vertex> vertices;  // Liste des sommets
    std::unordered_map<int, std::vector<Edge>> adjList;  // Liste d'adjacence
};

#endif // GRAPH_H
