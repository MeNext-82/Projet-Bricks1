#ifndef GAME_GEOMETRY_H_
#define GAME_GEOMETRY_H_

/**
 * @file game_geometry.h
 *
 * @brief
 * Contient les fonctions et les macros pour les calculs de géométrie du jeu,
 * notamment les collisions entre la balle et les briques, les murs et les
 * raquettes.
 */

/*   ____ _____ ___  __  __ _____ _____ ______   __ */
/*  / ___| ____/ _ \|  \/  | ____|_   _|  _ \ \ / / */
/* | |  _|  _|| | | | |\/| |  _|   | | | |_) \ V /  */
/* | |_| | |__| |_| | |  | | |___  | | |  _ < | |   */
/*  \____|_____\___/|_|  |_|_____| |_| |_| \_\|_|   */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/****************/
/*+ Rectangles +*/
/****************/

/**
 * @brief
 * Structure représentant un rectangle sur le plateau de jeu. Utilisé dans tous
 * les types qui représentent un objet du jeu (balles, briques, débris, bonus,
 * ...).
 *
 * @details
 * Pour chaque objet, on utilise un rectangle qui délimite la zone occupée par
 * l'objet sur le plateau de jeu. Ce rectangle est défini par les coordonnées du
 * coin supérieur gauche (x, y) et par la largeur (w) et la hauteur (h).
 *
 * @attention
 * Les coordonnées (x, y) correspondent au COIN SUPÉRIEUR GAUCHE du rectangle,
 * PAS À SON CENTRE.
 */
typedef struct {
    double x; // Coordonnée horizontale du coin supérieur gauche du rectangle.
    double y; // Coordonnée verticale du coin supérieur gauche du rectangle.
    int w;    // Largeur du rectangle.
    int h;    // Hauteur du rectangle.
} rectangle;

/**
 * @brief
 * Fonction qui vérifie si deux rectangles se chevauchent.
 *
 * @return true si les rectangles se chevauchent, false sinon.
 */
bool rectangles_overlap(rectangle *r1, //!< Premier rectangle.
                        rectangle *r2  //!< Deuxième rectangle.
);

/**************/
/*+ Raquette +*/
/**************/

/**
 * @brief
 * Catégories de vitesse d'une raquette.
 *
 * @details
 * La vitesse réelle de la raquette (stockée dans le champ \ref paddle.speed_x)
 * est la suivante :
 * - La vitesse correspondant à #SPEED_NORMAL correspond à la constante
 * #PADDLE_BASE_SPEED définie dans game.h.
 * - La vitesse correspondant à #SPEED_SLOW correspond à la moitié de
 * #PADDLE_BASE_SPEED.
 * - La vitesse correspondant à #SPEED_FAST correspond au double de
 * #PADDLE_BASE_SPEED.
 *
 * @remark
 * Les vitesses SPEED_SLOW et SPEED_FAST sont utilisées pour les bonus de
 * ralentissement et de vitesse.
 */
typedef enum {
    SPEED_NORMAL, //!< Raquette normale.
    SPEED_SLOW,   //!< Raquette lente.
    SPEED_FAST    //!< Raquette rapide.
} speed_mode;

/**
 * @brief
 * Catégories de taille d'une raquette.
 *
 * @details
 * La taille réelle de la raquette (stockée dans le \ref paddle.champ w) est la
 * suivante :
 * - La taille correspondant à #PADDLE_NORMAL correspond à la constante
 * #PADDLE_WIDTH définie dans game.h.
 * - La taille correspondant à #PADDLE_SMALL correspond à #PADDLE_SMALL_WIDTH.
 * - La taille correspondant à #PADDLE_LARGE correspond au #PADDLE_LARGE_WIDTH.
 */
typedef enum {
    PADDLE_NORMAL, //!< Raquette normale.
    PADDLE_SMALL,  //!< Raquette petite.
    PADDLE_LARGE   //!< Raquette grande.
} paddle_size;

/**
 * @brief
 * Structure représentant une raquette dans le jeu.
 */
