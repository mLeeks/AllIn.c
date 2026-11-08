#include <uuid/uuid.h>
#include <stdio.h>

#include "player.h"

#include <stdlib.h>


void reset_player(Player *player) {
  player->state = player->chips > 0 ? ACTIVE : OUT;
  player->cards[0] = (Card){0};
  player->cards[1] = (Card){0};
  player->current_bet = 0;
  player->total_bet = 0;
  player->rebuy_done = false;
};

void init_player(GameConfig *config, Player *player) {
  player->state = ACTIVE;
  player->chips = config->buy_in;
  player->cards[0] = (Card){0};
  player->cards[1] = (Card){0};
  player->current_bet = 0;
  player->total_bet = 0;
  player->rebuy_done = false;


};

void init_players(GameConfig *config, Player *players, size_t num_players) {
  for (size_t i = 0; i < num_players; i++) {
    init_player(config, &players[i]);
  }
}

Player *get_active_player(Player *players,size_t player_count,Player *referencePlayer,Direction direction) {
  if (!players || !referencePlayer || player_count == 0) {
    return NULL;
  }

  ptrdiff_t pos = referencePlayer - players;

  for (size_t i = 1; i < player_count; i++) {
    pos = (pos + direction + (ptrdiff_t)player_count)
          % (ptrdiff_t)player_count;

    if (players[pos].state == ACTIVE) {
      return &players[pos];
    }
  }

  return NULL;
}

Player *get_random_dealer(Player *players, size_t num_players) {
    int x = rand() % (num_players + 1);

  return &players[x];
}

uint8_t get_active_player_count(Player *players, size_t num_players) {
  uint8_t count = 0;
  for (size_t i = 0; i < num_players; i++) {
    if (players[i].state == ACTIVE || players[i].state == ALL_IN) {
      count++;
    }
  }
  return count;
}

uint8_t get_only_active_player_count(Player *players, size_t num_players) {
  uint8_t count = 0;
  for (size_t i = 0; i < num_players; i++) {
    if (players[i].state == ACTIVE) {
      count++;
    }
  }
  return count;
}

Player  *get_only_active_player(Player *players, size_t num_players) {
  for (size_t i = 0; i < num_players; i++) {
    if (players[i].state == ACTIVE) {
      return &players[i];
    }
  }
  return NULL;
}
