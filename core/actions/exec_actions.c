//
// Created by Maxe on 07.11.2026.
//

#include "exec_actions.h"
#include "validate_actions.c"


//
// Created by Maxe on 06.11.2026.
//

static bool execute_call() {

    return true;
}

static bool execute_raise() {

    return true;
};

static bool execute_fold() {

    return true;
};

static bool execute_bet() {

    return true;
}

static bool execute_check() {

    return true;

};

bool execute_action(Game *game, GameAction *game_action, Player *action_player) {
    if (!game || !game_action || !action_player)
        return false;

    if (game->pCurrentPlayer != action_player)
        return false;

    if (!is_valid_action(game, game_action, action_player)) return false;

    bool result = false;

    int amount = game_action->amount;

    switch (game_action->action) {
        case CALL:  result = execute_call();
        case RAISE: result = execute_raise();
        case FOLD:  result = execute_fold();
        case BET:   result = execute_bet();
        case CHECK: result = execute_check();
        default:    result = false;
    }

    return result;
}