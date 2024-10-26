# main.py
import sys
import argparse
import csv
from pyproj import CRS, Transformer
import networkx as nx

def read_vertices(filename):
    vertices = {}
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            # Ignorer les lignes vides ou les commentaires
            if not row or row[0].startswith('#'):
                continue
            if row[0] == 'V' and len(row) >= 4:
                try:
                    vertex_id = int(row[1])
                    longitude = float(row[2])
                    latitude = float(row[3])
                    vertices[vertex_id] = {'longitude': longitude, 'latitude': latitude}
                except ValueError as e:
                    print(f"Erreur de conversion dans la ligne: {row}, erreur: {e}")
    return vertices

def read_edges(filename):
    edges = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            # Ignorer les lignes vides ou les commentaires
            if not row or row[0].startswith('#'):
                continue
            if row[0] == 'E' and len(row) >= 4:
                try:
                    source_id = int(row[1])
                    dest_id = int(row[2])
                    weight = float(row[3])
                    edges.append((source_id, dest_id, weight))
                except ValueError as e:
                    print(f"Erreur de conversion dans la ligne: {row}, erreur: {e}")
    return edges

def convert_coordinates(vertices):
    # Utilisation de la projection Mercator EPSG:3857 (WGS84)
    crs_wgs84 = CRS.from_epsg(4326)  # Système géodésique WGS84
    crs_mercator = CRS.from_epsg(3857)  # Projection Mercator EPSG:3857
    transformer = Transformer.from_crs(crs_wgs84, crs_mercator, always_xy=True)
    for vertex_id, data in vertices.items():
        x, y = transformer.transform(data['longitude'], data['latitude'])
        data['x'] = x
        data['y'] = y
    return vertices

def build_graph(vertices, edges):
    G = nx.DiGraph()
    # Ajouter les sommets
    for vertex_id, data in vertices.items():
        G.add_node(vertex_id, **data)
    # Ajouter les arêtes
    for source_id, dest_id, weight in edges:
        G.add_edge(source_id, dest_id, weight=weight)
    return G

def run_algorithm(G, start_id, end_id, algorithm):
    if algorithm == 'bfs':
        try:
            # BFS ne prend pas en compte les poids, donc on peut utiliser shortest_path
            path = nx.shortest_path(G, source=start_id, target=end_id)
            visited_nodes = len(path)
            total_length = sum(G[u][v].get('weight', 1) for u, v in zip(path[:-1], path[1:]))
        except nx.NetworkXNoPath:
            print(f"Aucun chemin trouvé entre {start_id} et {end_id} avec BFS.")
            return None
    elif algorithm == 'dijkstra':
        try:
            path = nx.dijkstra_path(G, source=start_id, target=end_id, weight='weight')
            visited_nodes = len(G.nodes)
            total_length = nx.dijkstra_path_length(G, source=start_id, target=end_id, weight='weight')
        except nx.NetworkXNoPath:
            print(f"Aucun chemin trouvé entre {start_id} et {end_id} avec Dijkstra.")
            return None
    elif algorithm == 'astar':
        try:
            # Heuristique utilisant la distance euclidienne entre les sommets
            def heuristic(u, v):
                x1, y1 = G.nodes[u]['x'], G.nodes[u]['y']
                x2, y2 = G.nodes[v]['x'], G.nodes[v]['y']
                return ((x1 - x2)**2 + (y1 - y2)**2)**0.5
            path = nx.astar_path(G, source=start_id, target=end_id, heuristic=heuristic, weight='weight')
            visited_nodes = len(G.nodes)
            total_length = nx.astar_path_length(G, source=start_id, target=end_id, heuristic=heuristic, weight='weight')
        except nx.NetworkXNoPath:
            print(f"Aucun chemin trouvé entre {start_id} et {end_id} avec A*.")
            return None
    else:
        print(f"Algorithme non reconnu: {algorithm}")
        return None

    return {
        'path': path,
        'visited_nodes': visited_nodes,
        'total_length': total_length
    }

def main():
    parser = argparse.ArgumentParser(description='Graph Traversal')
    parser.add_argument('--start', type=int, required=True, help='ID du sommet de départ')
    parser.add_argument('--end', type=int, required=True, help='ID du sommet d\'arrivée')
    parser.add_argument('--algorithm', type=str, required=True, choices=['bfs', 'dijkstra', 'astar'], help='Algorithme à utiliser')
    parser.add_argument('--file', type=str, required=True, help='Fichier contenant les données du graphe')

    args = parser.parse_args()

    # Lecture des données
    vertices = read_vertices(args.file)
    edges = read_edges(args.file)

    # Vérifier que les sommets de départ et d'arrivée existent
    if args.start not in vertices or args.end not in vertices:
        print(f"Le sommet de départ ({args.start}) ou d'arrivée ({args.end}) n'existe pas dans le graphe.")
        sys.exit(1)

    # Conversion des coordonnées
    vertices = convert_coordinates(vertices)

    # Construction du graphe
    G = build_graph(vertices, edges)

    # Exécution de l'algorithme
    result = run_algorithm(G, args.start, args.end, args.algorithm)

    if result is None:
        sys.exit(1)

    # Affichage des résultats
    print(f"Total visited vertex = {result['visited_nodes']}")
    print(f"Total vertex on path from start to end = {len(result['path'])}")
    total_length = 0.0
    for idx, node_id in enumerate(result['path'], start=1):
        print(f"Vertex[{idx:4}] = {node_id:8}, length = {total_length:10.2f}")
        if idx < len(result['path']):
            edge_weight = G[node_id][result['path'][idx]]['weight']
            total_length += edge_weight

if __name__ == '__main__':
    main()
