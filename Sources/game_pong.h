#ifndef GAME_PONG_H_
#define GAME_PONG_H_

/**
 * @file game_pong.h
 * @brief Fonctions utilisées pour gérer un jeu de Pong, c'est à dire un jeu
 * sans briques, avec des bonus générés aléatoirement.
 */

/*  ____   ___  _   _  ____    ____    _    __  __ _____  */
/* |  _ \ / _ \| \ | |/ ___|  / ___|  / \  |  \/  | ____| */
/* | |_) | | | |  \| | |  _  | |  _  / _ \ | |\/| |  _|   */
/* |  __/| |_| | |\  | |_| | | |_| |/ ___ \| |  | | |___  */
/* |_|    \___/|_| \_|\____|  \____/_/   \_\_|  |_|_____| */

#include "game.h"
#include "game_bricks.h"
#include "game_geometry.h"

/******************************/
/*+ Création et fin d'un jeu +*/
/******************************/

/**
 * @brief
 * Fonction de création d'un nouveau jeu de Pong avec les paramètres spécifiés.
 *
 * @details
 * La fonction doit initialiser les champs du jeu de manière appropriée pour le
 * mode Pong.
 *
 * @remark
 * On pourra utiliser les fonctions écrites plus bas pour créer les balles.
 *
 * @return Un pointeur vers le jeu créé.
 */
game *create_pong_game(
    int nb_columns,        //!< Nombre de colonnes du plateau de jeu.
    int nb_rows,           //!< Nombre de lignes du plateau de jeu.
    short player_one_mode, //!< Mode de jeu du premier joueur (0: pas de premier
                           //!< joueur, 1: premier joueur contrôlé par l'IA, 2:
                           //!< premier joueur contrôlé par un humain).
    short
        player_two_mode, //!< Mode de jeu du deuxième joueur (0: pas de deuxième
                         //!< joueur, 1: deuxième joueur contrôlé par l'IA, 2:
                         //!< deuxième joueur contrôlé par un humain).
    short nb_balls, //!< Nombre de balles à créer au début du jeu (au moins 1 et
                    //!< au plus 8, si le paramètre est supérieur à 8, il sera
                    //!< réduit à 8).
    bool bonuses    //!< Indique si les bonus sont activés ou non dans le jeu.
);

/**
 * @brief
 * Teste si le jeu de Pong est terminé.
 *
 * @details
 * La fin d'un jeu de Pong dépend du nombre de joueur:
 * - S'il y a deux joueurs, le jeu prend fin lorsqu'un des deux joueurs perd
 * tous ses points de vie. Dans ce cas le joueur restant gagne la partie.
 * - S'il n'y a qu'un seul joueur, le jeu prend fin lorsque ce joueur perd tous
 * ses points de vie. Dans ce cas, il gagne la partie par défaut.
 * - S'il n'y a aucun joueur, le jeu ne doit jamais se terminer (il n'y a pas de
 * gagnant dans ce cas).
 *
 * @remark
 * La fonction doit stocker dans @p winner le numéro du joueur gagnant (0 pour
 * le joueur 1, 1 pour le joueur 2).
 *
 * @return true si le jeu est terminé, false sinon.
 */
bool game_pong_end(
    game *g,      //!< Le jeu.
    short *winner //!< Pointeur vers une variable dans laquelle la fonction doit
                  //!< stocker le numéro du joueur gagnant (0 pour le joueur 1,
                  //!< 1 pour le joueur 2) si le jeu est terminé.
);

/**
 * @brief Implémentation de l'IA en mode Pong.
 *
 * @details La fonction choisit une direction de déplacement pour la raquette du
 * joueur @p i contrôlé par l'IA, et modifie le paramètre \ref paddle.speed_x de
 * la raquette en conséquence. L'IA suit simplement la balle avec la raquette.
 * Si la balle est à gauche de la raquette, elle se déplace vers la gauche, si
 * elle est à droite, elle se déplace vers la droite, sinon elle suit la vitesse
 * horizontale de la balle.
 */
bool game_pongia(game *g, //!< Le jeu.
                 short i  //!< Joueur contrôlé par l'IA (0 pour le joueur 1, 1
                          //!< pour le joueur 2).
);

/************************/
/*+ Gestion des balles +*/
/************************/

/**
 * @brief
 * Ajoute une nouvelle balle au jeu, en la créant au dessus de la raquette du
 * joueur spécifié.
 *
 * @remark
 * La fonction doit allouer une nouvelle balle et l'ajouter au tableau \ref
 * game.ball_list du jeu. Si le tableau \ref game.ball_list est plein (c'est à
 * dire si \ref game.nb_balls est égal à \ref game.size_balls), la fonction doit
 * doubler la taille du tableau \ref game.ball_list pour y faire de la place
 * avant d'ajouter la nouvelle balle.
 *
 * @return
 * true si la balle a été ajoutée, false sinon.
 */
bool game_add_ball_player(
    game *g,      //!< Le jeu.
    short player, //!< Le joueur (0 pour le joueur 1, 1 pour le joueur 2) au
                  // dessus duquel la balle doit être créée.
    power pow //!< Le type de bonus que la balle doit avoir (#POW_NONE si aucun
              // bonus).
);

