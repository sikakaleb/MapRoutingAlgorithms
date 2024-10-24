//
// Created by caleb on 24/10/2024.
//

#ifndef MERCATORPROJECTION_H
#define MERCATORPROJECTION_H

class MercatorProjection {
public:
    explicit MercatorProjection(double centerLon = 0.0);  // Par défaut, centre sur le méridien de Greenwich

    // Convertir longitude et latitude (en degrés) en coordonnées cartésiennes x, y (en mètres)
    void toCartesian(double lon, double lat, double& x, double& y) const;

private:
    double lambda_0;  // Longitude du méridien central en radians
    const double R = 6378137.0;  // Rayon équatorial de la Terre en mètres (WGS84)
    const double MAX_LAT = 85.05112878;  // Latitude maximale en degrés pour Mercator
};

#endif // MERCATORPROJECTION_H
