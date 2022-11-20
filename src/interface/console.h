//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef INTERFACE_CONSOLE_H
#define INTERFACE_CONSOLE_H

#include <iostream>

#include "../model/difficulty.hpp"
#include "../model/game.hpp"
#include "exception.h"

namespace interface
{
    enum Action
    {
        Leave,
        TryAgain,
        DiscoverCell,
        FlagCell,
        UnFlagCell,
        Rules,
    };

    typedef struct
    {
        unsigned short x;
        unsigned short y;
    }coordinate;
    

    class Console
    {
    public:
        static void welcome();
        static void rules();
        static void win();
        static void failed();
        static void bye();
        static void error(const std::string &msg);
        static void printGame(model::Game &b);

        static model::difficultyValue chooseDifficulty();
        static Action chooseAction();

        static interface::coordinate selectCase();
    };

} // interface

#endif // INTERFACE_CONSOLE_H
