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
}*/


// Fonction de test pour la création et la gestion du Graphe
void test_graph_operations() {
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
}

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
}*/

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
}*/

int main() {
    test_graph_operations();
    //test_vertex_coordinates();
    //test_vertex_coordinates_duplicate();
   // touca();
    return 0;
}





