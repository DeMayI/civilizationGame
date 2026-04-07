#include "tile.hpp"

tile::tile(int imageID){
    this->bImgID = imageID;
}
tile::tile(int imageID, int foregroundID){
    this->bImgID = imageID;
    this->fImgID - foregroundID;
}
tile::tile(){
    this->bImgID = DEFAULTID;
    this->fImgID = 0;
}

int tile::getBackground(){
    return this->bImgID;
}
int tile::getForeground(){
    return this->fImgID;
}

void tile::setBackground(int newID){
    this->bImgID = newID;
}
void tile::setForeground(int newID){
    this->fImgID = newID;
}