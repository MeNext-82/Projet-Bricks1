/**
 * @file gui_init_graphic.h
 * @brief
 * Interface: initialisation de l'affichage. Ne PAS modifier.
 *
 * @attention
 * Cette partie est déjà implémentée. Il ne faut PAS la modifier.
 */

#ifndef UIDEFS_H_
#define UIDEFS_H_

// #include "gui_gamevars.h"
// #include "gui_textbuf.h"
#include "../error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
/*  ___       _ _   _       _ _           _   _                   _       */
/* |_ _|_ __ (_) |_(_) __ _| (_)___  __ _| |_(_) ___  _ __     __| | ___  */
/*  | || '_ \| | __| |/ _` | | / __|/ _` | __| |/ _ \| '_ \   / _` |/ _ \ */
/*  | || | | | | |_| | (_| | | \__ \ (_| | |_| | (_) | | | | | (_| |  __/ */
/* |___|_| |_|_|\__|_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|  \__,_|\___| */
/* | ( ) __ _ / _|/ _(_) ___| |__   __ _  __ _  ___                       */
/* | |/ / _` | |_| |_| |/ __| '_ \ / _` |/ _` |/ _ \                      */
/* | | | (_| |  _|  _| | (__| | | | (_| | (_| |  __/                      */
/* |_|  \__,_|_| |_| |_|\___|_| |_|\__,_|\__, |\___|                      */
/*                                       |___/                            */

/**************/
/*+ Couleurs +*/
/**************/

/**
 * @brief Noir.
 */
static const SDL_Color BLACK = {0, 0, 0, 255};

static const SDL_Color GREYT = {30, 30, 30, 255};

/**
 * @brief Blanc.
 */
static const SDL_Color WHITE = {255, 255, 255, 255};

/**
 * @brief Rouge
 */
static const SDL_Color REDT = {255, 43, 31, 200};

/**
 * @brief Vert
 */
static const SDL_Color GREENT = {16, 253, 56, 200};

/**
 * @brief Bleu
 */
static const SDL_Color BLUET = {25, 25, 252, 200};

/**
 * @brief Orange
 */
static const SDL_Color ORANGET = {239, 216, 7, 200};

/**
 * @brief Carmin
 */
static const SDL_Color CARML = {255, 0, 56, 255};

/**
 * @brief Carmin 2
 */
static const SDL_Color CARMT = {250, 235, 215, 200};

#define COLOR_TUPLE(color) ((color).r), ((color).g), ((color).b), ((color).a)

/* Brick colors */
// #define CELL_WIDTH 384
#define CELL_X 366
#define CELL_Y 128

#define BLOCK_Y 128
#define BLOCK_X 485

// Brick size
#ifndef ZOOM
#define ZOOM 2
#endif

/***********/
/*+ Fonts +*/
/***********/

extern TTF_Font *Sans18, *Sans16, *Paci20, *Over, *Overbold, *OverboldL;

/**
 * @brief Chargement des fonts.
 */
void init_fonts(void);

/*************/
/*+ Sprites +*/
/*************/

/**
 * @brief Initialisation du module pour charger les PNGs.
 */
void init_image(void);

typedef enum
{
    COL_BLUE,
    COL_GREEN,
    COL_GRAY,
    COL_RED,
    COL_YELLOW,
    COL_SIZE
} ui_color;

typedef enum
{
    UITYPE_EDGE,
    UITYPE_PLAIN,
    UITYPE_DEMI,
    UITYPE_SHADE,
    UITYPE_LINE,
    UITYPE_SIZE
} ui_type;

typedef enum
{
    UICON_UP,
    UICON_CROSS,
    UICON_SIZE
} ui_icons;

typedef enum
{
    UICA_NW,
    UICA_N,
    UICA_NE,
    UICA_W,
    UICA_C,
    UICA_E,
    UICA_SW,
    UICA_S,
    UICA_SE,
    UICA_SW_OFF,
    UICA_S_OFF,
    UICA_SE_OFF,
    UICA_SIZE
} ui_cardinals;

typedef enum
{
    MISC_ARROW_EAST,
    MISC_ARROW_NORTH,
    MISC_ARROW_SOUTH,
    MISC_ARROW_WEST,
    MISC_CARROW_EAST,
    MISC_CARROW_NORTH,
    MISC_CARROW_SOUTH,
    MISC_CARROW_WEST,
    MISC_RBOX_COLOR,
    MISC_RBOX_GRAY,
    MISC_RBOX_GFILLED,
    MISC_RBOX_CFILLED,
    MISC_SBOX_EMPTY,
    MISC_SBOX_OK,
    MISC_SBOX_NO,
    MISC_SBOX_STOP,
    MISC_SBOX_GEMPTY,
    MISC_SBOX_GOK,
    MISC_SBOX_GNO,
    MISC_SBOX_GSTOP,
    MISC_SIZE
} ui_misc;

