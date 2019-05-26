#include "./../headers/process.h"

/* *** Function Declaration *** */
/* These function declarations are organized in nested structure,
 * in order to visualize relationship
 */

/* MAIN PROCESS */
static int proc_init(r_srpack *r);
static int proc_menu(r_srpack *r);
/*  |_  MENU ROUTINE */
    static int menu_init(r_srpack *i_p, r_srpack *i);
    static int menu_opt_start(r_srpack *i);
    static int menu_opt_exit(r_srpack *i);
    static int menu_finish(r_srpack *i_p, r_srpack *i);
static int proc_gameplay(r_srpack *r);
/*  |_  GAMEPLAY ROUTINE */
    static int gameplay_init(r_srpack *i_p, r_srpack *i);
    static int gameplay_playing(r_srpack *r);
    static int gameplay_pause(r_srpack *r);
    static int gameplay_finish(r_srpack *r_p, r_srpack *r);
static int proc_finish(r_srpack *r);

int proc_routine() {
    /* Comments here are used to explain workflow of all similar routines. */

    /* Step 1: Set up (empty) local resource and information object */
    r_srpack rspack;

    /* Step 2: Pack extern/intern resource together
     * However this is the top-most level so there's no external
     * resource required to pack into rspack.
     */
    /* ~~ Nothing to do here ~~ */

    /* Step 3: Initialize state
     * Initial state should be something looks like "[XXX]_INIT".
     */
    int state = PSTATE_INIT;

    /* Step 4: Run the routine
     * Initialization of local resource is certain to be done at "[XXX]_INIT"
     * state, while cleanup should be done in "[XXX]_FINISH" state.
     * (All "[XXX]_EXIT" states are 0, and thus are used to break the while loop)
     */
    while (state) {
        switch (state) {
            case PSTATE_INIT:
                state = proc_init(&rspack);
                break;
            case PSTATE_MENU:
                state = proc_menu(&rspack);
                break;
            case PSTATE_GAMEPLAY:
                state = proc_gameplay(&rspack);
                break;
            case PSTATE_FINISH:
                state = proc_finish(&rspack);
                break;
        }
    }

    /* Step 5: Handle error 
     * Note: For other lower-level routine, if it completed without error,
     * then rspack.info.retcode should be already modified at somewhere else. 
     */
    if (rspack.info.errcode) {
        rspack.info.retcode = PCODE_ERR;
        print_routine_errmsg(rspack.info);
    }
    return rspack.info.retcode;
}

static int proc_init(r_srpack *r_p) {
    int errcode;
    /* Initialize all Allegro stuff */
    do {
        r_info_stat_init(r_p->info);

        allegro_init_try(al_init, r_p, R_INFO_MSG_ERR_AL5INIT);
        allegro_init_try(al_init_image_addon, r_p, R_INFO_MSG_ERR_AL5IMG);
        allegro_init_try(al_init_font_addon, r_p, R_INFO_MSG_ERR_AL5FONT);
        allegro_init_try(al_init_ttf_addon, r_p, R_INFO_MSG_ERR_AL5TTF);
        allegro_init_try(al_install_audio, r_p, R_INFO_MSG_ERR_AL5AUDI);
        allegro_init_try(al_init_acodec_addon, r_p, R_INFO_MSG_ERR_AL5ACOD);
        allegro_init_try(al_reserve_samples, r_p, R_INFO_MSG_ERR_AUDIO, 8);
        allegro_init_try(al_install_keyboard, r_p, R_INFO_MSG_ERR_KEYBD);

        /* Create control handle here.
         * Display is created at this point.
         */
        nzfcall_arg_try(create_ctrl_handle, r_p->ctrl, r_p, &errcode);

        /* This helps allegro to fetch files from correct directory,
         * and unlikely to cause any error at this point.
         */
        ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
        chdir(al_path_cstr(path, '/'));
        al_destroy_path(path);
        
        return (r_p->info.retcode = P_ICODE_MENU);
    } while (0);
    /* If any error occurs, cleanup and end the program */
    return (r_p->info.retcode = P_ICODE_FINISH);
}

