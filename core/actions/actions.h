//
// Created by Maxe on 06.11.2026.
//

#ifndef ALLIN_C_ACTIONS_H
#define ALLIN_C_ACTIONS_H
#include <stdbool.h>
#include <stddef.h>
#include "../game/game.h"

#endif //ALLIN_C_ACTIONS_H

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

bool is_valid_action(Game *game, GameAction action);