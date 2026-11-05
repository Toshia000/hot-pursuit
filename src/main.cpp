#include <bn_core.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_random.h>
#include <bn_display.h>

#include "create_bounding_box.h"
#include "Enemy.h"
#include "ScoreDisplay.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

// Maximum number of enemies
static constexpr int MAX_ENEMIES = 10;

// Delay for creating new enemy
static constexpr int NEW_ENEMY_DELAY = 300;

int main() {
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    Player player = Player(44, 22, 1.5, PLAYER_SIZE);
    
    // Create a vector for multiple enemies
    bn::vector<Enemy, MAX_ENEMIES> enemies;

    bn::fixed new_enemy = NEW_ENEMY_DELAY;

    bn::random random;

    // Create enemies and put them into vector
    enemies.push_back(Enemy(-50, 50, 1.15, ENEMY_SIZE));

    while(true) {
        player.update();

        if (new_enemy == 0) {
            bn::fixed new_y = random.get_fixed(MIN_Y, MAX_Y);
            bn::fixed new_x = random.get_fixed(MIN_X, MAX_X);
            bn::fixed new_speed = random.get_fixed(0.5, 1.5);

            enemies.push_back(Enemy(new_x, new_y, new_speed, ENEMY_SIZE));

            new_enemy = NEW_ENEMY_DELAY;
        }

        for (Enemy& e : enemies) {
            e.update(player);
    
            // Reset the current score and player position if the player collides with enemy
            if(e.bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);
                player.bounding_box = create_bounding_box(player.sprite, player.size);
    
                e.jump_to_random_position();

                while(enemies.size() > 1) {
                    enemies.pop_back();
                }
    
                while(e.bounding_box.intersects(player.bounding_box)) {
                    e.jump_to_random_position();
                }
            }
        }

        // Update the scores and disaply them
        scoreDisplay.update();

        new_enemy -= 1;
        bn::core::update();
    }
}