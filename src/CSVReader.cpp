//
// Created by caleb on 24/10/2024.
//

#include "CSVReader.h"

// CSVReader.cpp
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

std::vector<Vertex> CSVReader::readVertices() {
    std::vector<Vertex> vertices;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return vertices;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ignorer les lignes vides ou les commentaires
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Séparation des tokens par virgule
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Vérifier que la ligne correspond à un sommet
        if (tokens.size() >= 4 && tokens[0] == "V") {
            try {
                int vertexId = std::stoi(tokens[1]);
                double longitude = std::stod(tokens[2]);
                double latitude = std::stod(tokens[3]);

                Vertex vertex(vertexId, longitude, latitude);
                vertices.push_back(vertex);
            } catch (const std::exception& e) {
                std::cerr << "Erreur de conversion : " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return vertices;
}
