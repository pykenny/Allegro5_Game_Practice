#include "./resource_stage.h"

const unsigned int NUMBER_LEVEL = 9;
const unsigned int DIFFICULTY_DEFAULT = 120;
const unsigned int DIFFICULTY_SPEED_MAP [] =
        {120 ,110, 100, 90, 75, 60, 45, 30, 20};

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

/* Player Shoot */
const unsigned short NUMBER_SHOOT = 5; // Max number of shoots
const unsigned int SHOOT_SIZE_X = 24;
const unsigned int SHOOT_SIZE_Y = 32;
const unsigned int SHOOT_DRAW_OFFSET_X = SHOOT_SIZE_X/2;
const unsigned int SHOOT_DRAW_OFFSET_Y = 0; // Top of the graph should align with position
const unsigned int SHOOT_SPEED = 6;
const int SHOOT_Y_BOUNDARY = 0; // At which position will it leave


/* Enemy attack */
const unsigned short NUMBER_ATTACK = 6; // Max number of attacks
const unsigned int ATTACK_SIZE_X = 24;
const unsigned int ATTACK_SIZE_Y = 32;
const unsigned int ATTACK_DRAW_OFFSET_X = ATTACK_SIZE_X/2;
const unsigned int ATTACK_DRAW_OFFSET_Y = ATTACK_SIZE_Y; // Bottom of the image should aligh position
const unsigned int ATTACK_SPEED = 3;
const int ATTACK_Y_BOUNDARY = SCREEN_HEIGHT;
const unsigned int FRAME_ATTACK_PERIOD = 30; // How many frames should pass before the next attack generated

/* Visual/Audio Resource */
const unsigned int NUMBER_RESOURCE_IMAGE = 4;
const unsigned int NUMBER_RESOURCE_SOUND = 2;
const char *IMAGE_RESOURCE_PATH[] = {
        "resource/img/pilot.png",
        "resource/img/enemy.png",
        "resource/img/attack.png",
        "resource/img/shoot.png"
};

const char *SOUND_RESOURCE_PATH[] = {
        "resource/sfx/Explosion.wav",
        "resource/sfx/Laser_Shoot.wav"
};

/* Game Engine/Routines */
int routine_play(ALLEGRO_DISPLAY *d);
// int engine_run();
// 

// void handle_enemy_shoot_collisions(enemy **e, shoot **sl, stage *sg);


/* Stage control */
unsigned int stage_get_enemy_init_speed(stage *s){
    return s->difficulty;
}


/* Enemies */
enemy **create_enemies(stage *s) {
    int i;

    enemy **arr_e = malloc(sizeof(enemy*) * ENEMY_NUMBER);
    for (i = 0; i < ENEMY_NUMBER; i++) {
        arr_e[i] = init_enemy(ENEMY_POSITION_BOUNDARY_LEFT + i * (ENEMY_SIZE_X + ENEMY_DISTANCE_X),
                              ENEMY_POSITION_BOUNDARY_TOP,
                              s->difficulty);
    }
    return arr_e;
}

enemy *init_enemy(unsigned int x, unsigned int y, unsigned int d){
    enemy *e = malloc(sizeof(enemy));
    e->status = ENEMY_STATUS_ALIVE;
    e->pos_x = x;
    e->pos_y = y;
    e->move_counter = 0;
    e->move_flip = get_move_flip_by_difficulty(d);
    e->direction = ENEMY_DIRECTION_RIGHT;
    e->turn_step_count = ENEMY_TURN_STEPS;
    e->turn_step_counter = 0;
    return e;
}

void reset_enemies(enemy **arr_e, stage *s) {
    int i;
    int base_x = 20;
    int base_y = 20;
    for (i = 0; i < ENEMY_NUMBER; i++) {
        reset_enemy(arr_e[i],
                    ENEMY_POSITION_BOUNDARY_LEFT + i * (ENEMY_SIZE_X + ENEMY_DISTANCE_X),
                    ENEMY_POSITION_BOUNDARY_TOP,
                    s->difficulty);
    }
}


void reset_enemy(enemy *e, unsigned int x, unsigned int y, unsigned int d){
    if (e != NULL) {
        e->status = ENEMY_STATUS_ALIVE;
        e->pos_x = x;
        e->pos_y = y;
        e->move_counter = 0;
        e->move_flip = get_move_flip_by_difficulty(d);
        e->direction = ENEMY_DIRECTION_RIGHT;
        e->turn_step_count = 10;
        e->turn_step_counter = 0;
    }
}

