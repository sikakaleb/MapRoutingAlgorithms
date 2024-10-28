from pyproj import Proj, CRS
import sys

def to_cartesian(lon, lat):
    # Utilisation de la projection Mercator EPSG:3857 (WGS84) avec la nouvelle syntaxe
    crs = CRS.from_epsg(3857)
    p = Proj(crs)  # Créer une projection Mercator
    x, y = p(lon, lat)
    return x, y

if __name__ == "__main__":
    lon = float(sys.argv[1])
    lat = float(sys.argv[2])
    x, y = to_cartesian(lon, lat)
    print(f"{x},{y}")
