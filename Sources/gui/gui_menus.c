#include "gui_menus.h"
#include "../game_scores.h"
#include "../utils.h"
#include "gui_controller.h"
#include "gui_init_graphic.h"
#include "gui_rendering.h"
char menus_buffer[128];

/*************/
/*+ Anchors +*/
/*************/

void shift_to_anchor(int *x, int *y, int w, int h, anchor anc)
{
    switch (anc)
    {
    case ANC_NW:
        break;
    case ANC_NC:
        *x -= w / 2;
        break;
    case ANC_NE:
        *x -= w;
        break;
    case ANC_CW:
        *y -= h / 2;
        break;
    case ANC_CC:
        *x -= w / 2;
        *y -= h / 2;
        break;
    case ANC_CE:
        *x -= w;
        *y -= h / 2;
        break;
    case ANC_SW:
        *y -= h;
        break;
    case ANC_SC:
        *x -= w / 2;
        *y -= h;
        break;
    case ANC_SE:
        *x -= w;
        *y -= h;
        break;
    default:
        break;
    }
}

SDL_Rect var_uiboxes[BX_SIZE];

int var_button_countdown = 0;
button var_selected_button = BT_NONE;
bool var_buttons_flags[BT_SIZE];

button var_pushed_button = BT_NONE;

void var_reset_buttons(void)
{
    for (int i = 0; i < BT_SIZE; i++)
    {
        var_buttons_flags[i] = false;
    }
}

void var_push_button(button bt)
{
    var_pushed_button = bt;
    var_buttons_flags[bt] = true;
    var_button_countdown = SDL_GetTicks();
    set_flag(PUSHED);
}

void var_release_button(button bt)
{
    var_buttons_flags[bt] = false;
}

button_data var_buttons[BT_SIZE];

/******************************************/
/*+ Initialization of frames and buttons +*/
/******************************************/

#define RCOLWIDTH 320

void init_uiboxes(void)
{

    // Pong Setup
    var_uiboxes[BX_PONGIMENSIONS].x = var_screen_width / 2 - 560 - 16;
    var_uiboxes[BX_PONGIMENSIONS].y = 128;
    var_uiboxes[BX_PONGIMENSIONS].w = 560;
    var_uiboxes[BX_PONGIMENSIONS].h = 144;

    var_uiboxes[BX_PONGPARAMS].x = var_screen_width / 2 - 560 - 16;
    var_uiboxes[BX_PONGPARAMS].y = var_uiboxes[BX_PONGIMENSIONS].y + var_uiboxes[BX_PONGIMENSIONS].h + 16;
    var_uiboxes[BX_PONGPARAMS].w = 560;
    var_uiboxes[BX_PONGPARAMS].h = 144;

    var_uiboxes[BX_PONGP1].x = var_screen_width / 2 + 16;
    var_uiboxes[BX_PONGP1].y = 128;
    var_uiboxes[BX_PONGP1].w = 560;
    var_uiboxes[BX_PONGP1].h = 144;

    var_uiboxes[BX_PONGP2].x = var_screen_width / 2 + 16;
    var_uiboxes[BX_PONGP2].y = var_uiboxes[BX_PONGP1].y + var_uiboxes[BX_PONGP1].h + 16;
    var_uiboxes[BX_PONGP2].w = 560;
    var_uiboxes[BX_PONGP2].h = 144;

    // Brick setup
    var_uiboxes[BX_BRICKDIMENSIONS].x = var_screen_width / 2 - 560 - 16;
    var_uiboxes[BX_BRICKDIMENSIONS].y = 128;
    var_uiboxes[BX_BRICKDIMENSIONS].w = 560;
    var_uiboxes[BX_BRICKDIMENSIONS].h = 256;

    var_uiboxes[BX_BRICKLOAD].x = var_screen_width / 2 - 560 - 16;
    var_uiboxes[BX_BRICKLOAD].y = var_uiboxes[BX_BRICKDIMENSIONS].y + var_uiboxes[BX_BRICKDIMENSIONS].h + 16;
    var_uiboxes[BX_BRICKLOAD].w = 560;
    var_uiboxes[BX_BRICKLOAD].h = 300;

    // Pong HUD
    var_uiboxes[BX_STATUSPONG].x = var_game_width + 5;
    var_uiboxes[BX_STATUSPONG].y = 5;
    var_uiboxes[BX_STATUSPONG].w = var_info_width - 10;
    var_uiboxes[BX_STATUSPONG].h = PONGSTATUSHEIGHT;

    var_uiboxes[BX_P1PONG].x = var_game_width + 5;
    var_uiboxes[BX_P1PONG].y = 5 + PONGSTATUSHEIGHT + 5;
    var_uiboxes[BX_P1PONG].w = var_info_width - 10;
    var_uiboxes[BX_P1PONG].h = PONGPLAYERHEIGHT;

    var_uiboxes[BX_P2PONG].x = var_game_width + 5;
    var_uiboxes[BX_P2PONG].y = 5 + PONGSTATUSHEIGHT + 5 + PONGPLAYERHEIGHT + 5;
    var_uiboxes[BX_P2PONG].w = var_info_width - 10;
    var_uiboxes[BX_P2PONG].h = PONGPLAYERHEIGHT;

    // Brick HUD
    var_uiboxes[BX_STATUSBRICK].x = var_game_width + 5;
    var_uiboxes[BX_STATUSBRICK].y = 5;
    var_uiboxes[BX_STATUSBRICK].w = var_info_width - 10;
    var_uiboxes[BX_STATUSBRICK].h = BRICKSTATUSHEIGHT;

    var_uiboxes[BX_P1BRICK].x = var_game_width + 5;
    var_uiboxes[BX_P1BRICK].y = 5 + BRICKSTATUSHEIGHT + 5;
    var_uiboxes[BX_P1BRICK].w = var_info_width - 10;
    var_uiboxes[BX_P1BRICK].h = BRICKPLAYERHEIGHT;

    var_uiboxes[BX_P2BRICK].x = var_game_width + 5;
    var_uiboxes[BX_P2BRICK].y = 5 + BRICKSTATUSHEIGHT + 5 + BRICKPLAYERHEIGHT + 5;
    var_uiboxes[BX_P2BRICK].w = var_info_width - 10;
    var_uiboxes[BX_P2BRICK].h = BRICKPLAYERHEIGHT;

    // The screen box
    var_uiboxes[BX_SCREEN].x = 0;
    var_uiboxes[BX_SCREEN].y = 0;
    var_uiboxes[BX_SCREEN].w = var_screen_width;
    var_uiboxes[BX_SCREEN].h = var_screen_height;

    // Score
    var_uiboxes[BX_SCORESCREEN].x = 256 / 2;
    var_uiboxes[BX_SCORESCREEN].y = 256 / 2 - 64;

    var_uiboxes[BX_SCORESCREEN].w = var_screen_width - 256;
    // var_uiboxes[BX_SCORESCREEN].h = var_screen_height - 256 + 64;
    var_uiboxes[BX_SCORESCREEN].h = var_screen_height - 256 + 128;

    var_uiboxes[BX_SCOREMODE].w = 500;
    var_uiboxes[BX_SCOREMODE].h = 70;
    var_uiboxes[BX_SCOREMODE].x = var_uiboxes[BX_SCORESCREEN].x + var_uiboxes[BX_SCORESCREEN].w / 2 - var_uiboxes[BX_SCOREMODE].w / 2;
    var_uiboxes[BX_SCOREMODE].y = var_uiboxes[BX_SCORESCREEN].y + var_uiboxes[BX_SCORESCREEN].h - 179;

    // Save/Load
    var_uiboxes[BX_FILENAME].x = (var_screen_width - 768) / 2;
    var_uiboxes[BX_FILENAME].y = (var_screen_height - 128) / 2 - 64;

    var_uiboxes[BX_FILENAME].w = 768;
    var_uiboxes[BX_FILENAME].h = 128;
}

