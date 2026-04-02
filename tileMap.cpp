#include "tileMap.hpp"
#include <cmath>
#define HORIZONTALMOD 6
#define VERTICALMOD 5

struct Orientation {
    const double f0, f1, f2, f3;
    const double b0, b1, b2, b3;
    const double start_angle; // in multiples of 60°
    Orientation(double f0_, double f1_, double f2_, double f3_,
                double b0_, double b1_, double b2_, double b3_,
                double start_angle_)
    : f0(f0_), f1(f1_), f2(f2_), f3(f3_),
      b0(b0_), b1(b1_), b2(b2_), b3(b3_),
      start_angle(start_angle_) {}
};
const Orientation layout_flat
  = Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
                2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
                0.0);



void deleteChunk(chunk* currentChunk){
    if(currentChunk != nullptr){
        deleteChunk(currentChunk->get_neighbor(UP));
        deleteChunk(currentChunk->get_neighbor(DOWN));
        deleteChunk(currentChunk->get_neighbor(RIGHT));
        deleteChunk(currentChunk->get_neighbor(LEFT));
        delete currentChunk;
    }
}

tileMap::tileMap(){
    this->head_chunk = new chunk();
}

tileMap::~tileMap(){
    deleteChunk(this->head_chunk);
}

struct coordinateAxial tileMap::double_to_axial(coordinateDouble coor){
    coordinateAxial newCube;
    newCube.q = coor.x;
    newCube.r = (coor.y - coor.x) / 2;
    return newCube;
    
}
struct coordinateDouble tileMap::axial_to_double(coordinateAxial hex){
    coordinateDouble newDouble;
    newDouble.x = hex.q;
    newDouble.y = 2 * hex.r + hex.q;
    return newDouble;
}


struct coordinateAxial tileMap::axial_round(coordinateAxial frac){
    return cube_to_axial(cube_round(axial_to_cube(frac)));
}


struct coordinateAxial tileMap::convertToGridAxial(int x, int y){
    coordinateAxial newAxial = this->convertToGridAxialUnrounded(x, y);
    return axial_round(newAxial);
}
struct coordinateAxial tileMap::convertToGridAxialUnrounded(int x, int y){
    float x2 = (x - HORIZONTALMOD) / TILE_SIZE_WIDTH;
    float y2 = (y - VERTICALMOD) / TILE_SIZE_HEIGHT;
    const Orientation& M = layout_flat;
    coordinateAxial newAxial;
    newAxial.q = M.b0 * x2 + M.b1 * y2;
    newAxial.r = M.b2 * x2 + M.b3 * y2;
    return newAxial;
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
    newCube.s = (newCube.q * -1.0f) - newCube.r;
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
    while(x >= CHUNK_SIZE){
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
    while(y >= CHUNK_SIZE){
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