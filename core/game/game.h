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
    NONE,
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
    Player *pStartingPlayer;
    Player *sBlind;
    Player *bBlind;
    GameConfig config;

} Game;

void init_game(Game *game);

void create_game(Game *game);
void destroy_game(Game *game);
void start_game(Game *game);

void setup_flop(Game *game);
void manage_game_flow(Game *game);