typedef enum
{
    CUR_RIGHT,
    CUR_UP,
    CUR_RIGHTUP,
    CUR_LEFTUP,
    CUR_DOWN,
    CUR_RIGHTDOWN,
    CUR_LEFTDOWN,
    CUR_LEFT,
    CUR_CROSS_BIG,
    CUR_CROSS_SMALL,
    CUR_HAND_BIG,
    CUR_RHAND_BIG,
    CUR_UHAND_BIG,
    CUR_HAND_SMALL,
    CUR_RHAND_SMALL,
    CUR_UHAND_SMALL,
    CUR_THAND,
    CUR_VTHAND,
    CUR_PLUS,
    CUR_MINUS,
    CUR_LOCK,
    CUR_UNLOCK,
    CUR_BANG,
    CUR_QUESTION,
    CUR_SELEC_BIG,
    CUR_SELEC_SMALL,
    CUR_REWIND_LEFT,
    CUR_REWIND_RIGHT,
    CUR_BOMB,
    CUR_ZOOM_NEUTRAL,
    CUR_ZOOM_IN,
    CUR_ZOOM_OUT,
    CUR_SIZE
} ui_cursors;

typedef enum
{
    CIRCLE_BROWN,
    CIRCLE_GREY,
    CIRCLE_WHITE,
    CIRCLE_SIZE,
} ui_circle;

typedef enum
{
    ADV_LIGHT_BROWN,
    ADV_DARK_BROWN,
    ADV_LIGHT_GREY,
    ADV_BLUE,
    ADV_DARK_GREY,
    ADV_GREEN,
    ADV_RED,
    ADV_FRAMES_SIZE,
} ui_advframe;

typedef enum
{
    GAUGE_LEFT,   //!< Gauge left.
    GAUGE_CENTER, //!< Gauge center.
    GAUGE_RIGHT,  //!< Gauge right.
    GAUGE_SIZE,   //!< Element size.
} GAUGEs;

extern SDL_Texture *txt_ui[COL_SIZE];
extern SDL_Texture *txt_cursors;
extern SDL_Texture *txt_icons;
extern SDL_Texture *txt_advanced;
extern SDL_Texture *txt_bigarrows;
extern SDL_Texture *txt_objects;
extern SDL_Texture *txt_bricks;
extern SDL_Texture *txt_bonuses;
extern SDL_Texture *txt_paddle;
extern SDL_Texture *txt_spaddle;
extern SDL_Texture *txt_lpaddle;
extern SDL_Texture *txt_balls;

typedef enum
{
    CLP_SOLID,
    CLP_ANIM1,
    CLP_ANIM2,
    CLP_ANIM3,
    CLP_ANIM4,
    CLP_ANIM5,
    CLP_ANIM6,
    CLP_ANIM7,
    CLP_CRACKED1,
    CLP_CRACKED2,
    CLP_CRACKED3,
    CLP_BRSIZE,
} clip_bricks;

typedef enum
{
    CLP_MULTIBALL,
    CLP_COLORMODE,
    CLP_CLASSICMODE,
    CLP_SCORE500,
    CLP_SLOWDOWN,
    CLP_SPEEDUP,
    CLP_SCORE50,
    CLP_SCORE100,
    CLP_SCORE250,
    CLP_SHRINK,
    CLP_GROW,
    CLP_GRAVITY,
    CLP_BLANK,
    CLP_BNSIZE
} clip_bonuses;

typedef enum
{
    CLP_PADDLE_1,
    CLP_PADDLE_2,
    CLP_PADDLE_3,
    CLP_PADDLE_LONG_1,
    CLP_PADDLE_LONG_2,
    CLP_PADDLE_LONG_3,
    CLP_PADDLE_SHORT,
    CLP_BALL_1,
    CLP_BALL_2,
    CLP_BALL_RED_1,
    CLP_BALL_RED_2,
    CLP_BALL_GREEN_1,
    CLP_BALL_GREEN_2,
    CLP_STAR,
    CLP_HEART,
    CLP_OBSIZE
} clip_objects;

extern SDL_Rect clp_gauges[GAUGE_SIZE];
extern SDL_Rect clp_misc_large[MISC_SIZE];
extern SDL_Rect clp_misc_small[MISC_SIZE];
extern SDL_Rect clp_round_buttons[UITYPE_SIZE];
extern SDL_Rect clp_square_buttons[UITYPE_SIZE];
extern SDL_Rect clp_frames[UITYPE_SIZE][UICA_SIZE];
extern SDL_Rect clp_cursors[CUR_SIZE];
extern SDL_Rect clp_circles[CIRCLE_SIZE];
extern SDL_Rect clp_icons[UICON_SIZE];
extern SDL_Rect clp_advanced[ADV_FRAMES_SIZE][UICA_SW_OFF];
extern SDL_Rect clp_bigarrows[CUR_CROSS_BIG];
extern SDL_Rect clp_bricks[10][CLP_BRSIZE];
extern SDL_Rect clp_bonuses[CLP_BNSIZE][7];
extern SDL_Rect clp_objects[CLP_OBSIZE];
/**
 * @brief Initialisation des sprites.
 */
void init_load_sprites(void);

/*****************/
/*+ Fenêtre SDL +*/
/*****************/

extern SDL_Window *window;
extern SDL_Renderer *renderer;

/**
 * @brief Initialisation de la fenêtre SDL.
 */
bool init_SDL(int sc_width, int sc_height);

/**
 * @brief Fermeture de SDL.
 */
void shutdown_SDL(void);

#endif // UIDEFS_H_
