#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gui_gamevars.h"
#include "gui_init_graphic.h"
#include "gui_menus.h"

TTF_Font *Sans18, *Sans16, *Paci20, *Over, *Overbold, *OverboldL;

SDL_Texture *txt_ui[COL_SIZE];
SDL_Texture *txt_cursors;
SDL_Texture *txt_icons;
SDL_Texture *txt_advanced;
SDL_Texture *txt_bigarrows;
SDL_Texture *txt_objects;
SDL_Texture *txt_bricks;
SDL_Texture *txt_bonuses;
SDL_Texture *txt_paddle;
SDL_Texture *txt_spaddle;
SDL_Texture *txt_lpaddle;
SDL_Texture *txt_balls;
// SDL_Rect clp_textures[CLP_SIZE];

SDL_Rect clp_gauges[GAUGE_SIZE];
SDL_Rect clp_misc_large[MISC_SIZE];
SDL_Rect clp_misc_small[MISC_SIZE];
SDL_Rect clp_round_buttons[UITYPE_SIZE];
SDL_Rect clp_square_buttons[UITYPE_SIZE];
SDL_Rect clp_frames[UITYPE_SIZE][UICA_SIZE];
SDL_Rect clp_cursors[CUR_SIZE];
SDL_Rect clp_circles[CIRCLE_SIZE];
SDL_Rect clp_icons[UICON_SIZE];
SDL_Rect clp_advanced[ADV_FRAMES_SIZE][UICA_SW_OFF];
SDL_Rect clp_bigarrows[CUR_CROSS_BIG];
SDL_Rect clp_bricks[10][CLP_BRSIZE];
SDL_Rect clp_bonuses[CLP_BNSIZE][7];
SDL_Rect clp_objects[CLP_OBSIZE];

/***********/
/*+ Fonts +*/
/***********/

