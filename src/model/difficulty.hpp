//
// Created by GuillaumeDescroix & Ox0rio on 16/11/22.
//

#ifndef MODEL_DIFFICULTY_H
#define MODEL_DIFFICULTY_H

#include <string>
#include <map>

namespace model
{
  typedef struct
  {
    unsigned short width;
    unsigned short height;
    unsigned short mines;
  } difficultyValue;

  const std::map<std::string, difficultyValue> difficulty = {
      {"EASY", {8, 8, 10}}, {"MEDIUM", {16, 16, 40}}, {"HARD", {30, 16, 99}}};
} // namespace model

#endif // MODEL_DIFFICULTY_H
