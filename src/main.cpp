//
// Created by caleb on 24/10/2024.
//

#include <iostream>
#include "CSVReader.h"

int main() {
    CSVReader reader("../data/graph_dc_area.2022-03-11.csv"); // Assurez-vous que le fichier s'appelle bien 'vertices.csv'
    std::vector<Vertex> vertices = reader.readVertices();

    for (const auto& vertex : vertices) {
        std::cout << "Vertex ID: " << vertex.vertexId
                  << ", Longitude: " << vertex.longitude
                  << ", Latitude: " << vertex.latitude << std::endl;
    }

    return 0;
}
