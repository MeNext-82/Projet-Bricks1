#include "gui_rendering.h"
#include "../game.h"
#include "gui_gamevars.h"

void render_debris(void)
{
    if (nb_debris == 0)
    {
        return;
    }
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
    for (int i = 0; i < nb_debris; i++)
    {
        debris *d = debris_list[i];
        SDL_Rect r = {.x = (d->rect.x / var_zoom) + var_anchor_x,
                      .y = (d->rect.y / var_zoom) + var_anchor_y,
                      .w = (d->rect.w / var_zoom),
                      .h = (d->rect.h / var_zoom)};

        SDL_RenderFillRect(renderer, &r);
    }
}

void render_brick(SDL_Rect *ppos, brick *thebrick)
{
    DEBUG("Render brick (%d, %d) thecolor = %d", ppos->x, ppos->y,
          thebrick->color);
    if (thebrick->health == 0)
    {
        return;
    }
    else if (thebrick->health == thebrick->max_health)
    {
        SDL_RenderCopy(renderer, txt_bricks, &clp_bricks[BLUE][CLP_SOLID],
                       ppos);
    }
    else if (thebrick->health < thebrick->max_health &&
             thebrick->health > thebrick->max_health / 2)
    {
        SDL_RenderCopy(renderer, txt_bricks, &clp_bricks[BLUE][CLP_CRACKED1],
                       ppos);
    }
    else
    {
        SDL_RenderCopy(renderer, txt_bricks, &clp_bricks[BLUE][CLP_CRACKED2],
                       ppos);
    }
}

void render_ball(ball *b)
{
    SDL_Rect ppos = {.x = ((b->rect.x) / var_zoom) + var_anchor_x,
                     .y = ((b->rect.y) / var_zoom) + var_anchor_y,
                     .w = (b->rect.w) / var_zoom,
                     .h = (b->rect.h) / var_zoom};
    clip_objects ball_clip;
    switch (b->powerup)
    {
    case POW_RED:
        ball_clip = CLP_BALL_RED_2;
        break;
    case POW_GREEN:
        ball_clip = CLP_BALL_GREEN_2;
        break;
    default:
        ball_clip = CLP_BALL_2;
        break;
    }
    SDL_RenderCopy(renderer, txt_balls, &clp_objects[ball_clip], &ppos);
}

#define PADDLE_PERIOD 30
#define SLICE (PADDLE_PERIOD / 3)

