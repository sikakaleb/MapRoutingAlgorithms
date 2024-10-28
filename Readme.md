
## Introduction

### Présentation générale du projet
Le projet **Map Path Finder** se concentre sur l'exploration d'algorithmes de graphes, en mettant particulièrement l'accent sur les algorithmes de plus court chemin. Ces algorithmes sont cruciaux dans de nombreuses applications, notamment dans la navigation automobile, les applications de localisation (comme Google Maps), et plus généralement, pour déterminer le meilleur itinéraire entre deux points donnés.

### Objectif et fonctionnalités principales
L'objectif principal est de fournir une implémentation fonctionnelle de plusieurs algorithmes de graphes (BFS, Dijkstra, A*), permettant ainsi de calculer le chemin optimal entre deux sommets sur un graphe représentant une carte routière. Le projet comprend deux parties distinctes :  
1. **Non-graphique** (sections 1 à 5) : l'accent est mis sur l'implémentation des algorithmes de recherche de chemin. 
2. **Graphique** (section 6) : intégration d'une interface utilisateur pour afficher le graphe et le chemin trouvé sur une carte, avec la possibilité de sélectionner des points de départ et d'arrivée, ainsi que l'algorithme de recherche.

Voici la section **Prérequis** du README pour détailler les dépendances et les étapes d'installation :


## Prérequis

### Liste des dépendances logicielles
Pour exécuter et développer le projet **Map Path Finder**, les bibliothèques et outils suivants sont nécessaires :

- **CMake** : pour la gestion de la construction du projet.
- **Google Test** : pour l'exécution des tests unitaires, permettant de vérifier les performances et la robustesse des algorithmes.
- **Qt** : pour la création de l'interface graphique (si l’interface graphique est incluse).
- **Proj (PROJ.4)** : bibliothèque de conversion de coordonnées géographiques pour la gestion des projections cartographiques.
- **Compilateur C++17** : compatible avec la version C++17 pour compiler les sources (par exemple, GCC ou Clang).

### Instructions pour installer les dépendances

