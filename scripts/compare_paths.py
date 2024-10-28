import networkx as nx
import csv
import sys
from pyproj import Proj, CRS
import random

def detect_file_type(filename):
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if row[0] == 'V':
                return 'graph_dc_area'
            elif row[0].isdigit():
                return 'osm'
    return None

def load_graph_from_graph_dc_area(filename):
    G = nx.DiGraph()
    vertices = {}

    # Utiliser Mercator pour la conversion des coordonnées
    crs = CRS.from_epsg(3857)
    proj = Proj(crs)

    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if row[0] == 'V':  # Sommet
                vertex_id = int(row[1])
                longitude = float(row[2])
                latitude = float(row[3])
                # Conversion en coordonnées cartésiennes
                x, y = proj(longitude, latitude)
                vertices[vertex_id] = (x, y)
                G.add_node(vertex_id)  # Ajouter le sommet explicitement dans G
            elif row[0] == 'E':  # Arête
                source = int(row[1])
                target = int(row[2])
                weight = float(row[3])
                if source in vertices and target in vertices:
                    G.add_edge(source, target, weight=weight)
                else:
                    print(f"Sommets introuvables pour l'arête ({source}, {target})")

    return G, vertices


def load_graph_from_osm(filename):
    G = nx.DiGraph()
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            source = int(row[0])
            target = int(row[1])
            weight = float(row[2])
            G.add_edge(source, target, weight=weight)

    return G

def compare_paths(graph_file, source=None, target=None):
    file_type = detect_file_type(graph_file)

    if file_type == 'graph_dc_area':
        G, vertices = load_graph_from_graph_dc_area(graph_file)
        print("Loaded graph_dc_area with vertices:", len(vertices))
    elif file_type == 'osm':
        G = load_graph_from_osm(graph_file)
        print("Loaded OSM graph.")
    else:
        raise ValueError("Type de fichier inconnu")

    # Si source ou target n'est pas spécifié, choisir des sommets valides au hasard
    if source is None or target is None:
        source = random.choice(list(G.nodes))
        target = random.choice(list(G.nodes))
        while source == target:
            target = random.choice(list(G.nodes))

    #print("Sommets dans le graphe:", G.nodes())
    print(f"Source: {source}, Target: {target}")

    # Exécuter A* avec NetworkX
    a_star_path = nx.astar_path(G, source, target, heuristic=lambda u, v: 0)
    a_star_cost = nx.astar_path_length(G, source, target, heuristic=lambda u, v: 0)

    # Exécuter Dijkstra avec NetworkX
    dijkstra_path = nx.dijkstra_path(G, source, target)
    dijkstra_cost = nx.dijkstra_path_length(G, source, target)

    return a_star_path, a_star_cost, dijkstra_path, dijkstra_cost

if __name__ == "__main__":
    graph_file = sys.argv[1]
    if len(sys.argv) > 3:
        source = int(sys.argv[2])
        target = int(sys.argv[3])
    else:
        source = None
        target = None

    a_star_path, a_star_cost, dijkstra_path, dijkstra_cost = compare_paths(graph_file, source, target)
    print("A* Path:", a_star_path)
    print("A* Cost:", a_star_cost)
    print("Dijkstra Path:", dijkstra_path)
    print("Dijkstra Cost:", dijkstra_cost)
