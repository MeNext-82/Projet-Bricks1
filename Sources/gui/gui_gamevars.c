#include "gui_gamevars.h"
#include "gui_files.h"
#include "gui_init_graphic.h"

ui_mode var_mode = MODE_MAINMENU;

/******************************/
/*+ Dimensions de la fenêtre **/
/******************************/

int var_screen_width, var_screen_height;

int var_game_width;
int var_info_width = 400;

int gen_hsize = 200;
int gen_vsize = 200;

double var_ball_speed_x = 0, var_ball_speed_y = 0;

int var_board_width;
int var_board_height;
int var_anchor_x = 0;
int var_anchor_y = 0;
int var_extreme_x;
int var_extreme_y;
int var_mid_y;
int var_top_y;
int var_bottom_y;
double var_zoom = 1;

SDL_Rect var_game_box;

void var_init_game_dimensions(void)
{
    if (!var_game)
    {
        var_anchor_x = 0;
        var_anchor_y = 0;
        return;
    }

    var_board_width = (var_game->nb_columns * CELL_X) / ZOOM;
    var_board_height = (var_game->nb_rows * CELL_Y) / ZOOM;

    if (var_board_width <= (var_game_width - 20) && var_board_height <= (var_screen_height - 20))
    {
        var_anchor_x = (var_game_width - var_board_width) / 2;
        var_anchor_y = (var_screen_height - var_board_height) / 2;
        var_zoom = ZOOM;
    }
    else
    {

        double ratiox = var_board_width / (double)(var_game_width - 20);
        double ratioy = var_board_height / (double)(var_screen_height - 20);
        double temp = max(ratiox, ratioy);
        var_zoom = ZOOM * temp;
        var_board_width = var_board_width / temp;
        var_board_height = var_board_height / temp;
        var_anchor_x = (var_game_width - var_board_width) / 2;
        var_anchor_y = (var_screen_height - var_board_height) / 2;
    }
    var_extreme_x = var_anchor_x + var_board_width;
    var_extreme_y = var_anchor_y + var_board_height;
    var_mid_y = var_anchor_y + (var_board_height / 2);

    var_game_box.x = var_anchor_x - 5;
    var_game_box.y = var_anchor_y - 5;
    var_game_box.w = var_board_width + 10;
    var_game_box.h = var_board_height + 10;
    var_top_y = var_anchor_y + (var_game->topspace * CELL_Y) / var_zoom;
    var_bottom_y = var_anchor_y + ((var_game->nb_rows - var_game->bottomspace) * CELL_Y) / var_zoom;
}

void var_init_demo_dimensions(void)
{
    if (!var_game)
    {
        var_anchor_x = 0;
        var_anchor_y = 0;
        return;
    }

    var_board_width = (var_game->nb_columns * CELL_X) / ZOOM;
    var_board_height = (var_game->nb_rows * CELL_Y) / ZOOM;

    if (var_board_width <= (var_screen_width - 20) && var_board_height <= (var_screen_height - 20))
    {
        var_anchor_x = (var_screen_width - var_board_width) / 2;
        var_anchor_y = (var_screen_height - var_board_height) / 2;
        var_zoom = ZOOM;
    }
    else
    {

        double ratiox = var_board_width / (double)(var_screen_width - 20);
        double ratioy = var_board_height / (double)(var_screen_height - 20);
        double temp = max(ratiox, ratioy);
        var_zoom = ZOOM * temp;
        var_board_width = var_board_width / temp;
        var_board_height = var_board_height / temp;
        var_anchor_x = (var_screen_width - var_board_width) / 2;
        var_anchor_y = (var_screen_height - var_board_height) / 2;
    }
    var_extreme_x = var_anchor_x + var_board_width;
    var_extreme_y = var_anchor_y + var_board_height;
    var_mid_y = var_anchor_y + (var_board_height / 2);

    var_game_box.x = var_anchor_x - 5;
    var_game_box.y = var_anchor_y - 5;
    var_game_box.w = var_board_width + 10;
    var_game_box.h = var_board_height + 10;
    var_top_y = var_anchor_y + (var_game->topspace * CELL_Y) / var_zoom;
    var_bottom_y = var_anchor_y + ((var_game->nb_rows - var_game->bottomspace) * CELL_Y) / var_zoom;
}

int SDL_RenderDrawDashedLine(SDL_Renderer *myrenderer, int x1, int y1, int x2, int y2, int dash_length)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    double length = sqrt(dx * dx + dy * dy);
    double dash_count = length / dash_length;
    double dash_x = dx / dash_count;
    double dash_y = dy / dash_count;

    for (int i = 0; i < dash_count; i++)
    {
        if (i % 2 == 0)
        {
            SDL_RenderDrawLine(myrenderer, x1 + i * dash_x, y1 + i * dash_y, x1 + (i + 1) * dash_x, y1 + (i + 1) * dash_y);
        }
    }
    return 0;
}

/************/
/*+ Le jeu +*/
/************/

game *var_game;

/***************************/
/*+ Contrôle de la Souris **/
/***************************/

int var_mousePosx;
int var_mousePosy;
bool var_leftMouseButtonDown;
long var_mouse_time;

