#include "chunk.hpp"

//The maximium size of the map in chunks, centered around the head chunk
//EX; if max size is 2, then there will be 2 chunks in all directions from the head chunk so a 5x5 grid.
#define MAX_SIZE = 2


class tileMap{
    private:
        chunk* head_chunk;
        
        

    public:

        tileMap();  
        ~tileMap();

        tile* get_tile(int x, int y);
        void set_tile(int x, int y, tile* t);

};