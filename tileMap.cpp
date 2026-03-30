#include "tileMap.hpp"
#include <cmath>


struct coordinateAxial tileMap::double_to_axial(coordinateDouble coor){
    coordinateAxial newCube;
    newCube.q = coor.y;
    newCube.r = (coor.x - coor.y) / 2;
    return newCube;
    
}
struct coordinateDouble tileMap::axial_to_double(coordinateAxial hex){
    coordinateDouble newDouble;
    newDouble.y = hex.q;
    newDouble.x = 2 * hex.r + hex.q;
    return newDouble;
}

struct coordinateDouble tileMap::convertToGridDouble(int x, int y, int camera_x, int camera_y){

}
struct coordinateAxial tileMap::axial_round(coordinateAxial frac){
    return cube_to_axial(cube_round(axial_to_cube(frac)));
}


struct coordinateAxial tileMap::convertToGridAxial(int x, int y, int camera_x, int camera_y){
    float x2 = (x + camera_x) / TILE_SIZE;
    float y2 = (y + camera_y) / TILE_SIZE;
    coordinateAxial newAxial;
    newAxial.q = (2.0 / 3 * x2);
    newAxial.r = (-1.0 / 3 * x2 + 0.57735 * y2);
    return axial_round(newAxial);
}

struct coordinateCube tileMap::cube_round(coordinateCube frac){
    float q = round(frac.q);
    float r = round(frac.r);
    float s = round(frac.s);

    float q_dif = abs(q - frac.q);
    float r_dif = abs(r - frac.r);
    float s_dif = abs(s - frac.s);

    if(q_dif > r_dif && q_dif > s_dif){
        q = -r-s;
    }
    else if(r_dif > s_dif){
        r = -q-s;
    } else {
        s = -q-r;
    }
    coordinateCube newCube;
    newCube.q = q;
    newCube.r = r;
    newCube.s = s;
    return(newCube);
}

struct coordinateCube tileMap::axial_to_cube(coordinateAxial axial){
    coordinateCube newCube;
    newCube.q = axial.q;
    newCube.r = axial.r;
    newCube.s = newCube.q * -1 - newCube.r;
    return newCube;
}

struct coordinateAxial tileMap::cube_to_axial(coordinateCube cube){
    coordinateAxial newAxial;
    newAxial.q = cube.q;
    newAxial.r = cube.r;
    return newAxial;
}

//Generates a new empty chunk, and sets it as a neighor of the provided chunk in the specified direction
chunk* tileMap::generateChunk(chunk* currentChunk, int dir){
    chunk* newChunk = new chunk();
    currentChunk->set_neighbor(dir, newChunk);
    return newChunk;
}


tile* tileMap::get_tile(int x, int y){
    chunk* currentChunk = this->head_chunk;
    //Iterates through the chunks horizontally, then vertically

    //Iterates to the right until we are inside a chunk
    while(x > CHUNK_SIZE){
        x -= CHUNK_SIZE;
        //IF the neighor exists, set it to the current, otherwise create a new chunk
        if(currentChunk->get_neighbor(RIGHT) != nullptr){
            currentChunk = currentChunk->get_neighbor(RIGHT);
        } else {
            currentChunk = this->generateChunk(currentChunk, RIGHT);
        }
    }

    //Iterates to the left until we are inside a chunk
    while(x < 0){
        x += CHUNK_SIZE;
        if(currentChunk->get_neighbor(LEFT) != nullptr){
            currentChunk = currentChunk->get_neighbor(LEFT);
        } else {
            currentChunk = this->generateChunk(currentChunk, LEFT);
        }
    }
    //Iterates upwards until we are inside a chunk
    while(y > CHUNK_SIZE){
        y -= CHUNK_SIZE;
        if(currentChunk->get_neighbor(UP) != nullptr){
            currentChunk = currentChunk->get_neighbor(UP);
        } else {
            currentChunk = this->generateChunk(currentChunk, UP);
        }
    }

    //Iterates downwards until we are inside a chunk
    while(y < 0){
        y += CHUNK_SIZE;
        if(currentChunk->get_neighbor(DOWN) != nullptr){
            currentChunk = currentChunk->get_neighbor(DOWN);
        } else {
            currentChunk = this->generateChunk(currentChunk, DOWN);
        }
    }
    
    return currentChunk->get_tile(x, y);
}