typedef struct {
    rectangle rect;   //!< Rectangle représentant la position et la taille de la
                      //!< raquette.
    double speed_x;   //!< Vitesse de la raquette (positive vers la droite,
                      //!< négative vers la gauche).
    paddle_size size; //!< Taille de la raquette.
    speed_mode smode; //!< Mode de vitesse de la raquette.
    bool bottom;      //!< Indique si la raquette est en bas (true) ou en haut
                      //!< (false) du plateau de jeu.
    int health;       //!< Nombre de points de vie de la raquette.
    int score;        //!< Score du joueur.
    int goals;        //!< Nombre de buts marqués par le joueur.
    int bonuses;      //!< Nombre de bonus capturés par le joueur.
    int bricks;       //!< Nombre de briques détruites par le joueur.
} paddle;

/**
 * @brief
 * Fonction de création d'une raquette avec les paramètres spécifiés.
 *
 * @return Un pointeur vers la raquette créée.
 */
paddle *create_paddle(
    bool bottom, //!< Indique si la raquette est en bas (true) ou en haut
                 //!< (false) du plateau de jeu.
    int nb_rows, //!< Nombre de rangées de briques sur le plateau (la hauteur du
                 //!< plateau est #CELL_HEIGHT * nb_rows).
    int nb_columns //!< Nombre de colonnes de briques sur le plateau (la largeur
                   //!< du plateau est #CELL_WIDTH * nb_columns).
);

/************/
/*+ Balles +*/
/************/

/**
 * @brief
 */
typedef enum {
    POW_RED,   //!< Change la couleur de la balle.
    POW_GREEN, //!< Change la couleur de la balle.
    POW_NONE,  //!< Aucun bonus.

} power;

/**
 * @brief
 * Structure représentant une balle dans le jeu.
 */
typedef struct {
    rectangle
        rect; // Rectangle représentant la position et la taille de la balle.
    double speed_x; // Vitesse horizontale de la balle (positive vers la droite,
                    // négative vers la gauche).
    double speed_y; // Vitesse verticale de la balle (positive vers le bas,
                    // négative vers le haut).
    int last_hit;   // Indique le dernier côté qui a touché la balle (0 pour bas
                    // ou 1 pour haut), ou -1 si la balle n'a pas encore été
                    // touchée par un joueur.
    power powerup; // Bonus actif sur la balle (#POW_NONE si aucun bonus actif).
} ball;

/**
 * @brief
 * Fonction de création d'une balle avec les paramètres spécifiés.
 *
 * @return Un pointeur vers la balle créée.
 */
ball *create_ball(
    double x, // Coordonnée horizontale du coin supérieur gauche de la balle.
    double y, // Coordonnée verticale du coin supérieur gauche de la balle.
    bool top  // Indique si la balle est créée en haut (true) ou en bas (false)
              // du plateau de jeu, ce qui détermine la direction initiale de la
              // balle.
);

/**
 * @brief
 * Fonction qui calcule la norme (longueur) du vecteur vitesse d'une balle.
 *
 * @return La norme du vecteur vitesse de la balle.
 */
double ball_speednorm(ball *b);

/*************/
/*+ Briques +*/
/*************/

/**
 * @brief
 * Couleurs possibles pour les briques.
 *
 * @attention
 * COLSIZE n'est pas une couleur, mais une constante indiquant le nombre de
 * couleurs disponibles. Ne pas l'utiliser pour créer des briques.
 */
typedef enum {
    BLUE,
    LIGHTGREEN,
    PURPLE,
    RED,
    ORANGE,
    LIGHTBLUE,
    YELLOW,
    DARKGREEN,
    GRAY,
    BROWN,
    COLSIZE
} brick_color;

/**
 * @brief
 * Structure représentant une brique dans le jeu.
 */
typedef struct {
    // Propriétés de la brique
    brick_color color; //!< Couleur de la brique.
    rectangle rect; //!< Rectangle représentant la position et la taille de la
                    // brique. La largeur et la hauteur sont généralement égales
                    // à #CELL_X et #CELL_Y, mais peuvent être ajustées pour les
                    // briques plus résistantes.
    int health;     //!< Nombre de coups restants pour casser la brique.
    int max_health; //!< Nombre de coups nécessaires pour casser la brique.
    int origin;     //!< Position d'origine de la brique sur le plateau de jeu
                    //(index dans le tableau board). Utile pour les briques en
                    // mouvement qui changent de position sur le plateau.

    // Propriétés de l'animation de la brique
    int nb_frames; //!< Nombre de frames restantes pour le mouvement de la
                   // brique (0 si la brique n'est pas en mouvement).
    double speed;  //!< Vitesse verticale.
} brick;

