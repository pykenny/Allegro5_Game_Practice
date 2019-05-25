#ifndef __PROCESS_H
#define __PROCESS_H

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
// #include "errcode.h" // included in "routine_info.h"
// #include "routine_info.h" // included in "resource.h"
#include "resource.h"
#include "control.h"
#include "statecodes.h"

/* *** Macros *** */

/* Support head-appending of __VA_ARGS__
 * Ref: https://stackoverflow.com/a/22406915
 */
#define _NO_FIRST(first, ...) __VA_ARGS__
#define DO_APPEND_LAST(last, ...) _NO_FIRST(__VA_ARGS__, last)

/* ***** Try-or-break functions ***** */
/* These functions should be called inside a loop. */

/* For handling AL5 initialization. */
#define allegro_init_try(fname, pack, errid, ...) \
    if(!fname(__VA_ARGS__)) {                     \
        pack->info.retcode = errid;               \
        break;                                    \
    }

/* For handling function call that only "peek" returned value
 * without saving it to any variable.
 * Note that it assumes that a succesful call will return non-zero
 * value.
 * 
 * Right now it's essentially the same as allegro_init_try().
 */
#define vfcall_try(fname, pack, errid, ...)   \
    if(!fname(__VA_ARGS__)) {                 \
        pack->info.retcode = errid;           \
        break;                                \
    }

/* For handling other function calls which return non-zero
 * value on successful return, and store returned value inside
 * given variable.
 */
#define nzfcall_try(fname, lvalue, pack, errid, ...)   \
    if(!((lvalue) = fname(__VA_ARGS__))) {             \
        (pack)->info.retcode = errid;                  \
        break;                                         \
    }

/* Similar to vfcall_try() but obtains error code from given
 * function parameter.
 * Note that it assumes the function takes an (int *) type
 * value as the LAST argument for error value.
 */
#define vfcall_arg_try(fname, pack, errarg, ...)             \
    if(!fname(DO_APPEND_LAST(errarg, _, ## __VA_ARGS__))) {  \
        (pack)->info.retcode = *(errarg);                    \
        break;                                               \
    }

/* vfcall_arg_try() implementation for case of nzfcall_try().
 */
#define nzfcall_arg_try(fname, lvalue, pack, errarg, ...)                \
    if(!((lvalue) = fname(DO_APPEND_LAST(errarg, _, ## __VA_ARGS__)))) { \
        (pack)->info.retcode = *(errarg);                                \
        break;                                                           \
    }

/* Access control/infornation units */
#define SRP_EQP(r) (r->ctrl->evt_queue)
#define SRP_EVT(r) (r->ctrl->evt)
#define SRP_EVTADR(r) (&r->ctrl->evt)
#define SPR_EVT_KID(r) (SRP_EVT(r).keyboard.keycode)
#define SPR_INFO(r) (r->info)

/* Access stage object in old way */
#define SPR_SGP(r) (GP_RS(r->inter_rsr).sg)

/* *** Function Declaration *** */
int proc_routine();

#endif

