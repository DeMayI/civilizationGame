#include "tileMap.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <allegro5/allegro_color.h>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
#define SPRITE_SHEET_LOC "data/TempTiles-sheet.png"

struct SPRITES{
    ALLEGRO_BITMAP* sheet;
    int tileCount;
    vector<ALLEGRO_BITMAP*> tiles;
};
struct position{
    int x;
    int y;
};

typedef enum ALLEGRO_MOUSE_BUTTON
{
   ALLEGRO_MOUSE_BUTTON_LEFT = 1,
   ALLEGRO_MOUSE_BUTTON_RIGHT = 2,
   ALLEGRO_MOUSE_BUTTON_MIDDLE = 3
} ALLEGRO_MOUSE_BUTTON;


class session{
    private:
        tileMap* map;
        SPRITES sprites;
        position* mousePos;
        coordinateDouble hilightedTile;
        unsigned char* keys;
        unsigned char* mouseButtons;
        vector<int> buildings = {TILE_IDENTIFIER_MINE, TILE_IDENTIFIER_LUMBER, TILE_IDENTIFIER_FARM, TILE_IDENTIFIER_RESIDENCE};
        int selectedBuilding;

    public:
        //Simulates a tick of the game
        void tick();

        //Draws the currently visible tiles to the screen
        void drawMap();

        //Initializes the session using the provided spritesheet
        session(unsigned char* keys, unsigned char* mouseButtons, position* mousePos);

        //Deconstructor:Terminates the session and removes all memory associated with it
        ~session();


        void keyDown(int keycode);
        void mouseDown(unsigned int button);

        void updateHighlighted();
};