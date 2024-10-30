#include "../include/file_tools.h"
#include <fstream>
#include <filesystem>

// Fonction pour écrire un fichier en binaire
void FileTools::writeFile(const std::string& filename, const std::vector<unsigned char>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

bool FileTools::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

std::vector<unsigned char> FileTools::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Fonction pour obtenir la liste des fichiers dans un répertoire donné
std::string FileTools::listFilesInDirectory(const std::string& directory) {
    std::string fileList;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            fileList += entry.path().filename().string() + "\n";  // Add each file name to the list
        }
    }
    return fileList.empty() ? "No files found." : fileList;
}