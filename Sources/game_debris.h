#ifndef DEBRIS_H
#define DEBRIS_H

/**
 * @file game_debris.h
 *
 * @brief
 * Ce module gère les débris qui apparaissent à l'écran lorsqu'une brique est
 * détruite. Les débris sont de petits rectangles qui se déplacent dans des
 * directions aléatoires à partir de la position de la brique détruite, et
 * disparaissent après un certain nombre de frames.
 *
 * @remark
 * Les fonctions de ce module sont déjà écrites, vous n'avez pas à les
 * implémenter vous même. Vous devez cependant appeler add_debris() dans la
 * fonction game_remove_brick() du module game_bricks.c pour ajouter des débris
 * à chaque fois qu'une brique est détruite.
 */

#include "alloc.h"
#include "game_geometry.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*  ____       _          _      */
/* |  _ \  ___| |__  _ __(_)___  */
/* | | | |/ _ \ '_ \| '__| / __| */
/* | |_| |  __/ |_) | |  | \__ \ */
/* |____/ \___|_.__/|_|  |_|___/ */

/**
 * @brief
 * Nombre de frames pendant lesquelles les débris restent à l'écran avant de
 * disparaître.
 */
#define DEBRIS_MAX_FRAME 60

/**
 * @brief Structure représentant un débris à afficher à l'écran.
 */
typedef struct {
    rectangle rect; //!< Position et taille du débris
    double dx;      //!< Vitesse horizontale du débris
    double dy;      //!< Vitesse verticale du débris
    int frame;      //!< Nombre de frames restantes avant que le débris ne
                    //!< disparaisse
} debris;

/**
 * @brief
 * Tableau des débris à afficher à l'écran. debris_list est un tableau dynamique
 * de pointeurs, qui contient tous les débris actuellement à afficher à l'écran.
 */
extern debris **debris_list;

/**
 * @brief
 * Taille du tableau \ref debris_list.
 */
extern int size_debris;

/**
 * @brief
 * Nombre de débris dans le tableau \ref debris_list.
 */
extern int nb_debris;

/**
 * @brief
 * Initialise le système de gestion des débris. Cette fonction doit est appelée
 * par l'interface.
 */
void init_debris(void);

/**
 * @brief
 * Ajoute des débris à partir d'un rectangle donné correspondant à la position
 * et la taille de la brique détruite. Les débris sont générés à partir du
 * rectangle, avec des vitesses aléatoires
 *
 * @remark
 * C'est la seule fonction de ce module que vous devez appeler dans votre code,
 * à chaque fois qu'une brique est détruite (dans la fonction
 * game_remove_brick() du module game_bricks.c).
 */
void add_debris(rectangle *rect //!< Le rectangle correspondant à la position et
                                //!< la taille de la brique détruite.
);

/**
 * @brief
 * Met à jour l'état des débris. Cette fonction est appelée à chaque frame par
 * l'interface.
 */
void update_debris(void);

/**
 * @brief
 * Libère la mémoire occupée par les débris. Cette fonction est appelée par
 * l'interface lorsque le jeu est réinitialisé ou lorsqu'on quitte le jeu.
 */
void free_debris(void);

/**
 * @brief
 * Réinitialise le système de gestion des débris en supprimant tous les débris
 * actuellement à l'écran. Cette fonction est appelée par l'interface lorsque le
 * jeu est réinitialisé.
 */
void reset_debris(void);

#endif // DEBRIS_H
