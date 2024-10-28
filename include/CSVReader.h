//
// Created by caleb on 24/10/2024.
//

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include "Vertex.h"
#include "Graph.h"

class CSVReader {
public:
    explicit CSVReader(const std::string& filename);
    std::vector<Vertex> readVertices();
    void readEdges(Graph& graph);  // Méthode pour lire les arêtes et les ajouter au graphe

private:
    std::string filename;

    // Méthode pour lire le fichier graph_dc_area (sommets et arêtes)
    void readGraphDcArea(std::ifstream& file, Graph& graph);

    // Méthode pour lire le fichier OSM Berlin
    void readBerlinOsmEdges(std::ifstream& file, Graph& graph);
};

#endif // CSVREADER_H