/*************************/
/*+ Variables des menus +*/
/*************************/

int var_game_nb_columns = 8;
int var_game_nb_rows = 30;
int var_game_nb_balls = 4;
bool var_game_bonuses = true;
int var_game_player_one_mode = 2;
int var_game_player_two_mode = 0;
int var_game_topspace = 0;
int var_game_bottomspace = 3;
int var_game_brick_colors = 3;
int var_game_brick_health = 2;

/**************************************/
/*+ Contrôle du zoom et du Scrolling **/
/**************************************/

int var_scrollOffsetx;
int var_scrollOffsety;
int var_startx;
int var_starty;
int var_endx;
int var_endy;
int var_topleftx;
int var_toplefty;

/**************************/
/*+ Lecture des fichiers +*/
/**************************/

struct dirent **var_levelstab = NULL;
int var_levelindex = -1;
int var_leveltabsize = 0;
int var_levelpagesize = 0;
int var_levelpageindex = -1;

static int is_level_file(const struct dirent *dir)
{
    char *ext = strstr(dir->d_name, ".txt");
    if (ext && ext[4] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void var_init_levelstab(void)
{
    var_levelindex = -1;
    var_leveltabsize = scandir("./Levels/", &var_levelstab, is_level_file, alphasort);
    var_levelpagesize = var_leveltabsize / FILE_PER_PAGE + (var_leveltabsize % FILE_PER_PAGE != 0);
    var_levelpageindex = 0;
    if (var_leveltabsize > 0)
    {
        var_levelindex = 0;
    }
}

void var_free_levelstab(void)
{
    if (var_levelstab)
    {
        for (int i = 0; i < var_leveltabsize; i++)
        {
            free(var_levelstab[i]);
        }
        free(var_levelstab);
    }
    var_levelstab = NULL;
    var_levelindex = -1;
    var_leveltabsize = 0;
    var_levelpagesize = 0;
    var_levelpageindex = -1;
}

/****************/
/*+ Animations **/
/****************/

int var_frame = 0;
anim_mode var_crender = AN_IDLE;

/*****************/
/*+ Les boutons **/
/*****************/

// int var_button_countdown = 0;
// bool var_buttons_flags[BT_SIZE];

// void var_reset_buttons(void)
// {
//     for (int i = 0; i < BT_SIZE; i++)
//     {
//         var_buttons_flags[i] = false;
//     }
// }

// void var_push_button(buttons bt)
// {
//     var_buttons_flags[bt] = true;
//     var_button_countdown = SDL_GetTicks();
// }

// void var_release_button(buttons bt)
// {
//     var_buttons_flags[bt] = false;
// }

/*******************/
/*+ Keyboard text +*/
/*******************/

edit_mode var_edit_mode = ED_NONE;
text_buffer *var_editbuffer = NULL;

void init_text_buffer(edit_mode mode)
{
    var_edit_mode = mode;
    var_editbuffer = create_text_buffer();
}

void update_from_text_buffer(void)
{
    char *end_str;
    int num = strtol(var_editbuffer->content, &end_str, 10);
    if (*end_str != '\0')
    {
        fprintf(stderr, "Error: malformed string\n");
        return;
    }
    switch (var_edit_mode)
    {
    case ED_WIDTH:
        var_game_nb_columns = num >= 4 ? num : 4;
        break;
    case ED_HEIGHT:
        var_game_nb_rows = num >= 4 ? num : 4;
        break;
    case ED_TOP:
        var_game_topspace = num >= 0 ? num : 0;
        break;
    case ED_BOTTOM:
        var_game_bottomspace = num >= 0 ? num : 0;
        break;
    case ED_BALLS:
        var_game_nb_balls = num >= 1 ? min(num, 8) : 1;
        break;
    case ED_COLORS:
        var_game_brick_colors = num >= 1 ? min(num, COLSIZE) : 1;
        break;
    case ED_HEALTH:
        var_game_brick_health = num >= 1 ? min(num, 9) : 1;
        break;
    default:
        break;
    }
}

/******* Scores */

int var_scores_page = 0;
int var_scores_max_page = 0;
int var_scores_per_page = 14;

bool var_score_table_end = false;
short var_score_winner = -1;
short var_score_mode = 0; // 0 for pong, 1 for break

score_table *var_score_table = NULL;

void var_load_score_table(int *player_score)
{
    var_release_score_table();
    int size;
    char **lines = read_lines(var_score_mode == 0 ? "../scores/pongscores" : "../scores/brickscores", &size);
    var_score_table = load_score_table(lines, size, player_score);
    free_lines_tab(lines, size);
    if (var_score_table)
    {
        // Initializes the score table parameters
        var_scores_page = 0;
        var_scores_max_page = var_score_table->size / var_scores_per_page;
        if (var_score_table->size % var_scores_per_page > 0)
        {
            var_scores_max_page++;
        }
        sort_score_table(var_score_table, SC_SCORE);
    }
    else
    {
        fprintf(stderr, "Error loading score table.\n");
    }
}

void var_release_score_table(void)
{
    if (var_score_table)
    {
        delete_score_table(var_score_table);
        var_score_table = NULL;
    }
}
