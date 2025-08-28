// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint;
typedef const char *pchar;
typedef unsigned char uchar;


// ���������� ����� �����������
#define TIME_MEASURE  500


#ifdef WIN32
    #define IN_MODE_TEST
#else
    #define nullptr 0 //-V1059
    #pragma diag_suppress 2748
#endif


union BitSet32
{
    BitSet32(uint _word) : word(_word) { }
    uint   word;
    uint16 half_word[2];
    uint8  bytes[4];
};


inline void EmptyVV(void) { }
typedef void(*pFuncVV)(void);


#define _GET_BIT(value, bit)   (((value) >> (bit)) & 0x01)
#define _SET_BIT(value, bit)   ((value) |= (1 << (bit)))
#define _CLEAR_BIT(value, bit) ((value) &= (~(1 << (bit))))


#define ERROR_VALUE_FLOAT   1.111e29f


#define _bitset(bits)                               \
  ((uint8)(                                         \
  (((uint8)((uint)bits / 01)        % 010) << 0) |  \
  (((uint8)((uint)bits / 010)       % 010) << 1) |  \
  (((uint8)((uint)bits / 0100)      % 010) << 2) |  \
  (((uint8)((uint)bits / 01000)     % 010) << 3) |  \
  (((uint8)((uint)bits / 010000)    % 010) << 4) |  \
  (((uint8)((uint)bits / 0100000)   % 010) << 5) |  \
  (((uint8)((uint)bits / 01000000)  % 010) << 6) |  \
  (((uint8)((uint)bits / 010000000) % 010) << 7)))

#define BINARY_U8( bits ) _bitset(0##bits)


#include "Log.h"
#include "Utils/Debug.h"
