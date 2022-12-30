//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#include "game.hpp"
#include <iostream>
#include <cstdlib>

namespace model
{
  Game::Game(model::difficultyValue *d)
  {
    this->width = d->width;
    this->height = d->height;
    this->mines = d->mines;
    this->initBoardPlayer();
    this->initBoardSolver();
  }

  model::Board Game::play(unsigned short x, unsigned short y, Action a)
  {
    switch (a)
    {
    case Action::Flag:
      putFlag(x, y);
      break;
    case Action::UnFlag:
      removeFlag(x, y);
      break;
    case Action::Click:
      playClick(x, y);
      break;
    default:
      throw new std::exception();
    }

    return this->boardPlayer;
  }

  void Game::reset()
  {
    this->initBoardPlayer();
    this->initBoardSolver();
  }

  void Game::changeDifficulty(difficultyValue *d)
  {
    this->width = d->width;
    this->height = d->height;
    this->mines = d->mines;
    this->initBoardPlayer();
    this->initBoardSolver();
  }

  void Game::initBoardPlayer()
  {
    this->boardPlayer = Board(this->width, this->height);
    for (int x = 0; x < this->width; x++)
    {
      for (int y = 0; y < this->height; y++)
      {
        this->boardPlayer.setCell(x, y, -3);
      }
    }
  }

  void Game::initBoardSolver()
  {
    this->boardSolver = Board(this->width, this->height);

    short i = 0;
    while (i < this->mines)
    {
      unsigned short randWidth = ((unsigned short)std::rand()) % this->width;
      unsigned short randHeight = ((unsigned short)std::rand()) % this->height;

      try
      {
        if (this->boardSolver.getCell(randWidth, randHeight) != -1)
        {
          // Place Mines
          this->boardSolver.setCell(randWidth, randHeight, -1);
          i++;

          // Increment neighbours
          for (int x = -1; x < 2; x++)
          {
            for (int y = -1; y < 2; y++)
            {
              try
              {
                if (this->boardSolver.getCell(randWidth + x, randHeight + y) != -1)
                {
                  this->boardSolver.setCell(randWidth + x, randHeight + y, this->boardSolver.getCell(randWidth + x, randHeight + y) + 1);
                }
              }
              catch (const std::invalid_argument &e)
              {
                continue;
              };
            }
          }
        }
      }
      catch (const std::invalid_argument &e)
      {
      };
    }
  }

  void Game::putFlag(unsigned short x, unsigned short y)
  {
    // TODO : gérer erreur pas dans le tableau
    if (this->boardPlayer.getCell(x, y) == -3)
    {
      // Place Flag
      this->boardPlayer.setCell(x, y, -2);
    }
    else
    {
      // TODO : throw error
    }
  }

  void Game::removeFlag(unsigned short x, unsigned short y)
  {
    // TODO : gérer erreur pas dans le tableau
    if (this->boardPlayer.getCell(x, y) == -2)
    {
      // Remove Flag
      this->boardPlayer.setCell(x, y, -3);
    }
    else
    {
      // TODO : throw error
    }
  }

  void Game::playClick(unsigned short x, unsigned short y)
  {
    // TODO : gérer erreur pas dans le tableau
    switch (this->boardPlayer.getCell(x, y))
    {
    case -3: // Click on unknown cell
      this->clickUnknown(x, y);
      break;
    case -2: // Click on a Flag
      break;
    default: // Click on known cell
      this->clickKnown(x, y);
      break;
    }
  }

  void Game::clickUnknown(unsigned short x, unsigned short y)
  {
    try
    {
      if (this->boardPlayer.getCell(x, y) == -3)
      {
        switch (this->boardSolver.getCell(x, y))
        {
        case 0:
          this->boardPlayer.setCell(x, y, 0);

          for (int x_ = x-1; x_ <= x+1; x_++)
          {
            for (int y_ = y-1; y_ <= y+1; y_++)
            {
              this->clickUnknown(x_, y_);
            }
          }
          break;

        case -1:
          // TODO : Throw error
          break;

        default:
          this->boardPlayer.setCell(x, y, this->boardSolver.getCell(x, y));
          break;
        }
      }
    }
    catch (std::exception e)
    {
    };
  }

  unsigned short Game::countMines(unsigned short x, unsigned short y)
  {
    unsigned short cpt = 0;
    for (int x_ = x-1; x_ <= x+1; x_++)
    {
      for (int y_ = y-1; y_ <= y+1; y++)
      {
        try
        {
          if (this->boardPlayer.getCell(x_, y_) == -1)
          {
            cpt++;
          }
        }
        catch (std::exception e)
        {
        };
      }
    }
    return cpt;
  }

  void Game::clickKnown(unsigned short x, unsigned short y)
  {
    if (this->boardPlayer.getCell(x, y) == this->countMines(x, y))
    {
      for (int x_ = x-1; x_ < x+1; x_++)
      {
        for (int y_ = y-1; y_ < y+1; y_++)
        {
          try
          {
            if (this->boardPlayer.getCell(x_, y_) == -3)
            {
              this->clickUnknown(x_, y_);
            }
          }
          catch (std::exception e)
          {
          };
        }
      }
    }
  }
}