static int proc_menu(r_srpack *r_p) {
    r_srpack rspack;
    int state = P_MSTATE_INIT;
    /* TODO: Pack resource together */

    while (state) {
        switch (state) {
            case P_MSTATE_INIT:
                state = menu_init(r_p, &rspack);
                break;
            case P_MSTATE_OPT_START:
                state = menu_opt_start(&rspack);
                break;
            case P_MSTATE_OPT_EXIT:
                state = menu_opt_exit(&rspack);
                break;
            case P_MSTATE_FINISH:
                state = menu_finish(r_p, &rspack);
                break;
        }
    }
    if (rspack.info.errcode) {
        rspack.info.retcode = P_MCODE_FINISH;
        print_routine_errmsg(rspack.info);
    } else {
        rspack.info.retcode = P_MCODE_GAMEPLAY;
    }
    return rspack.info.retcode;
}

static int proc_gameplay(r_srpack *r_p) {
    r_srpack rspack;
    int state = P_GSTATE_INIT;

    /* TODO: Pack things together */


    while (state) {
        switch (state) {
            case P_GSTATE_INIT:
                state = gameplay_init(r_p, &rspack);
                break;
            case P_GSTATE_PLAYING:
                state = gameplay_playing(&rspack);
                break;
            case P_GSTATE_PAUSE:
                state = gameplay_pause(&rspack);
                break;
            case P_GSTATE_FINISH:
                state = gameplay_finish(r_p, &rspack);
                break;
        }
    }

    /* Note: If non-error result, then retcode should already be modified
     * somewhere else.
     */
    if (r_p->info.errcode) {
        r_p->info.retcode = P_GCODE_FINISH;
    } else {
        r_p->info.retcode = P_GCODE_FINISH;
    }
    
    return r_p->info.retcode;
}

static int proc_finish(r_srpack *r) {
    /* Note:
     * (1) There's no internal resource right now.
     * (2) r_srpack here is statically allocated.
     */
    destroy_ctrl_handle(r->ctrl);
    al_uninstall_audio();
    return P_FCODE_EXIT;
}

/* TODO:
 * Skip menu implementation and all user operation
 * between for now.
 */
static int menu_init(r_srpack *pi, r_srpack *i) {
    return P_M_ICODE_FINISH;
}
static int menu_opt_start(r_srpack *i) {
    return P_M_OSCODE_FINISH;
}
static int menu_opt_exit(r_srpack *i) {
    return P_M_OECODE_FINISH;
}
static int menu_finish(r_srpack *i_p, r_srpack *i) {
    return P_M_FCODE_EXIT;
}

static int gameplay_init(r_srpack *r_p, r_srpack *r) {
    int errcode = 0;
    /* Shift control handle */
    r->ctrl = r_p->ctrl;
    /* Direct shift. But there's nothing in current implementation. */
    r->exter_rsr = r_p->inter_rsr;
    /* INITIALIZE INTERNAL RESOURCE */
    r->inter_rsr = GRESR_PTR_CAST(create_gameplay_resr(&errcode));
    /* INITIALIZE PLAYER STATUS */
    /* INITIALIZE STAGE STATUS */

    /* If error, return error, else enter "PLAYING" */
    if (errcode) {
        SPR_INFO(r_p).errcode = SPR_INFO(r).errcode = errcode;
        SPR_INFO(r).retcode = P_G_ICODE_FINISH;
    }
    else {
        SPR_INFO(r).retcode = P_G_ICODE_PLAYING;
    }
    return SPR_INFO(r).retcode;
}

