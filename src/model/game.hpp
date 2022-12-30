//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef MODEL_GAME_H
#define MODEL_GAME_H

#include <vector>

#include "board.h"
#include "difficulty.hpp"

namespace model
{
  enum struct Action
  {
    Flag,
    UnFlag,
    Click
  };

  class Game
  {
  public:
    Game(model::difficultyValue *d);
    model::Board play(unsigned short x, unsigned short y, Action a);
    void reset();
    void changeDifficulty(model::difficultyValue *d);

    friend std::ostream &operator<<(std::ostream &os, Game &g)
    {
      short cell;
      for (unsigned short x = 0; x < g.width; x++)
      {

        os << "| ";
        for (unsigned short y = 0; y < g.height; y++)
        {
          cell = g.boardPlayer.getCell(x, y);
          if (cell == -3)
            os << " ";
          else if (cell == -2)
            os << "?";
          else
            os << cell;

          os << " | ";
        }
        os << std::endl;
      }

      return os;
    };

  private:
    void initBoardPlayer();
    void initBoardSolver();
    void putFlag(unsigned short x, unsigned short y);
    void removeFlag(unsigned short x, unsigned short y);
    void playClick(unsigned short x, unsigned short y);
    void clickUnknown(unsigned short x, unsigned short y);
    unsigned short countMines(unsigned short x, unsigned short y);
    void clickKnown(unsigned short x, unsigned short y);

  protected:
    /*
     * Board that is display to the player :
     *  - [0:8] : mines number close to the square
     *  - -3    : Unknown case 
     *  - -2    : Flag on the case
     */
    model::Board boardPlayer;
    model::difficultyValue d;
    unsigned short mines;
    unsigned short width;
    unsigned short height;
    
    /*
     * Board that is hide wich contains the solution :
     *  - [0:8] : mines number close to the square
     *  - -1    : mines
     */
    model::Board boardSolver;
  };
}

#endif // MODEL_GAME_H