#define SBUTTON_BWIDTH 60
#define SBUTTON_HEIGHT 32
#define LBUTTON_BWIDTH 80
#define LBUTTON_HEIGHT 48
#define TEXTEDIT_HEIGHT 48

void init_one_button(button bt, int x, int y, int w, int h, anchor a, uibox pbox)
{
    var_buttons[bt].parent_box = pbox;
    var_buttons[bt].x = x;
    var_buttons[bt].y = y;
    var_buttons[bt].w = w;
    var_buttons[bt].h = h;
    shift_to_anchor(&var_buttons[bt].x, &var_buttons[bt].y, w, h, a);
    var_buttons[bt].x += var_uiboxes[pbox].x;
    var_buttons[bt].y += var_uiboxes[pbox].y;
    var_buttons[bt].up = bt;
    var_buttons[bt].left = bt;
    var_buttons[bt].down = bt;
    var_buttons[bt].right = bt;
}

void init_boolean_toggle(button bt, int x, int y, uibox pbox)
{
    var_buttons[bt].x = x;
    var_buttons[bt].y = y;
    var_buttons[bt].w = 32;
    var_buttons[bt].h = 32;
    var_buttons[bt].x += var_uiboxes[pbox].x;
    var_buttons[bt].y += var_uiboxes[pbox].y;
    var_buttons[bt].up = bt;
    var_buttons[bt].left = bt;
    var_buttons[bt].down = bt;
    var_buttons[bt].right = bt;
    var_buttons[bt].parent_box = pbox;
}

void init_single_choice_button(button b, int x, int y, int tw, anchor a, uibox pbox)
{
    int h = 32;
    int w = tw + 32;

    var_buttons[b].x = x;
    var_buttons[b].y = y;
    shift_to_anchor(&var_buttons[b].x, &var_buttons[b].y, w, h, a);
    var_buttons[b].parent_box = pbox;
    var_buttons[b].x += var_uiboxes[pbox].x;
    var_buttons[b].y += var_uiboxes[pbox].y;
    var_buttons[b].w = 32;
    var_buttons[b].h = 32;
    var_buttons[b].up = b;
    var_buttons[b].right = b;
    var_buttons[b].down = b;
    var_buttons[b].left = b;
}

void init_double_choice_buttons(button lb, button rb, int x, int y, int tw, anchor a, uibox pbox)
{
    int h = 32;
    int w = 2 * tw + 64; // 32 for each side

    var_buttons[lb].x = x;
    var_buttons[lb].y = y;
    shift_to_anchor(&var_buttons[lb].x, &var_buttons[lb].y, w, h, a);
    var_buttons[lb].parent_box = pbox;
    var_buttons[lb].x += var_uiboxes[pbox].x;
    var_buttons[lb].y += var_uiboxes[pbox].y;
    var_buttons[lb].w = 32;
    var_buttons[lb].h = 32;
    var_buttons[lb].up = lb;
    var_buttons[lb].right = rb;
    var_buttons[lb].down = lb;
    var_buttons[lb].left = lb;

    var_buttons[rb].x = x + w / 2;
    var_buttons[rb].y = y;
    shift_to_anchor(&var_buttons[rb].x, &var_buttons[rb].y, w, h, a);
    var_buttons[rb].parent_box = pbox;
    var_buttons[rb].x += var_uiboxes[pbox].x;
    var_buttons[rb].y += var_uiboxes[pbox].y;
    var_buttons[rb].w = 32;
    var_buttons[rb].h = 32;
    var_buttons[rb].up = rb;
    var_buttons[rb].right = rb;
    var_buttons[rb].down = rb;
    var_buttons[rb].left = lb;
}

void init_triple_choice_buttons(button lb, button mb, button rb, int x, int y, int tw, anchor a, uibox pbox)
{
    int h = 32;
    int w = 3 * tw + 96; // 32 for each side

    var_buttons[lb].x = x;
    var_buttons[lb].y = y;
    shift_to_anchor(&var_buttons[lb].x, &var_buttons[lb].y, w, h, a);
    var_buttons[lb].parent_box = pbox;
    var_buttons[lb].x += var_uiboxes[pbox].x;
    var_buttons[lb].y += var_uiboxes[pbox].y;
    var_buttons[lb].w = 32;
    var_buttons[lb].h = 32;
    var_buttons[lb].up = lb;
    var_buttons[lb].right = mb;
    var_buttons[lb].down = lb;
    var_buttons[lb].left = lb;

    var_buttons[mb].x = x + 32 + tw;
    var_buttons[mb].y = y;
    shift_to_anchor(&var_buttons[mb].x, &var_buttons[mb].y, w, h, a);
    var_buttons[mb].parent_box = pbox;
    var_buttons[mb].x += var_uiboxes[pbox].x;
    var_buttons[mb].y += var_uiboxes[pbox].y;
    var_buttons[mb].w = 32;
    var_buttons[mb].h = 32;
    var_buttons[mb].up = mb;
    var_buttons[mb].right = rb;
    var_buttons[mb].down = lb;
    var_buttons[mb].left = mb;

    var_buttons[rb].x = x + 64 + tw * 2;
    var_buttons[rb].y = y;
    shift_to_anchor(&var_buttons[rb].x, &var_buttons[rb].y, w, h, a);
    var_buttons[rb].parent_box = pbox;
    var_buttons[rb].x += var_uiboxes[pbox].x;
    var_buttons[rb].y += var_uiboxes[pbox].y;
    var_buttons[rb].w = 32;
    var_buttons[rb].h = 32;
    var_buttons[rb].up = rb;
    var_buttons[rb].right = rb;
    var_buttons[rb].down = rb;
    var_buttons[rb].left = mb;
}

