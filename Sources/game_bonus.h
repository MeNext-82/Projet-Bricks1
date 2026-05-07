#ifndef GAME_BONUS_H_
#define GAME_BONUS_H_

/**
 * @file game_bonus.h
 * @brief Fonctions utilisées pour gérer les bonus dans les jeux de Pong et de
 * Briques
 */

/*  ____   ___  _   _ _   _ ____   */
/* | __ ) / _ \| \ | | | | / ___|  */
/* |  _ \| | | |  \| | | | \___ \  */
/* | |_) | |_| | |\  | |_| |___) | */
/* |____/ \___/|_| \_|\___/|____/  */

#include "game.h"

/***********************/
/*+ Gestion des bonus +*/
/***********************/

/**
 * @brief
 * Ajoute un bonus au jeu, en le créant à la position (x, y).
 *
 * @remark
 * La fonction doit allouer un nouveau bonus et l'ajouter au tableau \ref
 * game.bonus_list du jeu. Si le tableau \ref game.bonus_list est plein (c'est à
 * dire si \ref game.nb_bonus est égal à size_bonus), la fonction doit doubler
 * la taille du tableau \ref game.bonus_list pour y faire de la place avant
 * d'ajouter le nouveau bonus.
 */
void game_add_bonus(
    game *g,  //!< Le jeu.
    double x, //!< La position horizontale du bonus sur le plateau de jeu.
    double y, //!< La position verticale du bonus sur le plateau de jeu.
    bool down //!< Indique si le bonus doit descendre (true) ou monter (false)
              // sur le plateau de jeu.
);

/**
 * @brief
 * Supprime le bonus d'indice i du jeu.
 *
 * @details
 * La fonction doit libérer la mémoire occupée par le bonus, le retirer du
 * tableau \ref game.bonus_list. Pour combler le trou, on réorganisera le
 * tableau
 * \ref game.bonus_list de manière en remplaçant le bonus supprimé par le
 * dernier bonus du tableau (celui d'indice \ref game.nb_bonus - 1). Enfin, la
 * fonction doit décrémenter le nombre de bonus \ref game.nb_bonus (on a retiré
 * un bonus du jeu).
 */
void game_remove_bonus(game *g, //!< Le jeu.
                       int i //!< L'indice du bonus à supprimer dans le tableau
                             //!< \ref game.bonus_list.
);

/**
 * @brief
 * Teste si une raquette touche un bonus présent sur le plateau de jeu et change
 * l'état du jeu en conséquence (activation du bonus, suppression du bonus,
 * etc.).
 *
 * @details
 * Si une raquette touche un bonus, le bonus est activé et supprimé du plateau
 * de jeu. L'effet du bonus dépend de son type (voir la structure \ref bonus
 * dans game_geometry.h).
 *
 * @return true si la raquette touche un bonus, false sinon.
 */
bool game_capture_bonus(
    game *g,  //!< Le jeu.
    paddle *p //!< La raquette qui pourrait toucher un bonus.
);

#endif // GAME_BONUS_H_
