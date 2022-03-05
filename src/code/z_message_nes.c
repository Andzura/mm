#include "global.h"
#include "message_struct.h"

#if 0

//fontWidth
extern f32 D_801D0470[159];

//rupeesTextLocalization
u8 D_801D06F0[4][8] = { { "rupee(s)" }, //EN
                        { "rubin(e)" }, //DE
                        { "rubis"    }, //FR
                        { "rupia(s)" }  //SPA 
                        };

// rupeesTextLength
u8 D_801D0710[4] = {8,8,5,8};

//TextArea
char D_801D0714[11][16] = {
                                    "Great Bay Coast",
                                    "Zora Cape",
                                    "Snowhead",
                                    "Mountain Village",
                                    "Clock Town",
                                    "Milk Road",
                                    "Woodfall",
                                    "Southern Swamp",
                                    "Ikana Canyon",
                                    "Stone Tower",
                                    "Entrance"
                                };

//TextAreaLength
s16 D_801D07C4[11] = {15,9,8,16,10,9,8,14,12,11,8};

#endif

extern f32 D_801D0470[159];
extern u8 D_801D06F0[4][8];
extern u8 D_801D0710[4];
extern u8 D_801D0714[11][16];
extern s16 D_801D07C4[11];

void Message_FindMessageNES(GlobalContext* globalCtx, u16 textId) {
    const char* foundSegment;
    const char* nextSegment;
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = (MessageTableEntry*)msgCtx->messageEntryTableNes;
    const char* segment = msgEntry->segment;

    while (msgEntry->textId != 0xFFFF) {
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd = nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }
    msgEntry = msgCtx->messageEntryTableNes;
    foundSegment = msgEntry->segment;
    msgEntry++;
    nextSegment = msgEntry->segment;
    font->messageStart = foundSegment - segment;
    font->messageEnd = nextSegment - foundSegment;
}

void Message_LoadCharNES(GlobalContext* globalCtx, u8 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;
    Font_LoadCharNES(globalCtx, codePointIndex, temp1);
    ((u8*)msgCtx->decodedBuffer)[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->unk12098);
    *offset = temp1;
    *arg3 = temp2;
}

