#pragma once
#include <stdbool.h>

#include "../cards/cards.h"
#include <uuid/uuid.h>


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
void init_player(Player *player, const char *name, int starting_chips);

/**
 * @brief Bereitet den Player für die nächste Hand vor.
 * @param player
 */
void reset_player(Player *player);