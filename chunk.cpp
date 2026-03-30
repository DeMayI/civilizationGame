#include "chunk.hpp"


chunk::chunk(){
    tile*** tileArray = new tile**[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++){
        tileArray[i] = new tile*[CHUNK_SIZE];
        for(int j = 0; j < CHUNK_SIZE; j++){
            tileArray[i][j] = new tile();
        }
    }
    this->tiles = tileArray;
    for(int i = 0; i < 4; i++){
        this->neighbors[i] = nullptr;
    }
}

chunk::~chunk(){
    for(int i = 0; i < CHUNK_SIZE; i++){
        for(int j = 0; j < CHUNK_SIZE; j++){
            delete this->tiles[i][j];
        }
        delete this->tiles[i];
    }
    delete this->tiles;
}

tile* chunk::get_tile(int x, int y){
    if(x >= 0 && x <= CHUNK_SIZE){
        if(y >= 0 && x <= CHUNK_SIZE){
            return this->tiles[x][y];
        } 
    }
    return nullptr;

}
void chunk::set_tile(int x, int y, tile* t){
    if(x >= 0 && x <= CHUNK_SIZE){
        if(y >= 0 && x <= CHUNK_SIZE){
            tile* oldTile = this->tiles[x][y];
            this->tiles[x][y] = t;
            delete oldTile;
        } 
    }
}
void chunk::set_neighbor(int direction, chunk* neighbor){
    if(direction >= 0 && direction <= 3){
        this->neighbors[direction] = neighbor;
    }
}
chunk* chunk::get_neighbor(int direction){
    if(direction >= 0 && direction <= 3){
        return this->neighbors[direction];
    } else {
        return nullptr;
    }
}