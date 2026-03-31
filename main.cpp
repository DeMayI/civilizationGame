#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <allegro5/allegro_color.h>
#include "tileMap.hpp"
#include <cmath>

#define SCALED_WIDTH 240
#define SCALED_HEIGHT 120
#define KEY_SEEN 1
#define KEY_DOWN 2


ALLEGRO_DISPLAY* disp;
ALLEGRO_TRANSFORM t;

void display_init(float& scale_factor_x, float& scale_factor_y){
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    disp = al_create_display(SCALED_WIDTH, SCALED_HEIGHT);

    scale_factor_x = (float)al_get_display_width(disp) / SCALED_WIDTH;
    scale_factor_y = (float)al_get_display_height(disp) / SCALED_HEIGHT;
    
    al_identity_transform(&t);
	al_scale_transform(&t, scale_factor_x, scale_factor_y);
	al_use_transform(&t);
}

void display_deinit(){
    al_destroy_display(disp);
}

struct SPRITES{
    ALLEGRO_BITMAP* sheet;
    ALLEGRO_BITMAP* tiles[3];
};
SPRITES sprites;

void sprites_init(){
    sprites.sheet = al_load_bitmap("data/TempTiles-sheet.png");
    sprites.tiles[0] = al_create_sub_bitmap(sprites.sheet, 0, 0, 13, 13);
    sprites.tiles[1] = al_create_sub_bitmap(sprites.sheet, 13, 0, 13, 13);
    sprites.tiles[2] = al_create_sub_bitmap(sprites.sheet, 26, 0, 13, 13);
}

void sprites_deinit(){
    for(int i = 0; i < 3; i++){
        al_destroy_bitmap(sprites.tiles[i]);
    }
    al_destroy_bitmap(sprites.sheet);
}



void moveCamera(int& camera_x, int& camera_y, int camera_speed, unsigned char keys[]){
    if(keys[ALLEGRO_KEY_W]){
        camera_y -= camera_speed;
    }
    if(keys[ALLEGRO_KEY_S]){
        camera_y += camera_speed;
    }
    if(keys[ALLEGRO_KEY_A]){
        camera_x -= camera_speed;
    }
    if(keys[ALLEGRO_KEY_D]){
        camera_x += camera_speed;
    }
}

//Draws the bitmap of every object visible to the camera, using the camera's current position and size
void renderCamera(int camera_x, int camera_y, int camera_size_x, int camera_size_y){

}

int main()
{
    float scale_factor_x;
    float scale_factor_y;
    al_init();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    
    ALLEGRO_FONT* font = al_create_builtin_font();
    

    display_init(scale_factor_x, scale_factor_y);

    

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());       

    if(!al_init_image_addon()){
        printf("Failed to initialize image addon!\n");
        return 1;
    }

    al_hide_mouse_cursor(disp);

    sprites_init();

    ALLEGRO_BITMAP* mysha = al_load_bitmap("data/mysha.png");
    ALLEGRO_BITMAP* testPixel = al_load_bitmap("TestPixel.png");
    if(!mysha){
        printf("Failed to load mysha!\n");
        return 1;
    }

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    //Initializes camera variables
    int camera_x = 0;
    int camera_y = 0;
    int camera_speed = 2;
    int camera_size_x = SCALED_WIDTH;
    int camera_size_y = SCALED_HEIGHT;

    //Mouse information
    int mouse_x = 0;
    int mouse_y = 0;

    //Temporary
    int highlightX;
    int highlightY;

    //Array of all possible keys and their state
    unsigned char keys[ALLEGRO_KEY_MAX];
    //Initializes all the keys to 0
    memset(keys, 0, sizeof(keys));


    tileMap tiles = tileMap();

    // Main game loop

    while(1)
    {
        bool done = false;
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            //If its a timer event, redraw screen and update camera position
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                moveCamera(camera_x, camera_y, camera_speed, keys);

                //Marks each key as seen
                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    keys[i] &= ~KEY_SEEN;

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
            {
                //Sets the keys value to 00000011, meaning the key has been pressed
                keys[event.keyboard.keycode] = KEY_SEEN | KEY_DOWN;
                if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    done = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES:
            {
                int prevx = highlightX;
                int prevy = highlightY;
                mouse_x = event.mouse.x / scale_factor_x;
                mouse_y = event.mouse.y / scale_factor_y;
                printf("Mouse X:%d Y:%d\n", mouse_x, mouse_y);
                struct coordinateAxial highlightedTileAxial = tiles.convertToGridAxial(mouse_x, mouse_y);
                struct coordinateDouble highlightedTile = tiles.axial_to_double(highlightedTileAxial);
                tiles.get_tile(prevx, prevy)->setImageID(DEFAULTID);
                highlightX = highlightedTile.x;
                highlightY = highlightedTile.y;
                printf("Highlighted Tile X:%d Y%d\n", highlightX, highlightY);
                tiles.get_tile(highlightX, highlightY)->setImageID(2);
                break;
            }
            case ALLEGRO_EVENT_KEY_UP:
                //Sets the key down bit to 0, meaning the key has been released, but keeps the seen bit as it is until next timer event.
                keys[event.keyboard.keycode] &= ~KEY_DOWN;
                break;
        }
        //Exits the program if done
        if(done)
            break;


        //If the event queue all events have been processed and we need to redraw, redraw the screen
        if(redraw && al_is_event_queue_empty(queue))
        {
            //Clears the screen to black
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            //Draws hexagonal tiles
            for(int i = -2; i < 30; i++){
                for(int j = -2; j < 20; j++){
                    if((i % 2) == 0){
                        al_draw_bitmap(sprites.tiles[tiles.get_tile(j * 2, i)->getImageID()], j * 18, ((i / 2) * 10), 0);
                    } else {
                        al_draw_bitmap(sprites.tiles[tiles.get_tile(j * 2 + 1, i)->getImageID()], (j * 18) + 9, (((i - 1) / 2) * 10) + 5, 0);
                    }
                }
            }
            //al_draw_bitmap(testPixel, -1, -1, 0);
            //al_draw_bitmap(sprites.tiles[0], 0, 10, 0);
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(mysha);
    al_destroy_font(font);
    
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    display_deinit();
    sprites_deinit();
    return 0;
}