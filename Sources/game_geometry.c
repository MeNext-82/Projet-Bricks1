#include "game_geometry.h"
#include "alloc.h"
#include "game.h"
#include "utils.h"
#include <math.h>

/****************/
/*+ Rectangles +*/
/****************/

bool rectangles_overlap(rectangle *r1, rectangle *r2) { return false; }

/**************/
/*+ Raquette +*/
/**************/

paddle *create_paddle(bool bottom, int nb_rows, int nb_columns) { return NULL; }

/************/
/*+ Balles +*/
/************/

ball *create_ball(double x, double y, bool top) { return NULL; }

double ball_speednorm(ball *b) { return 0.0; }

/*************/
/*+ Briques +*/
/*************/

brick *create_brick(double x, double y, brick_color color, int max_health,
                    int origin) {
    return NULL;
}

/***********/
/*+ Bonus +*/
/***********/

bonus *create_random_bonus(double x, double y, bool down, bool bricks) {
    return NULL;
}
