#include <bn_core.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "create_bounding_box.h"
#include "Enemy.h"
#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

// Maximum number of enemies
static constexpr int MAX_ENEMIES = 10;

int main() {
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    Player player = Player(44, 22, 1.5, PLAYER_SIZE);
    
    // Create a vector for multiple enemies
    bn::vector<Enemy, MAX_ENEMIES> enemies;

    // Create enemies and put them into vector
    enemies.push_back(Enemy(-50, 50, 1.15, ENEMY_SIZE));
    enemies.push_back(Enemy(50, 50, 1, ENEMY_SIZE));
    enemies.push_back(Enemy(-100, 70, 0.5, ENEMY_SIZE));
    enemies.push_back(Enemy(100, -70, 0.7, ENEMY_SIZE));

    while(true) {
        player.update();

        for (Enemy& e : enemies) {
            e.update(player);
    
            // Reset the current score and player position if the player collides with enemy
            if(e.bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);
                player.bounding_box = create_bounding_box(player.sprite, player.size);
    
                e.jump_to_random_position();
    
                while(e.bounding_box.intersects(player.bounding_box)) {
                    e.jump_to_random_position();
                }
            }
        }

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}