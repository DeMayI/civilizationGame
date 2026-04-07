#include "session.hpp"


session::session(){
    this->sprites.sheet = al_load_bitmap_flags(SPRITE_SHEET_LOC, ALLEGRO_NO_PREMULTIPLIED_ALPHA);
    int x = al_get_bitmap_width(this->sprites.sheet) / IMG_WIDTH;
    int y = al_get_bitmap_height(this->sprites.sheet) / IMG_HEIGHT;
    this->sprites.tileCount = x * y;
    this->sprites.tiles.resize(x * y);
    this->map = new tileMap();
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            sprites.tiles[(y * j) + i] = al_create_sub_bitmap(sprites.sheet, i * IMG_WIDTH, j * IMG_HEIGHT, 13, 13);
        }
    }
}

session::~session(){
    for(int i = 0; i < this->sprites.tileCount; i++){
        
        al_destroy_bitmap(this->sprites.tiles[i]);
        
    }
    al_destroy_bitmap(this->sprites.sheet);
    delete this->map;
}

void session::drawMap(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            //Draws background tile
            al_draw_bitmap(sprites.tiles[this->map->get_tile(j, (i * 2) + (j % 2))->getBackground()], j * 1.5f * TILE_SIZE_WIDTH, (((j % 2)  * (IMG_HEIGHT/2)) + (i * (IMG_HEIGHT - TILE_BORDER))), 0);

            //Draws foreground tile if the foreground id of the tile does not equal 0
            if(this->map->get_tile(j, (i * 2) + (j % 2))->getForeground() != 0){
                al_draw_bitmap(sprites.tiles[this->map->get_tile(j, (i * 2) + (j % 2))->getForeground()], j * 1.5f * TILE_SIZE_WIDTH, (((j % 2)  * (IMG_HEIGHT/2)) + (i * (IMG_HEIGHT - TILE_BORDER))), 0);
            }
            /*
            if((i % 2) == 0){
                al_draw_bitmap(sprites.tiles[this->map.get_tile(j * 2, i)->getImageID()], j * 18, ((i / 2) * 10), 0);
                al_draw_bitmap(testPixel, j * 18, ((i / 2) * 10), 0);
            } else {
                al_draw_bitmap(sprites.tiles[this->map.get_tile(j * 2 + 1, i)->getImageID()], (j * 18) + 9, (((i - 1) / 2) * 10) + 5, 0);
                al_draw_bitmap(testPixel, (j * 18) + 9, (((i - 1) / 2) * 10) + 5, 0);
            }
            */
            
            if(j == this->hilightedTile.x && ((i * 2) + (j % 2)) == this->hilightedTile.y){
            //Draw highlight overlay
                al_draw_bitmap(sprites.tiles[3], j * 1.5f * TILE_SIZE_WIDTH, (((j % 2)  * (IMG_HEIGHT/2)) + (i * (IMG_HEIGHT - TILE_BORDER))), 0);
            }
        }
    }
}

void session::tick(unsigned char* keys, unsigned char* mouseButtons, position mousePos){
    


    
}
void session::updateHighlighted(position mousePos){
 //Calculates the currently highlighted tile
    struct coordinateAxial highlightedTileAxial = this->map->convertToGridAxial(mousePos.x, mousePos.y);

    //For debug
    //struct coordinateAxial highlightedTileAxialUnrounded = this->map.convertToGridAxialUnrounded(mouse_x, mouse_y);

    //Converts from axial to the double coordinate system
    this->hilightedTile = this->map->axial_to_double(highlightedTileAxial);
}