#include "gui_controller.h"
#include "../game.h"
#include "../game_bonus.h"
#include "../game_bricks.h"
#include "../game_parameters.h"
#include "../game_pong.h"
#include "../game_scores.h"
#include "../utils.h"
#include "gui_controller.h"
#include "gui_files.h"
#include "gui_gamevars.h"
#include "gui_menus.h"
#include <stdbool.h>

/*********************************/
/*+ Flags pour la boucle de jeu **/
/*********************************/

/* Tableau des flags */
bool flags[NB_FLAGS];

void reset_flags(void)
{
    for (int i = 0; i < NB_FLAGS; i++)
        flags[i] = false;
}

void set_flag(ctl_flags f) { flags[f] = true; }

void remove_flag(ctl_flags f) { flags[f] = false; }

bool get_flag(ctl_flags f) { return flags[f]; }

void switch_flag(ctl_flags f) { flags[f] = !flags[f]; }

clock_t start, end;

/**************************************/
/*+ Intialisation/Suppression du jeu **/
/**************************************/

void ctl_enter_menu(void)
{
    reset_flags();
    var_reset_buttons();
    var_mode = MODE_MAINMENU;
    var_selected_button = BT_PONGGAME;
    ctl_init_demo();
}

void ctl_enter_scoreboard(void)
{
    int player_score[SC_SIZE];
    if (var_game->mode == GAME_PONG)
    {
        get_pong_winner_score(var_game, var_score_winner, player_score);
        if (var_game->player_modes[0] == 0 || var_game->player_modes[1] == 0)
        {
            var_score_winner = -1; // No player, no winner
        }
    }
    else if (var_game->mode == GAME_BRICKS)
    {
        get_brick_winner_score(var_game, player_score);
    }

    ctl_enter_menu();
    var_mode = MODE_SCOREMENU;
    var_selected_button = BT_NONE;

    // Loads the score table
    var_load_score_table(player_score);
    if (!var_score_table)
    {
        ctl_switch_to_main_menu();
        return;
    }

    var_reset_buttons();
}
void ctl_switch_to_score_menu(void)
{
    var_mode = MODE_SCOREMENU;
    var_selected_button = BT_NONE;

    var_score_table_end = false;
    var_score_winner = -1;

    // Loads the score table
    var_load_score_table(NULL);
    if (!var_score_table)
    {
        ctl_switch_to_main_menu();
        return;
    }

    var_reset_buttons();
}

void ctl_switch_to_pong_menu(void)
{
    var_mode = MODE_PONGMENU;
    var_selected_button = BT_PONGLAUNCH;
    var_reset_buttons();
}

void ctl_switch_to_main_menu(void)
{
    var_mode = MODE_MAINMENU;
    var_selected_button = BT_PONGGAME;
    var_reset_buttons();
}

void ctl_switch_to_bricks_menu(void)
{
    var_mode = MODE_BRICKSMENU;
    var_selected_button = BT_BRICKGEN;
    var_reset_buttons();
}

void ctl_init_demo(void)
{
    if (var_game)
    {
        reset_debris();
        free_game(var_game);
        var_game = NULL;
    }
    var_game = create_pong_game(8, 12, 0, 0, 8, false);
    var_init_demo_dimensions();
}

void ctl_init_pong(void)
{
    if (var_game)
    {
        reset_debris();
        free_game(var_game);
        var_game = NULL;
    }
    var_game = create_pong_game(
        var_game_nb_columns, var_game_nb_rows, var_game_player_one_mode,
        var_game_player_two_mode, var_game_nb_balls, var_game_bonuses);
    if (!var_game)
    {
        fprintf(stderr, "Error: could not create game.\n");
        ctl_enter_menu();
        return;
    }
    // Réinitialisation des flags
    reset_flags();
    init_time_counter();
    var_init_game_dimensions();
    var_mode = MODE_PONG;
}

bool ctl_game_ok(game *thegame)
{
    if (!thegame)
    {
        return false;
    }

    return true;
}

