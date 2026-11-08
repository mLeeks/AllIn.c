
#include <stdbool.h>
#include "game_view.h"
#include "../game/game.h"
#include "../actions/validate_actions.h"
#include "../actions/exec_actions.h"

bool send_action(Game *game, GameAction *action, Player *action_player) {
    // Pointer Checks
    if (!game || !game_action || !action_player)
        return false;

    if (game->pCurrentPlayer != action_player)
        return false;

    // Execution
    if (!is_valid_action(game, action, action_player)) return false;
    execute_action(game, action, action_player);

    // Kehrt erst zurück, wenn eine Spieleraktion erwartet wird
    manage_game_flow(game);

    return true;

}
