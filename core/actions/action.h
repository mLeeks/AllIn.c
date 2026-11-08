//
// Created by Maxe on 08.11.2026.
//

#ifndef ALLIN_C_ACTION_H
#define ALLIN_C_ACTION_H
#include <stddef.h>

typedef enum {
    CALL,
    RAISE,
    FOLD,
    BET,
    CHECK,
    SHOW
} Action;

typedef struct {
    Action action;
    size_t amount;
} GameAction;


#endif //ALLIN_C_ACTION_H