void ctl_init_brick(void)
{
    if (var_game)
    {
        reset_debris();
        free_game(var_game);
        var_game = NULL;
    }
    var_game = create_random_brick_game(
        var_game_nb_columns, var_game_nb_rows, var_game_topspace,
        var_game_bottomspace, var_game_player_one_mode,
        var_game_player_two_mode, var_game_brick_colors, var_game_brick_health);

    if (!var_game)
    {
        fprintf(stderr, "Error: could not create game.\n");
        ctl_enter_menu();
        return;
    }
    // Réinitialisation des flags
    reset_flags();
    init_time_counter();
    var_init_game_dimensions();
    var_mode = MODE_BRICKS;
}

void ctl_load_game(void)
{
    if (var_levelindex == -1)
    {
        fprintf(stderr, "Error: no level selected.\n");
        return;
    }

    if (var_game)
    {
        reset_debris();
        free_game(var_game);
        var_game = NULL;
    }

    init_time_counter();
    char filepath[1128];
    sprintf(filepath, "./Levels/%s", var_levelstab[var_levelindex]->d_name);
    int size;
    char **input = read_lines(filepath, &size);
    if (!input)
    {
        fprintf(stderr, "Error: could not read file %s\n", filepath);
        ctl_enter_menu();
        return;
    }

    var_game = create_newgame_file(input, size, var_game_player_one_mode,
                                   var_game_player_two_mode);
    free_lines_tab(input, size);
    if (!var_game)
    {
        fprintf(stderr, "Error: could not create game from file %s\n",
                filepath);
        ctl_enter_menu();
        return;
    }
    // Réinitialisation des flags
    reset_flags();
    var_init_game_dimensions();
    var_mode = MODE_BRICKS;
}

/*********************************/
/*+ Prise en compte des actions **/
/*********************************/

static bool ctl_mouse_button_action(int x, int y)
{
    switch (var_mode)
    {
    case MODE_MAINMENU:
        return ctl_mouse_mainmenu(x, y);
        break;
    case MODE_PONGMENU:
        return ctl_mouse_pongmenu(x, y);
        break;
    case MODE_BRICKSMENU:
        return ctl_mouse_bricksmenu(x, y);
        break;
    case MODE_SCOREMENU:
        return ctl_mouse_score_screen(x, y);
        break;
    case MODE_BRICKS:
    case MODE_PONG:
        return ctl_mouse_game(x, y);
        break;
    default:
        break;
    }

    return false;
}

void ctl_mouse_click(SDL_Event *theevent)
{
    if (!flags[MOUSEDOWN] && theevent->button.button == SDL_BUTTON_LEFT)
    {
        set_flag(MOUSEDOWN);
    }
    if (ctl_mouse_button_action(theevent->button.x, theevent->button.y))
    {
        return;
    }
    else
    {
        var_mouse_time = SDL_GetTicks();
    }
}

void ctl_mouse_unclick(SDL_Event *theevent)
{
    if (flags[MOUSEDOWN] && theevent->button.button == SDL_BUTTON_LEFT)
    {
        remove_flag(MOUSEDOWN);
    }
}

bool ctl_mouse_mainmenu(int x, int y)
{
    if (flags[PUSHED])
    {
        return false;
    }
    // else if (var_high_scores)
    // {
    //     return mouse_capture_button(x, y, BT_SCOREBACK) ||
    //     ctl_mouse_score_screen(x, y);
    // }
    for (int i = BT_PONGGAME; i <= BT_QUIT; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }
    return false;
}

bool ctl_mouse_pongmenu(int x, int y)
{
    if (flags[PUSHED])
    {
        return false;
    }
    // else if (var_high_scores)
    // {
    //     return mouse_capture_button(x, y, BT_SCOREBACK) ||
    //     ctl_mouse_score_screen(x, y);
    // }
    for (int i = BT_PONGLAUNCH; i <= BT_PONGP2R; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }
    return false;
}

bool ctl_mouse_bricksmenu(int x, int y)
{
    if (flags[PUSHED])
    {
        return false;
    }
    // else if (var_high_scores)
    // {
    //     return mouse_capture_button(x, y, BT_SCOREBACK) ||
    //     ctl_mouse_score_screen(x, y);
    // }
    for (int i = BT_SETWIDTH; i <= BT_SELECPAGER; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }

    int nb_files = var_levelpageindex == (var_levelpagesize - 1)
                       ? var_leveltabsize - var_levelpageindex * FILE_PER_PAGE
                       : FILE_PER_PAGE;
    // printf("nb_files = %d\n", nb_files);

    for (int i = BT_FILE1; i < BT_FILE1 + nb_files; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }

    return false;
}

