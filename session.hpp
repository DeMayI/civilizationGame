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


class session{
    private:
        tileMap* map;
        SPRITES sprites;
        position mousePos;
        coordinateDouble hilightedTile;
        unsigned char* keys;
        unsigned char* mouseButtons;


    public:
        //Simulates a tick of the game
        void tick(unsigned char* keys, unsigned char* mouseButtons, position mousePos);

        //Draws the currently visible tiles to the screen
        void drawMap();

        //Initializes the session using the provided spritesheet
        session();

        //Deconstructor:Terminates the session and removes all memory associated with it
        ~session();

        void updateHighlighted(position mousePos);
};