#### Sous Windows
1. **Installer CMake** :
   - Téléchargez la version de CMake depuis le site officiel [CMake](https://cmake.org/download/).
   - Ajoutez CMake au PATH pendant l’installation pour pouvoir l’utiliser depuis le terminal.

2. **Installer Google Test** :
   - Clonez le dépôt [Google Test](https://github.com/google/googletest).
   - Compilez et installez en suivant les instructions dans le README de Google Test ou via CMake.

3. **Installer Qt** :
   - Téléchargez et installez Qt depuis [Qt.io](https://www.qt.io/download).
   - Assurez-vous que le compilateur est compatible avec Qt Creator si vous utilisez l'interface graphique.

4. **Installer Proj** :
   - Téléchargez le package Windows pour [PROJ](https://proj.org/download.html).
   - Configurez la variable d’environnement PROJ_LIB pour le bon fonctionnement.

#### Sous Linux
1. **Installer CMake et le compilateur C++** :
   ```bash
   sudo apt update
   sudo apt install cmake build-essential
   ```

2. **Installer Google Test** :
   ```bash
   sudo apt install libgtest-dev
   cd /usr/src/gtest
   sudo cmake .
   sudo make
   sudo cp *.a /usr/lib
   ```

3. **Installer Qt** :
   - Utilisez le gestionnaire de paquets ou téléchargez depuis [Qt.io](https://www.qt.io/download).

4. **Installer Proj** :
   ```bash
   sudo apt install proj-bin libproj-dev
   ```

#### Sous macOS
1. **Installer Homebrew** (si ce n’est pas déjà fait) :
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Installer les dépendances** :
   ```bash
   brew install cmake proj qt googletest
   ```

Vérifiez que toutes les installations sont configurées dans le PATH du système et sont accessibles en ligne de commande pour un fonctionnement optimal du projet.

## Installation

### Étape 1 : Cloner le dépôt

Clonez le dépôt Git pour récupérer tous les fichiers sources et les ressources nécessaires :
```bash
git clone https://github.com/sikakaleb/MapRoutingAlgorithms.git
cd MapRoutingAlgorithms
```

### Étape 2 : Compilation et construction avec CMake

Il est recommandé d'effectuer la construction du projet dans un dossier séparé pour une organisation optimale des fichiers de compilation. Suivez les étapes suivantes :

1. **Créer un dossier de construction** :
   ```bash
   mkdir build
   cd build
   ```

2. **Générer les fichiers de construction avec CMake** :
   ```bash
   cmake ..
   ```

3. **Compiler le projet** :
   ```bash
   cmake --build .
   ```

4. **Accéder au dossier de compilation (`cmake-build-debug` ou `cmake-build-release`)** :
   ```bash
   cd cmake-build-debug  # ou cd cmake-build-release si vous avez compilé en mode Release
   ```

### Étape 3 : Exécution du projet

Les exécutables générés se trouvent dans le dossier `cmake-build-debug` (ou `cmake-build-release`). Vous pouvez exécuter le programme avec les commandes suivantes :

#### Exécution de `graph_traversal`

1. Pour exécuter l'algorithme de recherche de chemin avec des options spécifiques :
   ```bash
   ./graph_traversal --start 86771 --end 110636 --algorithm bfs --file ../data/csv/graph_dc_area.2022-03-11.csv
   ```

2. Pour tester avec d'autres configurations :
   ```bash
   ./MapRoutingAlgorithms --start 100 --end 200 --algorithm astar --file ../data/csv/graph_dc_area.2022-03-11.csv
   ```

**Remarque :** Aucun dossier ou fichier de configuration supplémentaire n'est nécessaire pour lancer les commandes ci-dessus.


Cela inclut les étapes pour accéder aux dossiers `cmake-build-debug` ou `cmake-build-release` pour l'exécution.

**Remarque :** Aucun dossier ou fichier de configuration supplémentaire n'est nécessaire pour lancer les commandes ci-dessus.



### Structure du Projet

Le projet est organisé en plusieurs dossiers pour structurer les sources, les dépendances, les scripts, et les données de manière ordonnée :

```plaintext
MapRoutingAlgorithms/
├── CMakeLists.txt                  # Fichier de configuration CMake pour la construction du projet
├── README.md                       # Documentation principale du projet
├── data/                           # Contient les fichiers de données pour les tests et les graphes
│   └── csv/                        # Sous-dossier contenant les fichiers CSV pour les graphes de test
│       ├── berlin_osm_graph.csv    # Graphe de la ville de Berlin extrait d'OSM
│       └── graph_dc_area.csv       # Exemple de graphe basé sur des données géographiques
├── include/                        # Dossier contenant les fichiers d'en-tête (headers)
│   ├── Graph.h                     # Déclaration de la classe Graph et ses méthodes
│   ├── Vertex.h                    # Déclaration de la classe Vertex représentant un sommet
│   ├── Edge.h                      # Déclaration de la classe Edge pour les arêtes du graphe
│   ├── MercatorProjection.h        # Déclaration de la classe pour la projection Mercator
│   └── CSVReader.h                 # Déclaration de la classe CSVReader pour lire les données CSV
├── src/                            # Dossier contenant les fichiers source principaux
│   ├── main.cpp                    # Point d'entrée du programme principal
│   ├── Graph.cpp                   # Implémentation des méthodes de la classe Graph
│   ├── Vertex.cpp                  # Implémentation de la classe Vertex
│   ├── Edge.cpp                    # Implémentation de la classe Edge
│   ├── MercatorProjection.cpp      # Implémentation de la projection Mercator
│   └── CSVReader.cpp               # Implémentation de la lecture de fichiers CSV
├── scripts/                        # Dossier contenant les scripts Python pour l'évaluation croisée et la génération de données
│   ├── compare_paths.py            # Comparaison des chemins entre les résultats de `networkx` et notre implémentation
│   ├── generate_random_graph.py    # Génération de graphes aléatoires pour les tests
│   ├── graph_traversal.py          # Script de parcours de graphe avec BFS, Dijkstra et A*
│   ├── konect_to_csv.py            # Convertisseur de données KONECT vers CSV pour les utiliser dans le projet
│   ├── mercator_projection.py      # Validation des calculs de projection Mercator
│   ├── osm_to_csv.py               # Extraction et sauvegarde d'un graphe OpenStreetMap en CSV
│   └── snap_to_csv.py              # Alignement des points géographiques sur les arêtes du graphe
├── tests/                          # Contient les tests unitaires
│   ├── testPerformance.cpp         # Tests de performance pour mesurer le temps d'exécution des algorithmes
│   ├── testGraph.cpp               # Tests unitaires pour la structure du graphe
│   └── CMakeLists.txt              # Configuration CMake pour compiler les tests
└── cmake/                          # Dossier pour les configurations de CMake et les modules
    └── modules/                    # Modules additionnels pour la gestion de dépendances
```

---

#### Détails des principaux dossiers et fichiers

- **data/csv/** : Contient les fichiers CSV de graphes utilisés pour les tests. Par exemple, `berlin_osm_graph.csv` est un graphe généré depuis les données OpenStreetMap de Berlin, et `graph_dc_area.csv` est un graphe basé sur une zone géographique donnée.
  
- **include/** : Les fichiers d'en-tête du projet, notamment :
  - `Graph.h` : Définit la classe `Graph`, utilisée pour gérer les sommets, arêtes, et algorithmes de parcours.
  - `Vertex.h` et `Edge.h` : Représentent respectivement les sommets et arêtes du graphe.
  - `MercatorProjection.h` : Gère la conversion de coordonnées géographiques avec la projection Mercator.
  - `CSVReader.h` : Classe pour lire et traiter les fichiers CSV contenant les données de graphes.
  
- **src/** : Contient le code source des principales fonctionnalités du projet, avec les implémentations de `Graph`, `Vertex`, `Edge`, et `MercatorProjection`.

- **scripts/** : Regroupe des scripts Python pour des tâches d'évaluation et de manipulation de données. Ces scripts incluent :
  - `compare_paths.py` : Compare les chemins trouvés par les algorithmes internes et `networkx`.
  - `generate_random_graph.py` : Génère des graphes aléatoires pour les tests de performance.
  - `graph_traversal.py` : Exécute des parcours de graphe (BFS, Dijkstra, A*) en utilisant un fichier CSV en entrée.
  - `mercator_projection.py` : Vérifie la précision des calculs de projection Mercator.
  - `osm_to_csv.py` : Crée un fichier CSV de graphe à partir d'une zone d'OpenStreetMap.
  - `snap_to_csv.py` : Aligne les points géographiques sur les arêtes pour une meilleure précision dans les calculs.

- **tests/** : Contient les tests unitaires du projet, vérifiant la performance et l'intégrité des algorithmes de parcours et de gestion de graphe.

### Utilisation

Cette section vous guidera pour exécuter l'application en ligne de commande et tester les différents algorithmes de recherche (BFS, Dijkstra, A*) sur des graphes fournis.

---

#### Instructions pour exécuter l'application

L'exécutable principal, `graph_traversal`, permet de tester les parcours de graphe en utilisant plusieurs algorithmes. Avant de l'exécuter, assurez-vous d'avoir compilé le projet dans le bon répertoire (comme expliqué dans la section *Installation*).

Pour lancer l'application, vous devrez spécifier plusieurs options en ligne de commande, notamment les sommets de départ et d'arrivée, l'algorithme choisi, et le fichier de données du graphe.

---

#### Guide des options de ligne de commande

L'application `graph_traversal` prend en charge les options suivantes :

```bash
./graph_traversal --start <startId> --end <endId> --algorithm <bfs|dijkstra|astar> --file <path_to_graph_file>
```

- **`--start <startId>`** : ID du sommet de départ pour le parcours.
- **`--end <endId>`** : ID du sommet de destination.
- **`--algorithm <bfs|dijkstra|astar>`** : Algorithme de recherche à utiliser.
  - `bfs` : Parcours en largeur (Breadth-First Search).
  - `dijkstra` : Algorithme de Dijkstra pour le chemin le plus court basé sur les poids des arêtes.
  - `astar` : Algorithme A* pour le chemin le plus court en utilisant une heuristique basée sur la distance euclidienne.
- **`--file <path_to_graph_file>`** : Chemin vers le fichier CSV contenant les données du graphe.

---

#### Exemples de commandes pour lancer des cas de test

1. **Exécuter un parcours en largeur (BFS)** :
    ```bash
    ./graph_traversal --start 86771 --end 110636 --algorithm bfs --file ../data/csv/graph_dc_area.csv
    ```
    Cette commande exécute BFS de l'ID de sommet `86771` à l'ID `110636` en utilisant le fichier `graph_dc_area.csv`.

2. **Exécuter l'algorithme de Dijkstra** :
    ```bash
    ./graph_traversal --start 100 --end 200 --algorithm dijkstra --file ../data/csv/berlin_osm_graph.csv
    ```
    Ici, Dijkstra est utilisé pour trouver le chemin le plus court entre `100` et `200` dans le graphe `berlin_osm_graph.csv`.

3. **Exécuter l'algorithme A*** :
    ```bash
    ./graph_traversal --start 300 --end 400 --algorithm astar --file ../data/csv/graph_dc_area.csv
    ```
    L'algorithme A* est utilisé entre les sommets `300` et `400` dans le graphe `graph_dc_area.csv`.

---

Chaque exécution de commande affichera le nombre total de sommets visités, le nombre total de sommets sur le chemin trouvé, et le chemin complet du départ à la destination avec les distances cumulées à chaque étape.

### Tests

Le projet inclut des tests unitaires, réalisés avec la bibliothèque **Google Test**, pour garantir le bon fonctionnement et les performances des différents algorithmes de recherche de chemins (BFS, Dijkstra, A*). Les tests sont divisés en plusieurs catégories :

---

#### Tests unitaires (test_performance.cpp)

Les tests unitaires vérifient la performance des algorithmes en utilisant un graphe réel. Les tests mesurent le temps d'exécution pour différents chemins entre des sommets aléatoires, et s'assurent que le temps d'exécution ne dépasse pas 1 seconde. Si un chemin est trouvé et que l'exécution dépasse cette limite, le test échoue.

Commandes pour lancer les tests unitaires :

```bash
# Depuis le dossier de build, exécuter les tests
./test_performance
```

---

#### Tests de performance sur un graphe généré aléatoirement (test_performance_random_graphe.cpp)

Ce test génère un graphe aléatoire avec un nombre important de sommets et d'arêtes, puis effectue jusqu'à **10 000** combinaisons de tests entre des points de départ et d'arrivée choisis aléatoirement. Les graphes générés ont une profondeur de 100 à 3000 sommets, et les temps d'exécution sont mesurés pour chaque parcours. Ces tests garantissent qu'aucune exécution de chemin trouvé ne dépasse 1 seconde, et qu'en moyenne, le temps d'exécution des algorithmes est inférieur à **50 ms**.

Commandes pour lancer les tests de performance sur graphe aléatoire :

```bash
# Depuis le dossier de build, exécuter les tests
./test_performance_random_graphe
```

---

### Contenu des fichiers de test

- **test_performance.cpp** : Contient les tests de performance sur des graphes réels, utilisant un graphe de données stocké dans un fichier CSV. Les tests mesurent le temps d'exécution de chaque algorithme sur des milliers de paires de sommets dans le graphe.
  
- **test_performance_random_graphe.cpp** : Génère un graphe aléatoire pour chaque test et effectue les parcours en utilisant BFS, Dijkstra et A*. Cela permet d’évaluer la robustesse des algorithmes dans des conditions variées.

Les deux fichiers de test sont conçus pour vérifier que les algorithmes fonctionnent rapidement même sur des graphes de grande taille.


### Performance et Optimisation

#### Résultats attendus des tests de performance

Les tests de performance montrent que les algorithmes implémentés (BFS, Dijkstra, A*) fonctionnent efficacement sur des graphes de grande taille. Voici les résultats attendus :

1. **Temps d'exécution** : 
   - Tous les algorithmes sont conçus pour s'exécuter en moins d'une seconde sur des graphes de profondeur allant jusqu'à **3000 sommets**, avec un nombre d'arêtes proportionnel (jusqu'à 30 000 arêtes dans les tests).
   - En moyenne, pour les tests unitaires utilisant des paires aléatoires de points de départ et d'arrivée, le temps d'exécution des algorithmes devrait être inférieur à **50 ms**.

2. **Utilisation de la mémoire** :
   - L'algorithme A* nécessite plus de mémoire que BFS et Dijkstra, en raison du stockage des scores heuristiques pour chaque nœud. Cependant, son utilisation de la mémoire reste gérable pour des graphes de grande taille, grâce à des optimisations dans la gestion de la file de priorité.

3. **Scalabilité** :
   - Les tests montrent que l’algorithme A* est généralement plus rapide que Dijkstra lorsqu'une heuristique efficace est disponible, notamment pour les graphes avec des relations géographiques où la distance euclidienne est un bon estimateur.
   - BFS est plus rapide pour les graphes peu pondérés ou non pondérés, où l’optimisation par heuristique n’apporte pas d’avantages significatifs.

#### Conseils et paramètres pour améliorer l’efficacité

1. **Utiliser une heuristique efficace avec A*** :
   - La performance de l’algorithme A* dépend fortement de la qualité de l’heuristique. Une bonne heuristique, comme la **distance euclidienne** dans des graphes géographiques, peut réduire le nombre de nœuds explorés et ainsi améliorer l’efficacité.
   - Évitez les heuristiques trop faibles ou surestimées, car elles peuvent ralentir A* ou donner des chemins sous-optimaux.

2. **Adapter la structure des données pour des graphes très denses** :
   - Pour les graphes très denses, il peut être bénéfique d'utiliser des structures de données optimisées comme des **tas binomiaux** ou des **files de priorité avec d-ary heap** pour optimiser les opérations de mise à jour des coûts dans Dijkstra et A*.
   
3. **Limiter la profondeur de recherche dans BFS** :
   - Si le graphe est très vaste mais que le chemin recherché est local, limiter la profondeur maximale de BFS peut réduire les temps d'exécution.

4. **Optimiser les paramètres de construction du graphe** :
   - Si les graphes sont générés dynamiquement (comme dans les tests aléatoires), utilisez des tailles et des poids d'arête proportionnels à l'application cible. Par exemple, pour un réseau routier, limiter le nombre d'arêtes par sommet en fonction des connexions réalistes améliore la précision et les performances.

5. **Utiliser un compilateur optimisé et ajuster les options de compilation** :
   - Compiler avec des options d'optimisation (e.g., `-O2` ou `-O3` avec GCC/Clang) permet d'améliorer l'efficacité sans modification du code source.
   - Activer des flags de profilage et de vectorisation, en fonction de la machine cible, pour tirer parti des optimisations spécifiques au matériel.

En suivant ces recommandations, vous pouvez maximiser la performance des algorithmes de recherche dans des contextes variés, en assurant des temps de réponse rapides même sur des graphes de grande taille.
