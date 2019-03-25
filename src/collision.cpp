#include "collision.h"

extern float depth;

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.y - b.y) * 2 < (a.width + b.width)) &&
           (abs(a.z - b.z) * 2 < (a.height + b.height)) &&
           (abs(a.x - b.x) * 2 < (a.length + b.length));
}

bool ship_missile_col(Ship ship, Missile missl)
{
	bounding_box_t a, b;

	a.x = ship.ship.position.x;
	a.y = ship.ship.position.y;
	a.z = ship.ship.position.z;

	b.x = missl.missile.position.x;
	b.y = missl.missile.position.y;
	b.z = missl.missile.position.z;

	a.length = 20;
	a.width = 40;
	a.height = 80;

	b.length = 2;
	b.width = 10;
	b.height = 2;

	return(detect_collision(a, b));
}

bool ship_bomb_col(Ship ship, Bomb bomb)
{
	bounding_box_t a, b;

	a.x = ship.ship.position.x;
	a.y = ship.ship.position.y;
	a.z = ship.ship.position.z;

	b.x = bomb.bomb.position.x;
	b.y = bomb.bomb.position.y;
	b.z = bomb.bomb.position.z;

	a.length = 20;
	a.width = 40;
	a.height = 30;

	b.length = 3;
	b.width = 3;
	b.height = 3;

	return(detect_collision(a, b));
}

bool plane_missile_col(Plane jet, Missile missl)
{
	bounding_box_t a, b;

	a.x = jet.plane.position.x;
	a.y = jet.plane.position.y;
	a.z = jet.plane.position.z;

	b.x = missl.missile.position.x;
	b.y = missl.missile.position.y;
	b.z = missl.missile.position.z;

	a.length = 16;
	a.width = 18.5;
	a.height = 16.5;

	b.length = 2;
	b.width = 10;
	b.height = 2;

	return(detect_collision(a, b));
}

bool plane_volcano_col(Plane jet, Island island)
{
	bounding_box_t a, b;

	a.x = jet.plane.position.x;
	a.y = jet.plane.position.y;
	a.z = jet.plane.position.z;

	b.x = island.isld.position.x;
	b.y = island.isld.position.y;
	b.z = island.isld.position.z;

	a.length = 3;
	a.width = 16.5;
	a.height = 3;

	b.length = 100;
	b.width = 200;
	b.height = 100;

	return(detect_collision(a, b));
}

bool plane_fuel_col(Plane jet, Fuel fuel)
{
	bounding_box_t a, b;

	a.x = jet.plane.position.x;
	a.y = jet.plane.position.y;
	a.z = jet.plane.position.z;

	b.x = fuel.fuel.position.x;
	b.y = fuel.fuel.position.y;
	b.z = fuel.fuel.position.z;

	a.length = 16.5;
	a.width = 16.5;
	a.height = 3;

	b.length = 5;
	b.width = 5;
	b.height = 5;

	return(detect_collision(a, b));
}

bool plane_ring_col(Plane jet, Ring ring)
{
	bounding_box_t a, b;

	a.x = jet.plane.position.x;
	a.y = jet.plane.position.y;
	a.z = jet.plane.position.z;

	b.x = ring.ring.position.x;
	b.y = ring.ring.position.y;
	b.z = ring.ring.position.z;

	a.length = 16.5;
	a.width = 16.5;
	a.height = 3;

	b.length = 10;
	b.width = 1;
	b.height = 10;

	return(detect_collision(a, b));
}

bool plane_coin_col(Plane jet, Coin coin)
{
	bounding_box_t a, b;

	a.x = jet.plane.position.x;
	a.y = jet.plane.position.y;
	a.z = jet.plane.position.z;

	b.x = coin.coin.position.x;
	b.y = coin.coin.position.y;
	b.z = coin.coin.position.z;

	a.length = 16.5;
	a.width = 16.5;
	a.height = 3;

	b.length = 4;
	b.width = 1;
	b.height = 4;

	return(detect_collision(a, b));
}
