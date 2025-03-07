#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include "../pager/pager.h"

typedef struct {
    uint32_t root_page_num;
    Pager* pager;
} Table;


#endif