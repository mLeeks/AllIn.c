#include <uuid/uuid.h>
#include <stdio.h>

#include "player.h"

void reset_player(Player *player) {
  player->state = player->chips > 0 ? ACTIVE : OUT;
  player->cards[0] = (Card){0};
  player->cards[1] = (Card){0};
  player->current_bet = 0;
  player->total_bet = 0;
  player->rebuy_done = false;
};

void init_player(Player *player, const char *name, int starting_chips) {
  uuid_generate_random(player->uuid);
  snprintf(player->name, sizeof(player->name), "%s", name);
  player->chips = starting_chips;
  reset_player(player);

};