/**
 * @brief
 * Fonction de création d'une brique avec les paramètres spécifiés.
 *
 * @return Un pointeur vers la brique créée.
 */
brick *create_brick(
    double x, //!< Coordonnée horizontale du coin supérieur gauche de la brique.
    double y, //!< Coordonnée verticale du coin supérieur gauche de la brique.
    brick_color color, //!< Couleur de la brique.
    int max_health,    //!< Nombre de coups nécessaires pour casser la brique.
    int origin //!< Position d'origine de la brique sur le plateau de jeu.
);

/***********/
/*+ Bonus +*/
/***********/

typedef enum {
    // Bonus disponibles en mode Pong ET en mode Briques
    BNS_SHRINK,   //!< Réduit la taille de la raquette.
    BNS_GROW,     //!< Agrandit la taille de la raquette.
    BNS_SPEEDUP,  //!< Augmente la vitesse de la raquette.
    BNS_SLOWDOWN, //!< Diminue la vitesse de la raquette.
    BNS_SCORE50,  //!< Donne des points au joueur.
    BNS_SCORE100, //!< Donne des points au joueur.
    BNS_SCORE250, //!< Donne des points au joueur.
    BNS_SCORE500, //!< Donne des points au joueur.
    BNS_HEALTH,   //!< Donne une vie supplémentaire au joueur.
    BNS_NEWBALL,  //!< Ajoute une balle supplémentaire.

    // Bonus spécifique au mode briques
    BNS_COLORBALL,  //!< Ajoute une balle verte (quand celle balles détruit une
                    //!< brique, elle détruit également toutes les briques
                    //!< adjacentes de la même couleur).
    BNS_STRONGBALL, //!< Ajoute une balle rouge (détruit n'importe quelle brique
                    //!< en un seul coup).
    BNS_GRAVITY,    //!< Les briques tombent dans la direction du joueur qui a
                    //!< touché la balle en dernier.
    BNS_SIZE //!< Nombre de bonus possibles (ne pas utiliser pour créer des
             //!< bonus).
} bonus_type;

typedef struct {
    rectangle rect; //!< Rectangle représentant la position et la taille du
                    //!< bonus. La largeur et la hauteur sont généralement
                    //!< égales à #CELL_X et #CELL_Y, mais peuvent être ajustées
                    //!< pour les bonus plus grands ou plus petits.
    bonus_type type; //!< Type du bonus.
    double speed_y;  //!< Vitesse verticale du bonus (positive vers le bas,
                     //!< négative vers le haut). Les bonus tombent dans la
                     //!< direction du joueur qui a touché la balle en dernier.
    unsigned int frame; //!< Frame actuelle de l'animation du bonus (0 à 3). Ce
                        //!< champ est géré par l'interface graphique: NE PAS Y
                        //!< TOUCHER DANS VOTRE CODE.
} bonus;

/**
 * @brief
 * Fonction de création d'un bonus aléatoire avec les paramètres spécifiés.
 *
 * @remark
 * En mode pong, les bonus spécifiques au mode briques (BNS_COLORBALL,
 * BNS_STRONGBALL et BNS_GRAVITY) ne doivent pas être générés.
 *
 * @return Un pointeur vers le bonus créé.
 */
bonus *create_random_bonus(
    double x,  //!< Coordonnée horizontale du coin supérieur gauche du bonus.
    double y,  //!< Coordonnée verticale du coin supérieur gauche du bonus.
    bool down, //!< Indique si le bonus tombe vers le bas (true) ou vers le haut
               //!< (false).
    bool bricks //!< Indique si le jeu est en mode briques (true) ou pong
                //!< (false).
);

#endif // GAME_GEOMETRY_H_
