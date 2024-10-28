import osmnx as ox
import networkx as nx
import csv

# Extraire le graphe de la ville de Berlin
G = ox.graph_from_place('Berlin, Germany', network_type='drive')

# Sauvegarder le graphe en format CSV
def save_graph_to_csv(G, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for u, v, data in G.edges(data=True):
            writer.writerow([u, v, data.get('length', 1)])  # Utiliser la longueur des routes comme poids

save_graph_to_csv(G, '../data/csv/berlin_osm_graph.csv')
