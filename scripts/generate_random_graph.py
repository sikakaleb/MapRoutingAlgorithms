import networkx as nx
import random
import csv

# Générer un graphe aléatoire avec un nombre de sommets et d'arêtes
def generate_random_graph(num_nodes, num_edges):
    G = nx.gnm_random_graph(num_nodes, num_edges, directed=True)
    for (u, v) in G.edges():
        G[u][v]['weight'] = random.uniform(1, 10)  # Poids aléatoires entre 1 et 10
    return G

# Sauvegarder le graphe en format CSV
def save_graph_to_csv(G, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for u, v, data in G.edges(data=True):
            writer.writerow([u, v, data['weight']])

# Générer un graphe aléatoire avec 1000 sommets et 5000 arêtes
G = generate_random_graph(1000, 5000)
save_graph_to_csv(G, '../data/csv/random_graph.csv')
