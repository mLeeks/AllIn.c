//
// Created by Maxe on 06.11.2026.
//

#ifndef ALLIN_C_VALIDATE_ACTIONS_H
#define ALLIN_C_VALIDATE_ACTIONS_H

#include <stdbool.h>

#include "../game/game.h"
#include "action.h"

bool is_valid_action(Game *game, GameAction *game_action, Player *action_player);

#endif //ALLIN_C_VALIDATE_ACTIONS_H
