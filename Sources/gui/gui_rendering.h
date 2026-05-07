#ifndef GUI_RENDERING_H_
#define GUI_RENDERING_H_

#include "../game.h"
#include "gui_init_graphic.h"

void render_debris(void);

void render_get_cellpos(int i, int j, SDL_Rect *pos);

void render_brick(SDL_Rect *ppos, brick *thebrick);

void render_all_bricks(game *thegame);

void render_ball(ball *b);

void render_paddle(game *g);

void render_scene(game *);

void render_bonus(bonus *b);

void render_idle_game(game *thegame); // , bool win

#endif // GUI_RENDERING_H_
