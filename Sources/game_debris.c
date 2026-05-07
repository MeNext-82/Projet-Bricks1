#include "game_debris.h"
#include "utils.h"

debris **debris_list; // File des débris à afficher
int size_debris;      // Taille de la file des débris
int nb_debris;        // Nombre de débris dans la file
int debris_left;      // Index du premier débris dans la file
int debris_right;     // Index du dernier débris dans la file

void init_debris(void) {
    MALLOC(debris_list, 1);
    size_debris = 1;
    nb_debris = 0;
}

static void add_one_debris(double x, double y, double dx, double dy, int w,
                           int h) {
    if (nb_debris == size_debris) {
        size_debris <<= 1;
        REALLOC(debris_list, size_debris);
    }
    MALLOC(debris_list[nb_debris], 1);
    debris_list[nb_debris]->rect.x = x;
    debris_list[nb_debris]->rect.y = y;
    debris_list[nb_debris]->rect.w = w;
    debris_list[nb_debris]->rect.h = h;
    debris_list[nb_debris]->dx = dx;
    debris_list[nb_debris]->dy = dy;
    debris_list[nb_debris]->frame = DEBRIS_MAX_FRAME;
    nb_debris++;
}

void add_debris(rectangle *rect) {

    int w = rect->w >> 5;
    int h = rect->h >> 4;
    // printf("Adding debris at (%.2f, %.2f) with velocity (%.2f, %.2f) and size
    // (%d, %d)\n", rect->x, rect->y, 0.0, 0.0, w, h);

    for (int y = 0; y <= h * 4; y += h) {
        for (int x = 0; x <= w * 4; x += w) {

            add_one_debris(rect->x + rect->w / 2, rect->y + rect->h / 2,
                           random_double(-5.0, 5.0), random_double(1.0, 2.0), w,
                           h);
            // printf("Added debris at (%.2f, %.2f) with velocity (%.2f, %.2f)
            // and size (%d, %d)\n", rect->x + x, rect->y + y,
            // random_double(-5.0, 5.0), random_double(1.0, 2.0), w, h);
        }
    }
}

void update_debris(void) {

    for (int i = nb_debris - 1; i >= 0; i--) {
        if (debris_list[i]->frame < 0) // SCREEN_HEIGHT
        {
            nb_debris--;
            // printf("Removing debris at index %d\n", i);
            free(debris_list[i]);
            // printf("Freeing debris at index %d\n", i);
            if (i < nb_debris) {
                debris_list[i] = debris_list[nb_debris];
                debris_list[nb_debris] = NULL;
            }
            continue;
        }

        debris_list[i]->rect.x += debris_list[i]->dx;
        debris_list[i]->rect.y += debris_list[i]->dy;

        debris_list[i]->dy += 0.5;
        debris_list[i]->frame--;
    }
}

void free_debris(void) {
    for (int i = 0; i < nb_debris; i++) {
        if (debris_list[i]) {
            free(debris_list[i]);
        }
    }
    free(debris_list);
    debris_list = NULL;
}

void reset_debris(void) {
    free_debris();
    init_debris();
}
