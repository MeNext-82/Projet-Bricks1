#include "game_bricks.h"
#include "game_bonus.h"
#include "game_pong.h"

game *create_random_brick_game(int nb_columns, int nb_rows, int topspace,
                               int bottomspace, short player_one_mode,
                               short player_two_mode, int nb_colors,
                               int max_health) {
    return NULL;
}

game *create_newgame_file(char **input, int size, short player_one_mode,
                          short player_two_mode) {
    if (!input || size < 4) {
        fprintf(stderr, "Error: Invalid input for create_newgame_file\n");
        return NULL;
    }

    game *g;
    CALLOC(g, 1);

    // Lecture des dimensions du plateau et des espaces
    char *end;
    g->nb_columns = strtol(input[0], &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "Error: Invalid number of columns in input: %s\n",
                input[0]);
        free_game(g);
        return NULL;
    }
    g->nb_rows = strtol(input[1], &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "Error: Invalid number of rows in input: %s\n",
                input[1]);
        free_game(g);
        return NULL;
    }
    g->topspace = strtol(input[2], &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "Error: Invalid top space in input: %s\n", input[2]);
        free_game(g);
        return NULL;
    }
    g->bottomspace = strtol(input[3], &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "Error: Invalid bottom space in input: %s\n", input[3]);
        free_game(g);
        return NULL;
    }

    if (g->nb_columns <= 0 || g->nb_rows <= 0 || g->topspace < 0 ||
        g->bottomspace < 0 || g->topspace + g->bottomspace >= g->nb_rows) {
        fprintf(stderr, "Error: Invalid game parameters in input\n");
        free_game(g);
        return NULL;
    }

    // Propriétés du jeu
    g->mode = GAME_BRICKS;
    g->bonuses = true;

    // Création de la raquette
    g->player_modes[0] = player_one_mode;
    g->player_modes[1] = player_two_mode;
    g->paddles[0] = player_one_mode > 0
                        ? create_paddle(true, g->nb_rows, g->nb_columns)
                        : NULL;
    g->paddles[1] = player_two_mode > 0
                        ? create_paddle(false, g->nb_rows, g->nb_columns)
                        : NULL;

    g->size_balls = 1;
    g->nb_balls = 0;
    CALLOC(g->ball_list, g->size_balls);
    // Création des balle
    if (player_one_mode >= 1) {
        game_add_ball_player(g, 0, POW_NONE);
    }

    if (player_two_mode >= 1) {
        game_add_ball_player(g, 1, POW_NONE);
    }

    // Initialisation de la liste de briques et du plateau de jeu
    CALLOC(g->brick_list, 1);
    g->nb_bricks = 0;
    g->size_bricks = 1;
    MALLOC(g->board, g->nb_columns * g->nb_rows);
    memset(g->board, -1, g->nb_columns * g->nb_rows * sizeof(int));

    for (int i = 4; i < size; i++) {
        int x, y, thecolor, health;
        x = strtol(input[i], &end, 10);
        if (*end != ',') {
            fprintf(stderr, "Error: Invalid brick configuration in input: %s\n",
                    input[i]);
            continue;
        }
        y = strtol(end + 1, &end, 10);
        if (*end != ',') {
            fprintf(stderr, "Error: Invalid brick configuration in input: %s\n",
                    input[i]);
            continue;
        }
        thecolor = strtol(end + 1, &end, 10);
        if (*end != ',') {
            fprintf(stderr, "Error: Invalid brick configuration in input: %s\n",
                    input[i]);
            continue;
        }
        health = strtol(end + 1, &end, 10);
        if (*end != '\0') {
            fprintf(stderr, "Error: Invalid brick configuration in input: %s\n",
                    input[i]);
            continue;
        }

        if (x < 0 || x >= g->nb_columns || y < 0 || y >= g->nb_rows) {
            fprintf(stderr,
                    "Error: Brick position (%d, %d) is out of bounds in input: "
                    "%s\n",
                    x, y, input[i]);
            continue;
        }

        if (y < g->topspace || y >= g->nb_rows - g->bottomspace) {
            fprintf(stderr,
                    "Error: Brick position (%d, %d) is out of bounds in input: "
                    "%s\n",
                    x, y, input[i]);
            continue;
        }

        game_add_brick(g, x, y, thecolor, health);
    }

    // Bonus
    g->nb_bonus = 0;
    g->size_bonus = 1;
    CALLOC(g->bonus_list, g->size_bonus);

    return g;
}

bool game_brick_end(game *g, bool *win) { return false; }

bool game_brickia(game *g, short i) { return false; }

/*************************/
/*+ Gestion des briques +*/
/*************************/

void game_add_brick(game *g, int x, int y, brick_color color, int health) {}

void game_remove_brick(game *g, int i, short last_side_hit) {}

bool ball_hits_brick(game *g, int i) { return false; }

void game_gravity(game *g, bool bot) {}
