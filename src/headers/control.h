#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdlib.h>
#include <allegro5/allegro.h>
#include "general_settings.h"
#include "errcode.h"

/* Flags for flush_ctrl_handle()  */
extern const unsigned int FLUSH_TIMER_EVT;
extern const unsigned int FLUSH_DISPLAY_EVT;
extern const unsigned int FLUSH_KEYBOARD_EVT;
extern const unsigned int FLUSH_ALL_EVT;

/* [ctrl_handle] (control_handle_strt)
 * Used for control periodic update and user interaction.
 */
typedef struct control_handle_strt {
    ALLEGRO_EVENT_QUEUE *evt_queue;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT evt;
} ctrl_handle;

ctrl_handle * create_ctrl_handle(int *err);
void flush_ctrl_handle(ctrl_handle *ch, int mask);
void destroy_ctrl_handle(ctrl_handle *ch);

#endif