void free_enemies(enemy **e_arr) {
    int i = 0;
    if (e_arr != NULL) {
        for (i = 0; i < ENEMY_NUMBER; i++) {
            free_enemy(e_arr[i]);
        }
        free(e_arr);
    }
}

void free_enemy(enemy *e) {
    if (e != NULL) {
        free(e);
    }
}

void draw_enemies(enemy **es, stage *s) {
    int i;
    for (i = 0; i < ENEMY_NUMBER; i++) {
        draw_enemy(es[i], s);
    }
}

void draw_enemy(enemy *e, stage *s) {
    float f_posx = (float)e->pos_x;
    float f_posy = (float)e->pos_y;

    // If enemy is alive, draw it!
    if(e->status == ENEMY_STATUS_ALIVE) {
        al_draw_bitmap(
                s->game_resource->resource_images[IMAGE_RESOURCE_ID_ENEMY],
                f_posx - ENEMY_DRAW_OFFSET_X,
                f_posy - ENEMY_DRAW_OFFSET_Y,
                0);
    }
}

void move_enemies(enemy **es, stage *s) {
    int i;
    int active_enemy = 0;
    for (i = 0; i < ENEMY_NUMBER; i++) {
        if (es[i]->status == ENEMY_STATUS_ALIVE) {
            active_enemy = 1;
            break;
        }
    }
    // If all enemies left or crashed, reset them all
    if (active_enemy == 0) {
        reset_enemies(es, s);
    } else {
        for (i = 0; i < ENEMY_NUMBER; i++) {
            move_enemy(es[i]);
        }
    }
}

void move_enemy(enemy *e) {
    // Move when counter reach [move_flip]
    if (e->move_counter == e->move_flip) {
        // The enemy move in S-shaped route
        // Once enemy move [turn_step_count] horizontally,
        // It will move down in this step, and change its direction from the next step
        if (e->turn_step_counter == e->turn_step_count) {
            // Move down
            e->pos_y += ENEMY_MOVE_DOWN_DISTANCE;
            if (e->pos_y > ENEMY_LEAVE_POSITION_Y) {
                e->status = ENEMY_STATUS_LEFT;
            }
            else {
                // Flip direction
                if (e->direction == ENEMY_DIRECTION_LEFT) {
                    e->direction = ENEMY_DIRECTION_RIGHT;
                } else {
                    e->direction = ENEMY_DIRECTION_LEFT;
                }
            }
            e->turn_step_counter = 0;
        }
        else {
            if (e->direction == ENEMY_DIRECTION_LEFT) {
                e->pos_x -= ENEMY_MOVE_HORIZONTAL_DISTANCE;
            }
            else {
                e->pos_x += ENEMY_MOVE_HORIZONTAL_DISTANCE;
            }
            e->turn_step_counter += 1;
        }
        e->move_counter = 0;
    }
    else {
        e->move_counter += 1;
    }
}

/* Player Shoot */
shoot **create_shoots() {
    int i;
    shoot **sl = malloc(sizeof(shoot*) * NUMBER_SHOOT);
    for (i = 0; i < NUMBER_SHOOT; i++) {
        sl[i] = create_shoot();
    }
    return sl;
}

shoot *create_shoot() {
    shoot *s = malloc(sizeof(shoot));
    s->pos_x = 0;
    s->pos_y = 0;
    s->shoot_status = SHOOT_STATUS_HOLD;
    return s;
}

void free_shoots(shoot **sl) {
    int i;
    if(sl != NULL) {
        for (i = 0; i < NUMBER_SHOOT; i++) {
            free_shoot(sl[i]);
        }
        free(sl);
    }
}
void free_shoot(shoot *s) {
    free(s);
}

void draw_shoots(shoot **sl, stage *sg) {
    int i;
    for (i = 0; i < NUMBER_SHOOT; i++) {
        draw_shoot(sl[i], sg);
    }
}
void draw_shoot(shoot *s, stage *sg) {
    if (s->shoot_status == SHOOT_STATUS_ACTIVATED) {
        al_draw_bitmap(sg->game_resource->resource_images[IMAGE_RESOURCE_ID_PILOT_SHOOT],
                       s->pos_x - SHOOT_DRAW_OFFSET_X,
                       s->pos_y - SHOOT_DRAW_OFFSET_Y,
                       0
        );
    }
}

