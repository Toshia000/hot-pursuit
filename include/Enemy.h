#include "Player.h"
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_random.h>

class Enemy {
    public:

        bn::sprite_ptr sprite;
        bn::fixed speed;
        bn::size size; // The width and height of the sprite
        bn::rect bounding_box; // The rectangle around the sprite for checking collision
        bn::random random;

        Enemy(bn::fixed start_x, bn::fixed start_y, bn::fixed start_speed, bn::size enemy_size);

        void update(Player& player);

        void jump_to_random_position();
};
