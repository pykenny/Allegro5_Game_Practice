#ifndef __STATECODES_H
#define __STATECODES_H

/* Notes:
 * 1. All inner states should have _INIT, _FINISH, _EXIT codes.
 * 2. _EXIT code should be set to 0.
 * 3. Naming convention (draft)
 *   1) Prefix for a routine:
 *     * Suppose routine to be named is called "CurrentRoutine".
 *       - RoutineAbbr -> (Routine's first 1~2 letters)
 *       - ParentPrefix -> "" | RoutineAbbr @ "_" | ParentPrefix @ RoutineAbbr @ "_"
 *       - RoutinePrefix -> ParentPrefix @ CurrentRoutine @ "_"
 *   2) Code types:
 *       - Inner state: RoutinePrefix @ "STATE"
 *         These codes should only be used for the routine function itself,
 *         if there's any subroutine underneath that requires loop.
 * 
 *         For routine that does not have inner state, there's no definition
 *         for inner state codes. 
 * 
 *       - Return code for direct parent routine: RoutinePrefix @ "RETCODE"
 *         These codes should be defined based on states of its parent routine.
 *         The upmost layer for our structure is main() function, so return code
 *         of the upmost routine (PROC_RETCODE) should be implemented based on
 *         main()'s return code.
 */

/* Note for current routine structure:
    (Leaf nodes only have retcode.)
    [main()]                    | Has 'STATE' | RETCODE Target |    Header    |
        PROC                    |     YES     |     main()     |  PROC        |
            INIT                |      NO     |      PROC      |  P_INIT      |
            MENU                |     YES     |      PROC      |  P_MENU      |
                INIT            |      NO     |      MENU      |  P_M_INIT    |
                OPT_START       |      NO     |      MENU      |  P_M_OSTART  |
                OPT_EXIT        |      NO     |      MENU      |  P_M_OEXIT   |
                FINISH          |      NO     |      MENU      |  P_M_FINISH  |
            GAMEPLAY            |     YES     |      PROC      |  P_GAMEPLAY  |
                INIT            |      NO     |    GAMEPLAY    |  P_G_INIT    |
                PLAYING         |      NO     |    GAMEPLAY    |  P_G_PLAYING |
                PAUSE           |      NO     |    GAMEPLAY    |  P_G_PAUSE   |
                FINISH          |      NO     |    GAMEPLAY    |  P_G_FINISH  |
            FINISH              |      NO     |      PROC      |  P_FINISH    |
 */

enum PROC_STATE {
    PSTATE_EXIT =     0,
    PSTATE_FINISH =   1,
    PSTATE_INIT =     2,
    PSTATE_MENU =     3,
    PSTATE_GAMEPLAY = 4
};

enum PROC_RETCODE {
    PRET_SUC = 0,
    PCODE_ERR = 1
};

    enum P_INIT_RETCODE {
       P_ICODE_MENU =   PSTATE_MENU,
       P_ICODE_FINISH = PSTATE_FINISH
    };

    enum P_MENU_STATE {
        P_MSTATE_EXIT =      0,
        P_MSTATE_FINISH =    1,
        P_MSTATE_INIT =      2,
        P_MSTATE_OPT_START = 3,
        P_MSTATE_OPT_EXIT =  4
    };

    enum P_MENU_RETCODE {
        P_MCODE_FINISH =   PSTATE_FINISH,
        P_MCODE_GAMEPLAY = PSTATE_GAMEPLAY
    };

        enum P_M_INIT_RETCODE {
            P_M_ICODE_FINISH = P_MSTATE_FINISH
        };

        enum P_M_OSTART_RETCODE {
            P_M_OSCODE_FINISH = P_MSTATE_FINISH
        };

        enum P_M_OEXIT_RETCODE {
            P_M_OECODE_FINISH = P_MSTATE_FINISH
        };

        enum P_M_FINISH_RETCODE {
            P_M_FCODE_EXIT = P_MSTATE_EXIT
        };

    enum P_GAMEPLAY_STATE {
        P_GSTATE_EXIT =    0,
        P_GSTATE_FINISH =  1,
        P_GSTATE_INIT =    2,
        P_GSTATE_PLAYING = 3,
        P_GSTATE_PAUSE =   4
    };

    enum P_GAMEPLAY_RETCODE {
        P_GCODE_FINISH = PSTATE_FINISH,
        P_GCODE_MENU =   PSTATE_MENU
    };

        enum P_G_INIT_RETCODE {
            P_G_ICODE_PLAYING = P_GSTATE_PLAYING,
            P_G_ICODE_FINISH = P_GSTATE_FINISH
        };

        enum P_G_PLAYING_RETCODE {
            P_G_PLCODE_PAUSE = P_GSTATE_PAUSE,
            P_G_PLCODE_FINISH = P_GSTATE_FINISH
        };

        enum P_G_PAUSE_RETCODE {
            P_G_PSCODE_PLAYING = P_GSTATE_PLAYING,
            P_G_PSCODE_FINISH = P_GSTATE_FINISH
        };

        enum P_G_FINISH_RETCODE {
            P_G_FCODE_EXIT = P_GSTATE_EXIT
        };

    enum P_FINISH_RETCODE {
        P_FCODE_EXIT = PSTATE_EXIT
    };

#endif
