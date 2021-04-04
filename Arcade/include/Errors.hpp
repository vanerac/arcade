/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <stdexcept>

namespace Errors
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

#endif /* !ERRORS_HPP_ */
