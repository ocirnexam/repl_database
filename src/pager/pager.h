#ifndef PAGER_H
#define PAGER_H

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "../utils/global_defines.h"

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char*);
void* pager_get_page(Pager*, uint32_t);
void pager_flush(Pager*, uint32_t);

#endif