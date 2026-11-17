#pragma once
#include <stdbool.h>
#include <stddef.h>

#include "../player/player.h"
#include "../game/game.h"

struct GameConfig;

typedef struct {
    int current_bet;
    int min_raise;
    bool has_acted[10]; // Speichert pro Setzrunde wer eine Aktion durchgeführt hat | Wird für ALL_IN SPieler nicht zurückgesetzt!!
    size_t last_acted_bet[10]; // Speichert pro Setzrunde den letzten Einsatz, der jeweiligen Spieler

} BettingState;


void init_betting_state(GameConfig *config, BettingState *state);

bool betting_can_raise(BettingState *betting, size_t player_index);

void save_action(BettingState *betting, Player *players, Player *action_player);
void reset_betting(BettingState *betting, GameConfig *config, Player *players, size_t player_count);
void setup_betting_round(Game *game, size_t amount_burn_cards, size_t amount_draw_cards);
bool even_player_raise(BettingState *betting, size_t player_count, Player *players);
bool is_everyone_all_in(BettingState *betting, size_t player_count, Player *players);
bool every_player_acted(BettingState *betting, size_t player_count, Player *players);