void Message_LoadPluralRupeesNES(GlobalContext* globalCtx, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;

    ((u8*)msgCtx->decodedBuffer)[p] = 0x20;
    p++;
    Font_LoadCharNES(globalCtx, 0x52U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x52;
    p++;
    Font_LoadCharNES(globalCtx, 0x75U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x75;
    p++;
    Font_LoadCharNES(globalCtx, 0x70U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x70;
    p++;
    Font_LoadCharNES(globalCtx, 0x65U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x65;
    p++;
    Font_LoadCharNES(globalCtx, 0x65U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x65;
    p++;
    Font_LoadCharNES(globalCtx, 0x73U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x73;

    f += 16.0f * msgCtx->unk12098 * 6.0f;
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadLocalizedRupeesNES(GlobalContext* globalCtx, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u8 j;

    ((u8*)msgCtx->decodedBuffer)[p] = 0x20;
    p = p + 1;
    for (j = 0; j < D_801D0710[gSaveContext.language - 1]; j++) {
        Font_LoadCharNES(globalCtx, D_801D06F0[gSaveContext.language - 1][j], o);
        ((u8*)msgCtx->decodedBuffer)[p] = D_801D06F0[gSaveContext.language - 1][j];
        o += FONT_CHAR_TEX_SIZE;
        p++;
    }
    f += 16.0f * msgCtx->unk12098 * (D_801D0710[gSaveContext.language - 1] + 1);
    p--;
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadRupeesNES(GlobalContext* globalCtx, s16* decodedBufPos, s32* offset, f32* arg3, s16 singular) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;

    ((u8*)msgCtx->decodedBuffer)[p] = 0x20;
    p++;
    Font_LoadCharNES(globalCtx, 0x52U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x52;
    p++;
    Font_LoadCharNES(globalCtx, 0x75U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x75;
    p++;
    Font_LoadCharNES(globalCtx, 0x70U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x70;
    p++;
    Font_LoadCharNES(globalCtx, 0x65U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x65;
    p++;
    Font_LoadCharNES(globalCtx, 0x65U, o);
    o += FONT_CHAR_TEX_SIZE;
    ((u8*)msgCtx->decodedBuffer)[p] = 0x65;
    if (singular != 1) {
        p++;
        Font_LoadCharNES(globalCtx, 0x73U, o);
        o += FONT_CHAR_TEX_SIZE;
        ((u8*)msgCtx->decodedBuffer)[p] = 0x73;
        f += 16.0f * msgCtx->unk12098 * 6.0f;
    } else {
        f += 16.0f * msgCtx->unk12098 * 5.0f;
    }
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadTimeNES(GlobalContext* globalCtx, u8 arg1, s32* offset, f32* arg3, s16* decodedBufPos) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u32 dayTime;
    s16 digits[4];
    f32 timeInSeconds;
    s32 day;
    s16 i;

    if (arg1 == 0xCF) {
        dayTime = 0x40000 - (((day = gSaveContext.day) % 5) << 16) - (u16)(-0x4000 + gSaveContext.time);
    } else {
        dayTime = 0x10000 - (u16)(-0x4000 + gSaveContext.time);
    }
    timeInSeconds = dayTime * (24.0f * 60.0f / 0x10000);

    digits[0] = 0;
    digits[1] = (timeInSeconds / 60.0f);
    while (digits[1] >= 10) {
        digits[0]++;
        digits[1] -= 10;
    }

    digits[2] = 0;
    digits[3] = (s32)timeInSeconds % 60;
    while (digits[3] >= 10) {
        digits[2]++;
        digits[3] -= 10;
    }

    for (i = 0; i < 4; i++) {
        Font_LoadCharNES(globalCtx, digits[i] + '0', o);
        o += FONT_CHAR_TEX_SIZE;
        ((u8*)msgCtx->decodedBuffer)[p] = digits[i] + '0';
        p++;
        if (i == 1) {
            Font_LoadCharNES(globalCtx, ':', o);
            o += FONT_CHAR_TEX_SIZE;
            ((u8*)msgCtx->decodedBuffer)[p] = ':';
            p++;
        }
    }

    f += 5.0f * (16.0f * msgCtx->unk12098);
    *decodedBufPos = p - 1;
    *offset = o;
    *arg3 = f;
}

void Message_LoadAreaTextNES(GlobalContext* globalCtx, s32* offset, f32* arg2, s16* decodedBufPos) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg2;
    s16 i;
    u8 currentChar;
    s16 currentArea;
    s16 stringLimit;

    if ((func_8010A0A4(globalCtx) != 0) || (globalCtx->sceneNum == SCENE_SECOM)) {
        currentArea = 10;
    } else {
        currentArea = globalCtx->pauseCtx.unk_238[4];
    }
    stringLimit = D_801D07C4[currentArea];

    for (i = 0; i < stringLimit; i++) {
        ((u8*)msgCtx->decodedBuffer)[p] = D_801D0714[currentArea][i];
        currentChar = ((u8*)msgCtx->decodedBuffer)[p];
        if (currentChar != ' ') {
            Font_LoadCharNES(globalCtx, D_801D0714[currentArea][i], o);
            o += FONT_CHAR_TEX_SIZE;
        }
        currentChar = ((u8*)msgCtx->decodedBuffer)[p];
        p++;
        f += (D_801D0470[currentChar - ' '] * msgCtx->unk12098);
    }
    p--;
    f += (stringLimit - 1) * (16.0f * msgCtx->unk12098);
    *decodedBufPos = p;
    *offset = o;
    *arg2 = f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_80159438.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_8015966C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_8015B198.s")
