//
// Created by caleb on 24/10/2024.
//

// src/Graph.cpp
#include "Graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>  // Pour std::reverse

// Ajout de sommet
void Graph::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
    adjList[vertex.vertexId] = std::vector<Edge>();
}

// Ajout d'arête
void Graph::addEdge(int sourceId, int destId, double weight) {
    Edge edge(sourceId, destId, weight);
    adjList[sourceId].push_back(edge);
}
// Heuristique : distance euclidienne entre deux sommets
double Graph::heuristicEuclidean(int sourceId, int destId) const {
    const Vertex& source = vertices[sourceId - 1];  // Indices de 1 à n
    const Vertex& dest = vertices[destId - 1];
    double dx = dest.x - source.x;
    double dy = dest.y - source.y;
    return std::sqrt(dx * dx + dy * dy);
}

// A* pour trouver le chemin le plus court en tenant compte de l'heuristique
std::vector<int> Graph::a_star(int startId, int endId) {
    std::unordered_map<int, double> gScore;  // Coût depuis le départ
    std::unordered_map<int, double> fScore;  // Estimation de coût (g + heuristique)
    std::unordered_map<int, int> parent;  // Garder la trace des parents
    std::set<int> visited;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> openSet;

    // Initialisation des scores à l'infini
    for (const auto& vertex : vertices) {
        gScore[vertex.vertexId] = std::numeric_limits<double>::infinity();
        fScore[vertex.vertexId] = std::numeric_limits<double>::infinity();
    }

    gScore[startId] = 0.0;
    fScore[startId] = heuristicEuclidean(startId, endId);
    openSet.push({fScore[startId], startId});
    parent[startId] = -1;

    while (!openSet.empty()) {
        int current = openSet.top().second;
        openSet.pop();

        // Si on atteint le sommet de destination
        if (current == endId) {
            std::vector<int> path;
            for (int at = endId; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        visited.insert(current);

        // Pour chaque voisin
        for (const Edge& edge : adjList[current]) {
            int neighbor = edge.destId;

            if (visited.find(neighbor) != visited.end()) {
                continue;  // Ignorer les voisins déjà visités
            }

            double tentativeGScore = gScore[current] + edge.weight;
            if (tentativeGScore < gScore[neighbor]) {
                parent[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristicEuclidean(neighbor, endId);
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    // Si aucun chemin trouvé, retourner un vecteur vide
    return std::vector<int>();
}

// Dijkstra pour trouver le chemin le plus court en termes de poids
std::vector<int> Graph::dijkstra(int startId, int endId) {
    std::unordered_map<int, double> distances;  // Distances à partir du sommet de départ
    std::unordered_map<int, int> parent;  // Garder la trace des parents pour reconstruire le chemin
    std::set<int> visited;  // Marquer les sommets visités
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> minHeap;

    // Initialisation des distances à l'infini, sauf pour le sommet de départ
    for (const auto& vertex : vertices) {
        distances[vertex.vertexId] = std::numeric_limits<double>::infinity();
    }
    distances[startId] = 0;
    parent[startId] = -1;

    // Ajouter le sommet de départ à la file de priorité
    minHeap.push({0, startId});

    while (!minHeap.empty()) {
        int current = minHeap.top().second;
        minHeap.pop();

        // Si nous avons atteint le sommet d'arrivée
        if (current == endId) {
            std::vector<int> path;
            for (int at = endId; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Marquer le sommet comme visité
        visited.insert(current);

        // Pour chaque voisin
        for (const Edge& edge : adjList[current]) {
            int neighbor = edge.destId;
            double newDist = distances[current] + edge.weight;

            // Si le voisin n'a pas été visité et qu'une meilleure distance est trouvée
            if (visited.find(neighbor) == visited.end() && newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                parent[neighbor] = current;
                minHeap.push({newDist, neighbor});
            }
        }
    }

    // Si aucun chemin trouvé, retourner un vecteur vide
    return std::vector<int>();
}

// BFS pour comparer
std::vector<int> Graph::bfs(int startId, int endId) {
    std::queue<int> toVisit;
    std::unordered_map<int, int> parent;
    std::set<int> visited;

    toVisit.push(startId);
    visited.insert(startId);
    parent[startId] = -1;

    while (!toVisit.empty()) {
        int current = toVisit.front();
        toVisit.pop();

        if (current == endId) {
            std::vector<int> path;
            for (int at = endId; at != -1; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : adjList[current]) {
            int neighbor = edge.destId;
            if (visited.find(neighbor) == visited.end()) {
                toVisit.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = current;
            }
        }
    }

    return std::vector<int>();
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
