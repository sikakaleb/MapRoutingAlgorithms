//
// Created by caleb on 24/10/2024.
//

// src/Graph.cpp
#include "Graph.h"
#include <iostream>

void Graph::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
    // Ajouter une entrée vide dans la liste d'adjacence pour ce sommet
    adjList[vertex.vertexId] = std::vector<Edge>();
}

void Graph::addEdge(int sourceId, int destId, double weight) {
    Edge edge(sourceId, destId, weight);
    adjList[sourceId].push_back(edge);
}

std::vector<int> Graph::getNeighbors(int vertexId) const {
    std::vector<int> neighbors;
    // Récupérer les arêtes du sommet donné et extraire les identifiants des sommets voisins
    auto it = adjList.find(vertexId);
    if (it != adjList.end()) {
        for (const auto& edge : it->second) {
            neighbors.push_back(edge.destId);
        }
    }
    return neighbors;
}

void Graph::printGraph() const {
    for (const auto& vertex : vertices) {
        std::cout << "Vertex ID: " << vertex.vertexId
                  << " (" << vertex.longitude << ", " << vertex.latitude << ")\n";
        std::cout << "  Neighbors: ";
        for (const auto& edge : adjList.at(vertex.vertexId)) {
            std::cout << edge.destId << " (Weight: " << edge.weight << "), ";
        }
        std::cout << std::endl;
    }
}
