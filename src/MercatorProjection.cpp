//
// Created by caleb on 24/10/2024.
//

#include "MercatorProjection.h"
#include <cmath>  // pour tan(), log(), cos()


// Constructeur pour initialiser la projection avec un méridien central donné
MercatorProjection::MercatorProjection(double centerLon)
    : lambda_0(centerLon * M_PI / 180.0) {}  // Convertir en radians

// Méthode pour convertir longitude et latitude en coordonnées cartésiennes
void MercatorProjection::toCartesian(double lon, double lat, double& x, double& y) const {
    // Limiter la latitude pour éviter les valeurs infinies
    if (lat > MAX_LAT) lat = MAX_LAT;
    if (lat < -MAX_LAT) lat = -MAX_LAT;

    // Convertir la longitude et la latitude en radians
    double lambda = lon * M_PI / 180.0;
    double phi = lat * M_PI / 180.0;

    // Calcul de x et y en utilisant les formules standard de Mercator
    x = R * (lambda - lambda_0);
    y = R * log(tan(M_PI / 4.0 + phi / 2.0));
}
