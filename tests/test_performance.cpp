#include <gtest/gtest.h>
#include <chrono>
#include <MercatorProjection.h>
#include <cmath>
#include <random>
#include "Graph.h"
#include "CSVReader.h"

void runPerformanceTest(const std::string& algorithm, Graph& graph, int startId, int endId) {
    std::vector<int> path;
    auto startTime = std::chrono::steady_clock::now();

    // Exécuter l'algorithme choisi
    if (algorithm == "bfs") {
        path = graph.bfs(startId, endId);
    } else if (algorithm == "dijkstra") {
        path = graph.dijkstra(startId, endId);
    } else if (algorithm == "astar") {
        path = graph.a_star(startId, endId);
    } else {
        FAIL() << "Algorithme inconnu : " << algorithm;
    }

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Vérifier si le temps d'exécution dépasse 1 seconde uniquement si un chemin a été trouvé
    if (!path.empty()) {
        ASSERT_LE(duration, 1000) << "L'algorithme " << algorithm << " a trouvé un chemin mais a dépassé 1 seconde !";
        std::cout << "Algorithme " << algorithm << " : Chemin trouvé de " << startId << " à " << endId
                  << " avec une longueur de " << path.size() << " en " << duration << " ms" << std::endl;
    } else {
        std::cout << "Algorithme " << algorithm << " : Aucun chemin trouvé de " << startId << " à " << endId
                  << " en " << duration << " ms" << std::endl;
    }
}

TEST(GraphPerformanceTest, RealDataGraph) {
    // Charger le graphe depuis un fichier CSV
    std::string filename = "../data/csv/graph_dc_area.2022-03-11.csv";
    Graph graph;
    CSVReader reader(filename);
    std::vector<Vertex> vertices = reader.readVertices();

    // Ajouter les sommets au graphe
    MercatorProjection projection;
    for (auto& vertex : vertices) {
        vertex.toCartesian(projection);
        graph.addVertex(vertex);
    }

    // Ajouter les arêtes au graphe
    reader.readEdges(graph);

    // Générer plusieurs paires (startId, endId) de sommets pour les tests
    int numTests = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, vertices.size());

    for (int i = 0; i < numTests; ++i) {
        int startId = dist(gen);
        int endId = dist(gen);
        while (startId == endId) {  // S'assurer que startId et endId sont différents
            endId = dist(gen);
        }

        std::cout << "Test " << i + 1 << " : " << std::endl;

        // Exécuter et vérifier BFS
        runPerformanceTest("bfs", graph, startId, endId);

        // Réinitialiser les nœuds visités pour le test suivant
        graph.resetVisitedNodes();

        // Exécuter et vérifier Dijkstra
        runPerformanceTest("dijkstra", graph, startId, endId);

        // Réinitialiser les nœuds visités pour le test suivant
        graph.resetVisitedNodes();

        // Exécuter et vérifier A*
        runPerformanceTest("astar", graph, startId, endId);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
