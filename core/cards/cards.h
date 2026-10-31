#include <stdbool.h>
#include <stddef.h>

typedef enum {
    CLUB,
    DIAMOND,
    HEART,
    SPADE,
    PLACEHOLDER,
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
    ACE,
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

/**
 * @brief Generiert alle Karten aus den Enums Suit und Rank
 * @param deck
 */
void init_deck(Deck *deck);

/**
 * @brief Mischt die Karten in einem Deck
 * Nutzt den Fisher Yates Algorithm mit einer CSPRNG (library: libsodium) Zufallsvariable
 * @param deck
 */
void shuffle(Deck *deck);

/**
 * @brief Kopiert n Karten vom Deck in die cards
 * @param deck
 * @param cards
 * @param n
 * @return true, wenn erfolgreich.
 * @return false, wenn die Parameter ungültig sind
 *         oder nicht genügend Karten vorhanden sind.
 */
bool draw_n_cards(Deck *deck, Card *cards, size_t n);

