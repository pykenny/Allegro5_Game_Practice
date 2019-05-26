#ifndef __RESOURCE_H
#define __RESOURCE_H

/* Note about inclusion
 * [Customized inclusion]
 * [routine_info.h]
 * [control.h]
 */

#include "routine_info.h"
#include "control.h"

/* *** Include routine resource headers *** */
#include "../resource/resource_stage.h"
/* *** End of resource header inclusion *** */


/* Note about modified version
 * // Some customized resource types are already defined in 
 * // included headers.
 * typedef union general_resource {
 *   [rsr1];[rsr2];[rsr3]; ... ;
 * } g_resr;
 * typedef struct routine_stat_resc_pack_str {
    r_info info;
    ctrl_handle *ctrl;
    g_resr *inter_rsr;
    g_resr *exter_rsr;
   } r_srpack;
 */

/* Simple cast to generic type */
#define GRESR_PTR_CAST(p) ((g_resr *)p)

/*
 * General resource holder
 */
typedef union general_resource {
    /* TODO: Define it based on all resource types */
    gameplay_resr gameplay_resr; // Not a good way but can be easily recognized
} g_resr;

/* [r_srpack] [struct routine_stat_resc_pack_str]
 * Structure sued to store combined resource required for routine.
 */
typedef struct routine_stat_resc_pack_str {
    r_info info;       /* Routine information */
    ctrl_handle *ctrl;  /* Control handle */
    g_resr *inter_rsr;  /* Internal resource */
    g_resr *exter_rsr;  /* External resource */
} r_srpack;

#endif
