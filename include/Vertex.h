//
// Created by caleb on 24/10/2024.
//

// Vertex.h
#ifndef VERTEX_H
#define VERTEX_H

class MercatorProjection;  // Déclaration anticipée

class Vertex {
public:
    int vertexId;
    double longitude;
    double latitude;
    double x;  // Coordonnée cartésienne X
    double y;  // Coordonnée cartésienne Y

    // Constructeur par défaut
    Vertex() : vertexId(0), longitude(0.0), latitude(0.0), x(0.0), y(0.0) {}

    // Constructeur avec paramètres
    Vertex(int id, double lon, double lat)
        : vertexId(id), longitude(lon), latitude(lat), x(0.0), y(0.0) {}

    // Méthode pour convertir les coordonnées géographiques en coordonnées cartésiennes
    void toCartesian(const MercatorProjection& projection);
};


#endif // VERTEX_H


