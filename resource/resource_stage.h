#ifndef RESOURCE_STAGE_H
#define RESOURCE_STAGE_H

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "./../general_settings.h"
#include "./../errcode.h"

/* *** Old stage object *** */
/* Game difficulty */
extern const unsigned int NUMBER_LEVEL;
extern const unsigned int DIFFICULTY_DEFAULT;
extern const unsigned int DIFFICULTY_SPEED_MAP[];

/* Controller(Keyboard) */
enum KEY_OPERATION_ID {
    KEY_OPERATION_ID_LEFT,
    KEY_OPERATION_ID_RIGHT,
    KEY_OPERATION_ID_SHOOT
};
enum KEY_OPERATION_STATUS {
    KEY_OPERATION_STATUS_RELEASE,
    KEY_OPERATION_STATUS_HOLD
};

/* Enemy */
extern const unsigned int ENEMY_NUMBER;
extern const unsigned int ENEMY_SIZE_X;
extern const unsigned int ENEMY_SIZE_Y;
extern const unsigned int ENEMY_POSITION_BOUNDARY_LEFT;
extern const unsigned int ENEMY_POSITION_BOUNDARY_TOP;
extern const unsigned int ENEMY_DRAW_OFFSET_X;
extern const unsigned int ENEMY_DRAW_OFFSET_Y;
extern const unsigned int ENEMY_DISTANCE_X;
extern const unsigned int ENEMY_TURN_STEPS;
extern const unsigned int ENEMY_LEAVE_POSITION_Y;
extern const unsigned int ENEMY_MOVE_HORIZONTAL_DISTANCE;
extern const unsigned int ENEMY_MOVE_DOWN_DISTANCE;

enum ENEMY_STATUS {
    ENEMY_STATUS_ALIVE,
    ENEMY_STATUS_CRASHED,
    ENEMY_STATUS_LEFT
};
enum ENEMY_DIRECTION {
    ENEMY_DIRECTION_LEFT,
    ENEMY_DIRECTION_RIGHT
};

/* Player/Pilot */
extern const unsigned int PILOT_SIZE_X;
extern const unsigned int PILOT_SIZE_Y;
extern const unsigned int PILOT_DRAW_OFFSET_X;
extern const unsigned int PILOT_DRAW_OFFSET_Y;
extern const unsigned int PLAYER_POSITION_BOUNDARY_LEFT;
extern const unsigned int PLAYER_POSITION_BOUNDARY_RIGHT;
extern const unsigned int PLAYER_INIT_POSITION;
extern const unsigned int PLAYER_POSITION_Y;
extern const unsigned int PLAYER_DRAW_POSITION_Y;
extern const unsigned int PLAYER_SPEED;
extern const unsigned short PLAYER_MOVE_FRAME_COUNT;
extern const unsigned short PLAYER_SHOOT_FRAME_COUNT;

enum PLAYER_STATUS {
    PLAYER_STATUS_ALIVE,
    PLAYER_STATUS_CRASHED
};
enum PLAYER_DIRECTION {
    PLAYER_DIRECTION_LEFT,
    PLAYER_DIRECTION_RIGHT,
    PLAYER_DIRECTION_STILL
};
enum PLAYER_SHOOT_SIGNAL { // Whether player trigger shoot button
    PLAYER_SHOOT_SIGNAL_ON,
    PLAYER_SHOOT_SIGNAL_OFF
};

/* Player Shoot */
extern const unsigned short NUMBER_SHOOT; // Max number of shoots
extern const unsigned int SHOOT_SIZE_X;
extern const unsigned int SHOOT_SIZE_Y;
extern const unsigned int SHOOT_DRAW_OFFSET_X;
extern const unsigned int SHOOT_DRAW_OFFSET_Y; // Top of the graph should align with position
extern const unsigned int SHOOT_SPEED;
extern const int SHOOT_Y_BOUNDARY; // At which position will it leave

enum SHOOT_STATUS {
    SHOOT_STATUS_ACTIVATED,
    SHOOT_STATUS_HOLD
};

/* Enemy attack */
extern const unsigned short NUMBER_ATTACK; // Max number of attacks
extern const unsigned int ATTACK_SIZE_X;
extern const unsigned int ATTACK_SIZE_Y;
extern const unsigned int ATTACK_DRAW_OFFSET_X;
extern const unsigned int ATTACK_DRAW_OFFSET_Y; // Bottom of the image should aligh position
extern const unsigned int ATTACK_SPEED;
extern const int ATTACK_Y_BOUNDARY;
extern const unsigned int FRAME_ATTACK_PERIOD; // How many frames should pass before the next attack generated
enum ATTACK_STATUS {
    ATTACK_STATUS_ACTIVATED,
    ATTACK_STATUS_HOLD
};

