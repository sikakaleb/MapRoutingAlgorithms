//
// Created by caleb on 24/10/2024.
//

#include "Vertex.h"
#include "MercatorProjection.h"

Vertex::Vertex(int id, double lon, double lat)
    : vertexId(id), longitude(lon), latitude(lat), x(0.0), y(0.0) {}

void Vertex::toCartesian(const MercatorProjection& projection) {
    projection.toCartesian(longitude, latitude, x, y);
}