bool ctl_mouse_game(int x, int y)
{
    if (flags[PUSHED])
    {
        return false;
    }
    // else if (var_high_scores)
    // {
    //     return mouse_capture_button(x, y, BT_SCOREBACK) ||
    //     ctl_mouse_score_screen(x, y);
    // }
    for (int i = BT_PAUSE; i <= BT_BACKMENU; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }
    return false;
}

bool ctl_mouse_score_screen(int x, int y)
{
    for (int i = BT_SCGLOBAL; i <= BT_SCTIME; i++)
    {
        if (mouse_capture_button(x, y, i))
        {
            return true;
        }
    }
    if (var_scores_page > 0)
    {
        if (mouse_capture_button(x, y, BT_PREVSCORE))
        {
            return true;
        }
    }
    if (var_scores_page < var_scores_max_page - 1)
    {
        if (mouse_capture_button(x, y, BT_NEXTSCORE))
        {
            return true;
        }
    }

    if (var_score_table_end)
    {
        mouse_capture_button(x, y, BT_SCOREMENU);
        mouse_capture_button(x, y, BT_SCORESAVE);
    }
    else
    {
        mouse_capture_button(x, y, BT_SCOREBACK);
        mouse_capture_button(x, y, BT_SCOREMODEL);
        mouse_capture_button(x, y, BT_SCOREMODER);
    }

    return false;
}

static void ctl_button_push_main(void)
{
    switch (var_pushed_button)
    {
    case BT_PONGGAME:
        ctl_switch_to_pong_menu();
        break;
    case BT_BREAKGAME:
        ctl_switch_to_bricks_menu();
        break;
    case BT_SCORESCREEN:
        ctl_switch_to_score_menu();
        break;
    case BT_QUIT:
        set_flag(QUIT);
        break;
    default:
        break;
    }
}

static void ctl_button_push_pongsetup(void)
{
    switch (var_pushed_button)
    {
    case BT_PONGBACK:
        ctl_switch_to_main_menu();
        break;
    case BT_PONGLAUNCH:
        ctl_init_pong();
        break;
    case BT_PONGP1L:
        var_game_player_one_mode = 0;
        break;
    case BT_PONGP1C:
        var_game_player_one_mode = 1;
        break;
    case BT_PONGP1R:
        var_game_player_one_mode = 2;
        break;
    case BT_PONGP2L:
        var_game_player_two_mode = 0;
        break;
    case BT_PONGP2C:
        var_game_player_two_mode = 1;
        break;
    case BT_PONGP2R:
        var_game_player_two_mode = 2;
        break;
    case BT_PONGBONUS:
        var_game_bonuses = !var_game_bonuses;
        break;
    case BT_SETWIDTH:
        init_text_buffer(ED_WIDTH);
        break;
    case BT_SETHEIGHT:
        init_text_buffer(ED_HEIGHT);
        break;
    case BT_PONGNBALLS:
        init_text_buffer(ED_BALLS);
        break;
    default:
        break;
    }
}

static void ctl_button_push_breaksetup(void)
{
    switch (var_pushed_button)
    {
    case BT_BRICKBACK:
        ctl_switch_to_main_menu();
        break;
    case BT_BRICKGEN:
        ctl_init_brick();
        break;
    case BT_BRICKLOAD:
        ctl_load_game();
        break;
    case BT_PONGP1L:
        var_game_player_one_mode = 0;
        break;
    case BT_PONGP1C:
        var_game_player_one_mode = 1;
        break;
    case BT_PONGP1R:
        var_game_player_one_mode = 2;
        break;
    case BT_PONGP2L:
        var_game_player_two_mode = 0;
        break;
    case BT_PONGP2C:
        var_game_player_two_mode = 1;
        break;
    case BT_PONGP2R:
        var_game_player_two_mode = 2;
        break;
    case BT_SETWIDTH:
        init_text_buffer(ED_WIDTH);
        break;
    case BT_SETHEIGHT:
        init_text_buffer(ED_HEIGHT);
        break;
    case BT_SETBRICKTOP:
        init_text_buffer(ED_TOP);
        break;
    case BT_SETBRICKBOT:
        init_text_buffer(ED_BOTTOM);
        break;
    case BT_SETCOLORS:
        init_text_buffer(ED_COLORS);
        break;
    case BT_SETBRICKHEALTH:
        init_text_buffer(ED_HEALTH);
        break;
    case BT_SELECPAGEL:
        if (var_levelpageindex > 0)
        {
            var_levelpageindex--;
        }
        break;
    case BT_SELECPAGER:
        if (var_levelpageindex < var_levelpagesize - 1)
        {
            var_levelpageindex++;
        }
        break;
    case BT_FILE1:
    case BT_FILE2:
    case BT_FILE3:
    case BT_FILE4:
    case BT_FILE5:
    case BT_FILE6:
    case BT_FILE7:
    case BT_FILE8:
        var_levelindex =
            var_levelpageindex * FILE_PER_PAGE + (var_pushed_button - BT_FILE1);
        break;
    default:
        break;
    }
}

