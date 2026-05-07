#include "game_scores.h"
#include "utils.h"

score_table *load_score_table(char **input, int size, int *player_score) {
    return NULL;
}

char **save_score_table(score_table *table, const char *playername, int *size) {
    if (!table || !size) {
        fprintf(stderr, "Invalid table or size pointer in save_score_table.\n");
        return NULL;
    }

    *size = table->size;
    char **lines;
    MALLOC(lines, *size);

    char buffer[1024]; // Buffer to hold the formatted score line
    for (int i = 0; i < table->size; i++) {
        const char *name = (i == table->player_index && playername)
                               ? playername
                               : table->names[i];
        sprintf(buffer, "%s,%d,%d,%d,%d,%d,%d,%d", name, table->scores[i][0],
                table->scores[i][1], table->scores[i][2], table->scores[i][3],
                table->scores[i][4], table->scores[i][5], table->scores[i][6]);
        MALLOC(lines[i], strlen(buffer) + 1);
        strcpy(lines[i], buffer);
    }

    return lines;
}

void delete_score_table(score_table *table) {}

void sort_score_table(score_table *table, score_type type) {}

bool get_pong_winner_score(game *g, short p, int *score_array) { return false; }

bool get_brick_winner_score(game *g, int *score_array) { return false; }
