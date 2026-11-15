#include "betting.h"

#include <string.h>

#include "../game/game.h"

void init_betting_state(GameConfig *config, BettingState *state) {
    state->min_raise = config->big_blind;
    state->current_bet = 0;
    memset(state->has_acted, false, 10);
    memset(state->last_acted_bet, 0, 10);
};

/**
 * @brief Prüft das Erhöhungsrecht gemäß TDA-Regel 49A.
 *
 * @param betting Zustand der aktuellen Setzrunde.
 * @param player_index Index des zu prüfenden Spielers.
 *
 * @return true, wenn das Erhöhungsrecht besteht.
 * @return false, wenn das Erhöhungsrecht gesperrt ist
 *         oder die Parameter ungültig sind.
 *
 * @note Prüft nicht Chipstand, Spielerstatus
 *       oder die Höhe eines konkreten Raises.
 */
bool betting_can_raise(BettingState *betting, size_t player_index) {
    if (!betting || player_index >= 10)
        return false;

    if (!betting->has_acted[player_index])
        return true;

    return betting->current_bet >=
               betting->last_acted_bet[player_index] &&
           betting->current_bet -
               betting->last_acted_bet[player_index]
               >= betting->min_raise;
}

void save_action(BettingState *betting, Player *players, Player *action_player) {
    ptrdiff_t index = action_player - players;
    betting->has_acted[index] = true;
    betting->last_acted_bet[index] =
        betting->current_bet;
}

void setup_betting_round(Game *game, size_t amount_burn_cards, size_t amount_draw_cards) {
    if (game->phase != FLOP && game->phase != TURN && game->phase != RIVER) {return;}

    draw_n_cards(&game->deck, game->board.burn_cards, game->board.bCount, amount_burn_cards);
    draw_n_cards(&game->deck, game->board.cards, game->board.count, amount_draw_cards);
    game->board.bCount += amount_burn_cards;
    game->board.count += amount_draw_cards;

    if (game->phase == FLOP) {
        game->pStartingPlayer = get_active_player(game->players, game->player_count, game->pDealer, CLOCKWISE);
    }

    game->pCurrentPlayer = game->pStartingPlayer;

}

void reset_betting(BettingState *betting, GameConfig *config) {
    memset(betting->has_acted, false, 10);
    memset(betting->last_acted_bet, 0, 10);
    betting->current_bet = 0;
    betting->min_raise = config->big_blind;
}

