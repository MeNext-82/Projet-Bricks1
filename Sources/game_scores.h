/**
 * @file game_scores.h
 *
 * @brief
 * Gestion des meilleurs scores en mode classique. Contient une fonction pour
 * charger, enregistrer et trier les meilleurs scores du fichier de scores
 *
 * @details
 * Vous devez respecter le format spécifié pour le fichier de scores afin de
 * garantir un bon chargement et sauvegarde des scores (voir la
 * documentation du projet pour plus de détails).
 */

#ifndef _GAME_SCORES_H_
#define _GAME_SCORES_H_

/*  _   _ _       _       ____                           */
/* | | | (_) __ _| |__   / ___|  ___ ___  _ __ ___  ___  */
/* | |_| | |/ _` | '_ \  \___ \ / __/ _ \| '__/ _ \/ __| */
/* |  _  | | (_| | | | |  ___) | (_| (_) | | |  __/\__ \ */
/* |_| |_|_|\__, |_| |_| |____/ \___\___/|_|  \___||___/ */
/*          |___/                                        */

#include "alloc.h"
#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** @brief
 * Paramètres affichés dans le tableau de scores.
 */
typedef enum {
    SC_SCORE,   //!< Score global fu joueur.
    SC_GOALS,   //!< Nombre de buts marqués par le joueur.
    SC_BONUS,   //!< Nombre de bonus collectés par le joueur.
    SC_HEALTH,  //!< Santé restante du joueur.
    SC_BRICKS,  //!< Nombre de briques détruites par le joueur.
    SC_PLAYERS, //!< Nombre de joueurs dans la partie (1 ou 2).
    SC_TIME,    //!< Temps écoulé depuis le début de la partie (en secondes).
    SC_SIZE     //!< Nombre total de paramètres (ne pas utiliser comme un
                //!< paramètre).
} score_type;

/**
 * @brief
 * Structure représentant un tableau de scores. Elle contient les noms des
 * joueurs, leurs scores, la taille du tableau et l'indice du score du joueur
 * actuel (s'il est présent)
 *
 * @details
 * Cette structure est utilisée dans trois situations spécifiques :
 * - Quand on affiche les scores dans le menu. Dans ce cas, elle est remplie
 * avec les scores chargés depuis le fichier de scores uniquement (il n'y a pas
 * de score du joueur actuel à afficher dans le menu).
 * - Quand on affiche le score à la fin d'un jeu Pong. Dans ce cas, elle
 * contient les scores chargés depuis le fichier de scores plus le score du
 * joueur actuel.
 * - Quand on affiche le score final à la fin d'un jeu briques. Dans ce cas,
 * elle contient les scores chargés depuis le fichier de scores plus le score du
 * joueur actuel.
 *
 * @remark
 * Le tableau des noms des joueurs contient des chaînes de caractères de
 * longueur maximale 64 (y compris le caractère de fin de chaîne). Cela signifie
 * que les noms des joueurs peuvent comporter au maximum 63 caractères.
 */
typedef struct {
    char (*names)[64]; //!< Pointeur vers un tableau de chaînes de caractères
                       //!< contenant les noms des joueurs.
    int (*scores)[SC_SIZE]; //!< Pointeur vers un de tableau de tableaux
                            //!< d'entiers contenant les scores.
    int size; //!< Nombre d'entrées dans le tableau de scores (taille des
              //!< tableaux de noms et de scores).
    int player_index; //!< Index du score du joueur actuel (-1 si non présent).
    int *permutation; //!< Pointeur vers un tableau représentant l'ordre trié
                      //!< des scores.
} score_table;

/**
 * @brief
 * Appelée par l'interface pour charger un tableau de scores depuis un tableau
 * de chaînes de caractères extrait d'un fichier de scores. Si un @p
 * player_score est fourni, elle l'ajoute comme une entrée pour le joueur actuel
 * sous le nom "Player".
 *
 * @return
 * Un pointeur vers le tableau de scores créé ou NULL en cas d'erreur.
 */
score_table *load_score_table(
    char **input, //!< Tableau de chaines de caractères contenant les lignes
                  //!< lues depuis le fichier de scores.
    int size, //!< Taille du tableau de chaines de caractères (0 si le fichier
              //!< de scores n'existe pas ou est vide).
    int *player_score //!< Pointeur vers le tableau de scores du joueur actuel
                      //!< (NULL quand utilisé pour charger les meilleurs scores
                      //!< depuis le menu).
);

/**
 * @brief
 * Appelée par l'interface pour sauvegarder un tableau de scores. La fonction
 * retourne un tableau de chaînes de caractères. Chaque chaîne correspond à une
 * ligne qui sera écrite dans le fichier de scores (cette partie est faite par
 * l'interface). La fonction remplit également la taille du tableau de chaînes
 * de caractères retourné dans le paramètre size.
 *
 * @return
 * Le tableau de chaînes de caractères à écrire dans le fichier de scores ou
 * NULL en cas d'erreur.
 */
char **save_score_table(
    score_table *table, //!< Pointeur vers le tableau de scores à sauvegarder.
    const char *playername, //!< Nom choisi pour le joueur actuel (peut être
                            //!< NULL, quand aucun score de joueur actuel n'est
                            //!< chargé dans le tableau).
    int *size //!< Pointeur vers un entier dans lequel écrire la taille du
              //!< tableau de chaînes de caractères retourné.
);

/**
 * @brief
 * Appelée par l'interface pour supprimer un tableau de scores et libérer la
 * mémoire allouée.
 */
void delete_score_table(
    score_table *table //!< Pointeur vers le tableau de scores à supprimer.
);

/**
 * @brief
 * Appelée par l'interface pour trier un tableau de scores dans l'ordre
 * décroissant selon un type de score spécifié.
 */
void sort_score_table(
    score_table *table, //!< Pointeur vers le tableau de scores à trier.
    score_type type     //!< Type de score par lequel trier.
);

/**
 * @brief
 * Appelée par l'interface pour récupérer les scores du joueur gagnant à la fin
 * d'une partie de Pong.
 *
 * @details
 * Le tableau score_array pris en paramètre est supposé être de taille #SC_SIZE.
 * On doit y écrire les scores du joueur gagnant:
 * - Si le paramètre @p p est égal à 0 ou 1, la fonction récupère les scores du
 * joueur correspondant (0 pour le joueur 1, 1 pour le joueur 2) et les écrit
 * dans score_array. Si ce joueur n'est pas présent dans la partie, la fonction
 * retourne false.
 * - Sinon (typiquement si p est égal à -1), la fonction retourne false.
 */
bool get_pong_winner_score(
    game *g, //!< Pointeur vers la structure de jeu.
    short p, //!< Numéro du joueur gagnant (0 ou 1). Sinon, la fonction retourne
             //!< false.
    int *score_array // <! Pointeur vers un tableau d'entiers de taille #SC_SIZE
                     // dans lequel écrire les scores.
);

/**
 * @brief
 * Appelée par l'interface pour récupérer les scores du joueur gagnant à la fin
 * d'une partie de Briques.
 *
 * @details
 * Le tableau score_array pris en paramètre est supposé être de taille #SC_SIZE.
 * On doit y écrire les sommes des scores des joueur présents (sauf pour le
 * temps qui est commun aux deux joueurs).
 */
bool get_brick_winner_score(
    game *g,         //!< Pointeur vers la structure de jeu.
    int *score_array //!< Pointeur vers un tableau d'entiers de taille #SC_SIZE
                     //!< dans lequel écrire les scores.
);

#endif /* _GAME_SCORES_H_ */
