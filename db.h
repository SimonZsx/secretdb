
/***************
 Copyright (c) 2013, Matthew Levenstein
 Copyright (c) 2018, Shixiong Zhao

 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************/

#ifndef SECRETDB_LIBRARY_H
#define SECRETDB_LIBRARY_H


#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef L_ctermidNOPE
#include <unistd.h>
#include <fcntl.h>
#define LOCK
#endif


typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef struct db db;

#define SIZEOF_LONG sizeof(uint64_t)
#define _HASH 33
#define _ORDER 99
#define _WIDTH 1+_HASH*_ORDER+SIZEOF_LONG*(_ORDER+1)
#define _DEPTH 10
#define _MAX 0xf4240

struct db{
    FILE* fp;
    unsigned char path[_DEPTH][_WIDTH];
    uint64_t node_addrs[_DEPTH];
#ifdef LOCK
    struct flock fl;
#endif
};


void node_split(db *, int, unsigned char);
void _insert(db *, unsigned char *, int, uint64_t, uint64_t, int);
void put(db *, unsigned char *, unsigned char *);
uint64_t search(db *, unsigned char *, int *);
unsigned char* get(db *, unsigned char *);
void db_init(db *, const char *);

#ifdef LOCK
int db_lock(db *);
int db_unlock(db *);
#endif


void db_close(db *);


#ifdef LOCK
int
db_lock(db* db) {
  db->fl.l_type   = F_WRLCK;
  db->fl.l_whence = SEEK_SET;
  db->fl.l_start  = 0;
  db->fl.l_len    = 0;
  db->fl.l_pid    = getpid();
  return fcntl((db->fp)->_file,F_SETLKW, &(db->fl));
}

int
db_unlock(db* db) {
  db->fl.l_type = F_UNLCK;
  fcntl((db->fp)->_file, F_SETLK, &(db->fl));
}
#endif



#endif