static void ctl_button_push_game(void)
{
    switch (var_pushed_button)
    {
    case BT_PAUSE:
        if (get_flag(PAUSED))
        {
            ctl_resume_game();
        }
        else
        {
            ctl_pause_game();
        }
        break;
    case BT_BACKMENU:
        ctl_enter_menu();
        break;
    default:
        break;
    }
}

static void ctl_button_push_score(void)
{
    switch (var_pushed_button)
    {
    case BT_SCGLOBAL:
        sort_score_table(var_score_table, SC_SCORE);
        break;
    case BT_SCGOALS:
        sort_score_table(var_score_table, SC_GOALS);
        break;
    case BT_SCBONUS:
        sort_score_table(var_score_table, SC_BONUS);
        break;
    case BT_SCHEALTH:
        sort_score_table(var_score_table, SC_HEALTH);
        break;
    case BT_SCBRICKS:
        sort_score_table(var_score_table, SC_BRICKS);
        break;
    case BT_SCPLAYERS:
        sort_score_table(var_score_table, SC_PLAYERS);
        break;
    case BT_SCTIME:
        sort_score_table(var_score_table, SC_TIME);
        break;
    case BT_PREVSCORE:
        if (var_scores_page > 0)
        {
            var_scores_page--;
        }
        break;
    case BT_NEXTSCORE:
        if (var_scores_page < var_scores_max_page - 1)
        {
            var_scores_page++;
        }
        break;
    case BT_SCOREMENU:
    case BT_SCOREBACK:
        ctl_switch_to_main_menu();
        break;
    case BT_SCORESAVE:
        init_text_buffer(ED_NAME);
        break;
    case BT_SCOREMODEL:
        var_score_mode = 0;
        var_load_score_table(NULL);
        break;
    case BT_SCOREMODER:
        var_score_mode = 1;
        var_load_score_table(NULL);
        break;
    default:
        break;
    }
}

void ctl_button_push(void)
{
    switch (var_mode)
    {
    case MODE_MAINMENU:
        ctl_button_push_main();
        break;
    case MODE_PONGMENU:
        ctl_button_push_pongsetup();
        break;
    case MODE_BRICKSMENU:
        ctl_button_push_breaksetup();
        break;
    case MODE_SCOREMENU:
        ctl_button_push_score();
        break;
    case MODE_BRICKS:
    case MODE_PONG:
        ctl_button_push_game();
        break;
    default:
        break;
    }
    var_pushed_button = BT_NONE;
}

// void ctl_init_action(game *thegame, move themove) {}

// void ctl_update_action(game *thegame) {}

// void ctl_move_action(game *thegame, move themove) {}

void ctl_pause_game(void)
{
    // INFO("Pause, %g %g", thegame->ball_speed_x, thegame->ball_speed_y);
    pause_time_counter();
    set_flag(PAUSED);
    // var_ball_speed_x = thegame->ball_speed_x;
    // var_ball_speed_y = thegame->ball_speed_y;
    // thegame->ball_speed_x = thegame->ball_speed_y = 0;
}

void ctl_resume_game(void)
{
    // INFO("Resume, %g %g", thegame->ball_speed_x, thegame->ball_speed_y);
    resume_time_counter();
    remove_flag(PAUSED);
    // thegame->ball_speed_x = var_ball_speed_x;
    // thegame->ball_speed_y = var_ball_speed_y;
}

