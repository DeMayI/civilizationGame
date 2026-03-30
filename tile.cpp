#include "tile.hpp"

tile::tile(int imageID){
    this->imageID = imageID;
}
tile::tile(){
    this->imageID = DEFAULTID;
}

int tile::getImageID(){
    return this->imageID;
}

void tile::setImageID(int newID){
    this->imageID = newID;
}