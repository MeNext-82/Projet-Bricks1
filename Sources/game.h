#ifndef GAME_H_
#define GAME_H_

/**
 * @file game.h
 * @brief Définition de la structure de données représentant l'état du jeu et
 * des fonctions pour manipuler cette structure.
 */

/*   ____    _    __  __ _____  */
/*  / ___|  / \  |  \/  | ____| */
/* | |  _  / _ \ | |\/| |  _|   */
/* | |_| |/ ___ \| |  | | |___  */
/*  \____/_/   \_\_|  |_|_____| */

#include "alloc.h"
#include "game_debris.h"
#include "game_geometry.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

/***************************************************************/
/*+ Constantes utilisées pour initialiser les éléments du jeu +*/
/***************************************************************/
/**
 * @brief
 * Largeur d'une cellule sur le plateau. À utiliser pour initialiser la largeur
 * d'une nouvelle brique.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define CELL_WIDTH 366

/**
 * @brief
 * Hauteur d'une cellule sur le plateau. À utiliser pour la initialiser la
 * hauteur d'une nouvelle brique.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define CELL_HEIGHT 128

/**
 * @brief
 * Hauteur d'une raquette. À utiliser pour la création des raquettes.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define PADDLE_HEIGHT 64

/**
 * @brief
 * Largeur d'une raquette. À utiliser pour la création des raquettes.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define PADDLE_WIDTH 243

/**
 * @brief
 * Largeur d'une petite raquette. À utiliser pour la gestion des bonus qui
 * réduisent la taille de la raquette.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define PADDLE_SMALL_WIDTH 115

/**
 * @brief
 * Largeur d'une grande raquette. À utiliser pour la gestion des bonus qui
 * agrandissent la taille de la raquette.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define PADDLE_LARGE_WIDTH 347
/**
 * @brief
 * Largeur d'un bonus (hors bonus de vie). À utiliser pour la création des
 * bonus.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define BONUS_WIDTH 242

/**
 * @brief
 * Hauteur d'un bonus (hors bonus de vie). À utiliser pour la création des
 * bonus.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define BONUS_HEIGHT 64

/**
 * @brief
 * Largeur d'un bonus de vie. À utiliser pour la création des bonus de vie.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define HEALTH_WIDTH 96

/**
 * @brief
 * Hauteur d'un bonus de vie. À utiliser pour la création des bonus de vie.
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define HEALTH_HEIGHT 96

/**
 * @brief
 * Rayon d'une balle. À utiliser pour la création des balles et les calculs de
 * collisions.
 *
 * @remark
 * La balle est représentée par un rectangle de largeur et de hauteur égales à
 * BALL_RADIUS * 2;
 *
 * @attention
 * Ne pas changer cette valeur!
 */
#define BALL_RADIUS 32

/**
 * @brief
 * Vitesse de la balle. À utiliser pour la création des balles.
 *
 * @remark
 * Peut-être changé pour rendre le jeu plus facile ou plus difficile.
 */
#define BALL_SPEED 12

/**
 * @brief
 * Vitesse de déplacement d'un bonus en valeur absolue.
 */
#define BONUS_SPEED 6

/**
 * @brief
 * Vitesse de déplacement d'une brique en valeur absolue.
 */
#define BRICK_SPEED 4

/**
 * @brief
 * Vitesse de base de déplacement d'une raquette en valeur absolue.
 *
 * @remark
 * Les bonus affectent la vitesse de déplacement de la raquette:
 * - en multipliant cette valeur par 2 (bonus de vitesse)
 * - en la divisant par 2 (bonus de ralentissement).
 */
#define PADDLE_BASE_SPEED 8

/********************************************************/
/*+ Définition du type utilisé pour représenter un jeu +*/
/********************************************************/

/**
 * @brief
 * Les deux modes de jeu disponibles.
 */
typedef enum {
    GAME_PONG,   //!< Mode de jeu Pong (pas de briques, les bonus sont générés
                 //!< automatiquement de façon aléatoire).
    GAME_BRICKS, //!< Mode de jeu Briques (les bonus sont générés aléatoirement
                 //!< quand une brique est détruite).
    GAME_SIZE
} game_mode;

/**
 * @brief
 * Structure représentant l'état du jeu, y compris le plateau de jeu, les
 * briques, les balles, les raquettes.
 *
 * @remark
 * Le plateau est composé de nb_columns x nb_rows cellules. Chaque cellule est
 * de taille #CELL_WIDTH x #CELL_HEIGHT et peut contenir une brique (seulement
 * en mode Briques) ou être vide. Le plateau de jeu entier est donc de taille
 * (#CELL_WIDTH * nb_columns) x (#CELL_HEIGHT * nb_rows).
 */
