//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef MODEL_EXCEPTION_H
#define MODEL_EXCEPTION_H

#include <exception>

namespace model {

    struct ExitException : public std::exception
    {
        [[nodiscard]] const char * what () const noexcept override
        {
            return "Quitter le jeu";
        }
    };
} // model

#endif //MODEL_EXCEPTION_H
