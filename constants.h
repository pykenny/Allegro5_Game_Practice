/* Notes:
 * [2019/05/25]
 *   Not used (they're all roughly included to resource.h) but
 *   kept for further usage.
 */

#ifndef __CONSTANTS_H
#define __CONSTANTS_H

/* Timer Flip */
const double FPS = 60.0;

/* Screen size */
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

/* Game difficulty */
const unsigned int NUMBER_LEVEL = 9;
const unsigned int DIFFICULTY_DEFAULT = 120;
const unsigned int DIFFICULTY_SPEED_MAP [NUMBER_LEVEL] =
        {120 ,110, 100, 90, 75, 60, 45, 30, 20};

/* Controller(Keyboard) */
enum KEY_OPERATION_ID {
    KEY_OPERATION_ID_LEFT = 0,
    KEY_OPERATION_ID_RIGHT,
    KEY_OPERATION_ID_SHOOT
};
enum KEY_OPERATION_STATUS {
    KEY_OPERATION_STATUS_RELEASE = 0,
    KEY_OPERATION_STATUS_HOLD
};

/* Enemy */
const unsigned int ENEMY_NUMBER = 7;
const unsigned int ENEMY_SIZE_X = 32;
const unsigned int ENEMY_SIZE_Y = 32;
const unsigned int ENEMY_POSITION_BOUNDARY_LEFT = ENEMY_SIZE_X / 2;
const unsigned int ENEMY_POSITION_BOUNDARY_TOP = ENEMY_SIZE_Y / 2;
const unsigned int ENEMY_DRAW_OFFSET_X = ENEMY_SIZE_X / 2;
const unsigned int ENEMY_DRAW_OFFSET_Y = ENEMY_SIZE_Y / 2;
const unsigned int ENEMY_DISTANCE_X = ENEMY_SIZE_X/2; // Horizontal gap between enemies
const unsigned int ENEMY_TURN_STEPS = 10; // How many steps required before turn direction
const unsigned int ENEMY_LEAVE_POSITION_Y = 448; // At which position will it leave
const unsigned int ENEMY_MOVE_HORIZONTAL_DISTANCE = 32;
const unsigned int ENEMY_MOVE_DOWN_DISTANCE = 32;

enum ENEMY_STATUS {
    ENEMY_STATUS_ALIVE = 0,
    ENEMY_STATUS_CRASHED,
    ENEMY_STATUS_LEFT
};
enum ENEMY_DIRECTION {
    ENEMY_DIRECTION_LEFT = 0,
    ENEMY_DIRECTION_RIGHT
};

/* Player/Pilot */
const unsigned int PILOT_SIZE_X = 56;
const unsigned int PILOT_SIZE_Y = 32;
const unsigned int PILOT_DRAW_OFFSET_X = PILOT_SIZE_X/2;
const unsigned int PILOT_DRAW_OFFSET_Y = PILOT_SIZE_Y/2;
const unsigned int PLAYER_POSITION_BOUNDARY_LEFT = PILOT_SIZE_X / 2;
const unsigned int PLAYER_POSITION_BOUNDARY_RIGHT = SCREEN_WIDTH - (PILOT_SIZE_X / 2);
const unsigned int PLAYER_INIT_POSITION = 320;
const unsigned int PLAYER_POSITION_Y = SCREEN_HEIGHT - (PILOT_SIZE_Y/2);
const unsigned int PLAYER_DRAW_POSITION_Y = PLAYER_POSITION_Y - (PILOT_DRAW_OFFSET_Y);
const unsigned int PLAYER_SPEED = 4;
const unsigned short PLAYER_MOVE_FRAME_COUNT = 10; // Preserved for additional animation
const unsigned short PLAYER_SHOOT_FRAME_COUNT = 15; // Frames to wait before next shot

enum PLAYER_STATUS {
    PLAYER_STATUS_ALIVE = 0,
    PLAYER_STATUS_CRASHED
};
enum PLAYER_DIRECTION {
    PLAYER_DIRECTION_LEFT = 0,
    PLAYER_DIRECTION_RIGHT,
    PLAYER_DIRECTION_STILL
};
enum PLAYER_SHOOT_SIGNAL { // Whether player trigger shoot button
    PLAYER_SHOOT_SIGNAL_ON = 0,
    PLAYER_SHOOT_SIGNAL_OFF
};

/* Player Shoot */
const unsigned short NUMBER_SHOOT = 5; // Max number of shoots
const unsigned int SHOOT_SIZE_X = 24;
const unsigned int SHOOT_SIZE_Y = 32;
const unsigned int SHOOT_DRAW_OFFSET_X = SHOOT_SIZE_X/2;
const unsigned int SHOOT_DRAW_OFFSET_Y = 0; // Top of the graph should align with position
const unsigned int SHOOT_SPEED = 6;
const int SHOOT_Y_BOUNDARY = 0; // At which position will it leave

enum SHOOT_STATUS {
    SHOOT_STATUS_ACTIVATED = 0,
    SHOOT_STATUS_HOLD
};

/* Enemy attack */
const unsigned short NUMBER_ATTACK = 6; // Max number of attacks
const unsigned int ATTACK_SIZE_X = 24;
const unsigned int ATTACK_SIZE_Y = 32;
const unsigned int ATTACK_DRAW_OFFSET_X = ATTACK_SIZE_X/2;
const unsigned int ATTACK_DRAW_OFFSET_Y = ATTACK_SIZE_Y; // Bottom of the image should aligh position
const unsigned int ATTACK_SPEED = 3;
const int ATTACK_Y_BOUNDARY = SCREEN_HEIGHT;
const unsigned int FRAME_ATTACK_PERIOD = 30; // How many frames should pass before the next attack generated
enum ATTACK_STATUS {
    ATTACK_STATUS_ACTIVATED = 0,
    ATTACK_STATUS_HOLD
};

/* Visual/Audio Resource */
#define RESSIZE_IMG 4
#define RESSIZE_SFX 2

const unsigned int NUMBER_RESOURCE_IMAGE = 4;
const unsigned int NUMBER_RESOURCE_SOUND = 2;

const char *IMAGE_RESOURCE_PATH[RESSIZE_IMG] = {
        "./img/pilot.png",
        "./img/enemy.png",
        "./img/attack.png",
        "./img/shoot.png"
};
enum IMAGE_RESOURCE_ID {
    IMAGE_RESOURCE_ID_PILOT = 0,
    IMAGE_RESOURCE_ID_ENEMY,
    IMAGE_RESOURCE_ID_ENEMY_ATTACK,
    IMAGE_RESOURCE_ID_PILOT_SHOOT
};
const char *SOUND_RESOURCE_PATH[RESSIZE_SFX] = {
        "./sfx/Explosion.wav",
        "./sfx/Laser_Shoot.wav"
};
enum SOUND_RESOURCE_ID {
    SOUND_RESOURCE_ID_EXPLOSION = 0,
    SOUND_RESOURCE_ID_LASER
};

enum GAME_STATUS {
    GAME_STATUS_PLAYING = 0
};

#endif
