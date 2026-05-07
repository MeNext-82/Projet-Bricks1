#ifndef GAME_BRICKS_H_
#define GAME_BRICKS_H_

/**
 * @file game_bricks.h
 * @brief Fonctions utilisées pour gérer un jeu de Briques, c'est à dire un jeu
 * avec des briques, des bonus et des raquettes.
 */

#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*  ____  ____  ___ ____ _  ______   */
/* | __ )|  _ \|_ _/ ___| |/ / ___|  */
/* |  _ \| |_) || | |   | ' /\___ \  */
/* | |_) |  _ < | | |___| . \ ___) | */
/* |____/|_| \_\___\____|_|\_\____/  */

/******************************/
/*+ Création et fin d'un jeu +*/
/******************************/

/**
 * @brief
 * Fonction de création d'un nouveau jeu de Briques avec les paramètres
 * spécifiés.
 *
 * @remark
 * On utilisera la fonction game_add_brick pour ajouter les briques au jeu.
 *
 * @details
 * La génération est aléatoire.
 *
 * @return Un pointeur vers le jeu créé.
 */
game *create_random_brick_game(
    int nb_columns, //!< Nombre de colonnes du plateau de jeu.
    int nb_rows,    //!< Nombre de lignes du plateau de jeu.
    int topspace,   //!< Espace entre le haut du plateau de jeu et la première
                    // rangée de briques. Aucune brique ne sera générée dans cet
                    // espace.
    int bottomspace, //!< Espace entre le bas du plateau de jeu et la dernière
                     // rangée de briques. Aucune brique ne sera générée dans
                     // cet espace.
    short player_one_mode, //!< Mode de jeu du premier joueur (0: pas de premier
                           //!< joueur, 1: premier joueur contrôlé par l'IA, 2:
                           //!< premier joueur contrôlé par un humain).
    short
        player_two_mode, //!< Mode de jeu du deuxième joueur (0: pas de deuxième
                         //!< joueur, 1: deuxième joueur contrôlé par l'IA, 2:
                         //!< deuxième joueur contrôlé par un humain).
    int nb_colors,       //!< Nombre de couleurs différentes pour les briques.
    int max_health       //!< Santé maximale des briques.
);

/**
 * @brief
 * Fonction de création d'un nouveau jeu à partir d'un fichier de configuration.
 *
 * @remark
 * On utilisera la fonction game_add_brick() pour ajouter les briques au jeu.
 *
 * @return Un pointeur vers le jeu créé.
 */
game *create_newgame_file(
    char **input, //!< Tableau des lignes extrait du fichier de configuration du
                  //!< jeu, contenant les dimensions du plateau et la
                  //!< disposition des briques.
    int size,     //!< Taille du tableau input (nombre de lignes).
    short player_one_mode, //!< Mode de jeu du premier joueur (0: pas de premier
                           //!< joueur, 1: premier joueur contrôlé par l'IA, 2:
                           //!< premier joueur contrôlé par un humain).
    short player_two_mode  //!< Mode de jeu du deuxième joueur (0: pas de
                           //!< deuxième joueur, 1: deuxième joueur contrôlé par
    //!< l'IA, 2: deuxième joueur contrôlé par un humain).
);

/**
 * @brief Teste si le jeu de Briques est terminé.
 *
 * @details Un jeu de briques prend fin si toutes les briques sont détruites
 * (victoire) ou si tous les joueurs ont perdu (défaite).
 *
 * @remark La fonction doit stocker dans @p win la valeur true si le joueur a
 * gagné, ou false s'il a perdu.
 *
 * @return true si le jeu est terminé, false sinon.
 */
bool game_brick_end(
    game *g,  //!< Le jeu.
    bool *win //!< Pointeur vers une variable dans laquelle la fonction doit
              //!< stocker true si le joueur a gagné, ou false s'il a perdu, si
              //!< le jeu est terminé.
);

/**
 * @brief Implémentation de l'IA en mode Briques.
 *
 * @details La fonction choisit une direction de déplacement pour la raquette du
 * joueur i contrôlé par l'IA, et modifie le paramètre \ref paddle.speed_x de la
 * raquette en conséquence. L'IA suit simplement la balle avec la raquette. Si
 * la balle est à gauche de la raquette, elle se déplace vers la gauche, si elle
 * est à droite, elle se déplace vers la droite, sinon elle suit la vitesse
 * horizontale de la balle.
 *
 */
