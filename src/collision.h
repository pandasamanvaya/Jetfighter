#ifndef COLLISION_H
#define COLLISION_H

#include "main.h"
#include "plane.h"
#include "ship.h"
#include "weapons.h"
#include "island.h"
#include "float_obj.h"

bool detect_collision(bounding_box_t a, bounding_box_t b);
bool ship_missile_col(Ship ship, Missile missl);
bool ship_bomb_col(Ship ship, Bomb bomb);
bool plane_missile_col(Plane jet, Missile missl);
bool plane_volcano_col(Plane jet, Island island);
bool plane_fuel_col(Plane jet, Fuel fuel);
bool plane_ring_col(Plane jet, Ring ring);
bool plane_coin_col(Plane jet, Coin coin);

#endif