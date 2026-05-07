#include "game_pong.h"

/************************/
/*+ Création d'un jeu +*/
/***********************/

game *create_pong_game(int nb_columns, int nb_rows, short player_one_mode,
                       short player_two_mode, short nb_balls, bool bonuses) {
                        game* g = calloc(1,sizeof(game));
                         
                           // Dimensions 
                           g->nb_columns =nb_columns ;
                           g->nb_rows =nb_rows ;
                           g->mode = GAME_PONG ; 
                        
                           // players 
                           g->player_modes[0] = player_one_mode ;
                           g->player_modes[1]= player_two_mode ;

                          if (player_one_mode !=0){
                            g->paddles[0]=create_paddle(true,nb_rows,nb_columns);
                          }
                          if (player_two_mode !=0){
                            g->paddles[1]=create_paddle(false,nb_rows,nb_columns);
                          }
                          g->ball_list = malloc(1 * sizeof(ball*));
                          g->size_balls=1;
                          g->nb_balls=0;

                          // ON ajoute des balles
                          if(player_one_mode != 0 || player_two_mode != 0){

                        
                            for(int i =0;i<nb_balls;i++){
                                double frac ; 
                                if(nb_balls ==1){
                                frac=0.5;
                                }else {
                                frac=(i+0.5)/nb_balls;
                                }
                                game_add_ball_center(g,frac,POW_NONE);
                            }
                          }

                          // Bonus
                         g->bonus_list=malloc(1* sizeof(bonus*));
                         g->size_bonus=1;
                         g->nb_bonus=0;
                         g->bonuses=bonuses;

                         return g;
                       }

bool game_pong_end(game *g, short *winner){
    if(g->paddles[0] != NULL && g->paddles[0]->health <=0){
        if(g->paddles[1]!=NULL){
            *winner=1;
        }
        else{
            *winner=0;
        }
        return true;
    }
    if(g->paddles[1] != NULL && g->paddles[1]->health <=0){
        if(g->paddles[0]!=NULL){
            *winner=0;
        }
        else{
            *winner=1;
        }
        return true;
    }
    return false;
}

bool game_pongia(game *g, short i){
    paddle *pad= g->paddles[i];
    if(pad==NULL){
        return false;
    }
    if(g->nb_balls==0){
        pad->speed_x=0;
        return true;
    }
    ball *cible=g->ball_list[0];
    
    double centre_cible = cible->rect.x + cible->rect.w / 2.0 ;
    double centre_raquette= pad->rect.x + pad->rect.w / 2.0 ;
    double dist_min=fabs(centre_cible-centre_raquette);

    for(int j=1;j<g->nb_balls;j++){
        ball *b=g->ball_list[j];
        double centre_b=b->rect.x+b->rect.w / 2.0;
        double dist = fabs(centre_b - centre_raquette);
        if(dist < dist_min){
            dist_min=dist;
            cible=b;
        }
    }
    centre_cible=cible->rect.x + cible->rect.w / 2.0;
    centre_raquette=pad->rect.x+pad->rect.w / 2.0;
   
    double vitesse = PADDLE_BASE_SPEED;
    if(pad->smode == SPEED_SLOW){
        vitesse = PADDLE_BASE_SPEED / 2 ;
    }
    else if(pad->smode == SPEED_FAST){
        vitesse =PADDLE_BASE_SPEED *2 ;
    }
    if(centre_cible < centre_raquette -5){
        pad->speed_x = -vitesse ;
    }
    else if(centre_cible > centre_raquette +5){
        pad->speed_x=vitesse;
    }
    else{
        pad->speed_x=0;
    }
    return true;
}

bool game_add_ball_player(game *g, short player, power pow);

void game_add_ball_center(game *g, double frac, power pow){
    if(g->nb_balls>=g->size_balls){
        g->size_balls*=2;
        g->ball_list=realloc(g->ball_list,g->size_balls * sizeof(ball*));
    }
    double largeur = g->nb_columns*CELL_WIDTH;
    double hauteur=g->nb_rows * CELL_HEIGHT ;
    double x = largeur * frac ;
    double y = hauteur /2.0 ;

    ball *b= create_ball(x,y,false);
    b->powerup= pow;
    g->ball_list[g->nb_balls]= b ;
    g->nb_balls ++;
    
}

