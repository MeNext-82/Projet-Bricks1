#include "game_pong.h"

/************************/
/*+ Création d'un jeu +*/
/***********************/

game *create_pong_game(int nb_columns, int nb_rows, short player_one_mode,
                       short player_two_mode, short nb_balls, bool bonuses) {
    return NULL;
}

bool game_pong_end(game *g, short *winner) { return false; }

bool game_pongia(game *g, short i) { return false; }

/************************/
/*+ Gestion des balles +*/
/************************/

bool game_add_ball_player(game *g, short player, power pow) { return false; }

void game_add_ball_center(game *g, double frac, power pow) {}

void game_remove_ball(game *g, int i) {}

bool ball_hits_wall(game *g, int i) { return false; }

bool ball_hits_paddle(game *g, int i, paddle *p) { return false; }

bool ball_collide(ball *b1, ball *b2) { return false; }
