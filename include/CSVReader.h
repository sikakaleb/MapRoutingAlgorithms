//
// Created by caleb on 24/10/2024.
//

// CSVReader.h
#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include "Vertex.h"

class CSVReader {
public:
    explicit CSVReader(const std::string& filename);
    std::vector<Vertex> readVertices();

private:
    std::string filename;
};

#endif // CSVREADER_H