void game_remove_ball(game *g, int i){
    if(g==NULL){
        return;
    }
    if(i<0 || i>=g->nb_balls){
        return;
    }
    free(g->ball_list[i]);
    if(i < g->nb_balls -1){
        g->ball_list[i]=g->ball_list[g->nb_balls -1];

    }
    g->ball_list[g->nb_balls -1]=NULL;
    g->nb_balls--;
}

bool ball_hits_wall(game *g, int i){
    if(g->ball_list[i]==NULL){
        return false;
    }

    ball *b = g->ball_list[i];
    double largeur = g->nb_columns* CELL_WIDTH ;
    double hauteur= g->nb_rows * CELL_HEIGHT ;
    bool hit = false;

    if(b->rect.x<0 ){
        b->speed_x=-b->speed_x;
        b->rect.x=0;
        hit= true;
    }
    else if(b->rect.x + b->rect.w >largeur){
        b->speed_x=-b->speed_x;
        b->rect.x=largeur - b->rect.w;
        hit=true;
    }
    if(b->rect.y <0){
        if(g->paddles[1] !=NULL){
            g->paddles[1]->health--;
            if(g->paddles[0] !=NULL){
                g->paddles[0]->goals++;
            }
            game_remove_ball(g , i);
            return true;

        }else{
            b->speed_y=-b->speed_y ;
            b->rect.y=0;
            hit = true ;
        }
        
    }
    else if(b->rect.y +b->rect.h > hauteur){
        if(g->paddles[0] !=NULL){
            g->paddles[0] ->health--;
            if(g->paddles[1]!=NULL){
                g->paddles[1]->goals++;
                
            }
            game_remove_ball(g,i);
            return true;
        }
        else{
            b->speed_y=-b->speed_y;
            b->rect.y=hauteur - b->rect.h;
            hit=true;
        }

    }
    return hit ;
}

bool ball_hits_paddle(game *g, int i, paddle *p){
    if(p==NULL){
        return false;
    }
     ball *b=g->ball_list[i];
    if(!rectangles_overlap(&b->rect, &p->rect)){
        return false;
    }
    double centre_balle= b->rect.x + b->rect.w / 2.0 ;
    double bord_gauche = p->rect.x ;
    double largeur= p->rect.w ;
    double position= (centre_balle - bord_gauche) / largeur ;
    double angle_deg=(position -0.5) *120.0;
    double angle_rad=angle_deg * M_PI / 180.0;

    b->speed_x=sin(angle_rad) *BALL_SPEED;
    b->speed_y=cos(angle_rad) * BALL_SPEED;

    if(p->bottom){
        b->speed_y= -fabs(b->speed_y);
    }
    else{
        b->speed_y= fabs(b->speed_y);
    }

    b->last_hit = p->bottom ? 0 :1;

    return true;
}

bool ball_collide(ball *b1, ball *b2){
    
    if(b1==NULL || b2 == NULL){
        return false;
    } 
    if(!rectangles_overlap(&b1->rect, &b2->rect)){
        return false;
    }
    double cx1=b1->rect.x + b1->rect.w / 2.0 ;
    double cy1 = b1->rect.y + b1->rect.h /2.0 ;
    double cx2 = b2->rect.x + b2->rect.w / 2.0;
    double cy2 = b2->rect.y + b2->rect.h / 2.0;

    double dx1=cx1-cx2;
    double dy1=cy1-cy2;
    double longueur=sqrt(dx1*dx1 + dy1 * dy1);
    if(longueur==0){
        b1->speed_x=BALL_SPEED;
        b1->speed_y=0;
        b2->speed_x=-BALL_SPEED;
        b2->speed_y=0;
        return true;
    }
    b1->speed_x = (dx1 /longueur) * BALL_SPEED;
    b1->speed_y= (dy1 / longueur) * BALL_SPEED;

    b2->speed_x= -b1->speed_x;
    b2->speed_y=-b1->speed_y;

    return true;
  
}
    


