#include "game.h"

#include <stdio.h>

static void setup_cards(Deck *deck, Player *players, uint8_t player_count) {
    // TODO: Beim Texas Hold'em wird dagegen reihum jeweils eine Karte pro Spieler ausgeteilt,
    // TODO: beginnend beim Small Blind. Danach folgt eine zweite Runde.
    for (uint8_t i = 0; i < player_count; i++) {
        if (players[i].state != ACTIVE && players[i].state != ALL_IN) {
            continue;
        }

        draw_n_cards(deck, players[i].cards, 2);
    }
}

static void post_blind(Player *player, int amount) {
    int bet = player->chips < amount
              ? player->chips : amount;

    player->chips -= bet;
    player->current_bet += bet;
    player->total_bet += bet;

    if (player->chips == 0) {
        player->state = ALL_IN;
    }
}

void setup_flop(Game *game) {
    if (game->phase != PRE_FLOP) {
        printf("Error Code: %d\n", 1);
        return;
    }

    shuffle_deck(&game->deck);

    if (get_active_player_count(game->players, game->player_count) == 2) {
        // Sonderfall: Heads Up
        // TODO: Heads up logik beim ersten Übergang anpassen
        Player *prev_sBlind = game->sBlind;
        game->pDealer = get_active_player(game->players, game->player_count, game->pDealer, CLOCKWISE);
        if (prev_sBlind == game->pDealer) {
            game->pDealer = get_active_player(game->players, game->player_count, game->pDealer, CLOCKWISE);
        }

        game->sBlind = game->pDealer;
        game->bBlind = get_active_player(
            game->players, game->player_count,
            game->sBlind, CLOCKWISE
        );
    } else {
        // Normalfall mit mind. 3 Spielern
        game->pDealer = get_active_player(game->players, game->player_count, game->pDealer, CLOCKWISE);
        game->sBlind = get_active_player(game->players, game->player_count, game->pDealer, CLOCKWISE);
        game->bBlind = get_active_player(game->players, game->player_count, game->sBlind, CLOCKWISE);
    }

    post_blind(game->sBlind, game->config.big_blind  /2);
    post_blind(game->bBlind, game->config.big_blind);

    setup_cards(&game->deck, game->players, game->player_count);


    game->pStartingPlayer = get_active_player(game->players, game->player_count, game->bBlind, CLOCKWISE);

    game->betting.current_bet = game->config.big_blind;
    game->betting.min_raise = game->config.big_blind;

}

void init_game(Game *game) {
    init_players(&game->config, game->players, game->player_count);
    init_deck(&game->deck);
    init_board(&game->board);
    init_betting_state(&game->config, game->betting);
    game->win = NONE;
    game->pDealer = get_random_dealer(game->players, game->player_count);
    game->pCurrentPlayer = NULL;
    game->phase = PRE_FLOP;
    setup_flop(game);
}
