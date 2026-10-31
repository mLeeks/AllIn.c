#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "../player/player.h"
#include "../betting/betting.h"

typedef enum {
    WAITING,
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN,
    GAME_HAND_FINISHED,
    GAME_REBUY,
    GAME_END
} Phase;

typedef enum {
    BY_SHOWDOWN,
    BY_FOLD
} Win;


typedef struct {
    uint8_t ai_count;
    int big_blind;
    int small_blind;
    int buy_in;
    bool debug_mode;

} GameConfig;

typedef struct {
    Player players[10];
    uint8_t player_count;
    Deck deck;
    Board board;
    BettingState betting;
    Phase phase;
    Win win;
    Player *pDealer;
    Player *pCurrentPlayer;
    GameConfig config;

} Game;

void init_game_config(GameConfig *game_config);