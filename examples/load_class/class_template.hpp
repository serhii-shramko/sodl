#pragma once

#include <string>

class Entity {
public:
  Entity();
  virtual void do_sound_times(int n);

private:
  std::string sound;
};