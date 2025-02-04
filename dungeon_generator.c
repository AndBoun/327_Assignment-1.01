//
// Created by Andrew Boun on 2/6/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK " "

#define FLOOR "."
#define CORRIDOR "#"

#define DOWN_STAIRS ">" // stairs down
#define UP_STAIRS "<" // stairs up

#define HORIZONTAL_BORDER "-"
#define VERTICAL_BORDER "|" // vertical border

#define DUNGEON_WIDTH 80
#define DUNGEON_HEIGHT 21

#define PLACABLE_HEIGHT (DUNGEON_HEIGHT - 2)
#define PLACABLE_WIDTH (DUNGEON_WIDTH - 2)

#define MIN_ROOMS 6

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_HEIGHT 3


// Dungeon Grid
char grid[DUNGEON_HEIGHT][DUNGEON_WIDTH];

// Set of coordinate to be randomized
int x_coordinates[PLACABLE_WIDTH];
int y_coordinates[PLACABLE_HEIGHT];

void randomizedCoordinates(){
    srand(time(NULL));

    for (int i = PLACABLE_WIDTH - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = x_coordinates[i];
        x_coordinates[i] = x_coordinates[j];
        x_coordinates[j] = temp;
    }

    for (int i = PLACABLE_HEIGHT - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = y_coordinates[i];
        y_coordinates[i] = y_coordinates[j];
        y_coordinates[j] = temp;
    }
}

// Prints grid with a border
void print_grid(){
    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        printf("|");
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            printf("%c", grid[i][j]);
        }
        printf("|");
        printf("\n");
    }

    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("-");
    }
    printf("\n");
}

int main (int argc, char *argv[]){
    int i, j;
    for (i = 0; i < DUNGEON_HEIGHT; i++) {
        for (j = 0; j < DUNGEON_WIDTH; j++) {
            grid[i][j] = ' ';
        }
    }
    
    print_grid();

    return 0;
}   