static void rend_paddle_aux(paddle *p, int turn)
{
    clip_objects PADDLE1, PADDLE2, PADDLE3;
    SDL_Texture *texture;

    switch (p->size)
    {
    case PADDLE_SMALL:
        PADDLE1 = CLP_PADDLE_SHORT;
        PADDLE2 = CLP_PADDLE_SHORT;
        PADDLE3 = CLP_PADDLE_SHORT;
        texture = txt_spaddle;
        break;
    case PADDLE_NORMAL:
        PADDLE1 = CLP_PADDLE_1;
        PADDLE2 = CLP_PADDLE_2;
        PADDLE3 = CLP_PADDLE_3;
        texture = txt_paddle;
        break;
    case PADDLE_LARGE:
        PADDLE1 = CLP_PADDLE_LONG_1;
        PADDLE2 = CLP_PADDLE_LONG_2;
        PADDLE3 = CLP_PADDLE_LONG_3;
        texture = txt_lpaddle;
        break;
    default:
        break;
    }

    SDL_Rect ppos = {.x = (p->rect.x / var_zoom) + var_anchor_x,
                     .y = (p->rect.y / var_zoom) + var_anchor_y,
                     .w = (p->rect.w / var_zoom),
                     .h = (p->rect.h / var_zoom)};
    if (turn % PADDLE_PERIOD < SLICE)
    {
        SDL_RenderCopyEx(renderer, texture, &clp_objects[PADDLE1], &ppos, 0,
                         NULL, p->bottom ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
    }
    else if (turn % PADDLE_PERIOD < 2 * SLICE)
    {
        SDL_RenderCopyEx(renderer, texture, &clp_objects[PADDLE2], &ppos, 0,
                         NULL, p->bottom ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
    }
    else
    {
        SDL_RenderCopyEx(renderer, texture, &clp_objects[PADDLE3], &ppos, 0,
                         NULL, p->bottom ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
    }
}

void render_paddle(game *g)
{

    static int turn;
    if (g->paddles[0])
    {
        rend_paddle_aux(g->paddles[0], turn);
    }
    if (g->paddles[1])
    {
        rend_paddle_aux(g->paddles[1], turn);
    }
    turn++;
}

// static int normalize_frame(int frame, int max)
// {
//     if (frame < 0)
//     {
//         return 0;
//     }
//     if (frame >= max)
//     {
//         return max - 1;
//     }
//     return frame;
// }

// BNS_SHRINK,          //!< Réduit la taille de la raquette.
//     BNS_GROW,        //!< Agrandit la taille de la raquette.
//     BNS_SPEEDUP,     //!< Augmente la vitesse de la balle.
//     BNS_SLOWDOWN,    //!< Diminue la vitesse de la balle.
//     BNS_COLORBALL,   //!< Passe le jeu en mode SCCs (détuire une brique
//     détruit également toutes les briques adjacentes de la même couleur
//     récursivement). BNS_STRONGBALL, //!< Passe le jeu en mode normal (les
//     briques sont détruites une par une). BNS_NEWBALL,   //!< Ajoute une balle
//     supplémentaire. BNS_SCORE,       //!< Donne des points au joueur.
//     BNS_GRAVITY,     //!< Les briques tombent dans la direction du joueur qui
//     a touché la balle en dernier.

void render_bonus(bonus *b)
{
    SDL_Rect ppos = {.x = (b->rect.x / var_zoom) + var_anchor_x,
                     .y = (b->rect.y / var_zoom) + var_anchor_y,
                     .w = (b->rect.w / var_zoom),
                     .h = (b->rect.h / var_zoom)};
    b->frame++;
    unsigned int myframe = b->frame / 16;
    // printf("Render bonus of type %d at (%d, %d) with score %d and frame
    // %d\n", b->type, ppos.x, ppos.y, b->score, b->frame);
    switch (b->type)
    {
    case BNS_SHRINK:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SHRINK][myframe % 6], &ppos);
        break;
    case BNS_GROW:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_GROW][myframe % 6], &ppos);
        break;
    case BNS_SPEEDUP:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SPEEDUP][myframe % 6], &ppos);
        break;
    case BNS_SLOWDOWN:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SLOWDOWN][myframe % 6], &ppos);
        break;
    case BNS_STRONGBALL:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_COLORMODE][myframe % 7], &ppos);
        break;
    case BNS_COLORBALL:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_CLASSICMODE][myframe % 7], &ppos);
        break;
    case BNS_NEWBALL:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &(clp_bonuses[CLP_MULTIBALL][myframe % 7]), &ppos);
        break;
    case BNS_HEALTH:
        SDL_RenderCopy(renderer, txt_balls, &clp_objects[CLP_HEART], &ppos);
        break;
    case BNS_SCORE50:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SCORE50][myframe % 6], &ppos);
        break;
    case BNS_SCORE100:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SCORE100][myframe % 6], &ppos);
        break;
    case BNS_SCORE250:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SCORE250][myframe % 6], &ppos);
        break;
    case BNS_SCORE500:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_SCORE500][myframe % 6], &ppos);
        break;

    case BNS_GRAVITY:
        SDL_RenderCopy(renderer, txt_bonuses,
                       &clp_bonuses[CLP_GRAVITY][myframe % 6], &ppos);
        break;

    default:
        break;
    }
}

// void render_scene(game *g) {}
#define SHINE_TIME 42

void render_idle_game(game *thegame) // , bool win
{
    SDL_Rect ppos;
    static int shine;
    static int shine_time = SHINE_TIME;

    if (shine_time == SHINE_TIME)
    {
        shine_time = 0;
        if (thegame->nb_bricks > 0)
            shine = rand() % thegame->nb_bricks;
        else
            shine = 0;
    }

    int c = 0;
    for (int i = 0; i < thegame->nb_bricks; i++)
    {
        brick *thebrick = thegame->brick_list[i];
        if (thebrick->health == 0)
        {
            continue;
        }

        ppos.x = (thebrick->rect.x / var_zoom) + var_anchor_x;
        ppos.y = (thebrick->rect.y / var_zoom) + var_anchor_y;
        ppos.w = (thebrick->rect.w / var_zoom);
        ppos.h = (thebrick->rect.h / var_zoom);

        // // printf("Render brick %d at (%d, %d) with color %d and health
        // %d/%d\n", i, ppos.x, ppos.y, thebrick->color, thebrick->health,
        // thebrick->max_health);

        if (thebrick->health == thebrick->max_health)
        {
            if (c == shine)
            {
                SDL_RenderCopy(
                    renderer, txt_bricks,
                    &clp_bricks[thebrick->color][CLP_ANIM1 + (shine_time / 6)],
                    &ppos);
            }
            else
            {
                SDL_RenderCopy(renderer, txt_bricks,
                               &clp_bricks[thebrick->color][CLP_SOLID], &ppos);
            }
        }
        else if (thebrick->health < thebrick->max_health &&
                 thebrick->health > thebrick->max_health / 2)
        {
            SDL_RenderCopy(renderer, txt_bricks,
                           &clp_bricks[thebrick->color][CLP_CRACKED1], &ppos);
        }
        else
        {
            SDL_RenderCopy(renderer, txt_bricks,
                           &clp_bricks[thebrick->color][CLP_CRACKED2], &ppos);
        }
        c++;
    }

    for (int i = 0; i < thegame->nb_bonus; i++)
    {
        bonus *b = thegame->bonus_list[i];
        render_bonus(b);
    }

    shine_time++;
    render_debris();
}
