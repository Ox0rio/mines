//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef MODEL_BOARD_H
#define MODEL_BOARD_H

#include <stdexcept>
#include <vector>
#include <ostream>

namespace model
{
  class Board
  {
  public:
    // Constructor
    Board();
    Board(unsigned short w, unsigned short h);

    // Get cell
    short getCell(unsigned short x, unsigned short y);

    // Set cell
    void setCell(unsigned short x, unsigned short y, short v);

  private:
    // Attributes
    unsigned short width;
    unsigned short height;

    // Cell in board
    std::vector<std::vector<short>> grid;
  };
} // model

#endif // MODEL_BOARD_H