bool game_brickia(game *g, //!< Le jeu.
                  short i  //!< Joueur contrôlé par l'IA (0 pour le joueur 1, 1
                           //!< pour le joueur 2).
);

/*************************/
/*+ Gestion des briques +*/
/*************************/

/**
 * @brief Ajoute une brique au jeu avec les caractéristiques spécifiées.
 *
 * @remark
 * La fonction doit allouer une nouvelle brique et l'ajouter au tableau
 * \ref game.brick_list du jeu. Si le tableau \ref game.brick_list est plein
 * (c'est à dire si \ref game.nb_bricks est égal à \ref game.size_bricks), la
 * fonction doit doubler la taille du tableau \ref game.brick_list pour y faire
 * de la place avant d'ajouter la nouvelle brique.
 */
void game_add_brick(
    game *g, //!< Le jeu.
    int x,   //!< La colonne de la brique à ajouter (entre 0 et nb_columns - 1).
    int y,   //!< La ligne de la brique à ajouter (entre 0 et nb_rows - 1).
    brick_color color, //!< La couleur de la brique.
    int health         //!< La santé de la brique.
);

/**
 * @brief Retire la brique d'indice i du jeu, en mettant à jour l'état du jeu en
 * conséquence (score du joueur, génération d'un bonus, etc.).
 *
 * @details
 * La fonction doit libérer la mémoire occupée par la brique, la retirer du
 * tableau \ref game.brick_list. Pour combler le trou, on réorganisera le
 * tableau
 * \ref game.brick_list de manière en remplaçant la brique supprimée par la
 * dernière brique du tableau (celle d'indice \ref game.nb_bricks - 1). Enfin,
 * la fonction doit décrémenter le nombre de briques \ref game.nb_bricks (on a
 * retiré une brique du jeu).
 *
 * @details
 * Lorsque une brique est supprimée, on doit effectuer les opérations suivantes
 * :
 * - Ajouter des débris pour la brique détruite (en utilisant la fonction
 * add_debris(), voir game_debris.h).
 * - Mettre à jour le score du joueur qui a détruit la brique (il gagne 500
 * points) et son nombre de briques détruites.
 * - Générer un bonus avec une probabilité de 50% (en utilisant la fonction
 * game_add_bonus(), voir game_bonus.h).
 *
 * @remark
 * Le paramètre @p last_hit indique le dernier joueur qui a touché la balle.
 * Cela permet de savoir quel joueur a détruit la brique et doit donc être
 * récompensé par des points et un bonus. @p last_hit vaut 0 si c'est le joueur
 * 1 qui a touché la balle, 1 si c'est le joueur 2, ou -1 si la balle n'a pas
 * encore touché de raquette.
 */
void game_remove_brick(
    game *g, //!< Le jeu.
    int i,   //!< L'indice de la brique à retirer dans le tableau brick_list.
    short last_hit //!< Le dernier joueur qui a touché la balle (0 pour le
                   // joueur 1, 1 pour le joueur 2, -1 si la balle n'a pas
                   // encore touché de raquette).
);

/**
 * @brief Teste si une balle touche l'une des briques présentes sur le plateau
 * de jeu et change l'état du jeu en conséquence (inversion de la vitesse de la
 * balle, diminution de la santé de la brique, etc.).
 *
 * @details
 * La fonction devra passer en revue toutes les briques présentes sur le plateau
 * de jeu pour vérifier si la balle touche l'une d'entre elles.
 *
 * @remark
 * On utilisera la fonction game_remove_brick si la brique touchée est détruite
 * (sa santé devient nulle ou négative).
 *
 * @return true si la balle touche une brique, false sinon.
 */
bool ball_hits_brick(game *g, //!< Le jeu.
                     int i    //!< L'indice de la balle dans le tableau.
);

/**
 * @brief Applique la gravité aux briques du jeu, en les faisant tomber vers le
 * bas ou vers le haut du plateau de jeu.
 */
void game_gravity(game *g, //!< Le jeu.
                  bool bot //!< Si true, la gravité est appliquée vers le bas
                           //!< (les briques tombent vers le bas du plateau de
                           //!< jeu), sinon elle est appliquée vers le haut (les
                           //!< briques tombent vers le haut du plateau de jeu).
);

#endif // GAME_BRICKS_H_
