#include "Player.h"
#include "bn_sprite_items_ball_3d.h"
#include <bn_keypad.h>
#include "create_bounding_box.h"
#include <bn_display.h>

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Player::Player(bn::fixed start_x, bn::fixed start_y, bn::fixed start_speed, bn::size player_size) : 
    sprite(bn::sprite_items::ball_3d.create_sprite(start_x, start_y)),
    speed(start_speed),
    size(player_size),
    bounding_box(create_bounding_box(sprite, size)),
    dash_timer(0),
    dash_cooldown(0)
    {
}

void Player::update() {
    if(dash_cooldown > 0) {
        dash_cooldown--;
    }

    if(bn::keypad::a_pressed() && dash_cooldown == 0) {
        dash_timer = 25;
        dash_cooldown = 180;
    }

    bn::fixed movement_speed = speed;

    if(dash_timer > 0) {
        movement_speed = speed * 3;
        dash_timer--;
    }

    if(bn::keypad::right_held()) {
      sprite.set_x(sprite.x() + movement_speed);
    }
    if(bn::keypad::left_held()) {
        sprite.set_x(sprite.x() - movement_speed);
    }
    if(bn::keypad::up_held()) {
        sprite.set_y(sprite.y() - movement_speed);
    }
    if(bn::keypad::down_held()) {
        sprite.set_y(sprite.y() + movement_speed);
    }
    // Ensure player will not go off the screen
    int min_x = MIN_X + size.width() / 2;
    int max_x = MAX_X - size.width() / 2;
    int min_y = MIN_Y + size.height() / 2;
    int max_y = MAX_Y - size.height() / 2;

    if(sprite.x() < min_x) {
        sprite.set_x(min_x);
    }
    if(sprite.x() > max_x) {
        sprite.set_x(max_x);
    }
    if(sprite.y() < min_y) {
        sprite.set_y(min_y);
    }
    if(sprite.y() > max_y) {
        sprite.set_y(max_y);
    }

    bounding_box = create_bounding_box(sprite, size);
}
