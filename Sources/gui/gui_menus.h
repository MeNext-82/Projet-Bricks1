/**
 * @file gui_menus.h
 * @brief
 * Rendering of the game menus and definitions of the buttons. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

/*  __  __                       */
/* |  \/  | ___ _ __  _   _ ___  */
/* | |\/| |/ _ \ '_ \| | | / __| */
/* | |  | |  __/ | | | |_| \__ \ */
/* |_|  |_|\___|_| |_|\__,_|___/ */

#ifndef _GUI_MENUS_H_
#define _GUI_MENUS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>

#include "gui_gamevars.h"
#include "gui_init_graphic.h"
// #include "project_tools.h"

// Score menu
#define SCORE_BT_WIDTH 135   // Button width
#define SCORE_BT_SEP 15      // Separation between buttons
#define SCORE_NAME_WIDTH 300 // Width of the name column

#define SCORE_BT_TOP 200    // Top of the buttons
#define SCORE_TI_TOP 80     // Top of the title
#define SCORE_WI_TOP 160    // Top of the window
#define SCORE_NB_TOP 240    // Top of the scores
#define SCORE_NB_STEP 30    // Step between scores
#define SCORE_BOT_SPACE 200 // Space at the bottom

#define PONGPLAYERHEIGHT 205
#define PONGSTATUSHEIGHT 165
#define BRICKPLAYERHEIGHT 285
#define BRICKSTATUSHEIGHT 205

/*************/
/*+ Anchors +*/
/*************/

/**
 * @brief
 * Anchor positions for buttons and frames.
 */
typedef enum
{
    ANC_NW, //!< North-West.
    ANC_NC, //!< North-Centre.
    ANC_NE, //!< North-East.
    ANC_CW, //!< Centre-West.
    ANC_CC, //!< Centre-Centre.
    ANC_CE, //!< Centre-East.
    ANC_SW, //!< South-West.
    ANC_SC, //!< South-Centre.
    ANC_SE  //!< South-East.
} anchor;

/**
 * @brief
 * Shifts the coordinates from the anchor to top left.
 */
void shift_to_anchor(int *, //!< Horizontal coordinate.
                     int *, //!< Vertical coordinate.
                     int,   //!< Width.
                     int,   //!< Height.
                     anchor //!< Anchor.
);

/*************/
/*+ Buttons +*/
/*************/

/**
 * @brief
 * Various frames used to display menus.
 */
typedef enum
{
    // Whole screen
    BX_SCREEN, //!< Screen.

    // Pong Setup
    BX_PONGIMENSIONS,
    BX_PONGPARAMS,
    BX_PONGP1,
    BX_PONGP2,

    // Pong game
    BX_STATUSPONG, //!< Status of the board in a pong game.
    BX_P1PONG,     //!< Player 1 status in a pong game.
    BX_P2PONG,     //!< Player 2 status in a pong game.

    // Bricks Setup
    BX_BRICKDIMENSIONS,
    BX_BRICKLOAD,

    // Bricks game
    BX_STATUSBRICK, //!< Status of the board in a bricks game.
    BX_P1BRICK,     //!< Player 1 status in a bricks game.
    BX_P2BRICK,     //!< Player 2 status in a bricks game.

    // Score
    BX_SCORESCREEN,
    BX_SCOREMODE,

    BX_FILENAME,

    BX_SIZE
} uibox;

/**
 * @brief Array of frames.
 */
extern SDL_Rect var_uiboxes[BX_SIZE];

/**
 * @brief
 * Internal names for all the buttons in the game.
 */
typedef enum
{

    // Main Menu
    BT_PONGGAME,    //!< Pong game.
    BT_BREAKGAME,   //!< Breakout game.
    BT_SCORESCREEN, //!< Scores.
    BT_QUIT,        //!< Quit.

    // Pong Setup
    BT_PONGLAUNCH,
    BT_PONGBACK,
    BT_PONGBONUS,
    BT_PONGNBALLS,
    BT_SETWIDTH,
    BT_SETHEIGHT,
    BT_PONGP1L,
    BT_PONGP1C,
    BT_PONGP1R,
    BT_PONGP2L,
    BT_PONGP2C,
    BT_PONGP2R,

    // BRICKS SETUP
    BT_SETBRICKTOP,
    BT_SETBRICKBOT,
    BT_SETCOLORS,
    BT_SETBRICKHEALTH,
    BT_BRICKGEN,
    BT_BRICKLOAD,
    BT_BRICKBACK,
    BT_SELECPAGEL,
    BT_SELECPAGER,
    BT_FILE1,
    BT_FILE2,
    BT_FILE3,
    BT_FILE4,
    BT_FILE5,
    BT_FILE6,
    BT_FILE7,
    BT_FILE8,

    // Game
    BT_PAUSE,
    BT_BACKMENU,

    // Save/Load
    BT_FILENAME,

    // Scores
    BT_SCOREBACK,

    BT_SCORESAVE,
    BT_SCOREMENU,

    BT_SCGLOBAL,
    BT_SCGOALS,
    BT_SCBONUS,
    BT_SCHEALTH,
    BT_SCBRICKS,
    BT_SCTYPE,
    BT_SCPLAYERS,
    BT_SCTIME,
    BT_PREVSCORE,
    BT_NEXTSCORE,

    BT_SCOREMODEL,
    BT_SCOREMODER,

    BT_SIZE,
    BT_NONE,
} button;

