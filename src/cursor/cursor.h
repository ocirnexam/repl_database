#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../btree/btree.h"
#include "../table/table.h"
#include "../row/row.h"
#include "../pager/pager.h"

typedef struct {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; // represent one element past the last one in the table (to insert one)
} Cursor;

Cursor* cursor_table_start(Table*);
Cursor* cursor_table_end(Table*);

void cursor_node_leaf_insert(Cursor* cursor, uint32_t key, Row* value);

void* cursor_value(Cursor*);
void cursor_advance(Cursor*);

Table* db_open(const char*);
void db_close(Table*);

#endif