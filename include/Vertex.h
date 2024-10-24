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

    // Constructeur
    Vertex(int id, double lon, double lat);

    // Méthode pour convertir les coordonnées géographiques en coordonnées cartésiennes
    void toCartesian(const MercatorProjection& projection);

};

#endif // VERTEX_H


