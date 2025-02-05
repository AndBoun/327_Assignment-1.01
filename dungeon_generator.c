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

// Fisher-Yates shuffle algorithm to shuffle coordinates
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

int can_insert_room(int x, int y, int width, int height){
    // Check if room is within bounds
    // Do not check for <= because we need to account for starting at 1
    if (x + (width - 1) > PLACABLE_WIDTH || y + (height - 1) > PLACABLE_HEIGHT){ // -1 to account for starting room at that index
        return 0;
    }

    // Check area of room and bordering area to see if it is empty
    for (int i = x - 1; i < x + width + 1; i++){
        for (int j = y - 1; j < y + height + 1; j++){
            if (grid[j][i] == '.'){
                return 0;
            }
        }
    }

    return 1;
}

// Generate room in grid, to only be called after can_insert_room
// This generates the room starting from it's top left corner, and including that initial point
void generate_room(int x, int y, int width, int height){
    for(int i = x; i < x + width; i++){
        for(int j = y; j < y + height; j++){
            grid[j][i] = '.';
        }
    }
}
void generate_random_room(){
    srand(time(NULL));
    int x, y, width, height;
    // c = 0;

    do {
        // Randomize and start at idx 1 to avoid border
        x = (rand() % PLACABLE_WIDTH) + 1;
        y = (rand() % PLACABLE_HEIGHT) + 1;

        // Randomize width and height, and set to min if less than min
        int random_width = rand() % PLACABLE_WIDTH;
        int random_height = rand() % PLACABLE_HEIGHT;
        width = (random_width > MIN_ROOM_WIDTH) ? random_width : MIN_ROOM_WIDTH;
        height = (random_height > MIN_ROOM_HEIGHT) ? random_height : MIN_ROOM_HEIGHT;

    } while (!can_insert_room(x, y, width, height));


    // Insert room into grid once valid parameters are found
    generate_room(x, y, width, height);
}



int main (int argc, char *argv[]){
    int i, j;
    
    // Initialize grid with '~' for debuggin
    for (i = 0; i < DUNGEON_HEIGHT; i++) {
        for (j = 0; j < DUNGEON_WIDTH; j++) {
            grid[i][j] = '~';
        }
    }

    // generate_random_room();
    // generate_random_room();
    // generate_random_room();
    // generate_random_room();
    // generate_random_room();
    // generate_random_room();

    if (can_insert_room(1, 1, 4, 3))
    {
        generate_room(1, 1, 4, 3);
    }

    if (can_insert_room(5, 1, 4, 3))
    {
        generate_room(5, 1, 4, 3);
    }

    if (can_insert_room(75, 1, 4, 3))
    {
        generate_room(75, 1, 4, 3);
    }

    if (can_insert_room(1, 17, 4, 3))
    {
        generate_room(1, 17, 4, 3);
    }

    if (can_insert_room(75, 17, 4, 3))
    {
        generate_room(75, 17, 4, 3);
    }
    

    
    print_grid();

    return 0;
}