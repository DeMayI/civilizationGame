//tile.hpp
//represents a single tile on the map
#define DEFAULTID 0
#define TILE_SIZE 6.5
class tile{
    private:
     int imageID;
    public:
        int getImageID();
        void setImageID(int newID);
        tile(int imageID);
        tile();
};