static int gameplay_playing(r_srpack *r) {
    /* This is to make sure there's no pending that will
     * affect game operation (e.g., stacked periodic timer
     * events, user's key press before game start, ...)
     */
    al_stop_timer(r->ctrl->timer);
    flush_ctrl_handle(r->ctrl, FLUSH_ALL_EVT);
    al_start_timer(r->ctrl->timer);
    /* Mostly copied from original version */
    while (1) {
        al_wait_for_event(SRP_EQP(r), SRP_EVTADR(r));
        if (SRP_EVT(r).type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            SPR_INFO(r).retcode = P_G_PLCODE_FINISH;
            break;
        }
        else if (SRP_EVT(r).type == ALLEGRO_EVENT_TIMER) {
            if (al_is_event_queue_empty(SRP_EQP(r))) {
                draw_screen(SPR_SGP(r)); /*  TODO: ???? */
            }
            handle_enemy_shoot_collisions(
                SPR_SGP(r)->list_enemy,
                SPR_SGP(r)->list_shoot,
                SPR_SGP(r)
            );
            move_enemies(
                SPR_SGP(r)->list_enemy,
                SPR_SGP(r)
            );
            move_shoots(
                SPR_SGP(r)->list_shoot,
                SPR_SGP(r)
            );
            move_attacks(
                SPR_SGP(r)->list_attack,
                SPR_SGP(r)
            );
            generate_attack(
                SPR_SGP(r)->list_enemy,
                SPR_SGP(r)->list_attack,
                SPR_SGP(r)
            );
            move_player(
                SPR_SGP(r)->game_player,
                SPR_SGP(r)
            );
        }
        else if (SRP_EVT(r).type == ALLEGRO_EVENT_KEY_DOWN) {
            if (SPR_EVT_KID(r) == ALLEGRO_KEY_LEFT) {
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_LEFT] = KEY_OPERATION_STATUS_HOLD;
            }
            else if (SPR_EVT_KID(r) == ALLEGRO_KEY_RIGHT) {
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_RIGHT] = KEY_OPERATION_STATUS_HOLD;
            }
            else if (SPR_EVT_KID(r) == ALLEGRO_KEY_SPACE) {
                // Currently, each key down only generate one bullet
                // The shoot signal on player object is shut down for each frame
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_SHOOT] = KEY_OPERATION_STATUS_HOLD;
                SPR_SGP(r)->game_player->shoot_signal = PLAYER_SHOOT_SIGNAL_ON;
            }
        }
        else if (SRP_EVT(r).type == ALLEGRO_EVENT_KEY_UP) {
            if (SPR_EVT_KID(r) == ALLEGRO_KEY_LEFT) {
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_LEFT] = KEY_OPERATION_STATUS_RELEASE;
            }
            else if (SPR_EVT_KID(r) == ALLEGRO_KEY_RIGHT) {
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_RIGHT] = KEY_OPERATION_STATUS_RELEASE;
            }
            else if (SPR_EVT_KID(r) == ALLEGRO_KEY_SPACE) {
                SPR_SGP(r)->key_operation[KEY_OPERATION_ID_SHOOT] = KEY_OPERATION_STATUS_RELEASE;
            }
        }
        // Additional handler to decide player movement
        if (SRP_EVT(r).type == ALLEGRO_EVENT_KEY_DOWN || SRP_EVT(r).type == ALLEGRO_EVENT_KEY_UP) {
            if (SPR_SGP(r)->key_operation[KEY_OPERATION_ID_LEFT] == KEY_OPERATION_STATUS_HOLD) {
                if(SPR_SGP(r)->key_operation[KEY_OPERATION_ID_RIGHT] == KEY_OPERATION_STATUS_RELEASE) {
                    SPR_SGP(r)->game_player->direction = PLAYER_DIRECTION_LEFT;
                }
                else {
                    SPR_SGP(r)->game_player->direction = PLAYER_DIRECTION_STILL;
                }
            }
            else if (SPR_SGP(r)->key_operation[KEY_OPERATION_ID_RIGHT] == KEY_OPERATION_STATUS_HOLD) {
                if(SPR_SGP(r)->key_operation[KEY_OPERATION_ID_LEFT] == KEY_OPERATION_STATUS_RELEASE) {
                    SPR_SGP(r)->game_player->direction = PLAYER_DIRECTION_RIGHT;
                }
                else {
                    SPR_SGP(r)->game_player->direction = PLAYER_DIRECTION_STILL;
                }
            }
            else {
                SPR_SGP(r)->game_player->direction = PLAYER_DIRECTION_STILL;
            }
        }
    /* HANDLE EVENT */
        /* Exit (close screen)? */
        /* Pause command? */
        /* Gameplay key press? (may have many cases) */

        /* Normal operation (timer) */
            /* Screen drawing */
            /* Collision update */
            /* Enemy movement */
            /* Player movement */
            /* Enemy Attack movement */
            /* Player Shoot movement */
            /* Enemy attack generation */
            /* Player shoot generation */
    }
    return P_G_PLCODE_FINISH;
}
static int gameplay_pause(r_srpack *r) {
    return P_G_PSCODE_FINISH;
}
static int gameplay_finish(r_srpack *pr, r_srpack *r) {
    /* Relay error code */
    pr->info.errcode = r->info.errcode;
    /* Release resource */
    destroy_gameplay_resr(GP_RESR_PTR_CAST(r->inter_rsr));
    r->inter_rsr = NULL;
    return P_G_FCODE_EXIT;
}