/**
 * @brief
 * Counter for the button animation.
 */
extern int var_button_countdown;

/**
 * @brief
 * Currently selected button.
 */
extern button var_selected_button;

/**
 * @brief
 * The last pushed button.
 */
extern button var_pushed_button;

/**
 * @brief
 * Array indicating which buttons are currently being pushed (for animations).
 */
extern bool var_buttons_flags[BT_SIZE];

/**
 * @brief
 * Resets the buttons.
 */
void var_reset_buttons(void);

/**
 * @brief
 * Pushes a button.
 */
void var_push_button(button);

/**
 * @brief
 * Releases a button.
 */
void var_release_button(button);

/**
 * @brief
 * Data structure representing a single button.
 */
typedef struct
{
    uibox parent_box; //!< Parent box of the button.
    int x;
    int y;
    int w;
    int h;
    int t_x;
    int t_y;
    button up;
    button left;
    button down;
    button right;
} button_data;

/**
 * @brief
 * Data for all buttons.
 */
extern button_data var_buttons[BT_SIZE];

/******************************************/
/*+ Initialization of frames and buttons +*/
/******************************************/

/**
 * @brief Initialization of all the UI boxes in the program.
 */
void init_uiboxes(void);

/**
 * @brief
 * Initialization of a single button.
 */
void init_one_button(button bt, //!< The button's internal name.
                     int x,     //!< Horizontal coordinate.
                     int y,     //!< Vertical coordinate.
                     int w,     //!< Width.
                     int h,     //!< Height.
                     anchor a,  //!< Anchor.
                     uibox pbox //!< Parent box.
);

/**
 * @brief
 * Initialization of a Boolean toggle button.
 *
 * @remark
 * Anchor is fixed to NW.
 */
void init_boolean_toggle(button bt, //!< The button's internal name.
                         int x,     //!< Horizontal coordinate.
                         int y,     //!< Vertical coordinate.
                         uibox pbox //!< Parent box.
);

void init_single_choice_button(button b, int x, int y, int tw, anchor a, uibox pbox);
/**
 * @brief
 * Initialization of double choice buttons.
 */
void init_double_choice_buttons(button lb, //!< Left button.
                                button rb, //!< Right button.
                                int x,     //!< Horizontal coordinate.
                                int y,     //!< Vertical coordinate.
                                int tw,    //!< Width of the text next to each button.
                                anchor a,  //!< Anchor.
                                uibox pbox //!< Parent box.
);

/**
 * @brief
 * Initialization of triple choice buttons.
 */
void init_triple_choice_buttons(button lb, //!< Left button.
                                button mb, //!< Middle button.
                                button rb, //!< Right button.
                                int x,     //!< Horizontal coordinate.
                                int y,     //!< Vertical coordinate.
                                int tw,    //!< Width of the text next to each button.
                                anchor a,  //!< Anchor.
                                uibox pbox //!< Parent box.
);

/**
 * @brief Initialization an editor button.
 */
void init_editor_button(button bt, //!< The button.
                        int x,     //!< Horizontal coordinate.
                        int y,     //!< Vertical coordinate.
                        int lw,    //!< Label width.
                        int tw,    //!< Editor window width.
                        anchor a,  //!< Anchor.
                        uibox pbox //!< Parent box.
);

/**
 * @brief
 * Initialization of selector buttons.
 */
void init_selector_buttons(button lb, //!< Left button.
                           button rb, //!< Right button.
                           int x,     //!< Horizontal coordinate.
                           int y,     //!< Vertical coordinate.
                           int tw,    //!< Width.
                           anchor a,  //!< Anchor.
                           uibox pbox //!< Parent box.
);

/**
 * @brief
 * Initialization of all buttons.
 */
void init_all_buttons(void);

/**
 * @brief
 * Capture the mouse on a button.
 */
bool mouse_capture_button(int x,    //!< Horizontal coordinate of the mouse.
                          int y,    //!< Vertical coordinate of the mouse.
                          button bt //!< The button.
);

/*********************/
/*+ Displaying text **/
/*********************/

/**
 * @brief Displays text.
 */
int render_text(int,          //!< Horizontal coordinate.
                int,          //!< Vertical coordinate.
                const char *, //!< Text to display.
                TTF_Font *,   //!< Font to use.
                SDL_Color,    //!< Text color.
                anchor        //!< Anchor.
);

/**
 * @brief Displays text truncates the end if too long.
 */
int render_text_truncate(int,           //!< Horizontal coordinate.
                         int,           //!< Vertical coordinate.
                         int max_width, //!< Maximum width of the text.
                         const char *,  //!< Text to display.
                         TTF_Font *,    //!< Font to use.
                         SDL_Color,     //!< Text color.
                         anchor         //!< Anchor.
);

