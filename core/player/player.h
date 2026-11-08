#pragma once
#include <stdbool.h>

#include "../cards/cards.h"
#include <uuid/uuid.h>
#include "../game/game.h"


typedef enum {
    ANTI_CLOCKWISE = -1,
    CLOCKWISE = 1
} Direction;

typedef enum {
    ACTIVE,
    FOLDED,
    ALL_IN,
    OUT
} PlayerState;

typedef struct {
    uuid_t uuid;
    char name[8];
    Card cards[2];
    int chips;
    PlayerState state;
    int current_bet;
    int total_bet;
    bool rebuy_done;

} Player;

/**
 * @brief Initialisiert einen Spieler
 * @param player
 * @param name
 * @param starting_chips
 */
void init_player(GameConfig *config, Player *players);

void init_players(GameConfig *config, Player *player, size_t num_players);

/**
 * @brief Bereitet den Player für die nächste Hand vor.
 * @param player
 */
void reset_player(Player *player);

Player *get_random_dealer(Player *players, size_t num_players);

Player *get_active_player(
    Player *players,
    size_t player_count,
    Player *referencePlayer,
    Direction direction
);

uint8_t get_active_player_count(Player *players, size_t num_players);
uint8_t get_only_active_player_count(Player *players, size_t num_players);
Player  *get_only_active_player(Player *players, size_t num_players);