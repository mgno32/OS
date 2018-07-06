#include <stdint.h>
#define dw uint16_t

struct PCB {
    dw ES; // 0
    dw DS; // 2
    dw SS; // 4
    dw CS; // 6
    dw DI; // 8
    dw SI; // 10
    dw BP; // 12
    dw SP; // 14
    dw AX; // 16
    dw BX; // 18
    dw CX; // 20
    dw DX; // 22
    dw IP; // 24
    dw FLAGS; // 26
};
