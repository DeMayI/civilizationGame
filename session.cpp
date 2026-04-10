#include "session.hpp"


session::session(unsigned char* keys, unsigned char* mouseButtons, position* mousePos){
    this->sprites.sheet = al_load_bitmap_flags(SPRITE_SHEET_LOC, ALLEGRO_NO_PREMULTIPLIED_ALPHA);
    int x = al_get_bitmap_width(this->sprites.sheet) / IMG_WIDTH;
    int y = al_get_bitmap_height(this->sprites.sheet) / IMG_HEIGHT;
    this->sprites.tileCount = x * y;
    this->sprites.tiles.resize(x * y);
    this->map = new tileMap();
    for(int j = 0; j < y; j++){
        for(int i = 0; i < x; i++){
            sprites.tiles[(x * j) + i] = al_create_sub_bitmap(sprites.sheet, i * IMG_WIDTH, j * IMG_HEIGHT, 13, 13);
        }
    }
    coordinateDouble current_highlighted;
    current_highlighted.x = 0;
    current_highlighted.y = 0;
    this->hilightedTile = current_highlighted;
    this->keys = keys;
    this->mouseButtons = mouseButtons;
    this->mousePos = mousePos;
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
            //al_draw_bitmap(sprites.tiles[j % this->sprites.tileCount], j * 1.5f * TILE_SIZE_WIDTH, (((j % 2)  * (IMG_HEIGHT/2)) + (i * (IMG_HEIGHT - TILE_BORDER))), 0);
            //Draws foreground tile if the foreground id of the tile does not equal 0
            if(this->map->get_tile(j, (i * 2) + (j % 2))->getForeground() != 0){
                //printf("Drawing foreground bitmap/n");
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

void session::tick(){
    


    
}
void session::updateHighlighted(){
 //Calculates the currently highlighted tile
    struct coordinateAxial highlightedTileAxial = this->map->convertToGridAxial(this->mousePos->x, this->mousePos->y);

    //For debug
    //struct coordinateAxial highlightedTileAxialUnrounded = this->map.convertToGridAxialUnrounded(mouse_x, mouse_y);

    //Converts from axial to the double coordinate system
    this->hilightedTile = this->map->axial_to_double(highlightedTileAxial);
}

void session::keyDown(int keycode){
    //Sets the selected building to the corresponding key(ie building 0 is key 1, building 1 is key 2, etc)
    if(keycode >= ALLEGRO_KEY_1 && keycode <= ALLEGRO_KEY_9){
        int id = keycode - ALLEGRO_KEY_1;
        if(id > buildings.size()){
            id = TILE_IDENTIFIER_EMPTY;
        }
        this->selectedBuilding = buildings[id];
        printf("CurrentBuilding:%d\n", this->selectedBuilding);
    }

}

tile* createNewTile(int tileIdentifier, int bckID){
    switch(tileIdentifier){
        case TILE_IDENTIFIER_EMPTY:
            return new tile(bckID);
        case TILE_IDENTIFIER_MINE:
            return new structure("Mine", bckID, TILE_IDENTIFIER_MINE);
        case TILE_IDENTIFIER_LUMBER:
            return new structure("Lumber", bckID, TILE_IDENTIFIER_LUMBER);
        case TILE_IDENTIFIER_RESIDENCE:
            return new structure("Residence", bckID, TILE_IDENTIFIER_RESIDENCE);
        case TILE_IDENTIFIER_COAL_ORE:
            return new structure("Coal Ore", bckID, TILE_IDENTIFIER_COAL_ORE);
        case TILE_IDENTIFIER_IRON_ORE:
            return new structure("Iron Ore", bckID, TILE_IDENTIFIER_IRON_ORE);
        case TILE_IDENTIFIER_WHEAT_FIELD:
            return new structure("Wheat Field", bckID, TILE_IDENTIFIER_WHEAT_FIELD);
        case TILE_IDENTIFIER_FARM:
            return new structure("Farm", bckID, TILE_IDENTIFIER_FARM);
        case TILE_IDENTIFIER_MAIN_HUB:
            return new structure("Main Hub", bckID, TILE_IDENTIFIER_MAIN_HUB);
        default:
            return new tile(bckID);
    }
   
}
void session::mouseDown(unsigned int button){
    if(button == ALLEGRO_MOUSE_BUTTON_LEFT){
        
        tileLocation prev = this->map->get_tile_detailed(this->hilightedTile.x, this->hilightedTile.y);
        //printf("%d\n", selectedBuilding
        
        //tile* newTile = new structure("Mine", 0, 5); 
        tile* newTile = createNewTile(selectedBuilding, prev.t->getBackground());
        this->map->set_tile(prev.x, prev.y, prev.c, newTile);
        //printf("Placed new tile!\n");
        tile* nTile = this->map->get_tile(hilightedTile.x, hilightedTile.y);
        printf("New Tile: back:%d, fore:%d\n", newTile->getBackground(), newTile->getForeground());
    }
}