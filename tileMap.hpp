#include "chunk.hpp"

//The maximium size of the map in chunks, centered around the head chunk
//EX; if max size is 2, then there will be 2 chunks in all directions from the head chunk so a 5x5 grid.
#define MAX_SIZE = 2

struct coordinateDouble {
    float x;
    float y;
};
struct coordinateAxial {
    float q;
    float r;
};
struct coordinateCube {
    float q;
    float r;
    float s;
};


class tileMap{
    private:
        chunk* head_chunk;
        
        

    public:

        tileMap();  
        ~tileMap();

        tile* get_tile(int x, int y);
        void set_tile(int x, int y, tile* t);

        chunk* generateChunk(chunk* currentChunk, int dir);


        //Converts screen coordinates to grid coordinate
        struct coordinateDouble convertToGridDouble(int x, int y, int camera_x, int camera_y);
        struct coordinateAxial convertToGridAxial(int x, int y);
        
        struct coordinateAxial double_to_axial(coordinateDouble coor);
        struct coordinateDouble axial_to_double(coordinateAxial hex);

        struct coordinateAxial axial_round(coordinateAxial frac);
        struct coordinateCube cube_round(coordinateCube frac);

        struct coordinateCube axial_to_cube(coordinateAxial axial);
        struct coordinateAxial cube_to_axial(coordinateCube cube);
};