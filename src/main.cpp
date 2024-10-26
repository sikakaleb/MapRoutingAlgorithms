//
// Created by caleb on 24/10/2024.
//
//
// Created by caleb on 24/10/2024.
//

#include <iostream>
#include "MercatorProjection.h"
#include "Graph.h"
#include "Vertex.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "CSVReader.h"
#include <chrono>  // Inclure chrono pour mesurer le temps d'exécution

int main(int argc, char* argv[]) {
    // Vérifier le nombre minimum d'arguments
    if (argc < 9) {
        std::cerr << "Usage: graph_traversal --start <startId> --end <endId> --algorithm <bfs|dijkstra|astar> --file <filename>" << std::endl;
        return 1;
    }

    // Variables pour stocker les arguments
    int startId = -1;
    int endId = -1;
    std::string algorithm;
    std::string filename;

    // Analyse des arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--start" && i + 1 < argc) {
            startId = std::stoi(argv[++i]);
        } else if (arg == "--end" && i + 1 < argc) {
            endId = std::stoi(argv[++i]);
        } else if (arg == "--algorithm" && i + 1 < argc) {
            algorithm = argv[++i];
        } else if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else {
            std::cerr << "Argument inconnu ou manquant : " << arg << std::endl;
            return 1;
        }
    }

    // Vérifier que tous les arguments requis sont fournis
    if (startId == -1 || endId == -1 || algorithm.empty() || filename.empty()) {
        std::cerr << "Tous les arguments (--start, --end, --algorithm, --file) sont requis." << std::endl;
        return 1;
    }

    // Initialiser le graphe
    Graph graph;

    // Lire les sommets et les arêtes du fichier
    CSVReader reader(filename);
    std::vector<Vertex> vertices = reader.readVertices();

    // Ajouter les sommets au graphe
    MercatorProjection projection;
    for (auto& vertex : vertices) {
        vertex.toCartesian(projection);
        graph.addVertex(vertex);
    }

    // Lire les arêtes et les ajouter au graphe
    reader.readEdges(graph);

    // Vérifier que les sommets de départ et d'arrivée existent
    if (!graph.hasVertex(startId) || !graph.hasVertex(endId)) {
        std::cerr << "Le sommet de départ ou d'arrivée n'existe pas dans le graphe." << std::endl;
        return 1;
    }

    // Mesurer le temps d'exécution de l'algorithme
    auto startTime = std::chrono::steady_clock::now();  // Temps de début

    // Exécuter l'algorithme choisi
    std::vector<int> path;
    if (algorithm == "bfs") {
        path = graph.bfs(startId, endId);
    } else if (algorithm == "dijkstra") {
        path = graph.dijkstra(startId, endId);
    } else if (algorithm == "astar") {
        path = graph.a_star(startId, endId);
    } else {
        std::cerr << "Algorithme inconnu : " << algorithm << ". Choisissez parmi 'bfs', 'dijkstra', 'astar'." << std::endl;
        return 1;
    }

    // Mesurer le temps de fin et calculer la durée
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Afficher le temps d'exécution
    std::cout << "Temps d'exécution de l'algorithme " << algorithm << ": " << duration << " ms" << std::endl;

    // Vérifier si le temps d'exécution dépasse 1 seconde
    if (duration > 1000) {
        std::cerr << "Avertissement : Le temps d'exécution a dépassé 1 seconde !" << std::endl;
    }

    // Vérifier si un chemin a été trouvé
    if (path.empty()) {
        std::cout << "Aucun chemin trouvé entre " << startId << " et " << endId << "." << std::endl;
        return 0;
    }

    // Calculer le nombre total de sommets visités (pour BFS et A*)
    int totalVisited = graph.getTotalVisitedNodes();

    // Afficher les résultats
    std::cout << "Total visited vertex = " << totalVisited << std::endl;
    std::cout << "Total vertex on path from start to end = " << path.size() << std::endl;

    double totalLength = 0.0;
    for (size_t i = 0; i < path.size(); ++i) {
        int vertexId = path[i];
        const Vertex& vertex = graph.getVertex(vertexId);
        std::cout << "Vertex[" << i + 1 << "] = " << vertexId << ", length = " << totalLength << std::endl;

        // Si ce n'est pas le dernier sommet, ajouter la longueur de l'arête au total
        if (i + 1 < path.size()) {
            int nextVertexId = path[i + 1];
            double edgeWeight = graph.getEdgeWeight(vertexId, nextVertexId);
            totalLength += edgeWeight;
        }
    }

    return 0;
}