void init_selector_buttons(button lb, button rb, int x, int y, int tw, anchor a, uibox pbox)
{
    int h = 32;
    int w = tw + 64; // 32 for each side

    var_buttons[lb].x = x;
    var_buttons[lb].y = y;
    shift_to_anchor(&var_buttons[lb].x, &var_buttons[lb].y, w, h, a);
    var_buttons[lb].parent_box = pbox;
    var_buttons[lb].x += var_uiboxes[pbox].x;
    var_buttons[lb].y += var_uiboxes[pbox].y;
    var_buttons[lb].w = 32;
    var_buttons[lb].h = 32;
    var_buttons[lb].up = lb;
    var_buttons[lb].right = rb;
    var_buttons[lb].down = lb;
    var_buttons[lb].left = lb;

    var_buttons[rb].x = x + 32 + tw;
    var_buttons[rb].y = y;
    shift_to_anchor(&var_buttons[rb].x, &var_buttons[rb].y, w, h, a);
    var_buttons[rb].parent_box = pbox;
    var_buttons[rb].x += var_uiboxes[pbox].x;
    var_buttons[rb].y += var_uiboxes[pbox].y;
    var_buttons[rb].w = 32;
    var_buttons[rb].h = 32;
    var_buttons[rb].up = rb;
    var_buttons[rb].right = rb;
    var_buttons[rb].down = rb;
    var_buttons[rb].left = lb;
}

void init_editor_button(button bt, int x, int y, int lw, int tw, anchor a, uibox pbox)
{
    int w = lw + tw;
    shift_to_anchor(&x, &y, w, TEXTEDIT_HEIGHT, a);
    var_buttons[bt].t_x = x + var_uiboxes[pbox].x;
    x += lw;
    var_buttons[bt].parent_box = pbox;
    var_buttons[bt].x = x + var_uiboxes[pbox].x;
    var_buttons[bt].y = y + var_uiboxes[pbox].y;
    var_buttons[bt].w = tw;
    var_buttons[bt].h = TEXTEDIT_HEIGHT;
    var_buttons[bt].up = BT_NONE;
    var_buttons[bt].right = BT_NONE;
    var_buttons[bt].down = BT_NONE;
    var_buttons[bt].left = BT_NONE;
}

// Main menu
#define MAIN_TOP_BT 310
#define MAIN_STEP 75    // Separation between buttons
#define MAIN_BWIDTH 280 // Button width
#define MAIN_BHEIGHT 58 // Button height

#define HUD_BHEIGHT 46
#define HUD_BWIDTH 276

#define CHECKSKIP 40 // Check box width
#define MENUSKIP 60

