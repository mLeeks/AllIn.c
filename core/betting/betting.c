#include "betting.h"

#include <stdlib.h>
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

void reset_betting(BettingState *betting, GameConfig *config, Player *players, size_t player_count) {
    // ALL_IN Spieler haben in jeder Runde bereits gehandelt
    for (size_t i = 0; i < player_count; i++) {
        if (players[i].state != ALL_IN) {
            betting->has_acted[i] = false;
        }
    }
    memset(betting->last_acted_bet, 0, 10);
    betting->current_bet = 0;
    betting->min_raise = config->big_blind;
}

// Wettrunden End Bedingungen
/** @brief jeder Spieler hat bereits mind. einen Spielzug gemacht?
 * */
bool every_player_acted(BettingState *betting, size_t player_count, Player *players) {
    bool everyone_acted = true;

    for (size_t i = 0; i < player_count; i++) {
        if (!betting->has_acted[i] && players[i].state == ACTIVE) {
            everyone_acted = false;
            break;
        }
    }
    return everyone_acted;
}

/** @brief Raises wurden ausgeglichen?
 * **/
bool even_player_raise(BettingState *betting, size_t player_count, Player *players) {
    bool even_player_raise = true;
    size_t last_acted_bet = 0;

    for (size_t i = 0; i < player_count; i++) {
        // Ist ein Spieler ALL_IN in dieser Runde gegangen,dann ist last_acted_bet nicht null, ist er vorher all_in gegangen ist dieser wert null
        if (players[i].state == ACTIVE || players[i].state == ALL_IN && betting->last_acted_bet[i] != 0) {
            if (last_acted_bet == 0) {last_acted_bet = betting->last_acted_bet[i]; continue;}

            if (last_acted_bet != betting->last_acted_bet[i]) {
                even_player_raise = false;
                break;
            }
        }

    }
    return even_player_raise;

}

bool is_everyone_all_in(BettingState *betting, size_t player_count, Player *players) {
    int all_in_count = 0;
    int active_player_count = 0;

    if (!even_player_raise(betting, player_count, players)) {return false;}


    for (int i = 0; i < player_count; i++) {
        if (players[i].state == ACTIVE || players[i].state == ALL_IN)  {active_player_count++;}
        if (players[i].state == ALL_IN) {all_in_count++;}
    }

    if (abs((all_in_count - active_player_count)) > 1) {return false;}

    return true;
}
