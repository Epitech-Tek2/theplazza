/*
** Epitech Project, tek2.
** Sarah-Keppler
** Plazza
*/

#ifndef PLAZZA_Exception_HPP
#define PLAZZA_Exception_HPP

#include <stdexcept>
#include <string>

namespace Plazza
{
    class Exception : std::exception
    {
        public:
            Exception() = delete;
            Exception(std::string const &message) noexcept;
            ~Exception() = default;

            Exception &operator=(Exception const &other) = delete;

            const char *what() const noexcept;
        private:
            std::string const _message;
    };

    class IPCException : public Exception
    {
        public:
            IPCException() = delete;
            IPCException(std::string const &message) noexcept : Exception{std::string{"IPC Exception: " + message}} {}
            ~IPCException() = default;

            IPCException &operator=(IPCException const &other) = delete;
        private:
            std::string const _message;
    };

    class MajorException : public Exception
    {
        public:
            MajorException(std::string const &message) noexcept : Exception(message) {}
        private:
            std::string const _message;
    };

    class MinorException : public Exception
    {
        public:
            MinorException(std::string const &message) noexcept : Exception(message) {}
        private:
            std::string const _message;
    };
}

#endif
