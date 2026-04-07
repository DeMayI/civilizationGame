//tile.hpp
//represents a single tile on the map
#define DEFAULTID 0
#define IMG_WIDTH 13
#define IMG_HEIGHT 11
#define TILE_SIZE_WIDTH ((IMG_WIDTH - TILE_BORDER)/ 2.0f)
#define TILE_SIZE_HEIGHT ((IMG_HEIGHT - TILE_BORDER) / 1.73205080757f)
#define TILE_BORDER 1

class tile{
    private:
    //Image id for the background img
     int bImgID;
    //Image id for the foreground img
     int fImgID;
    public:
        int getBackground();
        void setBackground(int newID);
        int getForeground();
        void setForeground(int newID);
        tile(int imageID);
        tile(int imageID, int foregroundID);
        tile();
};