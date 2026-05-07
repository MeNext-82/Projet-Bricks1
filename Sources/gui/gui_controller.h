#ifndef GUI_CONTROLLER_H_
#define GUI_CONTROLLER_H_

#include "../game.h"
#include "gui_rendering.h"
#include "stdbool.h"
#include <time.h>

typedef enum
{
    QUIT,
    PAUSED,
    HELP,
    PUSHED,
    ANIMATED,
    MOUSEDOWN,
    KEYDOWN,
    WIN,
    NB_FLAGS
} ctl_flags;

/**
 * @brief Tableau des flags.
 */
extern bool flags[NB_FLAGS];

/**
 * @brief Activation d'un flag.
 */
void set_flag(ctl_flags //!< Le flag
);

/**
 * @brief Récupération d'un flag.
 */
bool get_flag(ctl_flags //!< Le flag
);

/**
 * @brief Changement de statut d'un flag.
 */
void switch_flag(ctl_flags //!< Le flag
);

/**
 * @brief Désactivation d'un flag.
 */
void remove_flag(ctl_flags //!< Le flag
);

/**
 * @brief Désactivation de tous les flags.
 */
void reset_flags(void);

/**************************/
/*+ Intialisation du jeu **/
/**************************/

void ctl_enter_menu(void);
void ctl_enter_scoreboard(void);
void ctl_switch_to_score_menu(void);

void ctl_switch_to_pong_menu(void);

void ctl_switch_to_bricks_menu(void);

void ctl_switch_to_main_menu(void);

/**
 * @brief Intialisation d'un jeu de démonstration.
 */
void ctl_init_demo(void);

/**
 * @brief Intialisation d'un jeu de Pong.
 */
void ctl_init_pong(void);

void ctl_init_brick(void);

void ctl_load_game(void);

/**
 * @brief Teste si un jeu est bien construit (autant que faire se peut)
 */
bool ctl_game_ok(game *);

/**
 * @brief Libération des objets alloués faisant partie de l'interface.
 */
void ctl_free_gui(void);

void ctl_handle_edit_return(void);

/*********************************/
/*+ Prise en compte des actions **/
/*********************************/

void ctl_button_push(void);

void ctl_mouse_click(SDL_Event *theevent);
void ctl_mouse_unclick(SDL_Event *theevent);
bool ctl_mouse_mainmenu(int x, int y);
bool ctl_mouse_pongmenu(int x, int y);
bool ctl_mouse_bricksmenu(int x, int y);
bool ctl_mouse_game(int x, int y);
bool ctl_mouse_score_screen(int x, int y);
// /**
//  * @brief Préparation d'une action classique avant la modification du jeu.
//  */
// void ctl_init_action(game *,
//                      move //!< Déplacement.
// );

void ctl_pause_game(void);

void ctl_resume_game(void);

void ctl_keyboard_general_menu(SDL_KeyCode key);

/**
 * @brief Fin de la préparation d'une action après la modification du jeu.
 */
void ctl_update_action(game * //!< Le jeu.
);

// /**
//  * @brief Mise en place d'une action de déplacement.
//  */
// void ctl_move_action(game * //!< Le jeu.
//                      ,
//                      move // Mouvement effectué
// );

/**
 * @brief Traitement du clavier.
 */
void ctl_keyboard(game *,
                  SDL_Event * //!< L'Event pour avoir la touche utilisée.
);

void ctl_keyboard_up(game *thegame, SDL_Event *theevent);

/****************************/
/*+ Gestion des animations **/
/****************************/

/**
 * @brief Réinitialisation des animations.
 */
void ctl_anim_reset(void);

/**
 * @brief Animation des toons immobile (défaut).
 */
void ctl_anim_idle(game *);

/*******************/
/*+ Boucle de jeu **/
/*******************/

void ctl_menu_display(void);
void ctl_handle_pong_game(void);
void ctl_handle_brick_game(void);
/**
 * @brief La boucle de jeu.
 */
void event_loop(void);

#endif // GUI_CONTROLLER_H_