void ctl_keyboard_general_menu(SDL_KeyCode key)
{
    switch (key)
    {
    case SDLK_UP:
        var_selected_button = var_buttons[var_selected_button].up;
        return;
        break;
    case SDLK_DOWN:
        var_selected_button = var_buttons[var_selected_button].down;
        return;
        break;
    case SDLK_LEFT:
        var_selected_button = var_buttons[var_selected_button].left;
        return;
        break;
    case SDLK_RIGHT:
        var_selected_button = var_buttons[var_selected_button].right;
        return;
        break;
    case SDLK_RETURN:
        var_push_button(var_selected_button);
        return;
        break;

    default:
        break;
    }
}

void ctl_keyboard(game *thegame, SDL_Event *theevent)
{
    switch (theevent->key.keysym.sym)
    {
    case SDLK_SPACE:
        var_push_button(BT_PAUSE);
        break;
    case SDLK_ESCAPE:
        var_push_button(BT_BACKMENU);
        break;
    case SDLK_LEFT:
        if (!get_flag(PAUSED) && thegame->paddles[0])
        {

            game_move_player(thegame, 0, -1);
        }
        break;
    case SDLK_RIGHT:
        if (!get_flag(PAUSED) && thegame->paddles[0])
        {
            game_move_player(thegame, 0, 1);
        }
        break;
    case SDLK_s:
        if (!get_flag(PAUSED) && thegame->paddles[1])
        {

            game_move_player(thegame, 1, -1);
        }
        break;
    case SDLK_d:
        if (!get_flag(PAUSED) && thegame->paddles[1])
        {
            game_move_player(thegame, 1, 1);
        }
        break;
    default:
        break;
    }

#ifdef DEBUG_MODE
    switch (theevent->key.keysym.sym)
    {
    case SDLK_b:
        if (!get_flag(PAUSED) && thegame->paddles[0])
        {
            game_add_ball_player(thegame, 0, POW_GREEN);
        }
        break;
    case SDLK_v:
        if (!get_flag(PAUSED) && thegame->paddles[0])
        {
            game_add_ball_player(thegame, 0, POW_GREEN);
        }
        break;
    case SDLK_r:
        if (!get_flag(PAUSED) && thegame->paddles[0])
        {
            game_add_ball_player(thegame, 0, POW_RED);
        }
        break;
    case SDLK_g:
        if (!get_flag(PAUSED))
        {
            game_gravity(thegame, true);
        }
        break;
    case SDLK_h:
        if (!get_flag(PAUSED))
        {
            game_gravity(thegame, false);
        }
        break;
    }
#endif
}

void ctl_keyboard_up(game *thegame, SDL_Event *theevent)
{
    switch (theevent->key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_RIGHT:
        if (!get_flag(PAUSED))
        {
            game_move_player(thegame, 0, 0);
        }
        break;
    case SDLK_s:
    case SDLK_d:
        if (!get_flag(PAUSED))
        {
            game_move_player(thegame, 1, 0);
        }
        break;
    default:
        break;
    }
}

/****************************/
/*+ Gestion des animations **/
/****************************/

void ctl_free_gui(void) {}

// static char filepath[256];
void ctl_handle_edit_return(void)
{
    switch (var_edit_mode)
    {
    case ED_NAME:
        if (!var_score_table)
        {
            fprintf(stderr, "No score table initialized.\n");
            exit(EXIT_FAILURE);
            break;
        }
        if (var_score_table->player_index >= 0 &&
            var_score_table->player_index < var_score_table->size)
        {
            int mysize;
            char **lines = save_score_table(var_score_table,
                                            var_editbuffer->content, &mysize);
            write_lines(lines, mysize,
                        var_score_mode == 0 ? "../scores/pongscores"
                                            : "../scores/brickscores");
            free_lines_tab(lines, mysize);
        }
        else
        {
            fprintf(stderr, "Invalid player index in score table: %d\n",
                    var_score_table->player_index);
            exit(EXIT_FAILURE);
        }
        ctl_enter_menu();
        break;
    default:
        update_from_text_buffer();
        break;
    }
    free_text_buffer(var_editbuffer);
    var_editbuffer = NULL;
    var_edit_mode = ED_NONE;
}

/*******************/
/*+ Boucle de jeu **/
/*******************/

#define shine_time 1000

