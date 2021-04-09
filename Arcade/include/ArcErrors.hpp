/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** ArcErrors
*/

#ifndef ARCERRORS_HPP_
#define ARCERRORS_HPP_

#include <stdexcept>
#include "Errors.hpp"

namespace arcade
{
    namespace errors
    {    
        class LibError : public std::exception {
            public:
                LibError(const std::string &msg);
                LibError(const std::string &msg, const std::string &cause);
                ~LibError();

                const char *what() const noexcept override;

            protected:
            private:
                const std::string _msg;
        };
    } // namespace Errors
} // namespace arcade


#endif /* !ARCERRORS_HPP_ */
