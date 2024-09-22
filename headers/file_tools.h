#ifndef CLASS_FILE_TOOLS
#define CLASS_FILE_TOOLS

#include <string>
#include <vector>

class FileTools{
    private:

    public:
        void writeFile(const std::string& filename, const std::vector<unsigned char>& data);
        bool fileExists(const std::string& filename);
        std::vector<unsigned char> readFile(const std::string& filename);
        std::string listFilesInDirectory(const std::string& directory);
};

#endif