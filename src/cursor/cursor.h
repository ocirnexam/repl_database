#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../table/table.h"

typedef struct {
    Table* table;
    uint32_t row_num;
    bool end_of_table; // represent one element past the last one in the table (to insert one)
} Cursor;

Cursor* cursor_table_start(Table*);
Cursor* cursor_table_end(Table*);

void* cursor_value(Cursor*);
void cursor_advance(Cursor*);

#endif