void move_shoots(shoot **sl, stage *sg) {
    int i;
    if (sl != NULL) {
        for (i = 0; i < NUMBER_SHOOT; i++) {
            move_shoot(sl[i], sg);
        }
    }
}

void move_shoot(shoot *s, stage *sg) {
    if (s->shoot_status == SHOOT_STATUS_ACTIVATED) {
        s->pos_y -= SHOOT_SPEED;
        if (s->pos_y <= SHOOT_Y_BOUNDARY) {
            s->shoot_status = SHOOT_STATUS_HOLD;
        }
    }
}

int player_try_emit_shoot(player *p, shoot **sl) {
    int i;
    for (i = 0; i < NUMBER_SHOOT; i++) {
        if (trigger_shoot(sl[i], p->position, PLAYER_POSITION_Y) >= 0) {
            return 1;
        }
    }
    return -1;
}

int trigger_shoot(shoot *s, unsigned int pos_x, unsigned int pos_y) {
    if (s->shoot_status == SHOOT_STATUS_HOLD) {
        s->shoot_status = SHOOT_STATUS_ACTIVATED;
        s->pos_x = pos_x;
        s->pos_y = pos_y;
        return 1;
    }
    else {
        return -1;
    }
}

/* Enemy attacks */
attack **create_attacks() {
    int i;
    attack **al = malloc(sizeof(attack*) * NUMBER_ATTACK);
    for (i = 0; i < NUMBER_ATTACK; i++) {
        al[i] = create_attack();
    }
    return al;
}

attack *create_attack(){
    attack *a = malloc(sizeof(attack));
    a->pos_x = 0;
    a->pos_y = 0;
    a->attack_status = ATTACK_STATUS_HOLD;
    return a;
}

void free_attacks(attack **al) {
    int i;
    if(al != NULL) {
        for (i = 0; i < NUMBER_ATTACK; i++) {
            free_attack(al[i]);
        }
        free(al);
    }
}

void free_attack(attack *a) {
    free(a);
}

void draw_attacks(attack **al, stage *s) {
    int i;
    for (i = 0; i < NUMBER_ATTACK; i++) {
        draw_attack(al[i], s);
    }
}

void draw_attack(attack *a, stage *s) {
    if(a->attack_status == ATTACK_STATUS_ACTIVATED) {
        al_draw_bitmap(s->game_resource->resource_images[IMAGE_RESOURCE_ID_ENEMY_ATTACK],
                       a->pos_x - ATTACK_DRAW_OFFSET_X,
                       a->pos_y - ATTACK_DRAW_OFFSET_Y,
                       0
        );
    }
}

void move_attacks(attack **al, stage *s) {
    int i;
    if (al != NULL) {
        for (i = 0; i < NUMBER_ATTACK; i++) {
            move_attack(al[i], s);
        }
    }
}

void move_attack(attack *a, stage *s) {
    if (a->attack_status == ATTACK_STATUS_ACTIVATED) {
        a->pos_y += ATTACK_SPEED;
        if(a->pos_y >= ATTACK_Y_BOUNDARY) {
            a->attack_status = ATTACK_STATUS_HOLD;
        }
    }
}

// Randomly pick an enemy, and try generate attack
int try_emit_attack(enemy **e, attack **al) {
    int i;
    int flag_enemy_exist = 0;
    int randnum;
    int atk_id = -1;

    // Check if any enemy exists now
    for (i = 0; i < NUMBER_ATTACK; i++) {
        if(e[i]->status == ENEMY_STATUS_ALIVE) {
            flag_enemy_exist = 1;
        }
    }
    if (flag_enemy_exist != 1) {
       return -1;
    }

    // Check if there's attack slot available
    for (i = 0; i < NUMBER_ATTACK; i++) {
        if (al[i]->attack_status == ATTACK_STATUS_HOLD) {
            atk_id = i;
            break;
        }
    }
    if (atk_id < 0) {
        return -1;
    }
    randnum = rand() % ENEMY_NUMBER;
    i = 0;
    while (1) {
        if (e[i]->status == ENEMY_STATUS_ALIVE) {
            // Skip if countdown hasn't end, then count down
            if (randnum > 0) {
                randnum -= 1;
            }
            // When countdown end, let this enemy emit attack (atk_id)
            else {
                trigger_attack(al[atk_id], e[i]->pos_x, e[i]->pos_y);
                return 1;
            }
        }
        // Choose the next enemy
        i += 1;
        if (i == ENEMY_NUMBER) {
            i = 0;
        }
    }
}

