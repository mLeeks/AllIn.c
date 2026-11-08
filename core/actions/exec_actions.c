//
// Created by Maxe on 07.11.2026.
//

#include "exec_actions.h"
#include "validate_actions.h"


//
// Created by Maxe on 06.11.2026.
//

static bool execute_call(Game *game, Player *action_player) {

    int to_call = game->betting.current_bet - action_player->current_bet;

    // All-in berücksichtigen
    int bet = 0;

    if (to_call < action_player->chips) {
        bet = to_call;
    }
    else {
        bet = action_player->chips;
        action_player->state = ALL_IN;
    }

    action_player->chips -= bet;
    action_player->current_bet += bet;
    action_player->total_bet += bet;

    return true;
}

static bool execute_raise(Game *game, Player *player, size_t amount) {
    int difference = amount - player->current_bet;

    int raise_increment =
        amount - game->betting.current_bet;

    if (raise_increment >= game->betting.min_raise) {
        game->betting.min_raise = raise_increment;
    }

    player->chips -= difference;
    player->current_bet = amount;
    player->total_bet += difference;

    if (player->chips == 0) {
        player->state = ALL_IN;
    }

    game->betting.current_bet = amount;

    return true;
}

static bool execute_bet(Game *game, Player *action_player, size_t amount) {
    bool result = execute_raise(game, action_player, amount);

    return result;
};

static bool execute_fold(Game *game, Player *action_player) {
    action_player->state = FOLDED;
    if (get_active_player_count(game->players, game->player_count) < 2) {
        game->phase = GAME_HAND_FINISHED;
        game->win = BY_FOLD;
    }
    return true;
}

static bool execute_check() {
    // Nothing to do here
    return true;

};

bool is_wettrunden_end(Game *game) {

    if (game->phase == GAME_HAND_FINISHED)
        return true;

    const BettingState *betting = &game->betting;

    if (get_only_active_player_count(game->players, game->player_count) == 1) {
        Player *player = get_only_active_player(game->players, game->player_count);

        if (player->current_bet == betting->current_bet)
            return true;
    }

    for (size_t i = 0; i < game->player_count; i++) {
        const Player *player = &game->players[i];

        // Folded, All-in und Out müssen nicht mehr handeln
        if (player->state != ACTIVE)
            continue;

        // Spieler hat noch nicht gehandelt
        if (!betting->has_acted[i])
            return false;

        // Spieler muss noch einen Einsatz ausgleichen
        if (player->current_bet != betting->current_bet)
            return false;
    }

    return true;
}

bool execute_action(Game *game, GameAction *game_action, Player *action_player) {
    // TODO: SHOW wird noch ignoriert
    if (!game || !game_action || !action_player)
        return false;

    if (game->pCurrentPlayer != action_player)
        return false;

    if (!is_valid_action(game, game_action, action_player)) return false;

    bool result = false;

    int amount = game_action->amount;

    switch (game_action->action) {
        case CALL:  result = execute_call(game, action_player); break;
        case RAISE: result = execute_raise(game, action_player, amount); break;
        case FOLD:  result = execute_fold(game, action_player); break;
        case BET:   result = execute_bet(game, action_player, amount); break;
        case CHECK: result = execute_check(); break;
        default:    result = false;
    }

    if (!result) {
        return false;
    }

    save_action(&game->betting, game->players, action_player);

    if (is_wettrunden_end(game)) {
        // TODO: Phasenwechsel
        next_game_phase();
        return true;
    }

    game->pCurrentPlayer = get_active_player(game->players, game->player_count, game->pCurrentPlayer, CLOCKWISE);


    return result;
}