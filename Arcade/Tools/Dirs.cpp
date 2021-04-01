/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Dirs
*/

#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <stdexcept>
#include "Tools.hpp"

std::vector<std::string> Tools::Dirs::lsDir(const std::string &dirPath, bool withPath)
{
    return lsDir(dirPath, "", withPath);
}

std::vector<std::string> Tools::Dirs::lsDir(const std::string &dirPath, const std::string &ext, bool withPath)
{
    std::vector<std::string> res;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirPath.c_str())) != NULL) {
        std::string path = dirPath[dirPath.size() - 1] == '/' ? dirPath : dirPath + '/';
        while ((ent = readdir(dir)) != NULL) {
            std::string name(ent->d_name);
            if (name != "." && name != "..") {
                res.push_back(withPath ? path + name : name);
            }
        }
        closedir (dir);
        std::sort(res.begin(), res.end());
        if (ext.size()) {
            res.erase(std::remove_if(res.begin(), res.end(),
                    [ext](const std::string &file) {
                        return !Tools::Strings::endsWith(file, ext);
                    }), res.end());
        }
    } else {
        throw std::runtime_error("Could not open the directory: [" + dirPath + "]");
    }
    return res;
}