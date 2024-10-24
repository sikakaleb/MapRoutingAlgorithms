#include "gtest/gtest.h"
#include "Graph.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <array>

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("Erreur lors de l'exécution du script Python");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

TEST(CrossValidationTest, CompareWithNetworkX) {
    Graph graph;
    graph.addVertex(Vertex(1, -76.929192819, 38.8924826094));
    graph.addVertex(Vertex(2, -76.9296620544, 38.8925491793));
    graph.addVertex(Vertex(3, -76.981166842, 38.9025611176));
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(2, 3, 5.0);
    graph.addEdge(1, 3, 2.0);

    std::vector<int> aStarPath = graph.a_star(1, 3);
    std::vector<int> dijkstraPath = graph.dijkstra(1, 3);

    std::string cmd = "python ../scripts/compare_paths.py ../data/csv/graph_dc_area.2022-03-11.csv 1 3";
    std::string output = exec(cmd);

    std::istringstream iss(output);
    std::string line;
    while (getline(iss, line)) {
        std::cout << line << std::endl;
    }
}