void ctl_menu_display(void)
{

    if (var_game)
    {

        SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(BLACK));
        SDL_RenderFillRect(renderer, &var_game_box);
        SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(ORANGET));
        SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_anchor_x,
                           var_extreme_y);
        SDL_RenderDrawLine(renderer, var_extreme_x, var_anchor_y, var_extreme_x,
                           var_extreme_y);
        SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_extreme_x,
                           var_anchor_y);
        SDL_RenderDrawLine(renderer, var_anchor_x, var_extreme_y, var_extreme_x,
                           var_extreme_y);

        SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
        game_apply_moves(var_game);
        game_handle_collisions(var_game);
        render_idle_game(var_game);

        for (int i = 0; i < var_game->nb_balls; i++)
        {
            render_ball(var_game->ball_list[i]);
        }
    }

    switch (var_mode)
    {
    case MODE_MAINMENU:
        render_mainmenu();
        break;
    case MODE_PONGMENU:
        render_pongmenu();
        break;
    case MODE_BRICKSMENU:
        render_brickmenu();
        break;
    case MODE_SCOREMENU:
        render_score_screen();
        break;
    default:
        break;
    }
}

void ctl_handle_pong_game(void)
{
    static int bonus_timer = 0;
    // Mise à jour du jeu.
    if (!get_flag(PAUSED))
    {
        if (var_game->player_modes[0] == 1)
        {
            game_pongia(var_game, 0);
        }
        if (var_game->player_modes[1] == 1)
        {
            game_pongia(var_game, 1);
        }
        update_debris();
        game_apply_moves(var_game);
        if (var_game->bonuses &&
            (var_game->player_modes[0] > 0 || var_game->player_modes[1] > 0) &&
            bonus_timer >= 250 && rand() % 128 == 0)
        {
            game_place_bonus_pong(var_game);
            bonus_timer = 0;
        }
        bonus_timer++;
        game_handle_collisions(var_game);
        if (game_pong_end(var_game, &var_score_winner))
        {
            var_score_table_end = true;
            var_score_mode = 0;
            ctl_enter_scoreboard();
            return;
        }
    }

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(BLACK));
    SDL_RenderFillRect(renderer, &var_game_box);
    //    SDL_RenderDrawLine(renderer, var_game_width, 0, var_game_width,
    //    var_screen_height);

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(ORANGET));

    SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_anchor_x,
                       var_extreme_y);
    SDL_RenderDrawLine(renderer, var_extreme_x, var_anchor_y, var_extreme_x,
                       var_extreme_y);
    SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_mid_y, var_extreme_x,
                             var_mid_y, 10);

    if (var_game->paddles[1])
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_anchor_y,
                                 var_extreme_x, var_anchor_y, 10);
    }
    else
    {
        SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_extreme_x,
                           var_anchor_y);
    }

    if (var_game->paddles[0])
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_extreme_y,
                                 var_extreme_x, var_extreme_y, 10);
    }
    else
    {
        SDL_RenderDrawLine(renderer, var_anchor_x, var_extreme_y, var_extreme_x,
                           var_extreme_y);
    }

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

    render_pong_hud();

    render_idle_game(var_game); // , flags[WIN]

    for (int i = 0; i < var_game->nb_balls; i++)
    {
        render_ball(var_game->ball_list[i]);
    }
    render_paddle(var_game);
}

