#include "game.h"
#include "game_bonus.h"
#include "game_bricks.h"
#include "game_pong.h"

void free_game(game *the_game) {
     if(the_game==NULL){
        return;
    }
    for(int i=0;i<2;i++){
        if(the_game->paddles[i] !=NULL){
            free(the_game->paddles[i]);
            the_game->paddles[i]=NULL;
        }
    }
    for(int i=0;i<the_game->nb_balls;i++){
        if(the_game->ball_list[i] !=NULL){
            free(the_game->ball_list[i]);
        }
    }
    free(the_game->ball_list);
    the_game->ball_list=NULL;
    
}

void game_move_player(game *g, short p, short dir){
    paddle *pad = g->paddles[p];
    if (dir ==0){
        pad->speed_x=0;
        return;
    }else {
        double speed;
        if(pad->smode ==SPEED_NORMAL){
            speed= PADDLE_BASE_SPEED;
        }
        else if (pad->smode == SPEED_SLOW){
            speed = PADDLE_BASE_SPEED / 2 ;
        }
        else{
            speed= PADDLE_BASE_SPEED *2 ;
        }
        pad->speed_x=dir*speed;
    }
     
}

void game_apply_moves(game *g){
     if(g==NULL){
        return;
    }
    printf("Debut apply_moves,nb_balls=%d\n",g->nb_balls);
    int largeur_plateau=g->nb_columns * CELL_WIDTH ;
    
    for(int i=0;i<2;i++){
        if(g->paddles[i]!= NULL){
            g->paddles[i]->rect.x +=g->paddles[i]->speed_x;
            if(g->paddles[i]->rect.x <0){
                g->paddles[i]->rect.x=0;
            }
            if(g->paddles[i]->rect.x +g->paddles[i]->rect.w >largeur_plateau){
                g->paddles[i]->rect.x=largeur_plateau-g->paddles[i]->rect.w;
            }
        }
        
    }
    printf("Apres raquettes");
    for(int j=0;j<g->nb_balls;j++){
        printf("Deplacement balle %d avant: x=%.1f,y=%.1f\n",j,g->ball_list[j]->rect.x,g->ball_list[j]->rect.y);
        if(g->ball_list[j]!=NULL){
            g->ball_list[j]->rect.x+=g->ball_list[j]->speed_x;
            g->ball_list[j]->rect.y +=g->ball_list[j]->speed_y;
        }
        else{
            printf("ERREUR:balle %d est NULL!\n",j);
        }
        printf("Apres : x=%.1f,y=%.1f\n",g->ball_list[j]->rect.x,g->ball_list[j]->rect.y);
       
    }
    printf("Fin apply_moves");
}

void game_place_bonus_pong(game *g){
     if(!g->bonuses){
        return;
    }
    double hauteur_plateau=g->nb_rows *CELL_HEIGHT;
    double y= hauteur_plateau / 2.0;
    double largeur_plateau=g->nb_columns * CELL_WIDTH;
    double x= random_double(0.0,largeur_plateau);

    bool down;
    if(g->paddles[0]!=NULL && g->paddles[1]!=NULL){
        down= random_double(0.0,1.0);
    }
    else if(g->paddles[0]!=NULL){
        down=true;
    }
    else{
        down=false;
    }
    game_add_bonus(g,x,y,down);
    
}

void game_handle_collisions(game *g){
     printf("debut collisions,nb_balls=%d,paddles[0]=%p,paddles[1]=%p\n",g->nb_balls,(void*)g->paddles[0],(void*)g->paddles[1]);
    int i=0;
    while(i < g->nb_balls){
        bool supprime= ball_hits_wall(g,i) ;
        if(!supprime){
            i++ ;
        }
    }
    printf("Apres murs,nb_balls=%d\n",g->nb_balls);
    for( int j=0;j<2;j++){
        if(g->paddles[j]!=NULL){
            printf("Raquette %d presente\n",j);
            for(int k=0;k<g->nb_balls;k++){
                printf("Test raquette %d avec balle %d\n",j,k);
                ball_hits_paddle(g,k,g->paddles[j]);
            }
        }

    }
    printf("Apres raquette,nb_balls=%d\n",g->nb_balls);
    
    for(int a=0; a<g->nb_balls;a++){
        for(int b=a+1;b < g->nb_balls; b++){
            printf("collision balle %d et %d\n",a,b);
            ball_collide(g->ball_list[a],g->ball_list[b]);
        }
    }
    if(g->nb_balls==0){
        bool continuer= false;
        if(g->paddles[0]!=NULL && g->paddles[0]->health >0){
            continuer=true;
        }
        if(g->paddles[1]!=NULL && g->paddles[1]->health >0){
            continuer=true;
        }
        if(continuer){
            game_add_ball_center(g,0.5,POW_NONE);
        }
    }
    printf("Fin collisions\n");
    
}




