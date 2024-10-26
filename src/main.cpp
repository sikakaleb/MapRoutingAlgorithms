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

/*void touca() {
    // Initialiser la projection Mercator avec le centre spécifié
    MercatorProjection projection(-77.0369, 38.9072);  // Longitude et latitude du centre

    // Créer des sommets avec des coordonnées géographiques
    Vertex v1(1, -76.929192819, 38.8924826094);
    Vertex v2(2, -76.9296620544, 38.8925491793);

    // Convertir en coordonnées cartésiennes
    v1.toCartesian(projection);
    v2.toCartesian(projection);

    // Afficher les coordonnées cartésiennes
    std::cout << "Vertex 1: (" << v1.longitude << ", " << v1.latitude << ") -> Cartésiennes ("
              << v1.x << ", " << v1.y << ")\n";

    std::cout << "Vertex 2: (" << v2.longitude << ", " << v2.latitude << ") -> Cartésiennes ("
              << v2.x << ", " << v2.y << ")\n";
}


// Fonction de test pour la création et la gestion du Graphe
/*void test_graph_operations() {
    std::cout << "=== Test: Création et Gestion du Graphe ===\n";

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
    std::cout << "\n";

    // Afficher les voisins du sommet 1
    std::vector<int> neighbors = graph.getNeighbors(1);
    std::cout << "Neighbors of Vertex 1: ";
    for (int neighbor : neighbors) {
        std::cout << neighbor << " ";
    }
    std::cout << "\n\n";
}*/

// Fonction de test supplémentaire pour afficher les coordonnées cartésiennes des Vertex
/*void test_vertex_coordinates() {
    std::cout << "=== Test: Affichage des Coordonnées Cartésiennes des Vertex ===\n";

    // Initialiser la projection Mercator avec le centre spécifié
    MercatorProjection projection(-77.0369, 38.9072);  // Longitude et latitude du centre

    // Créer des sommets avec des coordonnées géographiques
    Vertex v1(1, -76.929192819, 38.8924826094);
    Vertex v2(2, -76.9296620544, 38.8925491793);

    // Convertir en coordonnées cartésiennes
    v1.toCartesian(projection);
    v2.toCartesian(projection);

    // Afficher les coordonnées cartésiennes
    std::cout << "Vertex 1: (" << v1.longitude << ", " << v1.latitude << ") -> Cartésiennes ("
              << v1.x << ", " << v1.y << ")\n";

    std::cout << "Vertex 2: (" << v2.longitude << ", " << v2.latitude << ") -> Cartésiennes ("
              << v2.x << ", " << v2.y << ")\n\n";
}

// Fonction de test supplémentaire pour afficher à nouveau les coordonnées cartésiennes des Vertex
/*void test_vertex_coordinates_duplicate() {
    std::cout << "=== Test: Affichage des Coordonnées Cartésiennes des Vertex (Duplicate) ===\n";

    // Initialiser la projection Mercator avec le centre spécifié
    MercatorProjection projection(-77.0369, 38.9072);  // Longitude et latitude du centre

    // Créer des sommets avec des coordonnées géographiques
    Vertex v11(1, -76.929192819, 38.8924826094);
    Vertex v22(2, -76.9296620544, 38.8925491793);

    // Convertir en coordonnées cartésiennes
    v11.toCartesian(projection);
    v22.toCartesian(projection);

    // Afficher les coordonnées cartésiennes
    std::cout << "Vertex 1: (" << v11.longitude << ", " << v11.latitude << ") -> Cartésiennes ("
              << v11.x << ", " << v11.y << ")\n";

    std::cout << "Vertex 2: (" << v22.longitude << ", " << v22.latitude << ") -> Cartésiennes ("
              << v22.x << ", " << v22.y << ")\n\n";
}

void  mainBfs() {
    Graph graph;

    // Ajouter des sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));
    graph.addVertex(Vertex(4, -77.1014062303, 38.924958382));

    // Ajouter des arêtes
    graph.addEdge(1, 2, 5.0);
    graph.addEdge(2, 3, 7.0);
    graph.addEdge(1, 3, 9.0);
    graph.addEdge(3, 4, 2.0);

    // Afficher le graphe
    graph.printGraph();

    // Trouver un chemin avec BFS
    std::vector<int> path = graph.bfs(1, 4);
    if (!path.empty()) {
        std::cout << "Chemin trouvé avec BFS : ";
        for (int vertexId : path) {
            std::cout << vertexId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé avec BFS." << std::endl;
    }

}


void mainDijkstra() {
    Graph graph;

    // Ajouter des sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));
    graph.addVertex(Vertex(4, -77.1014062303, 38.924958382));
    graph.addVertex(Vertex(5, -77.0000000000, 38.9000000000));

    // Ajouter des arêtes
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(2, 3, 5.0);
    graph.addEdge(1, 3, 2.0);  // Chemin plus direct mais plus lourd pour BFS
    graph.addEdge(3, 4, 2.0);
    graph.addEdge(1, 5, 10.0);
    graph.addEdge(5, 4, 1.0);  // Chemin plus court pour Dijkstra

    // Afficher le graphe
    graph.printGraph();

    // Trouver un chemin avec BFS
    std::vector<int> bfsPath = graph.bfs(1, 4);
    if (!bfsPath.empty()) {
        std::cout << "Chemin trouvé avec BFS : ";
        for (int vertexId : bfsPath) {
            std::cout << vertexId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé avec BFS." << std::endl;
    }

    // Trouver un chemin avec Dijkstra
    std::vector<int> dijkstraPath = graph.dijkstra(1, 4);
    if (!dijkstraPath.empty()) {
        std::cout << "Chemin trouvé avec Dijkstra : ";
        for (int vertexId : dijkstraPath) {
            std::cout << vertexId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé avec Dijkstra." << std::endl;
    }

}


int mainAstar() {
    Graph graph;

    // Ajouter des sommets
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));
    graph.addVertex(Vertex(4, -77.1014062303, 38.924958382));
    graph.addVertex(Vertex(5, -77.0000000000, 38.9000000000));

    // Ajouter des arêtes avec des poids
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(2, 3, 5.0);
    graph.addEdge(1, 3, 2.0);  // Chemin plus direct mais plus lourd pour BFS
    graph.addEdge(3, 4, 2.0);
    graph.addEdge(1, 5, 10.0);
    graph.addEdge(5, 4, 1.0);  // Chemin plus court pour Dijkstra

    // Afficher le graphe
    graph.printGraph();

    // Trouver un chemin avec A*
    std::vector<int> aStarPath = graph.a_star(1, 4);
    if (!aStarPath.empty()) {
        std::cout << "Chemin trouvé avec A* : ";
        for (int vertexId : aStarPath) {
            std::cout << vertexId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé avec A*." << std::endl;
    }

    // Trouver un chemin avec Dijkstra
    std::vector<int> dijkstraPath = graph.dijkstra(1, 4);
    if (!dijkstraPath.empty()) {
        std::cout << "Chemin trouvé avec Dijkstra : ";
        for (int vertexId : dijkstraPath) {
            std::cout << vertexId << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé avec Dijkstra." << std::endl;
    }

    return 0;
}
#include <iostream>
#include <string>
#include "Graph.h"
#include "CSVReader.h"*/



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
