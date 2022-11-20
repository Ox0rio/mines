//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef INTERFACE_EXCEPTION_H
#define INTERFACE_EXCEPTION_H

#include <exception>

namespace interface {

    struct ExitException : public std::exception
    {
        [[nodiscard]] const char * what () const noexcept override
        {
            return "Quitter le jeu";
        }
    };

    struct InputException : public std::exception
    {
        [[nodiscard]] const char * what () const noexcept override
        {
            return "L'action demandé n'existe pas";
        }
    };
} // interface

#endif //INTERFACE_EXCEPTION_H
