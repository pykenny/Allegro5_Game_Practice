#ifndef __STATECODES_H
#define __STATECODES_H

/* Inner state of main process */
enum PROC_STATE {
    PSTATE_EXIT =     0,
    PSTATE_FINISH =   1,
    PSTATE_INIT =     2,
    PSTATE_MENU =     3,
    PSTATE_GAMEPLAY = 4
};

/* Return code for main process
 * (equivalent to main return code)
 */
enum PROC_RETCODE {
    PCODE_RSUC = 0,
    PCODE_RERR = 1
};

enum PROC_ERRCODE {
    PCODE_SUC =    0,
    PCODE_EAL5IN = 1,  /* Failed on Allegro5 init */
    PCODE_ERES =   2     /* Failed on resource allocation */
};

/* Inner state of process->menu routine */
enum P_MENU_STATE {
    P_MSTATE_EXIT =    0,
    P_MSTATE_FINISH =  1,
    P_MSTATE_INIT =    2,
    P_MSTATE_OPT_START = 3,
    P_MSTATE_OPT_EXIT =  4
};

/* Return code for process->menu routine
 * (passed to main process as the next state)
 */
enum P_MENU_RETCODE {     /* Ref: PROC_STATE */
    P_MCODE_RFINISH =   1,
    P_MCODE_RGAMEPLAY = 4
};

enum P_MENU_ERRCODE {
    P_MCODE_SUC = 0,
    P_MCODE_ERR = 1
};

/* Inner state of process->gameplay routine */
enum P_GAMEPLAY_STATE {
    P_GSTATE_EXIT =   0,
    P_GSTATE_FINISH,
    P_GSTATE_INIT,
    P_GSTATE_PLAYING,
    P_GSTATE_PAUSE
};

/* Return code for process->gameplay routine
 * (sent to main process)
 */
enum P_GAMEPLAY_RETCODE { /* Ref: PROC_STATE */
    P_GCODE_RFINISH = 1,
    P_GCODE_RMENU = 3
};

enum P_GAMEPLAY_ERRCODE {
    P_GCODE_SUC = 0,
    P_GCODE_ERR = 1
};

/* Inner state of process->gameplay->pause routine*/
enum P_G_PAUSE_STATE {     /* Ref: P_GAMEPLAY_STATE */
    P_PSTATE_FINISH =  1,
    P_PSTATE_PLAYING = 3
};

#endif