#include "betting.h"

#include <string.h>

void init_betting_state(GameConfig *config, BettingState *state) {
    state->min_raise = config->big_blind;
    state->current_bet = 0;
    state->pLastRaiser = NULL;
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

void save_action(BettingState *betting, size_t player_index) {
    betting->has_acted[player_index] = true;
    betting->last_acted_bet[player_index] =
        betting->current_bet;
}