typedef struct {
    // Propriétés générales du jeu
    int nb_columns; //!< Nombre de colonnes du plateau de jeu.
    int nb_rows;    //!< Nombre de lignes du plateau de jeu.
    game_mode mode; //!< Mode de jeu (Pong ou Briques).

    // Raquettes des joueurs (numérotées par 0 et 1)
    paddle
        *paddles[2]; //!< Tableau contenant les deux raquettes du jeu (NULL si
                     //!< une raquette n'est pas utilisée dans le mode de jeu).
    short player_modes[2]; //!< Tableau contenant les modes de jeu des deux
                           //!< joueurs (0: pas de joueur, 1: joueur contrôlé
                           //!< par l'IA, 2: joueur contrôlé par un humain).

    // Balles présentes sur le plateau de jeu.
    ball **ball_list; //!< Tableau des balles présentes sur le plateau de jeu.
    int size_balls;   //!< Taille du tableau des balles.
    int nb_balls; //!< Nombre de balles actuellement présentes sur le plateau de
                  //!< jeu (elles sont stockées dans les nb_balls premières
                  //!< cases de tableau ball_list).

    // Bonus présents sur le plateau de jeu.
    bool bonuses; //!< Indique si les bonus sont activés ou non dans le jeu.
    bonus **bonus_list; //!< Tableau des bonus qui apparaissent sur le plateau
                        //!< de jeu.
    int size_bonus;     //!< Taille du tableau des bonus.
    int nb_bonus; //!< Nombre de bonus actuellement présents sur le plateau de
                  //!< jeu (ils sont stockés dans les nb_bonus premières cases
                  //!< de tableau bonus_list).

    // Briques présentes sur le plateau de jeu (uniquement en mode Briques).
    brick **brick_list; //!< Tableau contenant toutes les briques présentes sur
                        //!< le plateau de jeu.
    int size_bricks;    //!< Taille du tableau brick_list.
    int nb_bricks; //!< Nombre de briques restantes sur le plateau (elles sont
                   //!< stockées dans les nb_bricks premières cases de tableau
                   //!< brick_list).
    int *board;   //!< Tableau de taille nb_columns x nb_rows. La cellule (i, j)
                  //!< du plateau de jeu correspond à la case board[i + j *
                  //!< nb_columns], qui contient -1 si la cellule est vide, ou
                  //!< l'indice de la brique présente dans cette cellule (cette
                  //!< brique est stockée dans le tableau brick_list),
    int topspace; //!< Espace entre le haut du plateau de jeu et la première
                  //!< rangée de briques (utilisé pour les bonus de gravité).
    int bottomspace; //!< Espace entre le bas du plateau de jeu et la dernière
                     //!< rangée de briques (utilisé pour les bonus de gravité).
} game;

/**
 * @brief Libération d'un jeu.
 *
 * @remark
 * Les fonctions de création sont écrite dans game_pong.c et game_bricks.c. La
 * fonction de libération est écrite dans game.c car elle est commune aux deux
 * modes de jeu.
 */
void free_game(game *the_game //!< Le jeu.
);

/**
 * @brief Modifie le déplacement de la raquette du joueur spécifié (si il
 * existe).
 *
 * @details
 * La fonction devra mettre à jour la vitesse de déplacement de la raquette du
 * joueur spécifié en fonction de la direction donnée en paramètre. Si @p dir
 * est égal à -1, la raquette doit se déplacer vers la gauche, si dir est égal à
 * 1, elle doit se déplacer vers la droite, sinon elle doit s'arrêter. La valeur
 * de vitesse de déplacement doit être égale à #PADDLE_BASE_SPEED (ou à sa
 * valeur modifiée par les bonus) dans la direction indiquée.
 */
void game_move_player(game *g,  //!< Le jeu.
                      short p,  //!< Numéro du joueur (0 ou 1).
                      short dir //!< Direction du déplacement (-1 pour gauche, 1
                                //!< pour droite, 0 pour arrêt).
);

/**
 * @brief Bouge tous les objets du jeu selon leur vitesse : les raquettes, les
 * balles, les bonus et aussi les briques quand le bonus de gravité est actif.
 *
 * @details
 * Les objets sont déplacés en additionnant leur vitesse à leur position. Cette
 * fonction est appelée par l'interface à chaque tour de la boucle de jeu après
 * avoir pris en compte les actions de l'utilisateur.
 *
 * @attention
 * Pour les mouvements des raquettes, il faut veiller à ce que les raquettes ne
 * sortent pas du plateau de jeu.
 */
void game_apply_moves(game *game //!< Le jeu.
);
/**
 * @brief
 * Ajoute un nouveau bonus au jeu, à une coordonnée horizontale aléatoire au
 * centre du plateau. Utilisé dans le mode Pong pour générer des bonus
 * aléatoires pendant la partie.
 *
 * @details
 * Le bonus se déplacera ensuite verticalement vers le bas ou vers le haut selon
 * les joueurs présents dans le jeu :
 * - si il n'y a qu'un seul joueur, le bonus se déplacera vers ce joueur,
 * - sinon il se déplacera dans une direction aléatoire.
 *
 * @details
 * Cette fonction est appelée par l'interface régulièrement pendant la boucle de
 * jeu après game_apply_moves().
 */
void game_place_bonus_pong(game *g //!< Le jeu.
);

/**
 * @brief
 * Traite les collisions des balles avec les murs, les raquettes et les briques
 * et les collisions des bonus avec les raquettes.
 *
 * @details
 * Cette fonction est appelée à chaque tour de la boucle de jeu après
 * game_apply_moves() pour mettre à jour l'état du jeu en fonction des
 * différentes collisions qui peuvent se produire entre les objets du jeu. Elle
 * supprime également les balles et les bonus qui sortent du plateau de jeu.
 * Elle génère aussi une nouvelle balle si toutes les balles ont été perdues et
 * que le jeu n'est pas terminé.
 *
 * @remark
 * Cette fonction doit appeler ball_hits_wall, ball_hits_paddle et
 * ball_hits_brick pour gérer les différentes collisions.
 */
void game_handle_collisions(game *g //!< Le jeu.
);

#endif // GAME_H_
