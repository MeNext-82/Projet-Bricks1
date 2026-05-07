#ifndef UTILS_H_
#define UTILS_H_

#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Macro pour calculer le maximum de deux valeurs.
 */
#define max(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Macro pour calculer le minimum de deux valeurs.
 */
#define min(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief Génère un nombre aléatoire de type double entre @p min et @p max.
 *
 * @return Un nombre aléatoire de type double entre @p min et @p max.
 */
double random_double(double min, //!< La valeur minimale du double aléatoire.
                     double max  //!< La valeur maximale du double aléatoire.
);

/***********************/
/*+ Compteur de temps +*/
/***********************/

/**
 * @brief
 * Initialisation du compteur de temps.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez pas l'appeler vous
 * même.
 */
void init_time_counter(void);

/**
 * @brief
 * Initialisation du compteur de temps à une valeur spécifique.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez pas l'appeler vous
 * même.
 */
void init_time_counter_start(
    long start //!< Le temps en millisecondes auquel le compteur doit démarrer.
);
/**
 * @brief
 * Met le compteur de temps en pause.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez pas l'appeler vous
 * même.
 */
void pause_time_counter(void);

/**
 * @brief
 * Reprend le compteur de temps après une pause.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez pas l'appeler vous
 * même.
 */
void resume_time_counter(void);

/**
 * @brief
 * Récupère la valeur du compteur de temps en millisecondes.
 *
 * @return
 * La valeur du compteur de temps en millisecondes.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez pas l'appeler vous
 * même.
 */
int get_time_counter(void);

#endif // UTILS_H_