/**
 * @brief Displays text in an edition buffer.
 */
void print_text_buffer_center(void);

/***********************************/
/*+ Displaying frames and buttons +*/
/***********************************/

/**
 * @brief
 * Renders a standard button.
 */
void display_button(button bt,         //!< The button.
                    const char *label, //!< The label of the button.
                    TTF_Font *font,    //!< The font to use.
                    ui_color color,    //!< The color of the button.
                    ui_type type,      //!< The type of the button.
                    SDL_Color textcol  //!< The color of the text.
);

/**
 * @brief
 * Displays a Boolean toggle button.
 */
void display_boolean_toggle(button bt,        //!< The button.
                            const char *text, //!< The text to display.
                            bool checked,     //!< Whether the toggle is checked or not.
                            ui_color color    //!< The color of the button.
);

/**
 * @brief
 * Displays a single choice button.
 */
void display_one_choice_button(button bt,        //!< The button.
                               const char *text, //!< The text to display.
                               bool checked,     //!< Whether the choice is selected or not.
                               ui_color color    //!< The color of the button.
);

/**
 * @brief
 * Displays double choice buttons.
 */
void display_double_choice_buttons(button lb,         //!< Left button.
                                   const char *ltext, //< Text for the left button.
                                   button rb,         //!< Right button.
                                   const char *rtext, //!< Text for the right button.
                                   const char *label, //!< Label displayed above the choice buttons (NULL if not desired).
                                   bool left,         //!< Whether the left button is selected.
                                   ui_color color     //!< The color of the buttons.
);

/**
 * @brief
 * Displays triple choice buttons.
 */
void display_triple_choice_buttons(button lb,         //!< Left button.
                                   const char *ltext, //!< Text for the left button.
                                   button mb,         //!< Middle button.
                                   const char *mtext, //!< Text for the middle button.
                                   button rb,         //!< Right button.
                                   const char *rtext, //!< Text for the right button.
                                   const char *label, //!< Label displayed above the choice buttons (NULL if not desired).
                                   int n,             //!< Index of the selected button (0: left, 1: middle, 2: right).
                                   ui_color color     //!< The color of the buttons.
);

/**
 * @brief
 * Displays an editor button.
 */
void display_editor_button(button bt,             //!< The button.
                           const char *label,     //!< The label of the button.
                           const char *string,    //!< The text inside the editor.
                           ui_color color,        //!< The color of the button.
                           SDL_Color label_color, //!< The color of the label.
                           SDL_Color edit_color   //!< The color of the text inside the editor.
);

/**
 * @brief
 * Displays selector buttons.
 */
void display_selector_buttons(button lb,        //!< Left button.
                              button rb,        //!< Right button.
                              const char *text, //!< The text to display.
                              ui_color color    //!< The color of the buttons.
);

/**
 * @brief
 * Renders an advanced box.
 */
void render_ui_box_advanced(uibox box,        //!< The box.
                            ui_advframe frame //!< The frame to use.
);

/**
 * @brief
 * Displays a colored frame.
 */
void render_color_frame(int x,          //!< Horizontal coordinate.
                        int y,          //!< Vertical coordinate.
                        int w,          //!< Width.
                        int h,          //!< Height.
                        ui_color color, //!< Frame color (COL_BLUE, COL_GREEN, COL_GRAY, COL_RED or COL_YELLOW).
                        ui_type type,   //!< Type of frame (UITYPE_EDGE, UITYPE_PLAIN, UITYPE_DEMI, UITYPE_SHADE or UITYPE_LINE).
                        bool on,        //!< Whether the frame is pushed or not (used for buttons).
                        anchor anc      //!< Anchor for the placement.
);

/**
 * @brief
 * Displays an advanced frame.
 */
void render_advanced_frame(int x,             //!< Horizontal coordinate.
                           int y,             //!< Vertical coordinate.
                           int w,             //!< Width.
                           int h,             //!< Height.
                           ui_advframe frame, //!< Type of frame (ADV_LIGHT_BROWN, ADV_DARK_BROWN, ADV_LIGHT_GREY, ADV_BLUE, ADV_DARK_GREY or ADV_GREEN).
                           anchor anc         //!< Anchor for the placement.
);

/****************/
/*+ Main menus +*/
/****************/

/**
 * @brief Displays the main menu.
 */
void render_mainmenu(void);

void render_pongmenu(void);
void render_brickmenu(void);

/**************/
/*+ Pong Hud +*/
/**************/

void render_pong_hud(void);
void render_brick_hud(void);
/******************/
/*+ Score screen +*/
/******************/

/**
 * @brief Displays the score screen.
 */
void render_score_screen(void);

/***************/
/*+ Save/Load +*/
/***************/

void render_textbox_menu(const char *message, ui_advframe backframe, SDL_Color message_color, ui_color box_color, SDL_Color edit_color);

#endif // _GUI_MENUS_H_
