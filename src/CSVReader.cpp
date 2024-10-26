//
// Created by caleb on 24/10/2024.
//
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

        // Vérifier que la ligne correspond à un sommet et que les colonnes sont valides
        if (tokens.size() >= 4 && tokens[0] == "V") {
            try {
                if (!tokens[1].empty() && !tokens[2].empty() && !tokens[3].empty()) {
                    long vertexId = std::stoll(tokens[1]);
                    double longitude = std::stod(tokens[2]);
                    double latitude = std::stod(tokens[3]);

                    Vertex vertex(vertexId, longitude, latitude);
                    vertices.push_back(vertex);
                } else {
                    std::cerr << "Ligne mal formattée (sommets manquants) : " << line << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur de conversion : " << e.what() << " dans la ligne : " << line << std::endl;
            }
        }
    }

    file.close();
    return vertices;
}


// Lire les arêtes pour le fichier graph_dc_area
void CSVReader::readGraphDcArea(std::ifstream& file, Graph& graph) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Vérification des colonnes d'intérêt (les trois premières)
        if (tokens.size() >= 4 && tokens[0] == "E") {
            try {
                if (!tokens[1].empty() && !tokens[2].empty() && !tokens[3].empty()) {
                    int sourceId = std::stoi(tokens[1]);
                    int destId = std::stoi(tokens[2]);
                    double weight = std::stod(tokens[3]);

                    graph.addEdge(sourceId, destId, weight);
                } else {
                    std::cerr << "Ligne mal formattée (arêtes manquantes) : " << line << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Erreur de conversion : " << e.what() << " dans la ligne : " << line << std::endl;
            }
        }
    }
}


// Lire les arêtes pour le fichier OSM Berlin
void CSVReader::readBerlinOsmEdges(std::ifstream& file, Graph& graph) {
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string sourceId, destId, weight;

        std::getline(ss, sourceId, ',');
        std::getline(ss, destId, ',');
        std::getline(ss, weight, ',');

        try {
            if (!sourceId.empty() && !destId.empty() && !weight.empty()) {
                // Utiliser stoll pour les grands nombres
                long long source = std::stoll(sourceId);
                long long dest = std::stoll(destId);
                double weightVal = std::stod(weight);

                graph.addEdge(static_cast<int>(source), static_cast<int>(dest), weightVal);  // Ajouter les arêtes
            } else {
                std::cerr << "Ligne mal formattée (arêtes manquantes) : " << line << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Erreur de conversion : " << e.what() << " dans la ligne : " << line << std::endl;
        }
    }
}



// Utilisation de la fonction pour lire les arêtes selon le fichier
void CSVReader::readEdges(Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ignorer les lignes vides ou les commentaires
        if (line.empty() || line[0] == '#') {
            continue;  // Ignorer les lignes vides ou les commentaires
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Séparer la ligne en tokens
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Vérifier que c'est une arête et qu'il y a au moins 4 champs
        if (tokens.size() >= 4 && tokens[0] == "E") {
            try {
                std::string sourceStr = tokens[1];
                std::string destStr = tokens[2];
                std::string weightStr = tokens[3];

                // Convertir les chaînes en nombres
                long long sourceId = std::stoll(sourceStr);
                long long destId = std::stoll(destStr);
                double weight = std::stod(weightStr);

                // Ajouter les sommets s'ils n'existent pas
                if (!graph.hasVertex(sourceId)) {
                    graph.addVertex(Vertex(sourceId, 0.0, 0.0));
                }
                if (!graph.hasVertex(destId)) {
                    graph.addVertex(Vertex(destId, 0.0, 0.0));
                }

                // Ajouter l'arête
                graph.addEdge(sourceId, destId, weight);
            } catch (const std::exception& e) {
                std::cerr << "Erreur de conversion : " << e.what() << " dans la ligne : " << line << std::endl;
            }
        }
    }

    file.close();
}