void init_fonts(void) {
    if (TTF_Init() < 0) {
        FATAL("TTF_Init: %s\n", TTF_GetError());
    }

    if (!(Paci20 = TTF_OpenFont("../Fonts/Pacifico.ttf", 20))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (!(Sans18 = TTF_OpenFont("../Fonts/Arial_Rounded_Bold.ttf", 18))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (!(Sans16 = TTF_OpenFont("../Fonts/DejaVuSans.ttf", 16))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (!(Over = TTF_OpenFont("../Fonts/Overlock-Regular.ttf", 32))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (!(Overbold = TTF_OpenFont("../Fonts/Overlock-Black.ttf", 32))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (!(OverboldL = TTF_OpenFont("../Fonts/Overlock-Black.ttf", 64))) {
        FATAL("TTF_OpenFont: %s\n", TTF_GetError());
    }
}

/*************/
/*+ Sprites +*/
/*************/

void init_image(void) {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        FATAL("IMG_Init: %s", IMG_GetError());
    }
    else {
        DEBUG("IMG_Init OK");
    }
}

static void load_one_sheet(const char *path, SDL_Texture **texture) {
    SDL_Surface *image = IMG_Load(path);
    if (!image) {
        printf("Error when loading sprites :  %s", IMG_GetError());
        return;
    }
    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
}

void init_load_sprites(void) {

    load_one_sheet("../Sprites/paddlesmall.png", &txt_spaddle);
    load_one_sheet("../Sprites/paddlemid.png", &txt_paddle);
    load_one_sheet("../Sprites/paddlebig.png", &txt_lpaddle);

    int k = 0;
    for (int i = CLP_PADDLE_1; i <= CLP_PADDLE_3; i++) {
        clp_objects[i].x = k * 485;
        clp_objects[i].y = 0;
        clp_objects[i].w = 485;
        clp_objects[i].h = 128;
        k++;
    }

    k = 0;
    for (int i = CLP_PADDLE_LONG_1; i <= CLP_PADDLE_LONG_3; i++) {
        clp_objects[i].x = k * 693;
        clp_objects[i].y = 0;
        clp_objects[i].w = 693;
        clp_objects[i].h = 128;
        k++;
    }

    clp_objects[CLP_PADDLE_SHORT].x = 0;
    clp_objects[CLP_PADDLE_SHORT].y = 0;
    clp_objects[CLP_PADDLE_SHORT].w = 230;
    clp_objects[CLP_PADDLE_SHORT].h = 128;

    // Chargement des balles
    load_one_sheet("../Sprites/round.png", &txt_balls);
    k = 0;
    for (int i = CLP_BALL_1; i <= CLP_BALL_GREEN_2; i++) {
        clp_objects[i].x = k * 128;
        clp_objects[i].y = 0;
        clp_objects[i].w = 128;
        clp_objects[i].h = 128;
        k++;
    }

    clp_objects[CLP_STAR].x = 8 * 128;
    clp_objects[CLP_STAR].y = 0;
    clp_objects[CLP_STAR].w = 128;
    clp_objects[CLP_STAR].h = 128;

    clp_objects[CLP_HEART].x = 9 * 128;
    clp_objects[CLP_HEART].y = 0;
    clp_objects[CLP_HEART].w = 128;
    clp_objects[CLP_HEART].h = 128;

    // Charagement des briques
    load_one_sheet("../Sprites/bricksround.png", &txt_bricks);

    int yshift = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < CLP_BRSIZE; j++) {
            clp_bricks[i][j].x = j * CELL_X;
            clp_bricks[i][j].y = yshift;
            clp_bricks[i][j].w = CELL_X;
            clp_bricks[i][j].h = CELL_Y;
        }
        yshift += CELL_Y;
    }

    // Chargement des bonus
    load_one_sheet("../Sprites/bonuses.png", &txt_bonuses);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            clp_bonuses[i][j].x = j * BLOCK_X;
            clp_bonuses[i][j].y = i * BLOCK_Y;
            clp_bonuses[i][j].w = BLOCK_X;
            clp_bonuses[i][j].h = BLOCK_Y;
        }
    }

    int ri = 3, rj = 0;
    for (int i = 3; i < CLP_BNSIZE; i++) {
        for (int j = 0; j < 6; j++) {
            clp_bonuses[i][j].x = rj * BLOCK_X;
            clp_bonuses[i][j].y = ri * BLOCK_Y;
            clp_bonuses[i][j].w = BLOCK_X;
            clp_bonuses[i][j].h = BLOCK_Y;
            rj++;
            if (rj == 7) {
                rj = 0;
                ri++;
            }
        }
    }
    // Colored UI elements

    load_one_sheet("../Sprites/ui_blue.png", &txt_ui[COL_BLUE]);
    load_one_sheet("../Sprites/ui_green.png", &txt_ui[COL_GREEN]);
    load_one_sheet("../Sprites/ui_grey.png", &txt_ui[COL_GRAY]);
    load_one_sheet("../Sprites/ui_red.png", &txt_ui[COL_RED]);
    load_one_sheet("../Sprites/ui_yellow.png", &txt_ui[COL_YELLOW]);

    // Gauges
    clp_gauges[GAUGE_LEFT].h = 51;
    clp_gauges[GAUGE_LEFT].w = 25;
    clp_gauges[GAUGE_LEFT].x = 0;
    clp_gauges[GAUGE_LEFT].y = 0;
    clp_gauges[GAUGE_CENTER].h = 51;
    clp_gauges[GAUGE_CENTER].w = 1;
    clp_gauges[GAUGE_CENTER].x = 25;
    clp_gauges[GAUGE_CENTER].y = 0;
    clp_gauges[GAUGE_RIGHT].h = 51;
    clp_gauges[GAUGE_RIGHT].w = 25;
    clp_gauges[GAUGE_RIGHT].x = 77;
    clp_gauges[GAUGE_RIGHT].y = 0;

    // Buttons
    for (int i = 0; i < UITYPE_SIZE; i++) {
        clp_round_buttons[i].h = 128;
        clp_round_buttons[i].w = 128;
        clp_round_buttons[i].x = i * 256;
        clp_round_buttons[i].y = 115;

        clp_square_buttons[i].h = 128;
        clp_square_buttons[i].w = 128;
        if (i < 2) {
            clp_square_buttons[i].x = (UITYPE_SIZE + 2 * i) * 128;
            clp_square_buttons[i].y = 115;
        }
        else {
            clp_square_buttons[i].x = (2 * i - 4) * 128;
            clp_square_buttons[i].y = 243;
        }
    }

    // for (int i = 0; i < UITYPE_SIZE; i++) {
    //   clp_round_buttons[i].h = 256;
    //   clp_round_buttons[i].w = 256;
    //   clp_round_buttons[i].x = 2 * i * 256;
    //   clp_round_buttons[i].y = 230;

    //   clp_square_buttons[i].h = 256;
    //   clp_square_buttons[i].w = 256;
    //   if (i < 2) {
    //     clp_square_buttons[i].x = (UITYPE_SIZE + 2 * i) * 256;
    //     clp_square_buttons[i].y = 230;
    //   }
    //   else {
    //     clp_square_buttons[i].x = (2 * i - 4) * 256;
    //     clp_square_buttons[i].y = 486;
    //   }
    // }

    // Frames
    for (int i = 0; i < UITYPE_SIZE; i++) {
        for (int j = 0; j < UICA_SIZE; j++) {
            clp_frames[i][j].h = 16;
            clp_frames[i][j].w = 16;
        }

        clp_frames[i][UICA_NW].x = 0 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_NW].y = 371 + ((2 * i) / 4) * 128;

        clp_frames[i][UICA_N].x = 16 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_N].y = 371 + ((2 * i) / 4) * 128;
        clp_frames[i][UICA_N].w = 352;

        clp_frames[i][UICA_NE].x = 368 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_NE].y = 371 + ((2 * i) / 4) * 128;

        clp_frames[i][UICA_W].x = 0 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_W].y = 387 + ((2 * i) / 4) * 128;
        clp_frames[i][UICA_W].h = 96;

        clp_frames[i][UICA_C].x = 16 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_C].y = 387 + ((2 * i) / 4) * 128;
        clp_frames[i][UICA_C].w = 352;
        clp_frames[i][UICA_C].h = 96;

        clp_frames[i][UICA_E].x = 368 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_E].y = 387 + ((2 * i) / 4) * 128;
        clp_frames[i][UICA_E].h = 96;

        clp_frames[i][UICA_SW].x = 0 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_SW].y = 483 + ((2 * i) / 4) * 128;

        clp_frames[i][UICA_S].x = 16 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_S].y = 483 + ((2 * i) / 4) * 128;
        clp_frames[i][UICA_S].w = 352;

        clp_frames[i][UICA_SE].x = 368 + ((2 * i) % 4) * 384;
        clp_frames[i][UICA_SE].y = 483 + ((2 * i) / 4) * 128;

        clp_frames[i][UICA_SW_OFF].x = 0 + ((2 * i + 1) % 4) * 384;
        clp_frames[i][UICA_SW_OFF].y = 475 + ((2 * i + 1) / 4) * 128;
        clp_frames[i][UICA_SW_OFF].h = 24;

        clp_frames[i][UICA_S_OFF].x = 16 + ((2 * i + 1) % 4) * 384;
        clp_frames[i][UICA_S_OFF].y = 475 + ((2 * i + 1) / 4) * 128;
        clp_frames[i][UICA_S_OFF].w = 352;
        clp_frames[i][UICA_S_OFF].h = 24;

        clp_frames[i][UICA_SE_OFF].x = 368 + ((2 * i + 1) % 4) * 384;
        clp_frames[i][UICA_SE_OFF].y = 475 + ((2 * i + 1) / 4) * 128;
        clp_frames[i][UICA_SE_OFF].h = 24;
    }

    for (int i = 0; i < MISC_SIZE; i++) {
        clp_misc_large[i].h = 64;
        clp_misc_large[i].w = 64;
        clp_misc_large[i].x = i * 64;
        clp_misc_large[i].y = 51;
        clp_misc_small[i].h = 32;
        clp_misc_small[i].w = 32;
        clp_misc_small[i].x = i * 32;
        clp_misc_small[i].y = 755;
    }

    load_one_sheet("../Sprites/ui_cursors.png", &txt_cursors);

    for (int i = 0; i < CUR_SIZE; i++) {
        clp_cursors[i].h = 64;
        clp_cursors[i].w = 64;
        clp_cursors[i].x = (i % 8) * 64;
        clp_cursors[i].y = (i / 8) * 64;
    }

    load_one_sheet("../Sprites/ui_icons.png", &txt_icons);
    clp_icons[UICON_UP].h = 50;
    clp_icons[UICON_UP].w = 50;
    clp_icons[UICON_UP].x = 400;
    clp_icons[UICON_UP].y = 0;
    clp_icons[UICON_CROSS].h = 50;
    clp_icons[UICON_CROSS].w = 50;
    clp_icons[UICON_CROSS].x = 400;
    clp_icons[UICON_CROSS].y = 400;

    load_one_sheet("../Sprites/ui_bigarrows.png", &txt_bigarrows);

    for (int i = 0; i < CUR_CROSS_BIG; i++) {
        clp_bigarrows[i].h = 192;
        clp_bigarrows[i].w = 192;
        clp_bigarrows[i].x = i * 192;
        clp_bigarrows[i].y = 0;
    }

    load_one_sheet("../Sprites/ui_advanced.png", &txt_advanced);

    for (int i = 0; i < CIRCLE_SIZE; i++) {
        clp_circles[i].h = 256;
        clp_circles[i].w = 256;
        clp_circles[i].x = i * 256;
        clp_circles[i].y = 0;
    }

    for (int i = 0; i < ADV_FRAMES_SIZE; i++) {
        for (int j = 0; j < UICA_SW_OFF; j++) {
            clp_advanced[i][j].h = 32;
            clp_advanced[i][j].w = 32;
        }

        clp_advanced[i][UICA_NW].x = 0 + (i % 6) * 128;
        clp_advanced[i][UICA_NW].y = 256 + (i / 6) * 128;
        clp_advanced[i][UICA_N].x = 32 + (i % 6) * 128;
        clp_advanced[i][UICA_N].y = 256 + (i / 6) * 128;
        clp_advanced[i][UICA_NE].x = 96 + (i % 6) * 128;
        clp_advanced[i][UICA_NE].y = 256 + (i / 6) * 128;

        clp_advanced[i][UICA_W].x = 0 + (i % 6) * 128;
        clp_advanced[i][UICA_W].y = 288 + (i / 6) * 128;
        clp_advanced[i][UICA_C].x = 32 + (i % 6) * 128;
        clp_advanced[i][UICA_C].y = 288 + (i / 6) * 128;
        clp_advanced[i][UICA_E].x = 96 + (i % 6) * 128;
        clp_advanced[i][UICA_E].y = 288 + (i / 6) * 128;

        clp_advanced[i][UICA_SW].x = 0 + (i % 6) * 128;
        clp_advanced[i][UICA_SW].y = 352 + (i / 6) * 128;
        clp_advanced[i][UICA_S].x = 32 + (i % 6) * 128;
        clp_advanced[i][UICA_S].y = 352 + (i / 6) * 128;
        clp_advanced[i][UICA_SE].x = 96 + (i % 6) * 128;
        clp_advanced[i][UICA_SE].y = 352 + (i / 6) * 128;
    }
}

