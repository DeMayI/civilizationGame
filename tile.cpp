#include "tile.hpp"

tile::tile(int imageID){
    this->bImgID = imageID;
    this->fImgID = 0;
}
tile::tile(int imageID, int foregroundID){
    this->bImgID = imageID;
    this->fImgID = foregroundID;
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
void tile::on_tick(){
    return;
}

structure::structure(string name): tile() {
    this->name = name;
}
structure::structure(string name, int bckID, int frgID): tile(bckID, frgID){
    this->name = name;
}


struct resource storage::get_resource(string name){
    return this->currentResources.at(name);
}
void storage::add_resource(resource newResource){
    if(this->currentResources.find(newResource.name) != this->currentResources.end()){
        this->currentResources.at(newResource.name).quantity += newResource.quantity;
    } else {
        this->currentResources.insert({newResource.name, newResource});
    }
}
