#include <Arduboy2.h>       // required to build for Arduboy
#include <ArduboyFX.h>      // required to access the FX external flash
#include "fxdata/fxdata.h"  // this file contains all references to FX data
#include <ArduboyTones.h>
#include "Tinyfont.h"



Arduboy2 arduboy;
Arduboy2Audio audio;
ArduboyTones sound(arduboy.audio.enabled);

Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());


#define STAGE_GAME_TITLE    0
#define STAGE_PLAY_GAME     1
#define STAGE_LEVEL_COMPLETED     2

byte game_stage = STAGE_GAME_TITLE;

#define FRAME_RATE 30



bool enable_audio = true;
bool cheat_mode = false;
byte Current_Level =  1;

#define PLAYER_FRAME_RATE   4
#define PLAYER_SPEED        1


#define RIGHT               0
#define LEFT                1

#define JUMP_ITERATIONS     20
byte keys = 0;
struct Player {
    int x; // = 60;
    int y; // = 104;
    byte jump_iteration = 0;
    //byte sprite = RIGHT;        //0 - RIGHT SPRITE, 1 - LEFT SPRITE
    byte frame = 0; 

    byte direction = RIGHT;     //0 - right, 1 - left
    bool is_jumping = false;
    bool is_falling = false;
    bool is_walking = false; 
    bool is_directional_jumping = false; 
    bool is_directional_falling = false;
     
} player;

struct Portal {
     int x;
     int y;
} portal;

struct Camera {
    int x = player.x-60;
    int y = player.y-40;

}camera;

#define CAMERA_Y_OFFSET 24
#define SPEED_SLOW      2
#define SPEED_NORMAL    1
#define SPEED_FAST      0
byte guardian_frame = 0;
byte gurdian_horizontal_type;

struct Guardians_Horizontal {
    bool enabled = false;
    int x;             //cell 
    byte y;             //row
    byte start_position;
    byte end_position;          //cell
    byte direction;     //0 - RIGHT or 1 - LEFT
    byte speed = SPEED_NORMAL;
    
    
} guardian_horizontal[4];


byte gurdian_vertical_type;
#define UP      0
#define DOWN    1
struct Guardians_Vertical {
    bool enabled = false;
    int x;             
    int y;             
    byte start_position;
    byte end_position;         
    byte direction;     //0 - UP or 1 - DOWN
    byte speed = SPEED_NORMAL;
    
    
} guardian_vertical[4];



void title_screen(){
    
   do{
       
        
        arduboy.clear();
        arduboy.pollButtons();
        do{
            delay(1);
        }while (!(arduboy.nextFrame()));
        
        if (arduboy.everyXFrames(5)) {
            player.frame = player.frame+1;
            if (player.frame>7) {player.frame=0;}
        }
    
        
        FX::drawBitmap(0, 0, title_gfx, 0, 1);

        FX::drawBitmap(0, 0, player_gfx, player.frame, 1);

        tinyfont.setCursor(0, 60);
        tinyfont.print("LEVEL:");
        
        tinyfont.setCursor(30, 60);
        tinyfont.print(Current_Level);
        
        tinyfont.setCursor(45, 60);
        tinyfont.print("SOUND:");
        tinyfont.setCursor(75, 60);
        if (enable_audio){tinyfont.print("Y");
        }else {tinyfont.print("N");}
        
        tinyfont.setCursor(85, 60);
        tinyfont.print("CHEAT:");
        tinyfont.setCursor(115, 60);
        if (cheat_mode){tinyfont.print("Y");
        }else {tinyfont.print("N");}
        
        
        if (arduboy.justPressed(RIGHT_BUTTON)) {
             Current_Level = Current_Level + 1;
             if (Current_Level > 20) { Current_Level = 1;}
        }
    
        if (arduboy.justPressed(LEFT_BUTTON)) {
             Current_Level = Current_Level - 1;
             if (Current_Level < 1) { Current_Level = 20;}
        }
        
        if (arduboy.justPressed(DOWN_BUTTON)) {
             enable_audio = !enable_audio;
        }
    
        if (arduboy.justPressed(UP_BUTTON)) {
             cheat_mode = !cheat_mode;
        }
         
         
    
         arduboy.display();
         FX::display(CLEAR_BUFFER);
    }while(!arduboy.justReleased(A_BUTTON));
    
    if(enable_audio){ audio.on(); }
    else { audio.off(); }    
        
   prepare_level_parameters(Current_Level);
}

uint8_t tilemapBuffer[512]; //buffer to load Level map

