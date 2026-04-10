#include "tile.hpp"
#define CHUNK_SIZE 32
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class chunk{
    private:
        //2D array of tile pointers
        vector<vector<tile*>> tiles;
        //Pointer to each neighbor chunk
        chunk* neighbors[4]; //0 = up, 1 = right, 2 = down, 3 = left
    public:
        chunk();
        ~chunk();

        tile* get_tile(int x, int y);
        
        //Sets a tile to the provided tile pointer, if a tile already exists at those coordinates it will be deleted
        void set_tile(int x, int y, tile* t);

        void set_neighbor(int direction, chunk* neighbor);
        chunk* get_neighbor(int direction);
};