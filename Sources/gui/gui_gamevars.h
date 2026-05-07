/**
 * @file gui_gamevars.h
 * @brief
 * Interface: variables globales. Ne PAS modifier.
 *
 * @attention
 * Cette partie est déjà implémentée. Il ne faut PAS la modifier.
 */

#ifndef GAMEVARS_H_
#define GAMEVARS_H_

/* __     __         _       _     _                                         */
/* \ \   / /_ _ _ __(_) __ _| |__ | | ___  ___                               */
/*  \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|                              */
/*   \ V / (_| | |  | | (_| | |_) | |  __/\__ \                              */
/*    \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/                              */
/*   ____ _       _           _                 _             _              */
/*  / ___| | ___ | |__   __ _| | ___  ___    __| |_   _      | | ___ _   _   */
/* | |  _| |/ _ \| '_ \ / _` | |/ _ \/ __|  / _` | | | |  _  | |/ _ \ | | |  */
/* | |_| | | (_) | |_) | (_| | |  __/\__ \ | (_| | |_| | | |_| |  __/ |_| |  */
/*  \____|_|\___/|_.__/ \__,_|_|\___||___/  \__,_|\__,_|  \___/ \___|\__,_|  */

#include "../game.h"
#include "../game_scores.h"
#include "gui_textbuf.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>

extern FILE *var_current_level;

typedef enum
{
    MODE_MAINMENU,
    MODE_PONGMENU,
    MODE_BRICKSMENU,
    MODE_SCOREMENU,
    MODE_PONG,
    MODE_BRICKS,
    MODE_SIZE,
} ui_mode;

extern ui_mode var_mode;

/******************************/
/*+ Dimensions de la fenêtre **/
/******************************/

/**
 * @brief Taille horizontale de l'écran.
 */
extern int var_screen_width;

/**
 * @brief Taille verticale de l'écran.
 */
extern int var_screen_height;

/**
 * @brief Taille horizontale de la partie jeu
 */
extern int var_game_width;

/**
 * @brief Taille horizontale de la partie menu.
 */
extern int var_info_width;

extern int var_board_width;
extern int var_board_height;
extern int var_anchor_x;
extern int var_anchor_y;
extern int var_extreme_x;
extern int var_extreme_y;
extern int var_mid_y;
extern int var_top_y;
extern int var_bottom_y;
extern double var_zoom;

extern SDL_Rect var_game_box;

void var_init_game_dimensions(void);
void var_init_demo_dimensions(void);

int SDL_RenderDrawDashedLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int dash_length);

/***************************/
/*+ Contrôle de la Souris **/
/***************************/

/**
 * @brief Sauvegarde de la coordonnée horizontale de la souris.
 */
extern int var_mousePosx;

/**
 * @brief Sauvegarde de la coordonnée verticale de la souris.
 */
extern int var_mousePosy;

/**
 * @brief Mémorise si le bouton gauche de la souris en enfoncé.
 */
extern bool var_leftMouseButtonDown;

extern long var_mouse_time;

/*************************/
/*+ Variables des menus +*/
/*************************/

extern int var_game_nb_columns;
extern int var_game_nb_rows;
extern int var_game_nb_balls;
extern bool var_game_bonuses;
extern int var_game_player_one_mode;
extern int var_game_player_two_mode;
extern int var_game_topspace;
extern int var_game_bottomspace;
extern int var_game_brick_colors;
extern int var_game_brick_health;

/*************************/
/*+ Lecture des niveaux **/
/*************************/

#define FILE_PER_PAGE 8
/**
 * @brief Tableau de la liste des fichiers de niveaux.
 */
extern struct dirent **var_levelstab;

/**
 * @brief Taille du tableau de la liste des fichiers de niveaux.
 */
extern int var_leveltabsize;

/**
 * @brief Nombre de pages de niveaux (taille du tableau de la liste des fichiers de niveaux divisé par le nombre de niveaux affichés par page).
 */
extern int var_levelpagesize;

/**
 * @brief Index de la page de niveaux actuellement affichée.
 */
extern int var_levelpageindex;

/**
 * @brief Index du niveau sélectionné dans le tableau de la liste des fichiers
 * de niveaux. (-1 si aucun niveau n'est utilisé)
 */
extern int var_levelindex;

/**
 * @brief Initialisation du tableau de la liste des fichiers de niveaux.
 */
void var_init_levelstab(void);

/**
 * @brief Libération du tableau de la liste des fichiers de niveaux.
 */
void var_free_levelstab(void);

/****************/
/*+ Animations **/
/****************/

/**
 * @brief Frame de l'animation à afficher.
 */
extern int var_frame;

/**
 * @brief Les noms internes des différentes animations.
 */
typedef enum
{
    AN_IDLE = 0, //!< Immobile (par défaut).
    AN_NULL,
} anim_mode;

/**
 * @brief Variable globale qui enregistre l'animation courante.
 */
extern anim_mode var_crender;

/**
 * @brief Booléen indiquant si la balle est perdue.
 */
extern bool an_lost;

/**
 * @brief Est-ce qu'il y avait une brique touche par une balle
 * ?
 */
extern bool an_hadbrick;

/**
 * @brief Est-ce qu'une brique a été détruite?
 */
extern bool an_destroyed;

extern double var_ball_speed_x, var_ball_speed_y;

/************/
/*+ Le jeu +*/
/************/

extern game *var_game;

/*****************/
/*+ Les boutons **/
/*****************/

void var_init_levelstab(void);

/*******************/
/*+ Keyboard text +*/
/*******************/

/**
 * @brief Internal names of the various values that can be edited.
 */
typedef enum
{
    // In Normal mode
    ED_WIDTH,  //!< Taille horizontale du plateau de jeu (espace contenant les briques).
    ED_HEIGHT, //!< Taille verticale du plateau de jeu.
    ED_TOP,    //!< Espace entre le haut du plateau de jeu et la première rangée de briques.
    ED_BOTTOM, //!< Espace entre le bas du plateau de jeu et la dernière rangée de briques.
    ED_COLORS, //!< Couleurs des briques.
    ED_HEALTH, //!< Santé des briques.
    ED_BALLS,  //!< Nombre de balles.
    ED_LOAD,   //!< Charger une partie sauvegardée.
    ED_NAME,   //!< Saisir le nom du joueur pour les meilleurs scores.

    // Text
    ED_TEXT,

    ED_NONE, //!< Buffer is currently unused.
} edit_mode;

/**
 * @brief Global variable used to indicate the value which is currently being edited (ED_NONE if the buffer is unused).
 */
extern edit_mode var_edit_mode;

/**
 * @brief Global variable used for the buffer (NULL if the buffer is unused).
 */
extern text_buffer *var_editbuffer;

/**
 * @brief Initialization of the buffer
 */
void init_text_buffer(edit_mode //!< The value to edit.
);

/**
 * @brief Updates parameters from the buffer.
 */
void update_from_text_buffer(void);

/******* Scores */

extern int var_scores_page;
extern int var_scores_max_page;
extern int var_scores_per_page;
extern bool var_score_table_end;
extern short var_score_winner;
extern short var_score_mode;

/**
 * @brief Score table used to display high scores.
 */
extern score_table *var_score_table;

/**
 * @brief Loads the score table from the file and fills the global variable var_score_table. If player_score is not NULL, it should contain the current player's score to be included in the table (and highlighted in the display).
 */
void var_load_score_table(int *player_score);

/**
 * @brief
 * Release of the score table when not needed anymore.
 */
void var_release_score_table(void);

#endif