int trigger_attack(attack *a, int pos_x, int pos_y) {
    if (a->attack_status == ATTACK_STATUS_HOLD) {
        a->attack_status = ATTACK_STATUS_ACTIVATED;
        a->pos_x = pos_x;
        a->pos_y = pos_y;
        return 1;
    }
    else {
        return -1;
    }
}

void generate_attack(enemy **el, attack **al, stage *s) {
    if (s->attack_counter == FRAME_ATTACK_PERIOD) {
        if (try_emit_attack(el, al) >= 0) {
            s->attack_counter = 0;
        }
    }
    else {
        s->attack_counter += 1;
    }
}

/* Player */
player *create_player() {
    player *p = malloc(sizeof(player));
    p->life = 3;
    p->status = PLAYER_STATUS_ALIVE;
    p->position = PLAYER_INIT_POSITION;
    // NOTE: player should be able to move in the beginning
    p->shoot_counter = PLAYER_SHOOT_FRAME_COUNT;
    p->direction = PLAYER_DIRECTION_STILL;
    return p;
}

void free_player(player *p) {
    free(p);
}

void draw_player(player *p, stage *s) {
    al_draw_bitmap(s->game_resource->resource_images[IMAGE_RESOURCE_ID_PILOT],
                   p->position - PILOT_DRAW_OFFSET_X,
                   PLAYER_DRAW_POSITION_Y,
                   0
    );
}

