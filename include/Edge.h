//
// Created by caleb on 24/10/2024.
//

#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int sourceId;
    int destId;
    double weight;  // La distance ou le poids de l'arête

    Edge(int source, int dest, double weight)
        : sourceId(source), destId(dest), weight(weight) {}
};

#endif // EDGE_H
