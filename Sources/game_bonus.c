#include "game_bonus.h"
#include "game.h"
#include "game_bricks.h"
#include "game_pong.h"

/***********************/
/*+ Gestion des bonus +*/
/***********************/

void game_add_bonus(game *g, double x, double y, bool down) {

    if(g->nb_bonus>=g->size_bonus){
        g->size_bonus=g->size_bonus * 2 ;
        g->bonus_list=realloc(g->bonus_list,g->size_bonus * sizeof(bonus*));
    }
    bonus * nouveau= create_random_bonus(x,y,down,false);
    g->bonus_list[g->nb_bonus]=nouveau;
    g->nb_bonus++;
    
}

void game_remove_bonus(game *g, int i){
     if(i<0 || i>=g->nb_bonus){
        return;
    }
    free(g->bonus_list[i]);
    if(i<g->nb_bonus -1){
        g->bonus_list[i]=g->bonus_list[g->nb_bonus -1];
    }
    g->bonus_list[g->nb_bonus -1]=NULL;
    g->nb_bonus --;
}

bool game_capture_bonus(game *g, paddle *p){
    if(p==NULL){
        return false;
    }
    bool capture=false;
    int i=0;
    while(i<g->nb_bonus){
        bonus *bon=g->bonus_list[i];
        if(rectangles_overlap(&bon->rect,&p->rect)){
            capture=true;
            p->bonuses++;
            if(bon->type==BNS_SHRINK){
                if(p->size ==PADDLE_NORMAL){
                    p->size=PADDLE_SMALL;
                    p->rect.w=PADDLE_WIDTH ;
                }
                else if(p->size==PADDLE_LARGE){
                    p->size=PADDLE_NORMAL;
                    p->rect.w=PADDLE_WIDTH;
                }
            }
            else if(bon->type == BNS_GROW){
                if(p->size ==PADDLE_SMALL){
                    p->size=PADDLE_NORMAL;
                    p->rect.w =PADDLE_WIDTH;
                }
                else if(p->size==PADDLE_NORMAL){
                    p->size=PADDLE_LARGE;
                    p->rect.w=PADDLE_WIDTH;
                }
            }
            else if(bon->type== BNS_SPEEDUP){
                if(p->smode ==SPEED_SLOW){
                    p->smode=SPEED_NORMAL;
                }
                else if(p->smode==SPEED_NORMAL){
                    p->smode=SPEED_FAST;
                }
                double base=PADDLE_BASE_SPEED;
                if(p->smode==SPEED_SLOW){
                    base /=2.0;
                }
                else if(p->smode==SPEED_FAST){
                    base *=2.0;

                }
                if(p->speed_x>0){
                    p->speed_x=base;
                }
                else if(p->speed_x <0){
                    p->speed_x=-base;
                }
            }
            else if(bon->type==BNS_SLOWDOWN){
                if(p->smode == SPEED_FAST){
                    p->smode=SPEED_NORMAL;
                }
                else if(p->smode==SPEED_NORMAL){
                    p->smode=SPEED_SLOW;
                }
                double base=PADDLE_BASE_SPEED;
                if(p->smode==SPEED_SLOW){
                    base /=2.0;
                }
                else if(p->smode==SPEED_FAST){
                    base *=2.0;
                }
                if(p->speed_x>0){
                    p->speed_x=base;
                }
                if(p->speed_x<0){
                    p->speed_x=-base;
                }

            }
            else if(bon->type==BNS_SCORE50){
                p->score +=50;
            }
            else if(bon->type==BNS_SCORE100){
                p->score +=100;
            }
            else if(bon->type==BNS_SCORE250){
                p->score +=250;
            }
            else if(bon->type==BNS_SCORE500){
                p->score +=500;
            }
            else if(bon->type==BNS_HEALTH){
                p->health++;
            }
            else if(bon->type==BNS_NEWBALL){
                game_add_ball_player(g,p->bottom ? 0:1, POW_NONE);
            }
            game_remove_bonus(g,i);
        }
        else{
            i++;
        }
    }

    return capture;
}



