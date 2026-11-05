#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>

class Player {
    public:

        bn::sprite_ptr sprite;
        bn::fixed speed; // The speed of the player
        bn::size size; // The width and height of the sprite
        bn::rect bounding_box; // The rectangle around the sprite for checking collision
        int dash_timer;
        int dash_cooldown;

        Player(bn::fixed start_x, bn::fixed start_y, bn::fixed start_speed, bn::size player_size);

        void update();
};
