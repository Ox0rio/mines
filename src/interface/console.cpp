//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#include "console.h"

namespace interface
{
  void Console::welcome()
  {
    std::cout << "Welcome to Mines !!" << std::endl;
    Console::rules();
  }

  void Console::rules()
  {
    std::cout << "Rules :" << std::endl;
    std::cout << "- To finish the game, you must find the position of all the mines" << std::endl;
    std::cout << "- You can either discover a square by selecting it or place a flag to indicate a mine" << std::endl;
    std::cout << std::endl;
  }

  void Console::win()
  {
    std::cout << "Congratulations, you have won !";
    std::cout << std::endl;
  }

  void Console::failed()
  {
    std::cout << "Too bad, you lost !";
    std::cout << std::endl;
  }

  void Console::bye()
  {
    std::cout << "Thank you for playing at the Mines !" << std::endl;
  }

  void Console::error(const std::string &msg)
  {
    std::cout << msg << std::endl;
  }

  model::difficultyValue Console::chooseDifficulty()
  {
    std::cout << "List of difficulties :" << std::endl;

    auto diff_name = std::vector<std::string>();

    size_t code = 1;
    for (auto it = model::difficulty.begin(); it != model::difficulty.end(); it++)
    {
      std::cout << code++ // string (key)
                << ": "
                << it->first
                << " "
                << it->second.width
                << " x "
                << it->second.height
                << " ("
                << it->second.mines
                << " mines)"
                << std::endl;
      diff_name.push_back(it->first);
    }

    std::cout << code << ": Custom" << std::endl;
    std::cout << "0: Exit game" << std::endl;

    int ret;
    std::cin >> ret;

    if (ret == 0)
      throw ExitException();

    if (ret == code)
    {
      std::cout << "Choose width : ";
      unsigned short w;
      std::cin >> w;

      std::cout << "Choose height : ";
      unsigned short h;
      std::cin >> h;

      std::cout << "Choose mines : ";
      unsigned short m;
      std::cin >> m;

      return {w, h, m};
    }

    std::cout << "Difficulty choose : " << diff_name[ret - 1] << std::endl;
    return model::difficulty.at(diff_name[ret - 1]);
  }

  void Console::printGame(model::Game &game) {
    std::cout << game;
  }

  Action Console::chooseAction()
  {
    std::cout << "Choose action :" << std::endl;

    std::cout << "0: New game" << std::endl;
    std::cout << "1: Exit game" << std::endl;
    std::cout << "2: Discover cell" << std::endl;
    std::cout << "3: Flag cell" << std::endl;
    std::cout << "4: Unflag cell" << std::endl;
    std::cout << "5: Retry" << std::endl;

    int act;
    std::cin >> act;

    switch (act)
    {
    case 0:
      return Action::Leave;
    case 1:
      throw ExitException();
    case 2:
      return Action::DiscoverCell;
    case 3:
      return Action::FlagCell;
    case 4:
      return Action::UnFlagCell;
    case 5:
      return Action::TryAgain;
    default:
      throw InputException();
    }
  }

  interface::coordinate Console::selectCase()
  {
    std::cout << "Choose x : ";

    unsigned short x;
    std::cin >> x;

    std::cout << "Choose y : ";

    unsigned short y;
    std::cin >> y;

    return {x, y};
  }
} // interface