void init_all_buttons(void)
{

    init_one_button(BT_PONGGAME, var_screen_width >> 1, MAIN_TOP_BT, MAIN_BWIDTH, MAIN_BHEIGHT, ANC_CC, BX_SCREEN);
    init_one_button(BT_BREAKGAME, var_screen_width >> 1, MAIN_TOP_BT + MAIN_STEP, MAIN_BWIDTH, MAIN_BHEIGHT, ANC_CC, BX_SCREEN);
    init_one_button(BT_SCORESCREEN, var_screen_width >> 1, MAIN_TOP_BT + 2 * MAIN_STEP, MAIN_BWIDTH, MAIN_BHEIGHT, ANC_CC, BX_SCREEN);
    init_one_button(BT_QUIT, var_screen_width >> 1, MAIN_TOP_BT + 3 * MAIN_STEP, MAIN_BWIDTH, MAIN_BHEIGHT, ANC_CC, BX_SCREEN);
    // Main menu
    for (int bt = BT_PONGGAME; bt <= BT_QUIT; bt++)
    {
        var_buttons[bt].up = bt == BT_PONGGAME ? BT_QUIT : (button)(bt - 1);
        var_buttons[bt].right = bt;
        var_buttons[bt].down = bt == BT_QUIT ? BT_PONGGAME : (button)(bt + 1);
        var_buttons[bt].left = bt;
    }

    // Pong Setup
    init_editor_button(BT_SETWIDTH, 32, 72, 130, 110, ANC_NW, BX_PONGIMENSIONS);
    init_editor_button(BT_SETHEIGHT, var_uiboxes[BX_PONGIMENSIONS].w / 2 + 12, 72, 130, 110, ANC_NW, BX_PONGIMENSIONS);
    init_editor_button(BT_PONGNBALLS, 32, 72, 130, 110, ANC_NW, BX_PONGPARAMS);
    init_boolean_toggle(BT_PONGBONUS, 32, 80, BX_PONGPARAMS);
    init_editor_button(BT_PONGNBALLS, var_uiboxes[BX_PONGPARAMS].w / 2 + 12, 72, 130, 110, ANC_NW, BX_PONGPARAMS);
    init_triple_choice_buttons(BT_PONGP1L, BT_PONGP1C, BT_PONGP1R, var_uiboxes[BX_PONGP1].w >> 1, 80, 136, ANC_NC, BX_PONGP1);
    init_triple_choice_buttons(BT_PONGP2L, BT_PONGP2C, BT_PONGP2R, var_uiboxes[BX_PONGP2].w >> 1, 80, 136, ANC_NC, BX_PONGP2);

    init_one_button(BT_PONGLAUNCH, var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, 550, 300, 64, ANC_NC, BX_SCREEN);
    init_one_button(BT_PONGBACK, var_uiboxes[BX_PONGPARAMS].x + var_uiboxes[BX_PONGPARAMS].w / 2, 550, 300, 64, ANC_NC, BX_SCREEN);
    var_buttons[BT_PONGLAUNCH].up = BT_PONGLAUNCH;
    var_buttons[BT_PONGLAUNCH].right = BT_PONGLAUNCH;
    var_buttons[BT_PONGLAUNCH].down = BT_PONGLAUNCH;
    var_buttons[BT_PONGLAUNCH].left = BT_PONGBACK;
    var_buttons[BT_PONGBACK].up = BT_PONGBACK;
    var_buttons[BT_PONGBACK].right = BT_PONGLAUNCH;
    var_buttons[BT_PONGBACK].down = BT_PONGBACK;
    var_buttons[BT_PONGBACK].left = BT_PONGBACK;

    // Brick setup
    init_editor_button(BT_SETBRICKTOP, 32, 128, 130, 110, ANC_NW, BX_BRICKDIMENSIONS);
    init_editor_button(BT_SETBRICKBOT, var_uiboxes[BX_PONGIMENSIONS].w / 2 + 12, 128, 130, 110, ANC_NW, BX_BRICKDIMENSIONS);
    init_editor_button(BT_SETCOLORS, 32, 184, 130, 110, ANC_NW, BX_BRICKDIMENSIONS);
    init_editor_button(BT_SETBRICKHEALTH, var_uiboxes[BX_PONGIMENSIONS].w / 2 + 12, 184, 130, 110, ANC_NW, BX_BRICKDIMENSIONS);

    init_one_button(BT_BRICKGEN, var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, 500, 300, 64, ANC_NC, BX_SCREEN);
    init_one_button(BT_BRICKLOAD, var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, 580, 300, 64, ANC_NC, BX_SCREEN);
    init_one_button(BT_BRICKBACK, var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, 660, 300, 64, ANC_NC, BX_SCREEN);
    for (int bt = BT_BRICKGEN; bt <= BT_BRICKBACK; bt++)
    {
        var_buttons[bt].up = bt == BT_BRICKGEN ? BT_BRICKBACK : (button)(bt - 1);
        var_buttons[bt].right = bt;
        var_buttons[bt].down = bt == BT_BRICKBACK ? BT_BRICKGEN : (button)(bt + 1);
        var_buttons[bt].left = bt;
    }
    int myx = 25;
    int myy = 70;
    for (int i = BT_FILE1; i <= BT_FILE8; i++)
    {
        if (i == BT_FILE5)
        {
            myx = var_uiboxes[BX_BRICKLOAD].w / 2 + 25;
            myy = 70;
        }
        init_single_choice_button(i, myx, myy, 250, ANC_NW, BX_BRICKLOAD);
        myy += 40;
    }
    init_selector_buttons(BT_SELECPAGEL, BT_SELECPAGER, var_uiboxes[BX_BRICKLOAD].w / 2, 40 + 5 * 40, 220, ANC_NC, BX_BRICKLOAD);

    // Game
    init_one_button(BT_PAUSE, var_game_width + (var_info_width >> 1), var_screen_height - 2 * HUD_BHEIGHT - 32, HUD_BWIDTH, HUD_BHEIGHT, ANC_CC, BX_SCREEN);
    init_one_button(BT_BACKMENU, var_game_width + (var_info_width >> 1), var_screen_height - HUD_BHEIGHT - 16, HUD_BWIDTH, HUD_BHEIGHT, ANC_CC, BX_SCREEN);

    // Scores
    init_one_button(BT_SCOREBACK, var_uiboxes[BX_SCORESCREEN].w / 2, var_uiboxes[BX_SCORESCREEN].h - 90, 256, 64, ANC_NC, BX_SCORESCREEN);
    init_one_button(BT_SCORESAVE, var_uiboxes[BX_SCORESCREEN].w / 2 - 8 - 32, var_uiboxes[BX_SCORESCREEN].h - 96 - 64, 256, 64, ANC_NE, BX_SCORESCREEN);
    init_one_button(BT_SCOREMENU, var_uiboxes[BX_SCORESCREEN].w / 2 + 32 + 8, var_uiboxes[BX_SCORESCREEN].h - 96 - 64, 256, 64, ANC_NW, BX_SCORESCREEN);
    init_double_choice_buttons(BT_SCOREMODEL, BT_SCOREMODER, var_uiboxes[BX_SCOREMODE].w / 2, 20, 190, ANC_NC, BX_SCOREMODE);

    int total_width = SC_SIZE * (SCORE_BT_SEP + SCORE_BT_WIDTH) + SCORE_NAME_WIDTH;
    int start = var_uiboxes[BX_SCORESCREEN].w / 2 - total_width / 2;
    start += SCORE_NAME_WIDTH + SCORE_BT_SEP; // Skip name and score

    init_one_button(BT_SCGLOBAL, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCGOALS, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCBONUS, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCHEALTH, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCBRICKS, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCPLAYERS, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;
    init_one_button(BT_SCTIME, start, SCORE_BT_TOP - 48, SCORE_BT_WIDTH, 52, ANC_SW, BX_SCORESCREEN);
    start += SCORE_BT_WIDTH + SCORE_BT_SEP;

    init_one_button(BT_PREVSCORE, var_uiboxes[BX_SCORESCREEN].w / 2 - 64, var_uiboxes[BX_SCORESCREEN].h - 176 - 64, 220, 52, ANC_NE, BX_SCORESCREEN);
    init_one_button(BT_NEXTSCORE, var_uiboxes[BX_SCORESCREEN].w / 2 + 64, var_uiboxes[BX_SCORESCREEN].h - 176 - 64, 220, 52, ANC_NW, BX_SCORESCREEN);

    // Save/Load
    init_editor_button(BT_FILENAME, var_uiboxes[BX_FILENAME].w / 2, 60, 0, 720, ANC_NC, BX_FILENAME);

    return;
}

bool mouse_capture_button(int x, int y, button b)
{
    if (x < var_buttons[b].x || x > var_buttons[b].x + var_buttons[b].w)
    {
        return false;
    }
    if (y < var_buttons[b].y || y > var_buttons[b].y + var_buttons[b].h)
    {
        return false;
    }
    var_push_button(b);
    set_flag(PUSHED);
    return true;
}

/*****************/
/*+ Render text +*/
/*****************/

// Affichage de texte
int render_text(int x, int y, const char *text, TTF_Font *font, SDL_Color textcol, anchor anc)
{

    SDL_Surface *surf_text = TTF_RenderUTF8_Blended(font, text, textcol);
    if (!surf_text)
    {
        fprintf(stderr, "Error creating surface for text: %s\n", TTF_GetError());
        return 0;
    }
    SDL_Texture *text_text = SDL_CreateTextureFromSurface(renderer, surf_text);
    SDL_Rect pos;
    shift_to_anchor(&x, &y, surf_text->w, surf_text->h, anc);
    pos.x = x;
    pos.y = y;
    pos.h = surf_text->h;
    pos.w = surf_text->w;
    SDL_RenderCopy(renderer, text_text, NULL, &pos);
    SDL_FreeSurface(surf_text);
    SDL_DestroyTexture(text_text);
    return pos.w;
}

// Affichage de texte
int render_text_truncate(int x, int y, int max_width, const char *text, TTF_Font *font, SDL_Color textcol, anchor anc)
{

    int len = strlen(text);
    if (max_width <= 0 || len <= max_width)
    {
        return render_text(x, y, text, font, textcol, anc);
    }

    char truncated[15];
    strncpy(truncated, text, sizeof(truncated) - 1);
    truncated[sizeof(truncated) - 4] = '.';
    truncated[sizeof(truncated) - 3] = '.';
    truncated[sizeof(truncated) - 2] = '.';
    truncated[sizeof(truncated) - 1] = '\0';
    return render_text(x, y, truncated, font, textcol, anc);
}

void print_text_buffer_center(void)
{
    if (SDL_GetTicks() % 800 <= 400)
    {
        sprintf(menus_buffer, "%s_", var_editbuffer->content);
    }
    else
    {
        sprintf(menus_buffer, "%s   ", var_editbuffer->content);
    }
}

/***********************************/
/*+ Displaying frames and buttons +*/
/***********************************/

void display_button(button b, const char *label, TTF_Font *font, ui_color color, ui_type type, SDL_Color textcol)
{

    render_color_frame(var_buttons[b].x, var_buttons[b].y, var_buttons[b].w, var_buttons[b].h, color, type, var_buttons_flags[b], ANC_NW);

    int x = var_buttons[b].x + var_buttons[b].w / 2;
    int y = var_buttons[b].y + var_buttons[b].h / 2;
    if (var_buttons_flags[b])
    {
        y += 8; // Offset for pressed buttons
    }

    render_text(x, y - 10, label, font, textcol, ANC_CC);

    if (var_selected_button == b)
    {
        SDL_Rect pos;
        pos.h = 64;
        pos.w = 64;
        pos.x = var_buttons[b].x - pos.w - 4;
        pos.y = var_buttons[b].y - 16;
        SDL_RenderCopy(renderer, txt_cursors, &clp_cursors[CUR_RHAND_SMALL], &pos);
    }
}

void display_boolean_toggle(button bt, const char *text, bool checked, ui_color color)
{
    SDL_Rect pos;
    pos.h = 32;
    pos.w = 32;
    pos.x = var_buttons[bt].x;
    pos.y = var_buttons[bt].y;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_misc_small[checked ? MISC_SBOX_GOK : MISC_SBOX_GEMPTY], &pos);
    render_text(pos.x + 40, pos.y - 4, text, Overbold, WHITE, ANC_NW);
}

