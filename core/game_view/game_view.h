#include "../player/player.h"
#include "../game/game.h"
#include <stdint.h>

/**
 * Initializes preFilled Game
 * @param game
 * @return bool
 */
bool init_game(Game *game);

/**
 * @brief Free Game memory
 * @param game
 */
void destroyGame(Game *game);

/**
 * @brief  Returns the current Player awaited to do an action.
 * @param game
 * @return
 */
Player *get_current_player(Game *game);

/**
 * @brief Apply Player action
 * @param game
 * @param action
 * @return bool
 */
bool game_apply_action(Game *game, Action action);

/**
 * @brief Get Bitmask for possible Actions (1 ... valid action; 0... invalid action-)
 * @param game
 * @return
 */
uint8_t get_valid_actions(Game *game);

/**
 * @brief Get all important Data for graphical View
 * @param game
 * @return
 */
char get_game_view(Game *game);

/**
 * Returns the current Game Phase
 * @param game
 * @return Phase
 */
Phase get_game_state(Game *game);

/**
 * @brief Returns if the game is over
 * @param game
 * @return bool
 */
bool is_game_over(Game *game);

