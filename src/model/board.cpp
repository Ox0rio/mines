//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#include "board.h"
#include <iostream>

namespace model
{
  Board::Board()
  {
    this->width = 0;
    this->height = 0;
  }

  Board::Board(unsigned short w, unsigned short h)
  {
    this->width = w;
    this->height = h;

    this->grid = std::vector<std::vector<short>>(this->width);
    for (size_t i = 0; i < this->width; i++)
    {
      this->grid[i] = std::vector<short>(this->height);
      for (size_t j = 0; j < this->width; j++)
        this->grid[i][j] = 0;
    }
  }

  void Board::setCell(unsigned short x, unsigned short y, short v)
  {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
      throw std::invalid_argument("Cell not exists !");

    this->grid[x][y] = v;
  }

  short Board::getCell(unsigned short x, unsigned short y)
  {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
      throw std::invalid_argument("Cell not exists !");

    return this->grid[x][y];
  }
} // model