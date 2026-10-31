#include "../player/player.h"

typedef enum {
    A_CALL,
    A_RAISE,
    A_FOLD,
    A_BET,
    A_CHECK,
    A_ALL_IN
} Action;

typedef struct {
    int current_bet;
    int min_raise;
    Player *pLastRaiser;
} BettingState;

typedef struct {
    Action type;
    int amount;
} GameAction;