void prepare_level_parameters(byte Level){
    

    
    switch (Level){
        case 1:    
           // Current_Level = 1;
            FX::readDataArray(Level_1, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            break;
        case 2:
           // Current_Level = 2;
            FX::readDataArray(Level_2, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            break;
        case 3:
            FX::readDataArray(Level_3, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            break;
        case 4:
            FX::readDataArray(Level_4, 0, 0, 512, tilemapBuffer,512);
            player.direction = LEFT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            break;
        case 5:
            FX::readDataArray(Level_5, 0, 0, 512, tilemapBuffer,512);
            player.direction = LEFT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        case 6:
            FX::readDataArray(Level_6, 0, 0, 512, tilemapBuffer,512);
            player.direction = LEFT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        case 7:
            FX::readDataArray(Level_7, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        case 8:
            FX::readDataArray(Level_8, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        case 9:
            FX::readDataArray(Level_9, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_FAST;
            break;
            
        case 10:
            FX::readDataArray(Level_10, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        
        case 11:
            FX::readDataArray(Level_11, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_FAST;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_FAST;
            break;
        
        case 12:
            FX::readDataArray(Level_12, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;

            break;
            
        case 13:
            FX::readDataArray(Level_13, 0, 0, 512, tilemapBuffer,512);
            player.direction = LEFT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_SLOW;
            guardian_vertical[0].speed = SPEED_NORMAL;


            break;
         case 14:
            FX::readDataArray(Level_14, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;


            break;
        
        case 15:
            FX::readDataArray(Level_15, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_SLOW;
            guardian_vertical[2].speed = SPEED_NORMAL;


            break;
        
        case 16:
            FX::readDataArray(Level_16, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_SLOW;

            break;
        
        case 17:
            FX::readDataArray(Level_17, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_SLOW;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_NORMAL;
            guardian_vertical[3].speed = SPEED_FAST;
            break;
        
        case 18:
            FX::readDataArray(Level_18, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_SLOW;
            guardian_horizontal[1].speed = SPEED_SLOW;
            guardian_horizontal[2].speed = SPEED_NORMAL;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_FAST;
            guardian_vertical[3].speed = SPEED_SLOW;
            break;
        
        case 19:
            FX::readDataArray(Level_19, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_horizontal[1].speed = SPEED_NORMAL;
            guardian_horizontal[2].speed = SPEED_SLOW;
            guardian_horizontal[3].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;
            guardian_vertical[1].speed = SPEED_NORMAL;
            guardian_vertical[2].speed = SPEED_SLOW;
            guardian_vertical[3].speed = SPEED_NORMAL;
            break;
        
        case 20:
            FX::readDataArray(Level_20, 0, 0, 512, tilemapBuffer,512);
            player.direction = RIGHT;
            guardian_horizontal[0].speed = SPEED_NORMAL;
            guardian_vertical[0].speed = SPEED_NORMAL;

            break;
            
            
        default:
            break;
    }
    
    set_willy_initial_parametes();
    set_number_of_level_keys();
    set_initial_horizontal_guardians_parameters();   
    set_initial_vertical_guardians_parameters();     
  
    game_stage = STAGE_PLAY_GAME;
}

void check_keys(){
    
    

        if (arduboy.pressed(LEFT_BUTTON)) {
            if ((!player.is_jumping) && (!player.is_falling) && (!player.is_directional_jumping) && (!player.is_directional_falling))
           {
            player.direction = LEFT;
            player.is_walking = true;
        }
        }            
                    
        if (arduboy.justReleased(LEFT_BUTTON)) {
            player.is_walking = false;        
        }  
        
   
        if (arduboy.pressed(RIGHT_BUTTON)) {
            if ((!player.is_jumping) && (!player.is_falling) && (!player.is_directional_jumping) && (!player.is_directional_falling))
            {
                player.direction = RIGHT;
                player.is_walking = true;
            }
        }
                             
        if (arduboy.justReleased(RIGHT_BUTTON)) {
            player.is_walking = false;

        }
 
        
        if (arduboy.justPressed(A_BUTTON)) {
            if ((!player.is_walking) && (!player.is_jumping) && (!player.is_falling) && (!player.is_directional_jumping) && (!player.is_directional_falling)){
                player.jump_iteration = 0;
                player.is_jumping = true;  
            }
            if ((player.is_walking) && (!player.is_jumping) && (!player.is_falling) && (!player.is_directional_jumping) && (!player.is_directional_falling))
            {
                player.jump_iteration = 0;
                player.is_walking = false;
                player.is_jumping = false;
                player.is_directional_jumping = true;

            }
            
        }
    
    if (arduboy.justPressed(UP_BUTTON)) {
        cheat_mode = !cheat_mode;
    } 
    if (arduboy.justPressed(DOWN_BUTTON)) {
        enable_audio = !enable_audio;
    }            
                
    if ((arduboy.justPressed(B_BUTTON)) && (arduboy.pressed(B_BUTTON))){
        game_stage = STAGE_GAME_TITLE;
     
          
    }
     
    
}




void setup() {
    arduboy.begin();
    arduboy.setFrameRate(FRAME_RATE);
    audio.begin();
    audio.on();  
    
    arduboy.clear();
    arduboy.setTextSize(2);
    arduboy.setCursor(35,20);
    arduboy.print("smBIT");
    arduboy.setTextSize(1);
    arduboy.setCursor(40,40);
    arduboy.print("presents");
    arduboy.display();
  
    delay(1000);
    
  FX::begin(FX_DATA_PAGE);  // initialise FX chip
  

  

}

#define TILE_FLOOR_FIRST    1
#define TILE_FLOOR_LAST     12
#define TILE_WALL_FIRST  25
#define TILE_WALL_LAST   34
#define TILE_CONVEYOR_FIRST 35
#define TILE_CONVEYOR_LAST  78
#define TILE_CRUMBING_FIRST    90
#define TILE_CRUMBING_LAST    121
#define TILE_LAST  121

#define PORTAL    150

void draw_background(){
   
   // FX::readDataArray(Level_2, 0, 0, 512, tilemapBuffer,512);
    
    for(int i=0; i<16; i++){
        for(int j=i*32; j<(i*32)+32; j++){ 
            if (((tilemapBuffer[j])  !=  0) && (tilemapBuffer[j] <= TILE_LAST)) { 
                FX::drawBitmap((j-(i*32))*8-camera.x, i*8-camera.y, tiles, tilemapBuffer[j]-1, dbmNormal);
            }
            if ((tilemapBuffer[j])  ==  PORTAL){ 
                FX::drawBitmap((j-(i*32))*8-camera.x, i*8-camera.y, portals, Current_Level-1, dbmNormal);
            }
        }
               

    }
    
}
#define CRUMBING_1      90 //crumibing_floor_1-0.png
#define CRUMBING_1_1    91 //crumibing_floor_1-1.png
#define CRUMBING_1_2    92 //crumibing_floor_1-2.png
#define CRUMBING_1_3    93 //crumibing_floor_1-3.png
#define CRUMBING_1_4    94 //crumibing_floor_1-4.png
#define CRUMBING_1_5    95 //crumibing_floor_1-5.png
#define CRUMBING_1_6    96 //crumibing_floor_1-6.png
#define CRUMBING_1_7    97 //crumibing_floor_1-7.png
#define CRUMBING_2      98 //crumibing_floor_2-0.png
#define CRUMBING_2_1    99 //crumibing_floor_2-1.png
#define CRUMBING_2_2    100 //crumibing_floor_2-2.png
#define CRUMBING_2_3    101 //crumibing_floor_2-3.png
#define CRUMBING_2_4    102 //crumibing_floor_2-4.png
#define CRUMBING_2_5    103 //crumibing_floor_2-5.png
#define CRUMBING_2_6    104 //crumibing_floor_2-6.png
#define CRUMBING_2_7    105 //crumibing_floor_2-7.png
#define CRUMBING_3      106 //crumibing_floor_3-0.png
#define CRUMBING_3_1    107 //crumibing_floor_3-1.pngF
#define CRUMBING_3_2    108 //crumibing_floor_3-2.png
#define CRUMBING_3_3    109 //crumibing_floor_3-3.png
#define CRUMBING_3_4    110 //crumibing_floor_3-4.png
#define CRUMBING_3_5    111 //crumibing_floor_3-5.png
#define CRUMBING_3_6    112 //crumibing_floor_3-6.png
#define CRUMBING_3_7    113 //crumibing_floor_3-7.png
#define CRUMBING_4      114 //crumibing_floor_4-0.png
#define CRUMBING_4_1    115 //crumibing_floor_4-1.png
#define CRUMBING_4_2    116 //crumibing_floor_4-2.png
#define CRUMBING_4_3    117 //crumibing_floor_4-3.png
#define CRUMBING_4_4    118 //crumibing_floor_4-4.png
#define CRUMBING_4_5    119 //crumibing_floor_4-5.png
#define CRUMBING_4_6    120 //crumibing_floor_4-6.png
#define CRUMBING_4_7    121 //crumibing_floor_4-7.png

void detection_crumbing_floor(){
 //Rysowanie znikajacych plytek jak player na nie nadepnie
    if (arduboy.everyXFrames(2)) {
    
        for(int row=0; row<16; row++){
            for(int col=row*32; col<(row*32)+32; col++){ 
                
                if ((tilemapBuffer[col] >= CRUMBING_1) &&  (tilemapBuffer[col] <= CRUMBING_1_7)){
                    if (arduboy.collide(Rect(player.x, player.y+16, 8, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                        tilemapBuffer[col] = tilemapBuffer[col]+1;
                        if (tilemapBuffer[col]>CRUMBING_1_6) {
                            tilemapBuffer[col] = 0;
                            player.is_falling = true;
                        }
                    }
                }
                
                if ((tilemapBuffer[col] >= CRUMBING_2) &&  (tilemapBuffer[col] <= CRUMBING_2_7)){
                    if (arduboy.collide(Rect(player.x, player.y+16, 8, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                        tilemapBuffer[col] = tilemapBuffer[col]+1;
                        if (tilemapBuffer[col]>CRUMBING_2_6) {
                            tilemapBuffer[col] = 0;
                            player.is_falling = true;
                        }
                    }
                }
                
                if ((tilemapBuffer[col] >= CRUMBING_3) &&  (tilemapBuffer[col] <= CRUMBING_3_7)){
                    if (arduboy.collide(Rect(player.x, player.y+16, 8, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                        tilemapBuffer[col] = tilemapBuffer[col]+1;
                        if (tilemapBuffer[col]>CRUMBING_3_6) {
                            tilemapBuffer[col] = 0;
                            player.is_falling = true;
                        }
                    }
                }
                
                if ((tilemapBuffer[col] >= CRUMBING_4) &&  (tilemapBuffer[col] <= CRUMBING_4_7)){
                    if (arduboy.collide(Rect(player.x, player.y+16, 8, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                        tilemapBuffer[col] = tilemapBuffer[col]+1;
                        if (tilemapBuffer[col]>CRUMBING_4_6) {
                            tilemapBuffer[col] = 0;
                            player.is_falling = true;
                        }
                    }
                }
            }
        }
    }
}




uint8_t mapBuffer[32]; // a small buffer to store one horizontal row of tiles from the tilemap

void draw_background3(){
   
    for(int i=0; i<16; i++){
        FX::readDataArray(Level_1, 0, i*32, (i*32)+32, mapBuffer,32);
        
        for(int j=0; j<32; j++){ 
            if (((j*8)-camera.x >= 0) && ((i*8)-camera.y >=0) && ((j*8)-camera.x <128) && ((i*8)-camera.y <64)){
                if ((mapBuffer[j])  !=  0){ 
               
                    FX::drawBitmap((j*8)-camera.x, (i*8) -camera.y, tiles, mapBuffer[j]-1, dbmNormal);
                }
            }
        }
          
    }
    
}

#define TILE_CONVEYOR_FIRST TILE_CONVEYOR_1_0
#define TILE_CONVEYOR_LAST  TILE_CONVEYOR_11_3
#define TILE_CONVEYOR_1_0   35  //floor_move_1-0.png    LEFT:   Level 1/6/19
#define TILE_CONVEYOR_1_3   38  //floor_move_1-3.png
#define TILE_CONVEYOR_2_0   39  //floor_move_2-0.png    RIGHT:  Level 2/4/20
#define TILE_CONVEYOR_2_3   42  //floor_move_2-3.png
#define TILE_CONVEYOR_3_0   43  //floor_move_3-0.png    LEFT:   Level 3
#define TILE_CONVEYOR_3_3   46  //floor_move_3-3.png
#define TILE_CONVEYOR_4_0   47  //floor_move_4-0.png    LEFT    Level 5
#define TILE_CONVEYOR_4_3   50  //floor_move_4-3.png
#define TILE_CONVEYOR_5_0   51  //floor_move_5-0.png    LEFT:   Level 7
#define TILE_CONVEYOR_5_3   54  //floor_move_5-3.png
#define TILE_CONVEYOR_6_0   55  //floor_move_6-0.png    LEFT: Level 14
#define TILE_CONVEYOR_6_3   58  //floor_move_6-3.png
#define TILE_CONVEYOR_7_0   59  //floor_move_7-0.png    RIGHT: Level 9/13
#define TILE_CONVEYOR_7_3   62  //floor_move_7-3.png
#define TILE_CONVEYOR_8_0   63  //floor_move_8-0.png    LEFT: Level 11/15
#define TILE_CONVEYOR_8_3   66  //floor_move_8-3.png
#define TILE_CONVEYOR_9_0   67  //floor_move_9-0.png    RIGHT: Level 8/12
#define TILE_CONVEYOR_9_3   70  //floor_move_9-3.png
#define TILE_CONVEYOR_10_0  71  //floor_move_10-0.png   LEFT: Level 16
#define TILE_CONVEYOR_10_3  74  //floor_move_10-3.png
#define TILE_CONVEYOR_11_0  75  //floor_move_11-0.png   RIGHT: Level 17
#define TILE_CONVEYOR_11_3  78  //floor_move_11-3.png


void anim_conveyor(){
    
    if (arduboy.everyXFrames(4)) {
        
        for(int row=0; row<16; row++){
            for(int col=row*32; col<(row*32)+32; col++){ 
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_1_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_1_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_1_3) {tilemapBuffer[col] = TILE_CONVEYOR_1_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_2_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_2_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_2_3) {tilemapBuffer[col] = TILE_CONVEYOR_2_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_3_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_3_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_3_3) {tilemapBuffer[col] = TILE_CONVEYOR_3_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_4_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_4_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_4_3) {tilemapBuffer[col] = TILE_CONVEYOR_4_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_5_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_5_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_5_3) {tilemapBuffer[col] = TILE_CONVEYOR_5_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_6_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_6_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_6_3) {tilemapBuffer[col] = TILE_CONVEYOR_6_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_7_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_7_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_7_3) {tilemapBuffer[col] = TILE_CONVEYOR_7_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_8_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_8_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_8_3) {tilemapBuffer[col] = TILE_CONVEYOR_8_0;}
                }
        
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_9_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_9_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_9_3) {tilemapBuffer[col] = TILE_CONVEYOR_9_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_10_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_10_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_10_3) {tilemapBuffer[col] = TILE_CONVEYOR_10_0;}
                }
                    
                if ((tilemapBuffer[col] >= TILE_CONVEYOR_11_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_11_3)){
                    tilemapBuffer[col] = tilemapBuffer[col] + 1;
                    if (tilemapBuffer[col] > TILE_CONVEYOR_11_3) {tilemapBuffer[col] = TILE_CONVEYOR_11_0;}
                }
            }
        }    
    }
}

bool player_on_automove_layer(){
    //LEFT: M1 M3 M4 M5 M6 M8 M10
    //RIGHT: M2 M7 M9 M11
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            if ((tilemapBuffer[col] >= TILE_CONVEYOR_FIRST) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_LAST)){
                if (arduboy.collide(Rect(player.x+1, player.y+16, 8, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                //CONVEYOR LEFT
                    if (((tilemapBuffer[col] >= TILE_CONVEYOR_1_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_1_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_3_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_3_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_4_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_4_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_5_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_5_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_6_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_6_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_8_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_8_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_10_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_10_3)))
                    {
                        if ((player.direction == RIGHT) && ((player.is_directional_jumping) || (player.is_walking == true))) {return false;}
                        else {player.direction = LEFT; return true;} //taki ficzer zeby mozna bylo isc i skakac pod prad  
                    }
                    //CONVEYOR RIGHT
                    if (((tilemapBuffer[col] >= TILE_CONVEYOR_2_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_2_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_7_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_7_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_9_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_9_3)) ||
                        ((tilemapBuffer[col] >= TILE_CONVEYOR_11_0) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_11_3))) 
                    {
                        if ((player.direction == LEFT) && ((player.is_directional_jumping) || (player.is_walking == true))) {return false;}
                        else {player.direction = RIGHT;  return true;}
                    }
                }
            }
        }
    }
    
    return false;
}
#define KEY_FIRST   79
#define KEY_LAST    89
void set_number_of_level_keys(){
    keys = 0;
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            for (byte i=KEY_FIRST; i<=KEY_LAST; i++){
                if (tilemapBuffer[col] == i){
                    keys = keys + 1;
                }
            }
        }
    }
}    
    
void check_if_level_completed(){
    if(keys == 0){
        for(int row=0; row<16; row++){
            for(int col=row*32; col<(row*32)+32; col++){ 
                if (tilemapBuffer[col] == PORTAL){
                    if (arduboy.collide(Rect(player.x+1, player.y, 6, 16), Rect((col-(row*32))*8, (row)*8, 16,16))){
                        sound.tone(1000,100,1200,50);
                        Current_Level = Current_Level + 1;
                        if (Current_Level > 20){Current_Level = 1;
                            game_stage = STAGE_GAME_TITLE;
                        }else{
                            prepare_level_parameters(Current_Level);
                        }
                    }
                }
            } 
        }
    }
    
}




void collect_keys(){
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            for (byte i=KEY_FIRST; i<=KEY_LAST; i++){
                if (tilemapBuffer[col] == i){
                    if (arduboy.collide(Rect(player.x+1, player.y, 6, 16), Rect((col-(row*32))*8, (row)*8, 8,8))){
                        sound.tone(1000,100,1200,50); 
                        tilemapBuffer[col] = 0;
                        keys = keys - 1;
                    }
                }
            }
        }
    }
}


#define NASTY_FIRST  13
#define NASTY_LAST   24
bool detect_nasty_collisions(){
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            for (byte i=NASTY_FIRST; i<=NASTY_LAST; i++){
                if (tilemapBuffer[col] == i){
                    if (arduboy.collide(Rect(player.x+1, player.y, 6, 16), Rect((col-(row*32))*8, (row)*8, 8,8))){
                        return true;
                        //sound.tone(800,100,400,50);
                    }
                }
            }
        }
    }
    return false;
}

#define WILLY   250
void set_willy_initial_parametes(){
    player.frame = 0;
    player.is_directional_falling = false;
    player.is_directional_jumping = false;
    player.is_jumping = false;
    player.is_falling = false;
    player.is_walking = false;
    
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            
            if (tilemapBuffer[col] == WILLY){
                player.x = (col-(row*32))*8;
                player.y = row*8;   
            }
        }
    }
    
    if ((player.x>60) && (player.x<=190)) {camera.x = player.x-60;}
    if (player.x <=60) {camera.x = 0;}
    else if (player.x > 190) {camera.x =128;}
    //camera.x = player.x-60;
    
    
    if ((player.y <= 88) && (player.y > CAMERA_Y_OFFSET)) {camera.y = player.y-CAMERA_Y_OFFSET;}
    if (player.y > 88){camera.y = 64;}
    else if (player.y <= CAMERA_Y_OFFSET){camera.y = 0;}
    
   // camera.y = player.y-40;   
    
}

void check_if_willy_is_dead(){

    if((detect_guardians_collisions()) ||
    (detect_guardians_vertical_collisions()) ||
    (detect_nasty_collisions())){
        sound.tone(800,100,400,50);
        if (!cheat_mode){prepare_level_parameters(Current_Level);}
        //set_willy_initial_parametes();    
    }
}

#define G0S      200
#define G0E      201
#define G1S      202
#define G1E      203
#define G2S      204
#define G2E      205
#define G3S      206   
#define G3E      207
#define SWORDFISH   0
#define PENGUIN     8
#define CHICKEN     16
#define SEAL        24
#define TOILET      32
#define PACMAN      40
#define KANGO       48
#define WHEEL       56
#define WAGONIK     64
#define BUNNY       72
#define VEHICLE     80
#define STWOREK     88
#define SCORPION    96
#define TWO_LEGS    104
#define SPYCHACZ    112
#define LETTER      120
#define WAGONIK2    128
void set_initial_horizontal_guardians_parameters(){

    for(byte i=0;i<4;i++){
        guardian_horizontal[i].enabled = false;
    }
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            
            if (tilemapBuffer[col] == G0S){
                guardian_horizontal[0].enabled = true;
                guardian_horizontal[0].x = (col-(row*32))*8;
                guardian_horizontal[0].start_position = (col-(row*32))*8;
                guardian_horizontal[0].y = row*8;   
            }
            if (tilemapBuffer[col] == G0E){
                guardian_horizontal[0].end_position = (col-(row*32))*8; 
            
            }
            
            if (tilemapBuffer[col] == G1S){
                guardian_horizontal[1].enabled = true;
                guardian_horizontal[1].x = (col-(row*32))*8;
                guardian_horizontal[1].start_position = (col-(row*32))*8;
                guardian_horizontal[1].y = row*8;   
            }
            if (tilemapBuffer[col] == G1E){
                guardian_horizontal[1].end_position = (col-(row*32))*8; 
            
            }
            
            if (tilemapBuffer[col] == G2S){
                guardian_horizontal[2].enabled = true;
                guardian_horizontal[2].x = (col-(row*32))*8;
                guardian_horizontal[2].start_position = (col-(row*32))*8;
                guardian_horizontal[2].y = row*8;   
            }
            if (tilemapBuffer[col] == G2E){
                guardian_horizontal[2].end_position = (col-(row*32))*8; 
            
            }
            
            if (tilemapBuffer[col] == G3S){
                guardian_horizontal[3].enabled = true;
                guardian_horizontal[3].x = (col-(row*32))*8;
                guardian_horizontal[3].start_position = (col-(row*32))*8;
                guardian_horizontal[3].y = row*8;   
            }
            if (tilemapBuffer[col] == G3E){
                guardian_horizontal[3].end_position = (col-(row*32))*8; 
            
            }
        }
    }


        
    for(byte i=0;i<4;i++){
        if (Current_Level == 1){gurdian_horizontal_type = SWORDFISH;}
        if (Current_Level == 2){gurdian_horizontal_type = PENGUIN;}
        if (Current_Level == 3){gurdian_horizontal_type = CHICKEN;}
        if (Current_Level == 4){gurdian_horizontal_type = SEAL;}
        if (Current_Level == 5){gurdian_horizontal_type = TOILET;}
        if (Current_Level == 6){gurdian_horizontal_type = PACMAN;}
        if (Current_Level == 7){gurdian_horizontal_type = KANGO;}
        if (Current_Level == 8){gurdian_horizontal_type = WHEEL;}
        if (Current_Level == 9){gurdian_horizontal_type = WAGONIK;}
        if (Current_Level == 10){gurdian_horizontal_type = BUNNY;}
        if (Current_Level == 11){gurdian_horizontal_type = VEHICLE;}
        if (Current_Level == 12){gurdian_horizontal_type = WHEEL;}
        if (Current_Level == 13){gurdian_horizontal_type = STWOREK;}
        if (Current_Level == 15){gurdian_horizontal_type = LETTER;}
        if (Current_Level == 16){gurdian_horizontal_type = SCORPION;}
        if (Current_Level == 17){gurdian_horizontal_type = TWO_LEGS;}
        if (Current_Level == 18){gurdian_horizontal_type = WAGONIK;}
        if (Current_Level == 19){gurdian_horizontal_type = SPYCHACZ;}
        if (Current_Level == 20){gurdian_horizontal_type = WAGONIK2;}
        
            if (guardian_horizontal[i].start_position < guardian_horizontal[i].end_position){
                    guardian_horizontal[i].direction = RIGHT;
                }
            if (guardian_horizontal[i].start_position > guardian_horizontal[i].end_position){
                guardian_horizontal[i].direction = LEFT;
                guardian_horizontal[i].start_position = guardian_horizontal[i].end_position;
                guardian_horizontal[i].end_position = guardian_horizontal[i].x;
            }
    }

}


#define V0S      210
#define V0E      211
#define V1S      212
#define V1E      213
#define V2S      214
#define V2E      215
#define V3S      216   
#define V3E      217
#define EUGENE      0
#define PLAMA       4
#define TELEPHONE   8
#define EYE        12
#define WIATRAK    16
#define ROBOT      20
#define SOMETHING  27
#define OCTOPUS    31
#define ROBAL      35
#define SPHERE     39
 
void set_initial_vertical_guardians_parameters(){

    for(byte i=0;i<4;i++){
        guardian_vertical[i].enabled = false;
    }
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            
            if (tilemapBuffer[col] == V0S){
                guardian_vertical[0].enabled = true;
                guardian_vertical[0].x = (col-(row*32))*8;
                guardian_vertical[0].start_position = row*8;
                guardian_vertical[0].y = row*8;   
            }
            if (tilemapBuffer[col] == V0E){
                guardian_vertical[0].end_position = row*8; 
            
            }
            
            if (tilemapBuffer[col] == V1S){
                guardian_vertical[1].enabled = true;
                guardian_vertical[1].x = (col-(row*32))*8;
                guardian_vertical[1].start_position = row*8;;
                guardian_vertical[1].y = row*8;   
            }
            if (tilemapBuffer[col] == V1E){
                guardian_vertical[1].end_position = row*8;; 
            
            }
            
            if (tilemapBuffer[col] == V2S){
                guardian_vertical[2].enabled = true;
                guardian_vertical[2].x = (col-(row*32))*8;
                guardian_vertical[2].start_position = row*8;;
                guardian_vertical[2].y = row*8;   
            }
            if (tilemapBuffer[col] == V2E){
                guardian_vertical[2].end_position = row*8;; 
            
            }
            
            if (tilemapBuffer[col] == V3S){
                guardian_vertical[3].enabled = true;
                guardian_vertical[3].x = (col-(row*32))*8;
                guardian_vertical[3].start_position = row*8;;
                guardian_vertical[3].y = row*8;   
            }
            if (tilemapBuffer[col] == V3E){
                guardian_vertical[3].end_position = row*8;; 
            
            }
        }
    }


        
    for(byte i=0;i<4;i++){

        if (Current_Level == 5){gurdian_vertical_type = EUGENE;}
        if (Current_Level == 9){gurdian_vertical_type = PLAMA;}
        if (Current_Level == 11){gurdian_vertical_type = TELEPHONE;}
        if (Current_Level == 13){gurdian_vertical_type = EYE;}
        if (Current_Level == 14){gurdian_vertical_type = WIATRAK;}
        if (Current_Level == 15){gurdian_vertical_type = ROBOT;}
        if (Current_Level == 17){gurdian_vertical_type = SOMETHING;}
        if (Current_Level == 18){gurdian_vertical_type = OCTOPUS;}
        if (Current_Level == 19){gurdian_vertical_type = SPHERE;}
        if (Current_Level == 20){gurdian_vertical_type = EYE;}

            if (guardian_vertical[i].start_position < guardian_vertical[i].end_position){
                    guardian_vertical[i].direction = DOWN;
                }
            if (guardian_vertical[i].start_position > guardian_vertical[i].end_position){
                guardian_vertical[i].direction = UP;
                guardian_vertical[i].start_position = guardian_vertical[i].end_position;
                guardian_vertical[i].end_position = guardian_vertical[i].y;
            }
    }

}


void draw_guardians_horizontal(){               
    
   // for(byte i=0;i<4;i++){
        if (arduboy.everyXFrames(PLAYER_FRAME_RATE)) { 
            guardian_frame = guardian_frame+1;
            if (guardian_frame>3) {guardian_frame=0;}
        }
            
    for(byte i=0;i<4;i++){
        if (guardian_horizontal[i].enabled){
            
            
                if( guardian_horizontal[i].direction == RIGHT){
                    
                    if (guardian_horizontal[i].speed != SPEED_FAST) {if (arduboy.everyXFrames(guardian_horizontal[i].speed)) { guardian_horizontal[i].x = guardian_horizontal[i].x + 1;}}
                    else { if (arduboy.everyXFrames(1)) { guardian_horizontal[i].x = guardian_horizontal[i].x + 2;}}
                    
                    FX::drawBitmap(guardian_horizontal[i].x - camera.x, guardian_horizontal[i].y - camera.y, guardians_h_gfx, gurdian_horizontal_type + 4 + guardian_frame, 1);
                    
                    if (guardian_horizontal[i].x > guardian_horizontal[i].end_position){
                        guardian_horizontal[i].direction = LEFT;
                    }
                }
            
            
            
                
                if( guardian_horizontal[i].direction == LEFT){
                    if(guardian_horizontal[i].speed != SPEED_FAST) {if (arduboy.everyXFrames(guardian_horizontal[i].speed)) { guardian_horizontal[i].x = guardian_horizontal[i].x - 1;}}
                    else {if (arduboy.everyXFrames(1)) { guardian_horizontal[i].x = guardian_horizontal[i].x - 2;}}
                        
                    FX::drawBitmap(guardian_horizontal[i].x - camera.x, guardian_horizontal[i].y - camera.y, guardians_h_gfx, gurdian_horizontal_type + guardian_frame, 1);
                    if (guardian_horizontal[i].x < guardian_horizontal[i].start_position){
                        guardian_horizontal[i].direction = RIGHT;
                    }
                } 
            
       }
    }
}

void draw_guardians_vertical(){               
    
   // for(byte i=0;i<4;i++){
      //  if (arduboy.everyXFrames(PLAYER_FRAME_RATE)) { 
      //      guardian_frame = guardian_frame+1;
       //     if (guardian_frame>3) {guardian_frame=0;}
      //  }
            
    for(byte i=0;i<4;i++){
        if (guardian_vertical[i].enabled){
            
            
                if( guardian_vertical[i].direction == DOWN){
                    
                    if (guardian_vertical[i].speed != SPEED_FAST) {if (arduboy.everyXFrames(guardian_vertical[i].speed)) { guardian_vertical[i].y = guardian_vertical[i].y + 1;}}
                    else { if (arduboy.everyXFrames(1)) { guardian_vertical[i].y = guardian_vertical[i].y + 2;}}
                    
                    FX::drawBitmap(guardian_vertical[i].x - camera.x, guardian_vertical[i].y - camera.y, guardians_v_gfx, gurdian_vertical_type + guardian_frame, 1);
                    
                    if (guardian_vertical[i].y > guardian_vertical[i].end_position){
                        guardian_vertical[i].direction = UP;
                    }
                }
            
            
            
                
                if( guardian_vertical[i].direction == UP){
                    if(guardian_vertical[i].speed != SPEED_FAST) {if (arduboy.everyXFrames(guardian_vertical[i].speed)) { guardian_vertical[i].y = guardian_vertical[i].y - 1;}}
                    else {if (arduboy.everyXFrames(1)) { guardian_vertical[i].y = guardian_vertical[i].y - 2;}}
                        
                    FX::drawBitmap(guardian_vertical[i].x - camera.x, guardian_vertical[i].y - camera.y, guardians_v_gfx, gurdian_vertical_type + guardian_frame, 1);
                    if (guardian_vertical[i].y < guardian_vertical[i].start_position){
                        guardian_vertical[i].direction = DOWN;
                    }
                } 
            
       }
    }
}



bool detect_guardians_collisions(){
    for(byte i=0;i<4;i++){
        if (guardian_horizontal[i].enabled){
            if (arduboy.collide(Rect(player.x+1, player.y, 6, 16), Rect(guardian_horizontal[i].x+1, guardian_horizontal[i].y+1, 6,15))){
            return true;
            //sound.tone(800,100,400,50);
            }
        }   
    }
    return false;
}

bool detect_guardians_vertical_collisions(){
    for(byte i=0;i<4;i++){
        if (guardian_vertical[i].enabled){
            if (arduboy.collide(Rect(player.x+1, player.y, 6, 16), Rect(guardian_vertical[i].x+1, guardian_vertical[i].y+1, 6,15))){
                return true;
            //sound.tone(800,100,400,50);
        }
        }   
    }
    return false;
}



bool player_collisions(){
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            for (byte i=TILE_WALL_FIRST; i<TILE_WALL_LAST+1; i++){
                if (tilemapBuffer[col] == i){
                                 //if ((!player.is_directional_jumping) && (!player.is_jumping)){
                    if(player.is_walking){
                        if (player.direction == RIGHT){
                            if (arduboy.collide(Rect(player.x+2, player.y, 8, 16), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(100,100);
                                return true;
                            }
                        }
                        if (player.direction == LEFT){
                            if (arduboy.collide(Rect(player.x, player.y, 2, 16), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(200,100);
                                return true;
                            }
                        }
                    }
                    
                    if ((player.is_directional_jumping) || (player.is_directional_falling)){
                        if (player.direction == RIGHT){
                            if (arduboy.collide(Rect(player.x+10, player.y-1, 4, 8), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(300,100);
                                return true;
                            }
                        }
                        if (player.direction == LEFT){
                            if (arduboy.collide(Rect(player.x, player.y-2, 2, 10), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(400,100);
                                return true;
                            }
                        }
                    }
                    
                    if ((player.is_jumping) || (player.is_falling)){
                        if (player.direction == RIGHT){
                            if (arduboy.collide(Rect(player.x, player.y-1, 8, 10), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(700,100);
                                return true;
                            }
                        }
                        if (player.direction == LEFT){
                            if (arduboy.collide(Rect(player.x+2, player.y, 6, 8), Rect((col-(row*32))*8, (row)*8, 8,8))){
                                sound.tone(700,100);
                                return true;
                            }
                        }
                    }   
                }
            }
        }
    }
            
           
    
    return false;
    }




bool solid_below(){
    
    for(int row=0; row<16; row++){
        for(int col=row*32; col<(row*32)+32; col++){ 
            if (((tilemapBuffer[col] >= TILE_FLOOR_FIRST) &&  (tilemapBuffer[col] <= TILE_FLOOR_LAST))
                || ((tilemapBuffer[col] >= TILE_WALL_FIRST) &&  (tilemapBuffer[col] <= TILE_WALL_LAST))
                || ((tilemapBuffer[col] >= TILE_CONVEYOR_FIRST) &&  (tilemapBuffer[col] <= TILE_CONVEYOR_LAST))
                || ((tilemapBuffer[col] >= TILE_CRUMBING_FIRST) &&  (tilemapBuffer[col] <= TILE_CRUMBING_LAST)) )
            {
                if (arduboy.collide(Rect(player.x, player.y+16, 10, 1), Rect((col-(row*32))*8, (row)*8, 8,1))){
                    return true;
                }
            }
        }
    }
    return false;   
}

void player_movement(){
    
    if ((player_on_automove_layer() && (!player_collisions()) && (solid_below()))){
        player.is_walking = true;
     }
     
     if ((player_on_automove_layer() && (!player_collisions()) && (!solid_below()))){
        player.is_walking = false;
        player.is_falling = true;
     }
    
    
    if (arduboy.everyXFrames(PLAYER_FRAME_RATE)) {
        if((player.is_walking) || (player.is_directional_jumping) || (player.is_directional_falling)){
            player.frame = player.frame+1;
            if (player.frame>3) {player.frame=0;}
        }
    }
    
    if ((player.is_walking) && (solid_below()) && (!player_collisions())){
        
           // player.sprite = player.direction;
            if (player.direction == RIGHT) {
                if (arduboy.everyXFrames(PLAYER_SPEED)) { 
                    if ((player.x < 256)) {player.x = player.x + 1;
                    if ((player.x>60) && (player.x<=190)) {camera.x = camera.x + 1;}}
                    
                    
                }

            }
            if (player.direction == LEFT){
                if (arduboy.everyXFrames(PLAYER_SPEED)){ 
                    if (player.x > 0) {player.x = player.x - 1; 
                    if ((player.x>=60) && (player.x<190)) {camera.x = camera.x - 1;}}
                }
                
            }
    } 

    if ((player.is_walking) && (!player.is_jumping) && (!player.is_falling) && (!player.is_directional_jumping) && (!player.is_directional_falling) && (!player_on_automove_layer())){
        player.is_falling = true;
   }

  if (player.is_directional_jumping) {
         player.is_walking = false;
         if ((player.jump_iteration < JUMP_ITERATIONS) && (!player_collisions())){       
            if ((arduboy.everyXFrames(PLAYER_SPEED))) { 
               if ((player.y <= 88) && (player.y > CAMERA_Y_OFFSET)) {camera.y = camera.y - 1;}
                player.y = player.y - 1;
                player.jump_iteration++;
            }
        
        
             if (arduboy.everyXFrames(PLAYER_SPEED)) { 
                if((player.direction == RIGHT)){
                    if ((player.x < 256 - 18)) {player.x = player.x + 1;}
                    if ((player.x>60) && (player.x<190)) {camera.x = camera.x + 1;}
                } else if (player.direction == LEFT){
                    if ((player.x > 8)) {player.x = player.x - 1; }
                    if ((player.x>60) && (player.x<190)) {camera.x = camera.x - 1;}
                }
            }
            
        }else {

            player.jump_iteration = 0;
            player.is_directional_falling = true;
            player.is_directional_jumping = false; 
            
        }
    }  
    
    if (player.is_directional_falling){
        player.is_walking = false;
        if ((player.jump_iteration < JUMP_ITERATIONS) && (!solid_below()) && (!player_collisions())) {               
            
            if (arduboy.everyXFrames(PLAYER_SPEED)) {
                if ((player.y <= 88) && (player.y > CAMERA_Y_OFFSET)){camera.y = camera.y + 1;}
                player.y = player.y + 1;
                player.jump_iteration++;
            }
            if (arduboy.everyXFrames(PLAYER_SPEED)) {
                if ((player.direction == RIGHT)){
                    
                    if ((player.x < 256 - 18)) {player.x = player.x + 1;}
                    if ((player.x>60) && (player.x<190)) {camera.x = camera.x + 1;}
               
               
                } else if (player.direction == LEFT){
                    if ((player.x > 8)) {player.x = player.x - 1; }
                    if ((player.x>60) && (player.x<190)) {camera.x = camera.x - 1;}
                }
       
                
            //    player.frame = player.frame+1;
             //   if (player.frame>3) {player.frame=0;}
            }
        }
        else {
            player.jump_iteration = 0;
            player.is_directional_falling = false;
            player.is_falling = true;
        }
    }
   
    
    if (player.is_jumping){
        player.is_walking = false;
        if ((player.jump_iteration < JUMP_ITERATIONS) && (!player_collisions())) {
            if (arduboy.everyXFrames(PLAYER_SPEED)) { 
                if ((player.y < 90) && (player.y > CAMERA_Y_OFFSET)){camera.y = camera.y - 1;}
                player.y = player.y - 1;
                player.jump_iteration++;
            }
        }else {
            player.is_falling = true;
            player.is_jumping = false; 
            
            }
    }
    
   if (player.is_falling){
        if (!solid_below()) {
            if (arduboy.everyXFrames(PLAYER_SPEED)) {
                if ((player.y < 89) && (player.y > CAMERA_Y_OFFSET)){camera.y = camera.y + 1;}
                player.y = player.y + 1;
                player.is_walking = false;

            }
        } else {
            player.is_falling = false;
        }
    }
}

void loop() {
    
    if(game_stage == STAGE_GAME_TITLE){
        title_screen();
    } else if (game_stage == STAGE_LEVEL_COMPLETED){
    } else if (game_stage == STAGE_PLAY_GAME){
    
  if (!arduboy.nextFrame()) return;

        arduboy.clear();
        arduboy.pollButtons();
        
        
 
        if (cheat_mode){
            tinyfont.setCursor(123, 0);
            tinyfont.print("C");
        }
  
        
        
        draw_background();
        detection_crumbing_floor();
        anim_conveyor();
        collect_keys();
        check_keys();

        draw_guardians_horizontal();
        draw_guardians_vertical();

        check_if_willy_is_dead();
        check_if_level_completed();
        player_movement();
 
    if (player.direction == RIGHT){ FX::drawBitmap(player.x - camera.x, player.y - camera.y, player_gfx, player.frame, 1);}
    if (player.direction == LEFT){FX::drawBitmap(player.x - camera.x, player.y - camera.y, player_gfx, player.frame+4, 1);}
    
    
    arduboy.display();
    FX::display(CLEAR_BUFFER); 
}
}
