#ifndef _PROJECT_PARAMETERS_H_
#define _PROJECT_PARAMETERS_H_

/**
 * @file game_parameters.h
 *
 * @brief Parameters.
 *
 * @details Default values for the games parameters.
 */

/*  ____                                _                 */
/* |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___  */
/* | |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __| */
/* |  __/ (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \ */
/* |_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/ */

/************************************/
/*+ Activation des options de debug */
/************************************/

/**
 * @brief Flag pour activer le mode debug. Décommenter pour activer le mode
 * debug.
 *
 * @details
 * En mode debug, l'interface n'appelle pas les fonctions qui mettent fin aux
 * parties. Elle ne se terminent donc jamais. De plus des commandes clavier
 * supplémentaires sont disponibles pour tester les fonctionnalités du jeu:
 * - 'b' pour ajouter une balle sans pouvoir sur la raquette du joueur 1.
 * - 'v' pour ajouter une balle verte sur la raquette du joueur 1.
 * - 'r' pour ajouter une balle rouge sur la raquette du joueur 1.
 * - 'g' active la gravité vers la bas (appelle la fonction game_gravity()).
 * - 'h' active la gravité vers le haut (appelle la fonction game_gravity()).
 */
#define DEBUG_MODE

/***********************/
/*+ Window dimensions +*/
/***********************/

/**
 * @brief Dimension horizontale de l'application en pixels (par défaut = 1820).
 */
#define WINDOW_SCREENWIDTH 1820

/**
 * @brief Dimension verticale de l'application en pixels (par défaut = 980).
 */
#define WINDOW_SCREENHEIGHT 980

/************************/
/*+ Default parameters +*/
/************************/

/**
 * @brief Nombre de colonnes du plateau de jeu par défaut (en cellules)
 * (par défault = 8).
 */
#define GAME_NB_COLUMNS 8

/**
 * @brief Nombre de lignes du plateau de jeu par défaut (en cellules) (par
 * défaut = 18).
 */
#define GAME_NB_ROWS 18

/**
 * @brief Nombre de balles par défaut dans une partie de Pong (par défaut = 2).
 */
#define GAME_NB_BALLS 2

/**
 * @brief Mode par défaut pour le joueur 1, 0 : Joueur 1 désactivé, 1 : IA, 2 :
 * Humain (par défaut : 2).
 */
#define GAME_PLAYER_MODE_1 2

/**
 * @brief Mode par défaut pour le joueur 2, 0 : Joueur 2 désactivé, 1 : IA, 2 :
 * Humain (par défaut : 0).
 */
#define GAME_PLAYER_MODE_2 0

/**
 * @brief Espace entre le haut de la fenêtre et la zone contenant les briques
 * (par défaut :  0).
 */
#define GAME_TOP_SPACE 0

/**
 * @brief Espace entre le bas de la fenêtre et la zone contenant les briques
 * (par défaut :  6).
 */
#define GAME_BOTTOM_SPACE 6

/**
 * @brief Nombre de couleurs pour les briques générées aléatoirement (entre 1 et
 * 9) (par défaut : 3).
 */
#define GAME_NB_COLORS 3

/**
 * @brief Points de vie maximum de chaque brique générée aléatoirement (par
 * défaut : 2).
 */
#define GAME_BRICK_HEALTH 2

#endif // _PROJECT_PARAMETERS_H_