void display_one_choice_button(button bt, const char *text, bool checked, ui_color color)
{
    SDL_Rect pos;
    pos.h = 32;
    pos.w = 32;
    pos.x = var_buttons[bt].x;
    pos.y = var_buttons[bt].y;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_misc_small[checked ? MISC_SBOX_GSTOP : MISC_SBOX_GEMPTY], &pos);
    render_text(pos.x + 40, pos.y - 4, text, Overbold, WHITE, ANC_NW);
}

void display_double_choice_buttons(button lb, const char *ltext, button rb, const char *rtext, const char *label, bool left, ui_color color)
{
    display_one_choice_button(lb, ltext, left, color);
    display_one_choice_button(rb, rtext, !left, color);

    if (label)
    {
        render_text(var_buttons[lb].x, var_buttons[lb].y - 44, label, Overbold, WHITE, ANC_NW);
    }
}

void display_triple_choice_buttons(button lb, const char *ltext, button mb, const char *mtext, button rb, const char *rtext, const char *label, int n, ui_color color)
{
    display_one_choice_button(lb, ltext, n == 0, color);
    display_one_choice_button(mb, mtext, n == 1, color);
    display_one_choice_button(rb, rtext, n == 2, color);

    if (label)
    {
        render_text(var_buttons[lb].x, var_buttons[lb].y - 44, label, Overbold, WHITE, ANC_NW);
    }
}

void display_selector_buttons(button lb, button rb, const char *text, ui_color color)
{

    SDL_Rect pos;
    pos.h = 32;
    pos.w = 32;
    pos.x = var_buttons[lb].x;
    pos.y = var_buttons[lb].y;
    SDL_RenderCopy(renderer, var_buttons_flags[lb] ? txt_ui[COL_GRAY] : txt_ui[color], &clp_misc_small[MISC_ARROW_WEST], &pos);
    render_text((var_buttons[lb].x + 32 + var_buttons[rb].x) / 2, pos.y - 4, text, Overbold, WHITE, ANC_NC);

    pos.x = var_buttons[rb].x;
    pos.y = var_buttons[rb].y;
    SDL_RenderCopy(renderer, var_buttons_flags[rb] ? txt_ui[COL_GRAY] : txt_ui[color], &clp_misc_small[MISC_ARROW_EAST], &pos);
}

void display_editor_button(button bt, const char *label, const char *string, ui_color color, SDL_Color label_color, SDL_Color edit_color)
{

    render_color_frame(var_buttons[bt].x, var_buttons[bt].y, var_buttons[bt].w, var_buttons[bt].h, color, UITYPE_PLAIN, true, ANC_NW);
    render_text(var_buttons[bt].x + var_buttons[bt].w / 2, var_buttons[bt].y + 4, string, Overbold, edit_color, ANC_NC);
    render_text(var_buttons[bt].x - 8, var_buttons[bt].y + 4, label, Overbold, label_color, ANC_NE);
}

void render_ui_box_advanced(uibox box, ui_advframe frame)
{
    int x = var_uiboxes[box].x;
    int y = var_uiboxes[box].y;
    int w = var_uiboxes[box].w;
    int h = var_uiboxes[box].h;
    render_advanced_frame(x, y, w, h, frame, ANC_NW);
}

void render_color_frame(int x, int y, int w, int h, ui_color color, ui_type type, bool on, anchor anc)
{

    h = max(h, 32);
    w = max(w, 32);

    shift_to_anchor(&x, &y, w, h, anc);

    if (!on)
    {
        y -= 8;
    }

    SDL_Rect pos;

    pos.y = y;

    int midh = h - 32;
    int midw = w - 32;

    // Top line
    pos.x = x;
    pos.y = y;
    pos.h = 16;
    pos.w = 16;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_NW], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_N], &pos);
        pos.x += midw;
    }
    pos.w = 16;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_NE], &pos);

    // Middle line
    pos.x = x;
    pos.y += 16;
    pos.h = midh;
    pos.w = 16;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_W], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_C], &pos);
        pos.x += midw;
    }
    pos.w = 16;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][UICA_E], &pos);

    // Bottom line
    pos.x = x;
    pos.y += midh;
    pos.h = on ? 16 : 24;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][on ? UICA_SW : UICA_SW_OFF], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][on ? UICA_S : UICA_S_OFF], &pos);
        pos.x += midw;
    }
    pos.w = 16;
    SDL_RenderCopy(renderer, txt_ui[color], &clp_frames[type][on ? UICA_SE : UICA_SE_OFF], &pos);
}

static void render_ui_box_color(uibox box, ui_color color, ui_type type)
{
    int x = var_uiboxes[box].x;
    int y = var_uiboxes[box].y;
    int w = var_uiboxes[box].w;
    int h = var_uiboxes[box].h;
    render_color_frame(x, y, w, h, color, type, true, ANC_NW);
}

void render_advanced_frame(int x, int y, int w, int h, ui_advframe frame, anchor anc)
{
    h = max(h, 64);
    w = max(w, 64);

    shift_to_anchor(&x, &y, w, h, anc);

    SDL_Rect pos;
    pos.y = y;
    int midh = h - 64;
    int midw = w - 64;

    // Top line
    pos.x = x;
    pos.y = y;
    pos.h = 32;
    pos.w = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_NW], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_N], &pos);
        pos.x += midw;
    }
    pos.w = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_NE], &pos);

    // Middle line
    pos.x = x;
    pos.y += 32;
    pos.h = midh;
    pos.w = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_W], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_C], &pos);
        pos.x += midw;
    }
    pos.w = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_E], &pos);

    // Bottom line
    pos.x = x;
    pos.y += midh;
    pos.h = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_SW], &pos);
    pos.x += pos.w;
    if (midw > 0)
    {
        pos.w = midw;
        SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_S], &pos);
        pos.x += midw;
    }
    pos.w = 32;
    SDL_RenderCopy(renderer, txt_advanced, &clp_advanced[frame][UICA_SE], &pos);
}

/***************/
/*+ Main menu +*/
/***************/