void ctl_handle_brick_game(void)
{
    if (!get_flag(PAUSED))
    {
        if (var_game->player_modes[0] == 1)
        {
            game_brickia(var_game, 0);
        }
        if (var_game->player_modes[1] == 1)
        {
            game_brickia(var_game, 1);
        }
        update_debris();
        game_apply_moves(var_game);
        game_handle_collisions(var_game);
        bool theend;
        if (game_brick_end(var_game, &theend))
        {
            var_score_table_end = true;
            var_score_mode = 1;
            var_score_winner = theend ? 0 : -1;
            ctl_enter_scoreboard();
            return;
        }
    }

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(BLACK));
    SDL_RenderFillRect(renderer, &var_game_box);
    //    SDL_RenderDrawLine(renderer, var_game_width, 0, var_game_width,
    //    var_screen_height);

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(ORANGET));

    SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_anchor_x,
                       var_extreme_y);
    SDL_RenderDrawLine(renderer, var_extreme_x, var_anchor_y, var_extreme_x,
                       var_extreme_y);
    // SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_mid_y,
    // var_extreme_x, var_mid_y, 10);

    if (var_game->paddles[1])
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_anchor_y,
                                 var_extreme_x, var_anchor_y, 10);
    }
    else
    {
        SDL_RenderDrawLine(renderer, var_anchor_x, var_anchor_y, var_extreme_x,
                           var_anchor_y);
    }

    if (var_game->paddles[0])
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_extreme_y,
                                 var_extreme_x, var_extreme_y, 10);
    }
    else
    {
        SDL_RenderDrawLine(renderer, var_anchor_x, var_extreme_y, var_extreme_x,
                           var_extreme_y);
    }

    if (var_game->topspace != 0)
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_top_y,
                                 var_extreme_x, var_top_y, 10);
    }

    if (var_game->bottomspace != 0)
    {
        SDL_RenderDrawDashedLine(renderer, var_anchor_x, var_bottom_y,
                                 var_extreme_x, var_bottom_y, 10);
    }

    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

    render_brick_hud();

    render_idle_game(var_game); // , flags[WIN]

    for (int i = 0; i < var_game->nb_balls; i++)
    {
        render_ball(var_game->ball_list[i]);
    }
    render_paddle(var_game);
    // ctl_show_score(var_game);
    // ctl_show_remaining(var_game);

    // if (var_menu == MENU_PLAY && flags[WIN]) {
    //     render_victory();
    // }
}

void event_loop(void)
{
    ctl_enter_menu();
    init_debris();
    var_reset_buttons();

    SDL_Event event;

    while (!flags[QUIT])
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                set_flag(QUIT);
                break;
            }

            // Text input mode
            if (var_edit_mode != ED_NONE)
            {
                switch (event.type)
                {
                case SDL_TEXTINPUT:
                    if (var_edit_mode == ED_NAME &&
                        (event.text.text[0] == ',' ||
                         event.text.text[0] == ';'))
                    {
                        break;
                    }
                    append_to_text_buffer(var_editbuffer, event.text.text);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_BACKSPACE:
                        if (var_editbuffer->length > 0)
                            remove_char(var_editbuffer);
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        ctl_handle_edit_return();
                        break;
                    case SDLK_ESCAPE:
                        free_text_buffer(var_editbuffer);
                        var_editbuffer = NULL;
                        var_edit_mode = ED_NONE;
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
                continue;
            }

            // Mouse handling
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                ctl_mouse_click(&event);
                break;
            case SDL_MOUSEBUTTONUP:
                ctl_mouse_unclick(&event);
                break;

            default:
                break;
            }

            if ((var_mode == MODE_MAINMENU || var_mode == MODE_PONGMENU || var_mode == MODE_BRICKSMENU) && event.type == SDL_KEYDOWN)
            {
                ctl_keyboard_general_menu(event.key.keysym.sym);
            }

            if ((var_mode == MODE_PONG || var_mode == MODE_BRICKS))
            {

                // Lock du clavier tant qu'une touche est enfoncée
                if ((flags[KEYDOWN] && event.type != SDL_KEYUP))
                {
                    continue;
                }
                if (flags[KEYDOWN] && event.type == SDL_KEYUP)
                {
                    flags[KEYDOWN] = false;
                    ctl_keyboard_up(var_game, &event);
                }

                // Gestion du clavier
                if ((var_mode == MODE_PONG || var_mode == MODE_BRICKS) && event.type == SDL_KEYDOWN)
                {
                    set_flag(KEYDOWN);
                    ctl_keyboard(var_game, &event);
                }
            }
        }

        if (flags[PUSHED] && SDL_GetTicks() - var_button_countdown >= 100)
        {
            var_reset_buttons();
            remove_flag(PUSHED);
            ctl_button_push();
        }

        // Affichage
        SDL_RenderClear(renderer);

        switch (var_mode)
        {
        case MODE_MAINMENU:
        case MODE_BRICKSMENU:
        case MODE_PONGMENU:
        case MODE_SCOREMENU:
            ctl_menu_display();
            break;
        case MODE_PONG:
            ctl_handle_pong_game();
            break;
        case MODE_BRICKS:
            ctl_handle_brick_game();
            break;
        default:
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }

    ctl_free_gui();
    free_game(var_game);
}
