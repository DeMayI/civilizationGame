//tile.hpp
//represents a single tile on the map
#define DEFAULTID 0
#define IMG_WIDTH 13
#define IMG_HEIGHT 11
#define TILE_SIZE_WIDTH ((IMG_WIDTH - TILE_BORDER)/ 2.0f)
#define TILE_SIZE_HEIGHT ((IMG_HEIGHT - TILE_BORDER) / 1.73205080757f)
#define TILE_BORDER 1
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

typedef enum TILE_IDENTIFIER{
    TILE_IDENTIFIER_EMPTY = 0,
    TILE_IDENTIFIER_DARK = 1,
    TILE_IDENTIFIER_LIGHT = 2,
    TILE_IDENTIFIER_HIGHLIGHT = 3,
    TILE_IDENTIFIER_MINE = 4,
    TILE_IDENTIFIER_LUMBER = 5,
    TILE_IDENTIFIER_RESIDENCE = 6,
    TILE_IDENTIFIER_COAL_ORE = 7,
    TILE_IDENTIFIER_IRON_ORE = 8,
    TILE_IDENTIFIER_WHEAT_FIELD = 9,
    TILE_IDENTIFIER_FARM = 10,
    TILE_IDENTIFIER_MAIN_HUB = 11
}TILE_IDENTIFIER;

class tile{
    private:
    //Image id for the background img
     int bImgID;
    //Image id for the foreground img
     int fImgID;
     bool active;
    public:
        int getBackground();
        void setBackground(int newID);
        int getForeground();
        void setForeground(int newID);
        tile(int imageID);
        tile(int imageID, int foregroundID);
        tile();
        virtual void on_tick();
};

struct resource{
    int quantity;
    string name;
};
class structure: public tile{
    private:
        string name;
    public:
        structure(string name);
        structure(string name, int bckID, int frgID);
        ~structure();
        
        string get_name();
};
class storage: public tile{
    private:
        unordered_map<string, resource> currentResources;
    public:
        
        struct resource get_resource(string name);
        void add_resource(resource newResource);
        
};

