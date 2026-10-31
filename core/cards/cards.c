#include "cards.h"
#include <sodium.h>

void shuffle(Deck *deck) {
    for (int i = 51; i > 0; i--) {
        int j = randombytes_uniform(i + 1);

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}