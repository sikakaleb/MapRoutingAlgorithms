import networkx as nx
import csv
import sys

def load_graph_from_csv(filename):
    G = nx.DiGraph()
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            source = int(row[0])
            target = int(row[1])
            weight = float(row[2])
            G.add_edge(source, target, weight=weight)
    return G

def compare_paths(graph_file, source, target):
    G = load_graph_from_csv(graph_file)

    # Exécuter A* avec NetworkX
    a_star_path = nx.astar_path(G, source, target, heuristic=lambda u, v: 0)
    a_star_cost = nx.astar_path_length(G, source, target, heuristic=lambda u, v: 0)

    # Exécuter Dijkstra avec NetworkX
    dijkstra_path = nx.dijkstra_path(G, source, target)
    dijkstra_cost = nx.dijkstra_path_length(G, source, target)

    return a_star_path, a_star_cost, dijkstra_path, dijkstra_cost

if __name__ == "__main__":
    graph_file = sys.argv[1]
    source = int(sys.argv[2])
    target = int(sys.argv[3])

    a_star_path, a_star_cost, dijkstra_path, dijkstra_cost = compare_paths(graph_file, source, target)
    print("A* Path:", a_star_path)
    print("A* Cost:", a_star_cost)
    print("Dijkstra Path:", dijkstra_path)
    print("Dijkstra Cost:", dijkstra_cost)
