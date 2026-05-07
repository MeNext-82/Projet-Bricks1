#include "game_geometry.h"
#include "alloc.h"
#include "game.h"
#include "utils.h"
#include <math.h>

/****************/
/*+ Rectangles +*/
/****************/

bool rectangles_overlap(rectangle *r1, rectangle *r2) { 
    if(r1->x + r1->w <= r2->x){
        return false ;
    }
    if(r2->x + r2->w <=r1->x){
        return false;
    }
    if(r1->y + r1->h <= r2->y){
        return false;
    }
    if(r2->y +r2->h <= r1->y){
        return false;
    }
    return true;
}

ball *create_ball(double x, double y, bool top){
    ball *b=malloc(sizeof(ball));
    b->rect.x= x - BALL_RADIUS ;
    b->rect.y = y - BALL_RADIUS ;
    b->rect.w = 2 * BALL_RADIUS ; 
    b->rect.h = 2 * BALL_RADIUS;

    double angle_deg= random_double(-60 , 60);
    double angle_rad = angle_deg * M_PI /180.0 ;
    b->speed_x= sin(angle_rad) * BALL_SPEED;
    b->speed_y= cos(angle_rad) *BALL_SPEED ;

    if (top){
        b->speed_y= -fabs(b->speed_y);
    }else{
        b->speed_y= fabs(b->speed_y);
    }
    b->last_hit=-1 ;
    b->powerup=POW_NONE ;

    return b ;
}

double ball_speednorm(ball *b){
    return sqrt(b->speed_x * b->speed_x + b->speed_y *b->speed_y);
}

paddle *create_paddle(bool bottom, int nb_rows, int nb_columns){
    // 1. On alloue une raquete en mémoire
    paddle *p = malloc(sizeof(paddle));
    // 2 On calcule la position
    double x = (nb_columns * CELL_WIDTH) / 2.0 -PADDLE_WIDTH / 2.0 ;
    double y ; 
    if (bottom){
        y = nb_rows *CELL_HEIGHT - PADDLE_HEIGHT ;
    }
    else {
        y=0;
    }

    // 3. ON remplis les champs
    p->rect.x = x ;
    p->rect.y = y ;
    p->rect.w = PADDLE_WIDTH ;
    p->rect.h = PADDLE_HEIGHT;
    p->speed_x = 0 ;
    p->size = PADDLE_NORMAL;
    p->smode = SPEED_NORMAL;
    p->bottom = bottom ;
    p->health = 3;
    p->score=0;
    p->goals=0;
    p->bonuses=0;
    p->bricks=0;

    return p ;
}

brick *create_brick(double x, double y, brick_color color, int max_health, int origin);

bonus *create_random_bonus(double x, double y, bool down, bool bricks){
     bonus *b= malloc(sizeof(bonus));
    if(bricks){
        b->type= random_double(0,BNS_NEWBALL);
    }
    else {
        b->type = random_double(0,BNS_NEWBALL);
    }
    if(b->type == BNS_HEALTH){
        b->rect.w= HEALTH_WIDTH;
        b->rect.h= HEALTH_HEIGHT; 
    }
    else{
        b->rect.w= BONUS_WIDTH;
        b->rect.h= BONUS_HEIGHT;
    }
    b->rect.x=x-b->rect.w / 2.0 ;
    b->rect.y=y-b->rect.h / 2.0 ;
    if(down){
        b->speed_y=BONUS_SPEED;
    }
    else {
        b->speed_y=-BONUS_SPEED;
    }
    return b;
    
}


