//
// Created by Zhao Shixiong on 4/18/2018.
//
#include <utils.h>

void
to_big(unsigned char* buf, uint64_t val) {
    int i;
    for( i=0; i<sizeof(uint64_t); ++i )
        buf[i] = (val >> (56-(i*8))) & 0xff;
}

uint64_t
from_big(unsigned char* buf) {
    uint64_t val = 0;
    int i;
    for( i=0; i<sizeof(uint64_t); ++i )
        val |= (uint64_t) buf[i] << (56-(i*8));
    return val;
}