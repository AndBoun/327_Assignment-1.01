# How To Run The Project:

Build the Project
```bash
make
```

Run the project. No arguments needed.
```bash
./dungeon_generator
```


# About The Project:

## Constraints:
- Maximum Rooms: 20
- Maximum Down Stairs: 4
- Maximum Up Stairs: 4
- Maximum attempts to insert room: 2000 attempts

## How The Project Runs:
First, a global 2D array is generated to hold the dungeon, based off the constraints of a $(21 \times 80)$ grid. Another global array of static size `MAX_ROOMS` is also made to hold all the rooms. 

### Rooms
Rooms are a `typedef struct` that hold:
- x-coordinate
- y-coordinate
- width
- height
- center x-coordinate
- center y-coordinate

The coordinates of a room indicate its upper, leftmost position. This position is inclusive and part of the room.

### Initializing Rooms
In the main method, we first initialize the dungeon full of rocks, then we enter a do-while loop to insert all the rooms. The amount of rooms inserted is random, from `(6-20)` inclusive, with each room size being being random, with a lower limit of $(4 \times 3)$ up to the maximum available area of the grid. There are helper methods that randomly insert and check for valid placement of each room. Because each room is randomly inserted and randomly size, there's a hard 2000 attempt limit of insertion. If this is reached, the dungeon grid will be reset, and rooms will be inserted again.

### Generating Corridors
We iterate through the `rooms` array and call a helper method, `generate_corridor`, that takes two different rooms center x and y coordinates. In this helper method, we randomly decide to generate a diagonal, horizontal to vertical, or vertical to horizontal path between the two rooms. These paths generated to make all rooms accessible, and enable complete navigate using only up, down, left, and right movement (no diagonal movement.) These paths can also go though existing rooms, but don't actually generate special corridors within rooms.

### Generating Stairs
We call the helper method `generate_random_stair` that takes the stair character we want to insert. The method then places that character randomly in the dungeon (excluding areas with rock). We generate a random number between `(1 - 4)` twice, to decide how many down and up stair we generate. We then call for loops to call `generate_random_stair` those random amount of times.

# Example Output
```plain
----------------------------------------------------------------------------------
|                                                                                |
|  .................                                                             |
|  .................###############         ....          .........>..<          |
|  .................         .............. ....          .............     .... |
|     #                      .............. ....          .............     .... |
|     #                      .............. ....    ....  .............     .... |
|     #   ..........                #       ....    ....     ## #           .... |
|     #   ..........  ........      #       ....    ....#...............####.... |
|     #   ..........  ........      #       ....      #  ...............    .... |
|     #   ..........  ........##################      #  ...............    .... |
|     #   ..........  ......>.  .......       ##      #  ...............    .... |
|     #   .....>....  ........  .......       ##      # #...............         |
|     #   ..........      #     .......    .............#...............         |
|     #   ..........      #     .......####............. ...............         |
|     #            ##     #     .......    ............. ...............#        |
|   ....            ##    #     .......       ##         ...............##       |
|   ....             ##   #     .......      ....               #        ##      |
|   ....              #######################...>         ........        ....   |
|                         ###################....#########........########....   |
|                                                         ........        ....   |
|                                                                                |
----------------------------------------------------------------------------------
```
