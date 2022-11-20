//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#include "model/difficulty.hpp"
#include "model/game.hpp"

#include "interface/exception.h"
#include "interface/console.h"

bool playAction(model::Game &game, model::Action act)
{
  bool choice = false;
  do
  {
    try
    {
      auto select = interface::Console::selectCase();
      game.play(select.x, select.y, act);
      choice = true;
    }
    catch (std::invalid_argument const &ex)
    {
      interface::Console::error(ex.what());
    }
    catch (interface::ExitException &e)
    { // Récupération de l'erreur permettant de quitter
      return true;
    }
  } while (!choice);

  return false;
}

int main()
{
  // Definition des variables
  bool exit = false;            //  Arréter le programme
  bool exitPlay;                // Aréter la partie
  model::difficultyValue diffi; // Difficulté de la partie
  interface::Action act;
  model::Game *game;

  // Afficher message de bienvenue
  interface::Console::welcome();

  // Boucle de jeu
  do
    try
    {
      diffi = interface::Console::chooseDifficulty();

      // Création du plateau de jeu
      game = new model::Game(&diffi);

      // Boucle d'une d'une partie
      exitPlay = false;
      do
      {
        interface::Console::printGame(*game);

        // Demander une action
        try
        {
          act = interface::Console::chooseAction();
        }
        catch (interface::InputException &e)
        {
          interface::Console::error(e.what());
          continue;
        }

        // Realiser l'action
        switch (act)
        {
        case interface::Action::Leave:
          exitPlay = true;
          break;
        case interface::Action::TryAgain:
          game->reset();
          break;
        case interface::Action::Rules:
          interface::Console::rules();
          break;
        case interface::Action::FlagCell:
          exit = playAction(*game, model::Action::Flag);
          break;
        case interface::Action::UnFlagCell:
          exit = playAction(*game, model::Action::UnFlag);
          break;
        case interface::Action::DiscoverCell:
          exit = playAction(*game, model::Action::Click);
          break;
        }
      } while (!exitPlay && !exit);

      delete (game);
    }
    catch (interface::ExitException &e)
    { // Récupération de l'erreur permettant de quitter
      exit = true;
    }
    catch (std::exception &e)
    { // Récupération de lerreur indiquant une valeur entrée non reconnue
      interface::Console::error(e.what());
    }
  while (!exit);

  interface::Console::bye();

  return 0;
}
