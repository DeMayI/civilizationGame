//tile.hpp
//represents a single tile on the map
#define DEFAULTID 0
#define IMG_WIDTH 13
#define IMG_HEIGHT 11
#define TILE_SIZE_WIDTH ((IMG_WIDTH - TILE_BORDER)/ 2)
#define TILE_SIZE_HEIGHT ((IMG_HEIGHT - TILE_BORDER) / 1.73205080757f)
#define TILE_BORDER 1

class tile{
    private:
     int imageID;
    public:
        int getImageID();
        void setImageID(int newID);
        tile(int imageID);
        tile();
};