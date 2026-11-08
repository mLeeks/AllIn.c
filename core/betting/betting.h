#pragma once
#include "../player/player.h"


typedef struct {
    int current_bet;
    int min_raise;
    bool has_acted[10]; // Speichert pro Setzrunde wer eine Aktion durchgeführt hat
    size_t last_acted_bet[10]; // Speichert pro Setzrunde den letzten Einsatz, der jeweiligen Spieler

} BettingState;


void init_betting_state(GameConfig *config, BettingState *state);

bool betting_can_raise(BettingState *betting, size_t player_index);

void save_action(BettingState *betting, Player *players, Player *action_player);
void reset_betting(BettingState *betting, GameConfig *config);