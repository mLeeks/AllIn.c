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

void init_deck(Deck *deck) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck->cards[i * 13 + j] = (Card){
                .rank = (Rank)j,
                .suit = (Suit)i
            };
        }
    }
    deck->next_card = 0;
}

bool draw_n_cards(Deck *deck, Card *cards, size_t n) {
    if (n == 0 || deck->next_card > 52 ||
        n > 52 - deck->next_card)
        return false;

    for (size_t i = 0; i < n; i++) {
        cards[i] = deck->cards[deck->next_card++];
    }

    return true;
}