void render_mainmenu(void)
{
    int y = 120;
    render_color_frame(var_screen_width / 2, y, 860, 110, COL_RED, UITYPE_SHADE, true, ANC_CC);
    render_text(var_screen_width / 2, y - 6, "Breaking Bricks in C", OverboldL, WHITE, ANC_CC);

    display_button(BT_PONGGAME, "Pong game", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_BREAKGAME, "Breakout game", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_SCORESCREEN, "Scores", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_QUIT, "Quit", Overbold, COL_RED, UITYPE_SHADE, WHITE);

    // if (var_high_scores)
    // {
    //     render_score_screen(2);
    // }

    // if (var_edit_mode == ED_LOAD)
    // {
    //     render_textbox_menu("Enter the filename to load a game.", ADV_DARK_GREY, WHITE, COL_RED, WHITE);
    // }
}

void render_pongmenu(void)
{
    render_ui_box_advanced(BX_PONGIMENSIONS, ADV_DARK_GREY);

    render_text(var_uiboxes[BX_PONGIMENSIONS].x + var_uiboxes[BX_PONGIMENSIONS].w / 2, var_uiboxes[BX_PONGIMENSIONS].y + 22, "Dimensions of the board", Overbold, WHITE, ANC_NC);
    if (var_edit_mode == ED_WIDTH)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_nb_columns);
    }
    display_editor_button(BT_SETWIDTH, "Columns:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_HEIGHT)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_nb_rows);
    }
    display_editor_button(BT_SETHEIGHT, "Rows:", menus_buffer, COL_RED, WHITE, WHITE);

    render_ui_box_advanced(BX_PONGPARAMS, ADV_DARK_GREY);
    render_text(var_uiboxes[BX_PONGPARAMS].x + var_uiboxes[BX_PONGPARAMS].w / 2, var_uiboxes[BX_PONGPARAMS].y + 22, "Parameters", Overbold, WHITE, ANC_NC);
    display_boolean_toggle(BT_PONGBONUS, "Bonuses active", var_game_bonuses, COL_RED);
    if (var_edit_mode == ED_BALLS)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_nb_balls);
    }
    display_editor_button(BT_PONGNBALLS, "Balls:", menus_buffer, COL_RED, WHITE, WHITE);
    render_ui_box_advanced(BX_PONGP1, ADV_DARK_GREY);
    render_ui_box_advanced(BX_PONGP2, ADV_DARK_GREY);
    render_text(var_uiboxes[BX_PONGP1].x + var_uiboxes[BX_PONGP1].w / 2, var_uiboxes[BX_PONGP1].y + 22, "Player 1", Overbold, WHITE, ANC_NC);
    render_text(var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, var_uiboxes[BX_PONGP2].y + 22, "Player 2", Overbold, WHITE, ANC_NC);

    display_triple_choice_buttons(BT_PONGP1L, "None", BT_PONGP1C, "AI", BT_PONGP1R, "Human", NULL, var_game_player_one_mode, COL_RED);
    display_triple_choice_buttons(BT_PONGP2L, "None", BT_PONGP2C, "AI", BT_PONGP2R, "Human", NULL, var_game_player_two_mode, COL_RED);

    display_button(BT_PONGLAUNCH, "Launch Pong game", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_PONGBACK, "Back to Menu", Overbold, COL_RED, UITYPE_SHADE, WHITE);
}

void render_brickmenu(void)
{
    render_ui_box_advanced(BX_BRICKDIMENSIONS, ADV_DARK_GREY);

    render_text(var_uiboxes[BX_BRICKDIMENSIONS].x + var_uiboxes[BX_BRICKDIMENSIONS].w / 2, var_uiboxes[BX_BRICKDIMENSIONS].y + 22, "Parameters for random generation", Overbold, WHITE, ANC_NC);
    if (var_edit_mode == ED_WIDTH)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_nb_columns);
    }
    display_editor_button(BT_SETWIDTH, "Columns:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_HEIGHT)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_nb_rows);
    }
    display_editor_button(BT_SETHEIGHT, "Rows:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_TOP)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_topspace);
    }
    display_editor_button(BT_SETBRICKTOP, "Top:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_BOTTOM)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_bottomspace);
    }
    display_editor_button(BT_SETBRICKBOT, "Bottom:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_COLORS)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_brick_colors);
    }
    display_editor_button(BT_SETCOLORS, "Colors:", menus_buffer, COL_RED, WHITE, WHITE);

    if (var_edit_mode == ED_HEALTH)
    {
        print_text_buffer_center();
    }
    else
    {
        sprintf(menus_buffer, "%d", var_game_brick_health);
    }
    display_editor_button(BT_SETBRICKHEALTH, "Health:", menus_buffer, COL_RED, WHITE, WHITE);

    render_ui_box_advanced(BX_PONGP1, ADV_DARK_GREY);
    render_ui_box_advanced(BX_PONGP2, ADV_DARK_GREY);
    render_text(var_uiboxes[BX_PONGP1].x + var_uiboxes[BX_PONGP1].w / 2, var_uiboxes[BX_PONGP1].y + 22, "Player 1", Overbold, WHITE, ANC_NC);
    render_text(var_uiboxes[BX_PONGP2].x + var_uiboxes[BX_PONGP2].w / 2, var_uiboxes[BX_PONGP2].y + 22, "Player 2", Overbold, WHITE, ANC_NC);

    display_triple_choice_buttons(BT_PONGP1L, "None", BT_PONGP1C, "AI", BT_PONGP1R, "Human", NULL, var_game_player_one_mode, COL_RED);
    display_triple_choice_buttons(BT_PONGP2L, "None", BT_PONGP2C, "AI", BT_PONGP2R, "Human", NULL, var_game_player_two_mode, COL_RED);

    display_button(BT_BRICKGEN, "Random Game", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_BRICKLOAD, "Load Game", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_BRICKBACK, "Back to Menu", Overbold, COL_RED, UITYPE_SHADE, WHITE);

    render_ui_box_advanced(BX_BRICKLOAD, ADV_DARK_GREY);
    render_text(var_uiboxes[BX_BRICKLOAD].x + var_uiboxes[BX_BRICKLOAD].w / 2, var_uiboxes[BX_BRICKLOAD].y + 22, "File to Load", Overbold, WHITE, ANC_NC);
    int first_file_index = FILE_PER_PAGE * var_levelpageindex;
    int last_file_index = min(first_file_index + FILE_PER_PAGE, var_leveltabsize);
    for (int i = 0; i < last_file_index - first_file_index; i++)
    {
        display_one_choice_button(BT_FILE1 + i, var_levelstab[first_file_index + i]->d_name, first_file_index + i == var_levelindex, COL_RED);
    }
    sprintf(menus_buffer, "Page %d / %d", var_levelpageindex + 1, (var_leveltabsize + FILE_PER_PAGE - 1) / FILE_PER_PAGE);
    display_selector_buttons(BT_SELECPAGEL, BT_SELECPAGER, menus_buffer, COL_RED);
}