/* Visual/Audio Resource */
extern const unsigned int NUMBER_RESOURCE_IMAGE;
extern const unsigned int NUMBER_RESOURCE_SOUND;
extern const char *IMAGE_RESOURCE_PATH[];
enum IMAGE_RESOURCE_ID {
    IMAGE_RESOURCE_ID_PILOT,
    IMAGE_RESOURCE_ID_ENEMY,
    IMAGE_RESOURCE_ID_ENEMY_ATTACK,
    IMAGE_RESOURCE_ID_PILOT_SHOOT
};
extern const char *SOUND_RESOURCE_PATH[];
enum SOUND_RESOURCE_ID {
    SOUND_RESOURCE_ID_EXPLOSION,
    SOUND_RESOURCE_ID_LASER
};

enum GAME_STATUS {
    GAME_STATUS_PLAYING
};

/* Type Definition for Structs */
typedef struct enemy_obj enemy;
typedef struct stage_obj stage;
typedef struct player_obj player;
typedef struct shoot_obj shoot;
typedef struct resource_obj resource;
typedef struct attack_obj attack;

/* Structures */
struct enemy_obj {
    unsigned short status;
    // Allow position to be nagative
    int pos_x;
    int pos_y;
    unsigned short speed;
    // Control how often does enemy move
    unsigned short move_flip;
    unsigned short move_counter;
    /*
     * when move:
     *   if [turn_step_counter == turn_step_count]
     *     move down
     *     turn_step_counter = 0
     *     direction = direction==left ? right : left
     *   else
     *     move(direction)
     *     turn_step_counter ++
     */
    unsigned short direction;
    unsigned short turn_step_count;
    unsigned short turn_step_counter;
};

struct player_obj {
    unsigned short life;
    unsigned short status;
    unsigned int position;
    unsigned short shoot_signal;
    unsigned short shoot_counter;
    unsigned int direction;
};

struct shoot_obj {
    unsigned short shoot_status;
    int pos_x;
    int pos_y;
};

struct attack_obj {
    unsigned short attack_status;
    int pos_x;
    int pos_y;
};

struct stage_obj {
    unsigned short game_status;
    unsigned long score;
    enemy **list_enemy;
    shoot **list_shoot;
    attack **list_attack;
    unsigned int difficulty;
    resource *game_resource;
    player *game_player;
    ALLEGRO_DISPLAY *screen;
    time_t random_seed;
    unsigned short key_operation[3];
    unsigned attack_counter;
};

struct resource_obj {
    ALLEGRO_BITMAP **resource_images;
    ALLEGRO_SAMPLE **resource_sounds;
    ALLEGRO_AUDIO_STREAM **resource_music;
};

void draw_screen(stage *s);
void handle_enemy_shoot_collisions(enemy **e, shoot **sl, stage *sg);

/* Stage */
stage *create_stage(int *err);
void free_stage(stage *s);

/* Resouce */
resource *create_resource(int *err);
void free_resource(resource *r);

/* Enemies */
enemy **create_enemies(stage *s);
enemy *init_enemy(unsigned int x, unsigned int y, unsigned int d);
void reset_enemies(enemy **arr_e, stage *s);
void reset_enemy(enemy *e, unsigned int x, unsigned int y, unsigned int d);
void move_enemies(enemy **es, stage *s);
void move_enemy(enemy *e);
void draw_enemies(enemy **es, stage *s);
void draw_enemy(enemy *e, stage *s);
void free_enemies(enemy **e_arr);
void free_enemy(enemy *e);

/* Enemy speed */
unsigned int stage_get_enemy_init_speed(stage *s);
unsigned int get_move_flip_by_difficulty(unsigned int d);

/* Enemy Attacks */
attack **create_attacks();
attack *create_attack();
void free_attacks(attack **al);
void free_attack(attack *a);
void draw_attacks(attack **al, stage *s);
void draw_attack(attack *a, stage *s);
void move_attacks(attack **al, stage *s);
void move_attack(attack *a, stage *s);
int try_emit_attack(enemy **e, attack **al);
int trigger_attack(attack *a, int pos_x, int pos_y);
void generate_attack(enemy **el, attack **al, stage *s);

/* Player/Pilot */
player *create_player();
void draw_player(player *p, stage *s);
void move_player(player *p, stage *s);
void free_player(player *p);

/* Player Shoots */
shoot **create_shoots();
shoot *create_shoot();
void free_shoots(shoot **sl);
void free_shoot(shoot *s);
void draw_shoots(shoot **sl, stage *sg);
void draw_shoot(shoot *s, stage *sg);
void move_shoots(shoot **sl, stage *sg);
void move_shoot(shoot *s, stage *sg);
int player_try_emit_shoot(player *p, shoot **sl);
int trigger_shoot(shoot *s, unsigned int pos_x, unsigned int pos_y);


typedef struct resource_gameplay_str {
    stage *sg;
} gameplay_resr;

gameplay_resr *create_gameplay_resr(int *err);
void destroy_gameplay_resr(gameplay_resr *p);


/* *** Macros for using genetic type. ***
 *
 * NOTE: Should include resource.h beforehand!
 */

/* Simple cast */
#define GP_RESR_PTR_CAST(p) ((gameplay_resr *)p)
/* Access from generic type */
#define GP_RS(s) ((s)->gameplay_resr)

#endif