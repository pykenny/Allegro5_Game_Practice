#ifndef __ROUTINE_INFO_H
#define __ROUTINE_INFO_H

#include "errcode.h" 
#define R_INFO_MSG_LEN 128

/* [r_info] [struct routine_info_srt]
 * Structure used to store state and error information.
 */
typedef struct routine_info_srt {
    int retcode;
    int errcode;
    // unsigned char msg[R_INFO_MSG_LEN];
} r_info;

/* r_info data initialization */
#define r_info_stat_init(r)                                                     \
    do {                                                                        \
        r.retcode = r.errcode = 0;                                              \
    } while (0)
/*
#define r_info_stat_init(r)                                                     \
    do {                                                                        \
        r.retcode = r.errcode = 0;                                              \
        strncpy((char*)r.msg, _R_INFO_MSGS[R_INFO_MSG_SUC_ID], R_INFO_MSG_LEN); \
    } while (0)
*/

/* Simple error message print-out */
#define print_routine_errmsg(r)            \
    do {                                   \
        printf("%s\n", _R_INFO_MSGS[r.errcode]);      \
    } while (0)

#endif