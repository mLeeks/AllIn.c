#include "betting.h"

void init_betting_state(GameConfig *config, BettingState *state) {
    state->min_raise = config->big_blind;
    state->current_bet = 0;
    state->pLastRaiser = NULL;
};