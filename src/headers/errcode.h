#ifndef __ERRCODE_H
#define __ERRCODE_H

#define _R_INFO_MSG_NUM 17

enum R_INFO_MSG_ID {
    R_INFO_MSG_SUC_ID = 0,
    R_INFO_MSG_ERR_AL5INIT,
    R_INFO_MSG_ERR_AL5IMG,
    R_INFO_MSG_ERR_AL5FONT,
    R_INFO_MSG_ERR_AL5TTF,
    R_INFO_MSG_ERR_AL5AUDI,
    R_INFO_MSG_ERR_AL5ACOD,
    R_INFO_MSG_ERR_KEYBD,
    R_INFO_MSG_ERR_DISPL,
    R_INFO_MSG_ERR_AUDIO,
    R_INFO_MSG_ERR_FONTS,
    R_INFO_MSG_ERR_IMGLD,
    R_INFO_MSG_ERR_AUDLD,
    R_INFO_MSG_ERR_EVTQE,
    R_INFO_MSG_ERR_TIMER,
    R_INFO_MSG_ERR_CTRLH,
    R_INFO_MSG_ERR_OTHRS
};

extern const char *_R_INFO_MSGS[];

#endif