/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <memory>
#include <dlfcn.h>

class DLLoader {
    public:
        DLLoader(const std::string &path, int mode = (RTLD_NOW | RTLD_NODELETE))
        {
            load(path, mode);
        };
        DLLoader() {};
        ~DLLoader() { close(); }

        bool didLoad() const { return _handler != NULL; };

        bool load(const std::string &path, int mode = (RTLD_NOW | RTLD_NODELETE))
        {
            close();
            _handler = dlopen(path.c_str(), mode);
            return didLoad();
        };

        std::string getErrorMsg() const
        {
            return dlerror();
        }

        bool close()
        {
            if (!_handler) {
                return true;
            }
            bool res = dlclose(_handler) == 0;
            _handler = NULL;
            return res;
        };

        template<typename S>
        S *getSym(const std::string &name) const
        {
            if (!_handler) {
                return nullptr;
            }
            return reinterpret_cast<S *>(dlsym(_handler, name.c_str()));
        }

        template<typename F>
        F getFunc(const std::string &name) const
        {
            if (!_handler) {
                return nullptr;
            }
            return reinterpret_cast<F>(dlsym(_handler, name.c_str()));
        }

    protected:
    private:
        std::string _libName;
        void *_handler = NULL;
};

#endif /* !DLLOADER_HPP_ */
