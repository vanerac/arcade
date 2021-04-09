/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <string>

namespace arcade
{
    namespace errors
    {    
        class Error : public std::exception {
            public:
                Error(const std::string &msg);
                ~Error();

                const char *what() const noexcept override;

            protected:
            private:
                const std::string _msg;
        };
    } // namespace Errors
} // namespace arcade


#endif /* !ERRORS_HPP_ */
