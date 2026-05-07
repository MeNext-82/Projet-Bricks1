/**
 * @file main.h
 * @brief Paramètres.
 *
 * @details Permet de modifier la taille de l'interface et le jeu initial.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "game.h"
// #include "gui_controller.h"
#include "gui/gui_gamevars.h"
#include "gui/gui_init_graphic.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/**
 * @brief Dimension horizontale de la fenêtre du jeu (Défaut: 1170).
 */
#define WINDOW_MAZEWIDTH 1170

/**
 * @brief Dimension verticale de la fenêtre du jeu (Défaut: 970).
 */
#define WINDOW_GAMEHEIGHT 970

/**
 * @brief Taille horizontale du jeu initial.
 */
#define INITIAL_HSIZE 200

/**
 * @brief  Taille verticale du jeu initial.
 */
#define INITIAL_VSIZE 200

#endif // MAIN_H_