/**
 * @brief
 * Ajoute une nouvelle balle au jeu, en la créant au milieu (verticalement) du
 * plateau. La position horizontale de la balle est déterminée par le paramètre
 * f, qui doit être compris entre 0 et 1 et représente la position relative de
 * la balle sur le plateau (0 pour le bord gauche, 1 pour le bord droit).
 *
 * @remark
 * La fonction doit allouer une nouvelle balle et l'ajouter au tableau \ref
 * game.ball_list du jeu. Si le tableau \ref game.ball_list est plein (c'est à
 * dire si \ref game.nb_balls est égal à \ref game.size_balls), la fonction doit
 * doubler la taille du tableau \ref game.ball_list pour y faire de la place
 * avant d'ajouter la nouvelle balle.
 */
void game_add_ball_center(
    game *g,  //!< Le jeu.
    double f, //!< La position relative de la balle sur le plateau (0 pour le
              //!< bord gauche, 1 pour le bord droit).
    power pow //!< Le type de bonus que la balle doit avoir (#POW_NONE si aucun
              //!< bonus).
);

/**
 * @brief
 * Supprime la balle d'indice @p i du jeu.
 *
 * @details
 * La fonction doit libérer la mémoire occupée par la balle, la retirer du
 * tableau \ref game.ball_list. Pour combler le trou, on réorganisera le tableau
 * \ref game.ball_list de manière en remplaçant la balle supprimée par la
 * dernière balle du tableau (celle d'indice \ref game.nb_balls - 1). Enfin, la
 * fonction doit décrémenter le nombre de balles nb_balls (on a retiré une balle
 * du jeu).
 */
void game_remove_ball(
    game *g, //!< Le jeu.
    int i    //!< L'indice de la balle dans le tableau \ref game.ball_list
);

/**
 * @brief Teste si une balle touche un mur et change l'état du jeu en
 * conséquence (inversion de la vitesse de la balle, perte de balle, etc.).
 *
 * @details Les conséquences d'une collision avec un mur sont les suivantes :
 * - Si la balle touche un mur vertical (gauche ou droite), sa vitesse
 * horizontale est inversée.
 * - Si elle touche le mur du bas, et qu'il y a un joueur 1, la balle est
 * perdue.
 * - Si elle touche le mur du bas, et qu'il n'y a pas de joueur 1, sa vitesse
 * verticale est inversée.
 * - Si elle touche le mur du haut et qu'il y a un joueur 2, la balle est
 * perdue.
 * - Si elle touche le mur du haut et qu'il n'y a pas de joueur 2, sa vitesse
 * verticale est inversée.
 *
 * @attention Si une balle est perdue, elle est supprimée du jeu (on utilisera
 * game_remove_ball()) et le joueur qui perd la balle (1 ou 2) perd un point de
 * vie (on décrémentera le paramètre \ref paddle.health de la
 * raquette du joueur qui perd la balle). Si il y a un autre joueur, son score
 * de buts est incrémenté (le paramètre \ref paddle.goals).
 *
 * @return true si la balle touche un mur, false sinon.
 */
bool ball_hits_wall(
    game *g, //!< Le jeu.
    int i    //!< L'indice de la balle dans le tableau \ref game.ball_list.
);

/**
 * @brief Teste si une balle touche une raquette et change l'état du jeu en
 * conséquence (changement de la vitesse de la balle).
 *
 * @details Pour déterminer les conséquences d'une collision entre une balle et
 * une raquette, on doit calculer la position de la balle par rapport au centre
 * de la raquette au moment de l'impact. Cette position détermine l'angle de
 * rebond de la balle:
 * - Si la balle touche le centre de la raquette, elle rebondira verticalement
 * (angle de 0 degrés).
 * - Si elle touche les bords de la raquette, elle rebondira avec un angle plus
 * prononcé (jusqu'à 60 degrés).
 *
 * @details Dans tous les cas la valeur absolue de la vitesse de la balle reste
 * constante, seule sa direction change.
 *
 * @return true si la balle touche la raquette, false sinon.
 */
bool ball_hits_paddle(
    game *g, //!< Le jeu.
    int i,   //!< L'indice de la balle dans le tableau \ref game.ball_list.
    paddle *paddle //!< La raquette à vérifier.
);

/**
 * @brief Teste si deux balles se touchent et change l'état du jeu en
 * conséquence (changement de la vitesse des balles).
 *
 * @details Pour déterminer les conséquences d'une collision entre deux balles,
 * on calculera le vecteur qui mène du centre de la première balle au centre de
 * la deuxième balle au moment de l'impact. Ce vecteur détermine la direction
 * dans laquelle les balles rebondissent l'une par rapport à l'autre:
 * - la première balle rebondira dans la direction opposée à ce vecteur. Sa
 * norme (longueur) restera constante (identique à celle qu'elle avait avant),
 * seule sa direction changera.
 * - la seconde balle rebondira dans la direction de ce vecteur. Sa norme
 * (longueur) restera constante (identique à celle qu'elle avait avant), seule
 * sa direction changera.
 *
 * @return true si les balles se touchent, false sinon.
 */
bool ball_collide(ball *b1, //!< La première balle.
                  ball *b2  //!< La deuxième balle.
);

#endif // GAME_PONG_H_
