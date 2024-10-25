//
// Created by caleb on 24/10/2024.
//
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <cmath>  // Pour les calculs de distance
#include "Vertex.h"
#include "Edge.h"

class Graph {
public:
    void addVertex(const Vertex& vertex);
    void addEdge(int sourceId, int destId, double weight);

    // Méthodes de recherche de chemin
    std::vector<int> bfs(int startId, int endId);
    std::vector<int> dijkstra(int startId, int endId);
    std::vector<int> a_star(int startId, int endId);  // Ajout de A*

    std::vector<int> getNeighbors(int vertexId) const;
    void printGraph() const;
    bool hasVertex(int vertexId) const;

private:
    std::unordered_map<int, Vertex> vertices;  // Utiliser unordered_map pour stocker les sommets par vertexId
    std::unordered_map<int, std::vector<Edge>> adjList;

    // Méthode pour calculer la distance euclidienne entre deux sommets
    double heuristicEuclidean(int sourceId, int destId) const;
};

#endif // GRAPH_H

