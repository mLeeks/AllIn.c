#include "game.h"

#include <stdio.h>

static void setup_cards(Deck *deck, Player *players, uint8_t player_count) {
    for (uint8_t i = 0; i < player_count; i++) {
        if (players[i].state != ACTIVE && players[i].state != ALL_IN) {
            continue;
        }

        draw_n_cards(&deck[0], players[i].cards, 1);
    }

    for (uint8_t i = 0; i < player_count; i++) {
        if (players[i].state != ACTIVE && players[i].state != ALL_IN) {
            continue;
        }

        draw_n_cards(&deck[1], players[i].cards, 1);
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

static void heads_up(Game *game) {
    if (game->bBlind->chips > 0) {
        game->pDealer = game->bBlind;
    }

    game->sBlind = game->pDealer;

    game->bBlind = get_active_player(
        game->players,
        game->player_count,
        game->pDealer,
        CLOCKWISE
    );
}

void setup_flop(Game *game) {
    if (game->phase != PRE_FLOP) {
        printf("Error Code: %d\n", 1);
        return;
    }

    shuffle_deck(&game->deck);

    if (get_active_player_count(game->players, game->player_count) == 2) {
        // Sonderfall: Heads Up
        heads_up(game);
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

void manage_game_flow(Game *game) {
    
}