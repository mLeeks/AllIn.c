//
// Created by Maxe on 06.11.2026.
//

#ifndef ALLIN_C_ACTIONS_H
#define ALLIN_C_ACTIONS_H
#include <stdbool.h>
#include <stddef.h>
#include "../game/game.h"


typedef enum {
    CALL,
    RAISE,
    FOLD,
    BET,
    CHECK,
    SHOW
} Action;

typedef struct {
    Action action;
    size_t amount;
} GameAction;

bool execute_action(Game *game, GameAction *game_action, Player *action_player);

#endif //ALLIN_C_ACTIONS_H
