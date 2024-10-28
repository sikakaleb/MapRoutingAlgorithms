//
// Created by caleb on 25/10/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <array>
#include <memory>
#include <stdexcept>

// Utiliser inline pour éviter les multiples définitions
inline std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("Erreur lors de l'exécution du script Python");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

#endif // UTILS_H
