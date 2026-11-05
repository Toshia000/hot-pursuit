#include "Enemy.h"
#include "create_bounding_box.h"
#include "bn_sprite_items_cube_3d.h"
#include <bn_display.h>

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Enemy::Enemy(bn::fixed start_x, bn::fixed start_y, bn::fixed start_speed, bn::size enemy_size) :
    sprite(bn::sprite_items::cube_3d.create_sprite(start_x, start_y)),
    speed(start_speed),
    size(enemy_size),
    bounding_box(create_bounding_box(sprite, size)) {
}

void Enemy::update(Player& player) {
    if(sprite.x() <= player.sprite.x()) {
        sprite.set_x(sprite.x() + speed);
    }
    if(sprite.x() >= player.sprite.x()) {
        sprite.set_x(sprite.x() - speed);
    }
    if(sprite.y() <= player.sprite.y()) {
        sprite.set_y(sprite.y() + speed);
    }
    if(sprite.y() >= player.sprite.y()) {
        sprite.set_y(sprite.y() - speed);
    }

    bounding_box = create_bounding_box(sprite, size);
}

void Enemy::jump_to_random_position() {
    int min_x = MIN_X + size.width() / 2;
    int max_x = MAX_X - size.width() / 2;
    int min_y = MIN_Y + size.height() / 2;
    int max_y = MAX_Y - size.height() / 2;

    sprite.set_x(random.get_int(min_x, max_x + 1));
    sprite.set_y(random.get_int(min_y, max_y + 1));

    bounding_box = create_bounding_box(sprite, size);
}
