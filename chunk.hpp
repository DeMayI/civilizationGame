#include "tile.hpp"
#define CHUNK_SIZE 32


class chunk{
    private:
        tile* tiles[CHUNK_SIZE][CHUNK_SIZE];
        chunk* neighbors[4]; //0 = up, 1 = right, 2 = down, 3 = left
    public:
        chunk();
        ~chunk();
        
        tile* get_tile(int x, int y);
        void set_tile(int x, int y, tile* t);

        void set_neighbor(int direction, chunk* neighbor);
        chunk* get_neighbor(int direction);
}