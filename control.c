#include "control.h"

// /* zero-init data */
// static const ctrl_handle EmptyCtrlHandle;

const unsigned int FLUSH_TIMER_EVT =    0x01;
const unsigned int FLUSH_DISPLAY_EVT =  0x02;
const unsigned int FLUSH_KEYBOARD_EVT = 0x04;
const unsigned int FLUSH_ALL_EVT = FLUSH_TIMER_EVT | FLUSH_DISPLAY_EVT | FLUSH_KEYBOARD_EVT;

/* Create a handle */
ctrl_handle * create_ctrl_handle(int *err) {
    ctrl_handle *ch_ptr = NULL;
    int err_val = R_INFO_MSG_SUC_ID;
    do {
        if (!(ch_ptr = (ctrl_handle *)calloc(1, sizeof(ctrl_handle)))) {  /* zero-init */
            err_val = R_INFO_MSG_ERR_CTRLH;
            break;
        }
        if (!(ch_ptr->evt_queue = al_create_event_queue())) {
            err_val = R_INFO_MSG_ERR_EVTQE;
            break;
        }
        if (!(ch_ptr->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT))) {
            err_val = R_INFO_MSG_ERR_DISPL;
            break;
        }
        if (!(ch_ptr->timer = al_create_timer(1.0 / FPS))) {
            err_val = R_INFO_MSG_ERR_TIMER;
            break;
        }
        /* Things should go successfully at this point. */
        al_register_event_source(ch_ptr->evt_queue, al_get_display_event_source(ch_ptr->display));
        al_register_event_source(ch_ptr->evt_queue, al_get_timer_event_source(ch_ptr->timer));
        al_register_event_source(ch_ptr->evt_queue, al_get_keyboard_event_source());

        return ch_ptr;
    } while (0);

    /* If failed, destroy resource */
    destroy_ctrl_handle(ch_ptr);
    if (err) {  /* Set up error value if not NULL */
        *err = err_val;
    }

    return ch_ptr;

    /* // Old version (without error code)
    if (
      (ch_ptr = (ctrl_handle *)calloc(1, sizeof(ctrl_handle))) &&
      (ch_ptr->evt_queue = al_create_event_queue()) &&
      (ch_ptr->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT)) &&
      (ch_ptr->timer = al_create_timer(1.0 / FPS))
    ) {
       al_register_event_source(ch_ptr->evt_queue, al_get_display_event_source(ch_ptr->display));
       al_register_event_source(ch_ptr->evt_queue, al_get_timer_event_source(ch_ptr->timer));
       al_register_event_source(ch_ptr->evt_queue, al_get_keyboard_event_source());
    } else {
        destroy_ctrl_handle(ch_ptr);
    }
    return ch_ptr;
    */
}

/* Clear off all queuing events */
void flush_ctrl_handle(ctrl_handle *ch, int mask) {
    // Protective measure
    if (!(ch && ch->evt_queue && ch->timer && ch->display)) {
        return;
    }

    if (mask & FLUSH_TIMER_EVT) {
        // Question: Should I stop timer, or just let user decide that?
        al_unregister_event_source(ch->evt_queue, al_get_timer_event_source(ch->timer));
    }
    if (mask & FLUSH_DISPLAY_EVT) {
        al_unregister_event_source(ch->evt_queue, al_get_display_event_source(ch->display));
    }
    if (mask & FLUSH_KEYBOARD_EVT) {
        al_unregister_event_source(ch->evt_queue, al_get_keyboard_event_source());
    }

    /* Register everything again.
     * This does not take any effect for redundant registration.
     */
    al_register_event_source(ch->evt_queue, al_get_display_event_source(ch->display));
    al_register_event_source(ch->evt_queue, al_get_timer_event_source(ch->timer));
    al_register_event_source(ch->evt_queue, al_get_keyboard_event_source());
    return;
}

void destroy_ctrl_handle(ctrl_handle *ch) {
    if (ch) {
        if (ch->display) {
            al_destroy_display(ch->display);
            ch->display = NULL;
        }
        if (ch->timer) {
            al_stop_timer(ch->timer);
            al_destroy_timer(ch->timer);
            ch->timer = NULL;
        }
        if (ch->evt_queue) {
            al_destroy_event_queue(ch->evt_queue);
        }
    }
    ch = NULL;
    return;
}