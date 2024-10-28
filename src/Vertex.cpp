//
// Created by caleb on 24/10/2024.
//

#include "Vertex.h"
#include "MercatorProjection.h"


void Vertex::toCartesian(const MercatorProjection& projection) {
    projection.toCartesian(longitude, latitude, x, y);
}

