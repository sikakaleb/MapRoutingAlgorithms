#include <gtest/gtest.h>
#include <chrono>
#include <random>
#include "Graph.h"
#include <cmath>


// Générer un graphe aléatoire avec un nombre donné de sommets et d'arêtes
Graph generateRandomGraph(int numVertices, int numEdges) {
    Graph graph;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, numVertices);

    // Ajouter des sommets
    for (int i = 1; i <= numVertices; ++i) {
        graph.addVertex(Vertex(i, 0.0, 0.0));
    }

    // Ajouter des arêtes avec des poids aléatoires
    for (int i = 0; i < numEdges; ++i) {
        int source = dist(gen);
        int dest = dist(gen);
        double weight = static_cast<double>(dist(gen) % 100) + 1; // poids entre 1 et 100
        graph.addEdge(source, dest, weight);
    }

    return graph;
}

// Test pour vérifier que chaque algorithme s'exécute en moins de 1 seconde
void runPerformanceTest(const std::string& algorithm, Graph& graph, int startId, int endId) {
    std::vector<int> path;
    auto startTime = std::chrono::steady_clock::now();

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

    // Vérifier si le temps d'exécution dépasse 1 seconde
    ASSERT_LE(duration, 1000) << "L'algorithme " << algorithm << " a dépassé 1 seconde !";

    if (!path.empty()) {
        std::cout << "Algorithme " << algorithm << " : Chemin trouvé de " << startId << " à " << endId
                  << " avec une longueur de " << path.size() << " en " << duration << " ms" << std::endl;
    } else {
        std::cout << "Algorithme " << algorithm << " : Aucun chemin trouvé de " << startId << " à " << endId
                  << " en " << duration << " ms" << std::endl;
    }
}

TEST(GraphPerformanceTest, LargeGraphs) {
    int numTests = 10000; // Nombre de tests
    int numVertices = 10000; // Nombre de sommets par graphe
    int numEdges = 30000; // Nombre d'arêtes par graphe

    for (int i = 0; i < numTests; ++i) {
        Graph graph = generateRandomGraph(numVertices, numEdges);

        int startId = 1;
        int endId = numVertices;

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
