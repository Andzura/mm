#ifndef _MESSAGE_DATA_STATIC_H_
#define _MESSAGE_DATA_STATIC_H_
#include "PR/ultratypes.h"

struct MessageTableEntry{
    /* 0x0000 */ u16 textId;
    /* 0x0002 */ u8 typePos;
    /* 0x0003 */ //u8 pad3;
    /* 0x0004 */ const char* segment;
}; // size = 0x8;

#endif