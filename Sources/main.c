#include "main.h"
#include "game_parameters.h"
#include "gui/gui_controller.h"
#include "gui/gui_gamevars.h"
#include "gui/gui_rendering.h"
#include "utils.h"

FILE *var_current_level;

int main(void)
{
    atexit(shutdown_SDL);

    // Initialisation du générateur de nombres aléatoires.
    srand((unsigned int)(time(NULL)));

    var_game_nb_rows = GAME_NB_ROWS;
    var_game_nb_columns = GAME_NB_COLUMNS;
    var_game_topspace = GAME_TOP_SPACE;
    var_game_bottomspace = GAME_BOTTOM_SPACE;
    var_game_nb_balls = GAME_NB_BALLS;
    var_game_player_one_mode = GAME_PLAYER_MODE_1;
    var_game_player_two_mode = GAME_PLAYER_MODE_2;
    var_game_brick_colors = GAME_NB_COLORS;
    var_game_brick_health = GAME_BRICK_HEALTH;

    // Initializing the window and graphics.
    init_SDL(WINDOW_SCREENWIDTH, WINDOW_SCREENHEIGHT);

    INFO("SDL initialized");

    event_loop();

    exit(EXIT_SUCCESS);
}
