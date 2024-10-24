def convert_konect_to_csv(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
        writer = csv.writer(outfile)
        for line in infile:
            if not line.startswith("%"):  # Ignorer les commentaires
                row = line.split()
                writer.writerow([int(row[0]), int(row[1]), 1])  # Poids par défaut à 1

convert_konect_to_csv('../data/txt/ego-facebook.net', '../data/csv/konect_ego_facebook.csv')