/*****************/
/*+ Fenêtre SDL +*/
/*****************/

SDL_Window *window;
SDL_Renderer *renderer;

bool init_SDL(int sc_width, int sc_height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        FATAL("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    // Chargement des fonts
    init_fonts();

    // Initialisation des PNGs
    init_image();

    // Initialisation des tableaux de niveaux
    var_init_levelstab();

    var_screen_width = sc_width;
    var_screen_height = sc_height;
    SDL_DisplayMode DM;
    SDL_GetDesktopDisplayMode(0, &DM);
    //  printf("Screen width: %d, Screen height: %d\n", DM.w, DM.h);
    if (var_screen_width <= 0 || DM.w < var_screen_width) {
        var_screen_width = DM.w;
    }
    if (var_screen_height <= 0 || DM.h < var_screen_height) {
        var_screen_height = DM.h;
    }
    printf("Screen width: %d, Screen height: %d\n", var_screen_width,
           var_screen_height);
    var_game_width = var_screen_width - var_info_width;

    // Création de la fenêtre
    window = SDL_CreateWindow("Breaking Bricks in C", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, var_screen_width,
                              var_screen_height,
#ifndef SOFTWARE_MODE
                              SDL_WINDOW_OPENGL |
#endif
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        FATAL("Could not create window: %s\n", SDL_GetError());
    }

    // Création de l'affichage
    renderer = SDL_CreateRenderer(window, -1,
#if SOFTWARE_MODE
                                  SDL_RENDERER_SOFTWARE
#else
                                  SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC
#endif
    );
    if (renderer == NULL) {
        FATAL("Could not create renderer: %s\n", SDL_GetError());
    }

    SDL_SetWindowResizable(window, SDL_FALSE);

    // Initialisation des sprites
    init_load_sprites();

    // Chargement des boutons
    init_uiboxes();
    init_all_buttons();

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
    SDL_RenderClear(renderer);

    return true;
}

void shutdown_SDL(void) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
