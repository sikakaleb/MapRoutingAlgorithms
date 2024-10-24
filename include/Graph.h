//
// Created by caleb on 24/10/2024.
//
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Edge.h"

class Graph {
public:
    void addVertex(const Vertex& vertex);
    void addEdge(int sourceId, int destId, double weight);

    // Méthodes de recherche de chemin
    std::vector<int> bfs(int startId, int endId);
    std::vector<int> dijkstra(int startId, int endId);
    std::vector<int> getNeighbors(int vertexId) const;
    void printGraph() const;

private:
    std::vector<Vertex> vertices;
    std::unordered_map<int, std::vector<Edge>> adjList;
};

#endif // GRAPH_H
