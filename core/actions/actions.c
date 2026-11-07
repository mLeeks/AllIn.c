//
// Created by Maxe on 06.11.2026.
//

#include "actions.h"

static bool is_betting_phase(Phase phase) {
    return phase == PRE_FLOP ||
           phase == FLOP ||
           phase == TURN ||
           phase == RIVER;
}

static bool validate_call(Game *game) {
    if (!is_betting_phase(game->phase))
        return false;

    Player *player = game->pCurrentPlayer;

    if (player->state != ACTIVE)
        return false;

    int to_call = game->betting.current_bet
                - player->current_bet;

    return to_call > 0 && player->chips > 0;
}

static bool validate_raise(Game *game, size_t amount) {
    if (!is_betting_phase(game->phase)) {return false;}
    if (game->pCurrentPlayer->chips < amount) {return false;}
    if (game->betting.current_bet == 0) {return false;}
    const int new_bet = game->pCurrentPlayer->current_bet + amount;

    if (new_bet <= game->betting.current_bet)
        return false;

    if (new_bet < game->betting.current_bet
                  + game->betting.min_raise &&
        amount != game->pCurrentPlayer->chips)
        return false;

    if (!betting_can_raise(&game->betting, game->pCurrentPlayer - game->players)) {return false;}

    return true;

};

static bool validate_fold(Game *game) {
    if (!is_betting_phase(game->phase)) {return false;}
    return true;
};

static bool validate_bet(Game *game, int amount) {
    if (!is_betting_phase(game->phase))
        return false;

    Player *player = game->pCurrentPlayer;

    if (player->state != ACTIVE)
        return false;

    if (amount <= 0 || amount > player->chips)
        return false;

    if (game->betting.current_bet != 0)
        return false;

    return amount >= game->config.big_blind ||
           amount == player->chips;
}

static bool validate_check(Game *game) {
    if (game->phase != PRE_FLOP && game->phase != FLOP && game->phase != TURN && game->phase != RIVER ) {return false;}
    if (game->betting.current_bet != game->pCurrentPlayer->current_bet) return false;
    return true;

};

bool is_valid_action(Game *game, GameAction *game_action, Player *action_player) {
    if (!game || !game_action || !action_player)
        return false;

    if (game->pCurrentPlayer != action_player)
        return false;

    int amount = game_action->amount;

    switch (game_action->action) {
        case CALL:  return validate_call(game);
        case RAISE: return validate_raise(game, amount);
        case FOLD:  return validate_fold(game);
        case BET:   return validate_bet(game, amount);
        case CHECK: return validate_check(game);
        default:    return false;
    }
}