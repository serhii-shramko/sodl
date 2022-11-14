#include "class_template.hpp"
#include "dynamic.hpp"
#include <iostream>

Entity::Entity() { sound = "Woof"; }

void Entity::do_sound_times(int n) {
  while (n--) {
    std::cout << sound << " ";
  }
  std::cout << std::endl;
}

DYNAMIC_PREFIX Entity *create_object() { return new Entity; }

DYNAMIC_PREFIX void delete_object(Entity *object) { delete object; }
