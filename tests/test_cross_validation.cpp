#include "gtest/gtest.h"
#include "Graph.h"
#include "CSVReader.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <array>
#include "utils.h"  // Inclure l'en-tête avec la fonction exec()

TEST(CrossValidationTest, CompareWithNetworkX_GraphDcArea) {
    Graph graph;

    // Lire les sommets et arêtes à partir du fichier graph_dc_area
    CSVReader reader("../data/csv/graph_dc_area.2022-03-11.csv");
    std::vector<Vertex> vertices = reader.readVertices();
    for (const Vertex& v : vertices) {
        graph.addVertex(v);
    }
    reader.readEdges(graph);

    // Exécuter A* dans C++
    std::srand(std::time(nullptr)); // Utiliser l'heure actuelle comme graine pour le générateur de nombres aléatoires
    int startId = std::rand() % vertices.size() + 1;
    int endId = std::rand() % vertices.size() + 1;

    std::vector<int> aStarPath = graph.a_star(startId, endId);
    std::vector<int> dijkstraPath = graph.dijkstra(startId, endId);

    // Exécuter le script Python avec NetworkX
    std::string cmd = "python ../scripts/compare_paths.py ../data/csv/graph_dc_area.2022-03-11.csv " + std::to_string(startId) + " " + std::to_string(endId);
    std::string output = exec(cmd);

    // Analyser et afficher les résultats
    std::istringstream iss(output);
    std::string line;
    while (getline(iss, line)) {
        std::cout << line << std::endl;
    }
}

TEST(CrossValidationTest, CompareWithNetworkX_BerlinOsm) {
    Graph graph;

    // Lire les arêtes à partir du fichier berlin_osm
    CSVReader reader("../data/csv/berlin_osm_graph.csv");
    reader.readEdges(graph);  // Pas besoin de lire explicitement les sommets

    // Exécuter A* dans C++ (choisir des IDs valides en fonction des arêtes du fichier)
    std::vector<int> aStarPath = graph.a_star(172539, 34694336);  // Utilise des sommets valides du fichier
    std::vector<int> dijkstraPath = graph.dijkstra(172539, 34694336);

    // Exécuter le script Python avec NetworkX
    std::string cmd = "python ../scripts/compare_paths.py ../data/csv/berlin_osm_graph.csv 172539 34694336";
    std::string output = exec(cmd);

    // Analyser et afficher les résultats
    std::istringstream iss(output);
    std::string line;
    while (getline(iss, line)) {
        std::cout << line << std::endl;
    }
}