void move_player(player *p, stage *s) {
    int pos_predicted;

    // Handle shooting

    if (p->direction == PLAYER_DIRECTION_LEFT && p->position >= PLAYER_POSITION_BOUNDARY_LEFT) {
        pos_predicted = p->position - PLAYER_SPEED;
        if (pos_predicted >= PLAYER_POSITION_BOUNDARY_LEFT) {
            p->position = pos_predicted;
        }
        else {
            p->position = PLAYER_POSITION_BOUNDARY_LEFT;
        }
    }
    else if (p->direction == PLAYER_DIRECTION_RIGHT && p->position <= PLAYER_POSITION_BOUNDARY_RIGHT) {
        pos_predicted = p->position + PLAYER_SPEED;
        if (pos_predicted <= PLAYER_POSITION_BOUNDARY_RIGHT) {
            p->position = pos_predicted;
        }
        else {
            p->position = PLAYER_POSITION_BOUNDARY_RIGHT;
        }
    }

    if (p->shoot_counter == PLAYER_SHOOT_FRAME_COUNT) {
        // If signal is on, try to emit shoot
        if (p->shoot_signal == PLAYER_SHOOT_SIGNAL_ON) {
            // If shoot is successful, reset the counter
            if(player_try_emit_shoot(p, s->list_shoot) >= 0) {
                al_play_sample(s->game_resource->resource_sounds[SOUND_RESOURCE_ID_LASER],
                1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                p->shoot_counter = 0;
            }
        }
    } else {
        p->shoot_counter += 1;
    }

    // Turn off shoot signal
    p->shoot_signal = PLAYER_SHOOT_SIGNAL_OFF;
}

/* Stage */
stage *create_stage() {
    stage *sg = malloc(sizeof(stage));
    sg->game_status = GAME_STATUS_PLAYING;
    sg->score = 0;
    sg->difficulty = 0;
    sg->screen = NULL;

    time(&(sg->random_seed)); // Add random seed
    srand((unsigned int)sg->random_seed);

    sg->game_player = create_player();
    sg->game_resource = create_resource();
    sg->list_enemy = create_enemies(sg);
    sg->list_shoot = create_shoots();
    sg->list_attack = create_attacks();
    sg->key_operation[KEY_OPERATION_ID_LEFT] = KEY_OPERATION_STATUS_RELEASE;
    sg->key_operation[KEY_OPERATION_ID_RIGHT] = KEY_OPERATION_STATUS_RELEASE;
    sg->key_operation[KEY_OPERATION_ID_SHOOT] = KEY_OPERATION_STATUS_RELEASE;
    sg->attack_counter = FRAME_ATTACK_PERIOD;

    return sg;
}

void free_stage(stage *s) {
    if(s != NULL) {
        free_player(s->game_player);
        free_resource(s->game_resource);
        free_enemies(s->list_enemy);
        free_shoots(s->list_shoot);
        free_attacks(s->list_attack);
        free(s);
    }
}

/* Game Resource */
resource *create_resource() {
    int i;

    /* Locate to executable's directory (project root) */
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    chdir(al_path_cstr(path, '/'));
    al_destroy_path(path);

    resource *r = malloc(sizeof(resource));
    r->resource_images = malloc(sizeof(ALLEGRO_BITMAP*) * NUMBER_RESOURCE_IMAGE);
    r->resource_sounds = malloc(sizeof(ALLEGRO_SAMPLE*) * NUMBER_RESOURCE_SOUND);
    for (i = 0; i < NUMBER_RESOURCE_IMAGE; i++) {
        r->resource_images[i] = al_load_bitmap(IMAGE_RESOURCE_PATH[i]);
        if(r->resource_images[i] == NULL) {
            printf("Hey can't load file!\n");
        }
    }
    for (i = 0; i < NUMBER_RESOURCE_SOUND; i++) {
        r->resource_sounds[i] = al_load_sample(SOUND_RESOURCE_PATH[i]);
        if(r->resource_sounds[i] == NULL) {
            printf("Hey can't load sound file!\n");
        }
    }
    return r;
}

void free_resource(resource *r) {
    int i;
    for (i = 0; i < NUMBER_RESOURCE_IMAGE; i++) {
        al_destroy_bitmap(r->resource_images[i]);
    }
    for (i = 0; i < NUMBER_RESOURCE_SOUND; i++) {
        al_destroy_sample(r->resource_sounds[i]);
    }
    free(r->resource_images);
    free(r->resource_sounds);
    free(r);
}

/* Engine 
int engine_run() {
    ALLEGRO_DISPLAY *display = NULL;
    int routine_result = 0;

    // Initialize screen
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    // TODO: We should create screen of (640, 480), however retina screen makes this problematic
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    // al_resize_display(display, 640, 480);
    if (!display) {
        fprintf(stderr, "Error: Failed to create display window");
        return -1;
    }

    routine_result = routine_play(display);

    if (routine_result != 0) {
        fprintf(stderr, "Some error happens.");
    }

    al_destroy_display(display);

    return 0;
}
*/

/*
int routine_play(ALLEGRO_DISPLAY *d){
    // Initialize
    ALLEGRO_EVENT_QUEUE *evt_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
    // Note: Should use stack memory
    ALLEGRO_EVENT evt;

    if (!evt_queue) {
        fprintf(stderr, "Error: Failed to initialize event queue.");
        return -1;
    }
    if (!timer) {
        fprintf(stderr, "Error: Failed to initialize timer.");
        return -1;
    }

    stage *s = create_stage(d);

    al_register_event_source(evt_queue, al_get_display_event_source(d));
    al_register_event_source(evt_queue, al_get_timer_event_source(timer));
    al_register_event_source(evt_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    // A while loop...
    while (1) {
        al_wait_for_event(evt_queue, &evt);
        if (evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (evt.type == ALLEGRO_EVENT_TIMER) {
            if (al_is_event_queue_empty(evt_queue))
            {   // Note: Lazy drawing.
                draw_screen(s);
            }
            // TODO: Handle collision here.
            handle_enemy_shoot_collisions(s->list_enemy, s->list_shoot, s);
            move_enemies(s->list_enemy, s);
            move_shoots(s->list_shoot, s);
            move_attacks(s->list_attack, s);
            generate_attack(s->list_enemy, s->list_attack, s);
            move_player(s->game_player, s);
        }
        else if (evt.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evt.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                s->key_operation[KEY_OPERATION_ID_LEFT] = KEY_OPERATION_STATUS_HOLD;
            }
            else if (evt.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                s->key_operation[KEY_OPERATION_ID_RIGHT] = KEY_OPERATION_STATUS_HOLD;
            }
            else if (evt.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                // Currently, each key down only generate one bullet
                // The shoot signal on player object is shut down for each frame
                s->key_operation[KEY_OPERATION_ID_SHOOT] = KEY_OPERATION_STATUS_HOLD;
                s->game_player->shoot_signal = PLAYER_SHOOT_SIGNAL_ON;
            }
        }
        else if (evt.type == ALLEGRO_EVENT_KEY_UP) {
            if (evt.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                s->key_operation[KEY_OPERATION_ID_LEFT] = KEY_OPERATION_STATUS_RELEASE;
            }
            else if (evt.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                s->key_operation[KEY_OPERATION_ID_RIGHT] = KEY_OPERATION_STATUS_RELEASE;
            }
            else if (evt.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                s->key_operation[KEY_OPERATION_ID_SHOOT] = KEY_OPERATION_STATUS_RELEASE;
            }
        }

        // Additional handler to decide player movement
        if (evt.type == ALLEGRO_EVENT_KEY_DOWN || evt.type == ALLEGRO_EVENT_KEY_UP) {
            if (s->key_operation[KEY_OPERATION_ID_LEFT] == KEY_OPERATION_STATUS_HOLD) {
                if(s->key_operation[KEY_OPERATION_ID_RIGHT] == KEY_OPERATION_STATUS_RELEASE) {
                    s->game_player->direction = PLAYER_DIRECTION_LEFT;
                }
                else {
                    s->game_player->direction = PLAYER_DIRECTION_STILL;
                }
            }
            else if (s->key_operation[KEY_OPERATION_ID_RIGHT] == KEY_OPERATION_STATUS_HOLD) {
                if(s->key_operation[KEY_OPERATION_ID_LEFT] == KEY_OPERATION_STATUS_RELEASE) {
                    s->game_player->direction = PLAYER_DIRECTION_RIGHT;
                }
                else {
                    s->game_player->direction = PLAYER_DIRECTION_STILL;
                }
            }
            else {
                s->game_player->direction = PLAYER_DIRECTION_STILL;
            }
        }
    }
    // Release environment
    free_stage(s);

    // When ends, delete things allocated here
    al_stop_timer(timer);
    al_destroy_timer(timer);
    al_destroy_event_queue(evt_queue);

    return 0;
}
*/

void draw_screen(stage *s) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    draw_shoots(s->list_shoot, s);
    draw_enemies(s->list_enemy, s);
    draw_attacks(s->list_attack, s);
    draw_player(s->game_player, s);
    al_flip_display();
}

