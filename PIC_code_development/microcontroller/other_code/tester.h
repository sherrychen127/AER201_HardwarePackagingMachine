#if _pragma_once_support
#    pragma once
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    NONE = 0x00,
    R = 0x01,
    F = 0x02,
    L = 0x03,
    RF = 0x04,
    RL = 0x05,
    FL = 0x06,
    RRF = 0x07,
    RRL = 0x08,
    RFF = 0x09,
    RLL = 0x0A,
    RFL = 0x0B,
    FFL = 0x0C,
    FLL = 0x0D,
    RRFL = 0x0E,
    RFFL = 0x0F,
    RFLL = 0x10,
    RLLL = 0x11,
    FLLL = 0x12,
} DIET;


struct Instruction{
    unsigned short label;
    DIET diet;
    unsigned short amount;
    struct Instruction *next;
};
typedef struct Instruction Instruction;
typedef struct{
    unsigned short taped;  ///0 if not taped, 1 if taped
    unsigned short label;
    DIET diet[4];  ///maximum portions of a diet is 4
} Drawer;

char* get_diet_name(DIET diet);

Instruction* initInstruction();

void printDrawer(Drawer dr);
void printDiet(DIET d);
void printContainer(Drawer *dr);
void printKeypad();
