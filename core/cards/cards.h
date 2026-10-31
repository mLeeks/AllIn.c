#include <stddef.h>

typedef enum {
    SPADE,
    HEART,
    DIAMOND,
    CLUB
} Suit;

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

typedef struct {
    Rank rank;
    Suit suit;
} Card;

typedef struct {
    Card cards[52];
    size_t next_card;
} Deck;

typedef struct {
    Card cards[5];
    size_t count;

    Card burn_cards[3];
} Board;

void init_deck(Deck *deck);
// Kartengeneration auf Basis der Kombination aus Rank und Suit Enum

void shuffle(Deck *deck);
//Fisher Yates Algorithm + CSPRNG (libsodium)

Card* draw_one_card(Deck *deck);

Card* draw_two_cards(Deck *deck);

void return_card(Card *card);