unsigned int get_move_flip_by_difficulty(unsigned int d){
    if (d < NUMBER_LEVEL) {
        return DIFFICULTY_SPEED_MAP[d];
    } else {
        return DIFFICULTY_DEFAULT;
    }
}

void handle_enemy_shoot_collisions(enemy **e, shoot **sl, stage *sg) {
    int i, j;
    shoot* s_tmp;
    enemy* e_tmp;
    // If there's any collision, remove both entities
    for (i = 0; i < NUMBER_SHOOT; i++) {
        for (j = 0; j < ENEMY_NUMBER; j++) {
            s_tmp = sl[i];
            e_tmp = e[j];
            // Just simple rectangular collision detection
            if (s_tmp->shoot_status == SHOOT_STATUS_ACTIVATED &&
                e_tmp->status == ENEMY_STATUS_ALIVE) {
                if (s_tmp->pos_x + 4 > e_tmp->pos_x - 16 &&
                    s_tmp->pos_x - 4 < e_tmp->pos_x + 16 &&
                    s_tmp->pos_y + 16 > e_tmp->pos_y - 16 &&
                    s_tmp->pos_y - 16 < e_tmp->pos_y + 16) {
                    s_tmp->shoot_status = SHOOT_STATUS_HOLD;
                    e_tmp->status = ENEMY_STATUS_CRASHED;
                    al_play_sample(sg->game_resource->resource_sounds[SOUND_RESOURCE_ID_EXPLOSION],
                        1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    break;
                }
            }
        }
    }
    return;
}

gameplay_resr *create_gameplay_resr() {
    gameplay_resr* ptr = calloc(1, sizeof(gameplay_resr));
    // gameplay_resr *gpres_ptr = &(gres_ptr->gameplay_resr);
    ptr->sg = create_stage();
    return ptr;
}

void destroy_gameplay_resr(gameplay_resr *p) {
    if (p) {
        free_stage(p->sg);
        free(p);
    }
    return;
}