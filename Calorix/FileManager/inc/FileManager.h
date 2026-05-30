#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class Calorix;

class FileManager
{
public:
    static void save(const Calorix& system, const std::string& filename);
    static void load(Calorix& system, const std::string& filename);
};

#endif // FILE_MANAGER_H
