//
// Created by Andrew Boun on 2/6/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROCK ' '
#define FLOOR '.'
#define CORRIDOR '#'
#define DOWN_STAIRS '>'
#define UP_STAIRS '<'

#define HORIZONTAL_BORDER '-'
#define VERTICAL_BORDER '|' // vertical border

#define DUNGEON_WIDTH 80
#define DUNGEON_HEIGHT 21

#define PLACABLE_HEIGHT (DUNGEON_HEIGHT - 2)
#define PLACABLE_WIDTH (DUNGEON_WIDTH - 2)

#define MIN_ROOMS 6
#define MAX_ROOMS 12

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_HEIGHT 3

// Maximum number of attempts to generate a room
// If the number of attempts exceeds this value,
// The grid will reset and try again
#define MAX_ATTEMPTS 2000

typedef struct {
    int x, y;       // top-left coordinate (not including border)
    int width, height;
    int center_x, center_y;
} Room;

// Array of rooms
Room rooms[MAX_ROOMS];

// Dungeon Grid
char grid[DUNGEON_HEIGHT][DUNGEON_WIDTH];


void generate_corridor(int x1, int y1, int x2, int y2){
    int x = x1;
    int y = y1;

    srand(time(NULL));
    // 0 for horizontal, 1 for vertical, 2 for diagonal
    int direction = rand() % 3;

    while (x != x2 || y != y2){
        if (direction == 0 && x != x2){
            if (x < x2) x++; 
            else x--;

        } else if (direction == 1 && y != y2){
            if (y < y2) y++;
            else y--;

        } else {
            // if (x < x2){
            //     x++;
            // } else if (x > x2){
            //     x--;
            // }

            if (x != x2){
                if (x < x2) x++;
                else x--;

                if (grid[y][x] == ROCK) grid[y][x] = CORRIDOR;
            }

            if (y < y2){
                y++;
            } else if (y > y2){
                y--;
            }
        }

        if (grid[y][x] == ROCK) grid[y][x] = CORRIDOR;
    }
}

int can_insert_room(Room room){
    // Check if room is within bounds
    // Do not check for <= because we need to account for starting at 1
    if (room.x + (room.width - 1) > PLACABLE_WIDTH || room.y + (room.height - 1) > PLACABLE_HEIGHT){ // -1 to account for starting room at that index
        return 0;
    }

    // Check area of room and bordering area to see if it is empty
    for (int i = room.x - 1; i < room.x + room.width + 1; i++){
        for (int j = room.y - 1; j < room.y + room.height + 1; j++){
            if (grid[j][i] == FLOOR){
                return 0;
            }
        }
    }

    return 1;
}

// Generate room in grid, to only be called after can_insert_room
// This generates the room starting from it's top left corner, and including that initial point
void generate_room(Room room){
    for(int i = room.x; i < room.x + room.width; i++){
        for(int j = room.y; j < room.y + room.height; j++){
            grid[j][i] = FLOOR;
        }
    }
}

// Generate a random room
// Returns true if room was generated successfully
// Returns false if room could not be generated
// idx is the index of the room in the rooms array
bool generate_random_room(int idx){
    srand(time(NULL));
    Room room;
    int attempts = 0;

    do {
        attempts++;
        if (attempts >= MAX_ATTEMPTS) { // Reset grid if too many attempts
            return false;
        }

        room.x = (rand() % PLACABLE_WIDTH) + 1;
        room.y = (rand() % PLACABLE_HEIGHT) + 1;

        // Subract current coordinate from the maximum width and height
        // to get the maximum available width and height
        int random_width = rand() % (PLACABLE_WIDTH - room.x);
        int random_height = rand() % (PLACABLE_HEIGHT - room.y);
        room.width = (random_width < MIN_ROOM_WIDTH) ? MIN_ROOM_WIDTH : random_width;
        room.height = (random_height < MIN_ROOM_HEIGHT) ? MIN_ROOM_HEIGHT : random_height;

        room.center_x = room.x + (room.width / 2);
        room.center_y = room.y + (room.height / 2);

    } while (!can_insert_room(room));

    rooms[idx] = room;
    generate_room(room);
    return true;
}

void print_room_info(int num_rooms){
    for (int i = 0; i < num_rooms; i++){
        printf("Room %d\n", i + 1);
        printf("x: %d\n", rooms[i].x);
        printf("y: %d\n", rooms[i].y);
        printf("width: %d\n", rooms[i].width);
        printf("height: %d\n", rooms[i].height);
        printf("center_x: %d\n", rooms[i].center_x);
        printf("center_y: %d\n", rooms[i].center_y);
        printf("\n");
    }
}

// Prints grid with a border
void print_grid(){
    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");

    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        printf("%c", VERTICAL_BORDER);
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            printf("%c", grid[i][j]);
        }
        printf("%c", VERTICAL_BORDER);
        printf("\n");
    }

    for(int i = 0; i < DUNGEON_WIDTH + 2; i++){
        printf("%c", HORIZONTAL_BORDER);
    }
    printf("\n");
}

int main (int argc, char *argv[]){
    srand(time(NULL));
    int i, j;
    int num_rooms;

    bool success = false;

    // Generate Rooms
    do {
        // Initialize grid with ROCK
        for (i = 0; i < DUNGEON_HEIGHT; i++) {
            for (j = 0; j < DUNGEON_WIDTH; j++) {
                // grid[i][j] = '~';
                grid[i][j] = ROCK;
            }
        }

        success = true;
        num_rooms = MIN_ROOMS + rand() % (MAX_ROOMS - MIN_ROOMS + 1);

        for (i = 0; i < num_rooms; i++) {
            if (!generate_random_room(i)) {
                success = false;
                break;
            }
        }

        if (success) break;
    } while (1);

    // Generate Corridors
    for (i = 0; i < num_rooms - 1; i++){
        generate_corridor(
            rooms[i].center_x, 
            rooms[i].center_y, 
            rooms[i + 1].center_x, 
            rooms[i + 1].center_y
        );
    }

    generate_corridor(
        rooms[num_rooms - 1].center_x, 
        rooms[num_rooms - 1].center_y, 
        rooms[0].center_x, 
        rooms[0].center_y
    );

    // print_room_info(num_rooms);
    
    print_grid();

    return 0;
}