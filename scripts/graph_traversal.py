import argparse
import networkx as nx

def read_graph(filename):
    G = nx.DiGraph()  # Graphe orienté
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line or line.startswith('#'):
                continue  # Ignorer les lignes vides ou les commentaires
            tokens = line.split(',')
            if tokens[0] == 'V' and len(tokens) >= 4:
                try:
                    vertex_id = int(tokens[1])
                    longitude = float(tokens[2])
                    latitude = float(tokens[3])
                    G.add_node(vertex_id, longitude=longitude, latitude=latitude)
                except ValueError:
                    print(f"Erreur de conversion dans la ligne : {line}")
            elif tokens[0] == 'E' and len(tokens) >= 4:
                try:
                    source = int(tokens[1])
                    dest = int(tokens[2])
                    weight = float(tokens[3])
                    G.add_edge(source, dest, weight=weight)
                except ValueError:
                    print(f"Erreur de conversion dans la ligne : {line}")
    return G

def bfs(G, start, end):
    try:
        path = nx.shortest_path(G, source=start, target=end)
        visited = len(G.nodes)
        return path, visited
    except nx.NetworkXNoPath:
        print("Aucun chemin trouvé avec BFS.")
        return [], 0

def dijkstra(G, start, end):
    try:
        path = nx.dijkstra_path(G, source=start, target=end, weight='weight')
        visited = len(G.nodes)
        return path, visited
    except nx.NetworkXNoPath:
        print("Aucun chemin trouvé avec Dijkstra.")
        return [], 0

def astar(G, start, end):
    try:
        # Fonction heuristique : distance euclidienne
        def heuristic(u, v):
            u_data = G.nodes[u]
            v_data = G.nodes[v]
            dx = u_data['longitude'] - v_data['longitude']
            dy = u_data['latitude'] - v_data['latitude']
            return (dx * dx + dy * dy) ** 0.5

        path = nx.astar_path(G, source=start, target=end, heuristic=heuristic, weight='weight')
        visited = len(G.nodes)
        return path, visited
    except nx.NetworkXNoPath:
        print("Aucun chemin trouvé avec A*.")
        return [], 0

def main():
    parser = argparse.ArgumentParser(description='Graph traversal')
    parser.add_argument('--start', type=int, required=True, help='ID du sommet de départ')
    parser.add_argument('--end', type=int, required=True, help='ID du sommet d\'arrivée')
    parser.add_argument('--algorithm', type=str, choices=['bfs', 'dijkstra', 'astar'], required=True, help='Algorithme à utiliser')
    parser.add_argument('--file', type=str, required=True, help='Fichier de graphe')

    args = parser.parse_args()

    G = read_graph(args.file)

    if not G.has_node(args.start) or not G.has_node(args.end):
        print("Le sommet de départ ou d'arrivée n'existe pas dans le graphe.")
        return

    if args.algorithm == 'bfs':
        path, visited = bfs(G, args.start, args.end)
    elif args.algorithm == 'dijkstra':
        path, visited = dijkstra(G, args.start, args.end)
    elif args.algorithm == 'astar':
        path, visited = astar(G, args.start, args.end)
    else:
        print(f"Algorithme inconnu : {args.algorithm}")
        return

    if not path:
        print("Aucun chemin trouvé.")
        return

    # Calcul de la longueur totale
    total_length = 0.0
    for i in range(len(path) - 1):
        edge_data = G.get_edge_data(path[i], path[i+1])
        if edge_data and 'weight' in edge_data:
            total_length += edge_data['weight']

    print(f"Total visited vertex = {visited}")
    print(f"Total vertex on path from start to end = {len(path)}")
    for idx, node in enumerate(path):
        length_so_far = 0.0
        for i in range(idx):
            edge_data = G.get_edge_data(path[i], path[i+1])
            if edge_data and 'weight' in edge_data:
                length_so_far += edge_data['weight']
        print(f"Vertex[{idx+1:4}] = {node:8}, length = {length_so_far:10.2f}")

if __name__ == "__main__":
    main()
