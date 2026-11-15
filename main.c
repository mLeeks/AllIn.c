#include <stdio.h>
#include <string.h>

#include "core/game_view/game_view.h"

int main(void) {
    Player players[10] = {
        {.name = "Alice"},
        {.name = "Bob"},
        {.name = "Charlie"}
    };

    for (int i = 0; i < 10; i++) {
        uuid_generate_random(players[i].uuid);
    }


    GameConfig config = {2, 250, 125, 2000, false};
    Game game = {.config = config, .player_count = 2, .phase=PRE_FLOP};

    memcpy(game.players, players, sizeof(players));

    // -----------------------------------------------------------------------------------


    init_game(&game);
    /// wettrunden loop:
    ///     - get_current_player
    ///     - send aufforderung irwas zu machen
    ///     - warten
    ///     - spieler hat was gemacht
    ///     - wettrunde zuende?:
    ///         game_end? -->(ja) end;
    ///         next_wettrunde
    printf("\n");

}