/**************/
/*+ Pong Hud +*/
/**************/

static void render_health(int x, int y, int health)
{

    if (health <= 7)
    {
        for (int i = 0; i < health; i++)
        {
            SDL_Rect pos;
            pos.x = x - i * 32;
            pos.y = y + 8;
            pos.w = 28;
            pos.h = 28;
            SDL_RenderCopy(renderer, txt_balls, &clp_objects[CLP_HEART], &pos);
        }
        return;
    }
    else
    {
        SDL_Rect pos;
        pos.x = x;
        pos.y = y + 8;
        pos.w = 28;
        pos.h = 28;
        SDL_RenderCopy(renderer, txt_balls, &clp_objects[CLP_HEART], &pos);
        sprintf(menus_buffer, "%d x ", health);
        render_text(x, y, menus_buffer, Overbold, BLACK, ANC_NE);
    }
}

void render_pong_hud(void)
{
    render_ui_box_color(BX_STATUSPONG, COL_BLUE, UITYPE_EDGE);
    render_text(var_game_width + var_info_width / 2, 20, "Game status", Overbold, BLACK, ANC_NC);
    render_text(var_game_width + 40, 70, "In-game balls:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->nb_balls);
    render_text(var_screen_width - 40, 70, menus_buffer, Overbold, BLACK, ANC_NE);
    render_text(var_game_width + 40, 110, "Time:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%dm %ds", get_time_counter() / 60000, (get_time_counter() % 60000) / 1000);
    render_text(var_screen_width - 40, 110, menus_buffer, Overbold, BLACK, ANC_NE);

    int nb_players = var_game->paddles[0] ? 1 : 0;
    nb_players += var_game->paddles[1] ? 1 : 0;
    if (nb_players == 0)
    {
        return;
    }
    int fp = var_game->paddles[0] ? true : false;

    render_ui_box_color(BX_P1PONG, COL_GREEN, UITYPE_EDGE);
    render_text(var_game_width + var_info_width / 2, 25 + PONGSTATUSHEIGHT, fp ? "Player 1 status" : "Player 2 status", Overbold, BLACK, ANC_NC);
    render_text(var_game_width + 40, 75 + PONGSTATUSHEIGHT, "Health:", Overbold, BLACK, ANC_NW);
    render_health(var_screen_width - 65, 75 + PONGSTATUSHEIGHT, var_game->paddles[fp ? 0 : 1]->health);
    render_text(var_game_width + 40, 115 + PONGSTATUSHEIGHT, "Goals:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->goals);
    render_text(var_screen_width - 40, 115 + PONGSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);
    render_text(var_game_width + 40, 155 + PONGSTATUSHEIGHT, "Score:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->score);
    render_text(var_screen_width - 40, 155 + PONGSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

    if (nb_players == 2)
    {
        render_ui_box_color(BX_P2PONG, COL_GREEN, UITYPE_EDGE);
        render_text(var_game_width + var_info_width / 2, 30 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, "Player 2 status", Overbold, BLACK, ANC_NC);
        render_text(var_game_width + 40, 80 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, "Health:", Overbold, BLACK, ANC_NW);
        render_health(var_screen_width - 65, 80 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, var_game->paddles[1]->health);
        render_text(var_game_width + 40, 120 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, "Goals:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->goals);
        render_text(var_screen_width - 40, 120 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);
        render_text(var_game_width + 40, 160 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, "Score:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->score);
        render_text(var_screen_width - 40, 160 + PONGSTATUSHEIGHT + PONGPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);
    }

    display_button(BT_PAUSE, "Pause", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_BACKMENU, "Back to Menu", Overbold, COL_RED, UITYPE_SHADE, WHITE);

    // char score[20];
    // sprintf(score, "Score = %d", g->score);
    // render_text(var_game_width + var_info_width / 2, 60, remaining, Overbold, WHITE, ANC_NC);
}

void render_brick_hud(void)
{
    render_ui_box_color(BX_STATUSBRICK, COL_BLUE, UITYPE_EDGE);
    render_text(var_game_width + var_info_width / 2, 20, "Game status", Overbold, BLACK, ANC_NC);
    render_text(var_game_width + 40, 70, "In-game balls:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->nb_balls);
    render_text(var_screen_width - 40, 70, menus_buffer, Overbold, BLACK, ANC_NE);
    render_text(var_game_width + 40, 110, "In-game bricks:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->nb_bricks);
    render_text(var_screen_width - 40, 110, menus_buffer, Overbold, BLACK, ANC_NE);
    render_text(var_game_width + 40, 150, "Time:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%dm %ds", get_time_counter() / 60000, (get_time_counter() % 60000) / 1000);
    render_text(var_screen_width - 40, 150, menus_buffer, Overbold, BLACK, ANC_NE);

    int nb_players = var_game->paddles[0] ? 1 : 0;
    nb_players += var_game->paddles[1] ? 1 : 0;
    if (nb_players == 0)
    {
        return;
    }
    int fp = var_game->paddles[0] ? true : false;

    render_ui_box_color(BX_P1BRICK, COL_GREEN, UITYPE_EDGE);
    render_text(var_game_width + var_info_width / 2, 25 + BRICKSTATUSHEIGHT, fp ? "Player 1 status" : "Player 2 status", Overbold, BLACK, ANC_NC);
    render_text(var_game_width + 40, 75 + BRICKSTATUSHEIGHT, "Health:", Overbold, BLACK, ANC_NW);
    render_health(var_screen_width - 65, 75 + BRICKSTATUSHEIGHT, var_game->paddles[fp ? 0 : 1]->health);
    render_text(var_game_width + 40, 115 + BRICKSTATUSHEIGHT, "Goals:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->goals);
    render_text(var_screen_width - 40, 115 + BRICKSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

    render_text(var_game_width + 40, 155 + BRICKSTATUSHEIGHT, "Bricks killed:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->bricks);
    render_text(var_screen_width - 40, 155 + BRICKSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

    render_text(var_game_width + 40, 195 + BRICKSTATUSHEIGHT, "Bonuses taken:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->bonuses);
    render_text(var_screen_width - 40, 195 + BRICKSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

    render_text(var_game_width + 40, 235 + BRICKSTATUSHEIGHT, "Score:", Overbold, BLACK, ANC_NW);
    sprintf(menus_buffer, "%d", var_game->paddles[fp ? 0 : 1]->score);
    render_text(var_screen_width - 40, 235 + BRICKSTATUSHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

    if (nb_players == 2)
    {
        render_ui_box_color(BX_P2BRICK, COL_GREEN, UITYPE_EDGE);
        render_text(var_game_width + var_info_width / 2, 30 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Player 2 status", Overbold, BLACK, ANC_NC);
        render_text(var_game_width + 40, 80 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Health:", Overbold, BLACK, ANC_NW);
        render_health(var_screen_width - 65, 80 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, var_game->paddles[1]->health);
        render_text(var_game_width + 40, 120 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Goals:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->goals);
        render_text(var_screen_width - 40, 120 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

        render_text(var_game_width + 40, 160 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Bricks killed:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->bricks);
        render_text(var_screen_width - 40, 160 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

        render_text(var_game_width + 40, 200 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Bonuses taken:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->bonuses);
        render_text(var_screen_width - 40, 200 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);

        render_text(var_game_width + 40, 240 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, "Score:", Overbold, BLACK, ANC_NW);
        sprintf(menus_buffer, "%d", var_game->paddles[1]->score);
        render_text(var_screen_width - 40, 240 + BRICKSTATUSHEIGHT + BRICKPLAYERHEIGHT, menus_buffer, Overbold, BLACK, ANC_NE);
    }

    display_button(BT_PAUSE, "Pause", Overbold, COL_RED, UITYPE_SHADE, WHITE);
    display_button(BT_BACKMENU, "Back to Menu", Overbold, COL_RED, UITYPE_SHADE, WHITE);

    // char score[20];
    // sprintf(score, "Score = %d", g->score);
    // render_text(var_game_width + var_info_width / 2, 60, remaining, Overbold, WHITE, ANC_NC);
}

/******************/
/*+ Score screen +*/
/******************/

void render_score_screen(void)
{

    int middle = var_uiboxes[BX_SCORESCREEN].x + var_uiboxes[BX_SCORESCREEN].w / 2;

    render_ui_box_color(BX_SCORESCREEN, COL_YELLOW, UITYPE_EDGE);

    if (var_score_table_end)
    {
        if (var_score_mode == 0)
        {
            sprintf(menus_buffer, "Pong game over!%s", var_score_winner == -1 ? "" : var_score_winner == 0 ? " Player 1 wins!"
                                                                                                           : " Player 2 wins!");
        }
        else
        {
            sprintf(menus_buffer, "Brick game over!%s", var_score_winner == -1 ? " You lost!" : " You won!");
        }
        // printf("%d\n", var_score_winner);

        // printf("one\n");
        display_button(BT_SCORESAVE, "Save and Close", Overbold, COL_YELLOW, UITYPE_SHADE, BLACK);
        display_button(BT_SCOREMENU, "Close", Overbold, COL_YELLOW, UITYPE_SHADE, BLACK);
    }
    else
    {
        sprintf(menus_buffer, "High scores (%s mode)", var_score_mode == 0 ? "Pong" : "Brick");

        display_button(BT_SCOREBACK, "Close", Overbold, COL_YELLOW, UITYPE_SHADE, BLACK);
        render_ui_box_advanced(BX_SCOREMODE, ADV_DARK_GREY);
        display_double_choice_buttons(BT_SCOREMODEL, "Pong Scores", BT_SCOREMODER, "Brick Scores", NULL, var_score_mode == 0, COL_YELLOW);
    }

    render_text(var_uiboxes[BX_SCORESCREEN].x + var_uiboxes[BX_SCORESCREEN].w / 2, var_uiboxes[BX_SCORESCREEN].y + 38, menus_buffer, Overbold, BLACK, ANC_NC);

    display_button(BT_SCGLOBAL, "Score", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCGOALS, "Goals", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCBONUS, "Bonuses", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCHEALTH, "Health", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCBRICKS, "Bricks", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCTIME, "Time", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    // display_button(BT_SCTYPE, "Types", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    display_button(BT_SCPLAYERS, "Players", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);

    if (var_scores_page > 0)
    {
        display_button(BT_PREVSCORE, "Previous Page", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    }
    else
    {
        display_button(BT_PREVSCORE, "Previous Page", Overbold, COL_GRAY, UITYPE_PLAIN, BLACK);
    }

    sprintf(menus_buffer, "%d/%d", var_scores_page + 1, var_scores_max_page);
    render_text(middle, var_uiboxes[BX_SCORESCREEN].y + var_uiboxes[BX_SCORESCREEN].h - 236, menus_buffer, Overbold, BLACK, ANC_NC);
    if (var_scores_page < var_scores_max_page - 1)
    {
        display_button(BT_NEXTSCORE, "Next Page", Overbold, COL_YELLOW, UITYPE_PLAIN, BLACK);
    }
    else
    {
        display_button(BT_NEXTSCORE, "Next Page", Overbold, COL_GRAY, UITYPE_PLAIN, BLACK);
    }

    int top = SCORE_NB_TOP;

    int total_width = SC_SIZE * (SCORE_BT_SEP + SCORE_BT_WIDTH) + SCORE_NAME_WIDTH;

    if (var_scores_page >= var_scores_max_page || var_scores_page < 0)
    {
        var_scores_page = 0; // Reset page if out of range
    }

    for (int i = var_scores_page * var_scores_per_page; i < min(var_score_table->size, (var_scores_page + 1) * var_scores_per_page); i++)
    {
        // printf("%d\n", i);
        int start = middle - (total_width / 2);
        sprintf(menus_buffer, "*%d*", i + 1);
        render_text(start + 50, top, menus_buffer, Overbold, BLACK, ANC_CE);
        int k = var_score_table->permutation[i];
        if (k == var_score_table->player_index)
        {
            render_text_truncate(start + 60, top, 25, var_score_table->names[k], Overbold, BLUET, ANC_CW);
        }
        else
        {
            render_text_truncate(start + 60, top, 25, var_score_table->names[k], Overbold, BLACK, ANC_CW);
        }

        start += SCORE_NAME_WIDTH + SCORE_BT_SEP + SCORE_BT_WIDTH / 2;

        for (int j = 0; j < SC_SIZE - 1; j++)
        {
            sprintf(menus_buffer, "%d", var_score_table->scores[k][j]);
            render_text(start, top, menus_buffer, Overbold, BLACK, ANC_CC);
            start += SCORE_BT_WIDTH + SCORE_BT_SEP;
        }
        sprintf(menus_buffer, "%dm %ds", var_score_table->scores[k][SC_TIME] / 60, var_score_table->scores[k][SC_TIME] % 60);
        render_text(start, top, menus_buffer, Overbold, BLACK, ANC_CC);
        top += SCORE_NB_STEP;
    }

    if (var_edit_mode == ED_NAME)
    {
        render_textbox_menu("Enter your name to save your score.", ADV_DARK_BROWN, WHITE, COL_YELLOW, BLACK);
    }
}

/***************/
/*+ Save/Load +*/
/***************/

void render_textbox_menu(const char *message, ui_advframe backframe, SDL_Color message_color, ui_color box_color, SDL_Color edit_color)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

    render_ui_box_advanced(BX_FILENAME, backframe);
    render_text(var_uiboxes[BX_FILENAME].x + var_uiboxes[BX_FILENAME].w / 2, var_uiboxes[BX_FILENAME].y + 16, message, Overbold, message_color, ANC_NC);
    print_text_buffer_center();
    display_editor_button(BT_FILENAME, " ", menus_buffer, box_color, edit_color, edit_color);
}
