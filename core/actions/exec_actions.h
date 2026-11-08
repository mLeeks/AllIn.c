//
// Created by Maxe on 07.11.2026.
//

#ifndef ALLIN_C_EXEC_ACTIONS_H
#define ALLIN_C_EXEC_ACTIONS_H
#include "../game/game.h"
#include "action.h"



void execute_action(Game *game, GameAction *game_action, Player *action_player);
bool is_wettrunden_end();

#endif //ALLIN_C_EXEC_ACTIONS_H