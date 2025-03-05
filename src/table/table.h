#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define TABLE_MAX_PAGES 100
#define USERNAME_MAX_SIZE 32
#define EMAIL_MAX_SIZE 255

#define size_of_attribute(Struct, Attriute) sizeof(((Struct*)0)->Attriute)

typedef struct {
    uint32_t id;
    char username[USERNAME_MAX_SIZE];
    char email[EMAIL_MAX_SIZE];
} Row;

#define ID_SIZE ((uint32_t)size_of_attribute(Row, id))
#define USERNAME_SIZE ((uint32_t)size_of_attribute(Row, username))
#define EMAIL_SIZE ((uint32_t)size_of_attribute(Row, email))
#define ID_OFFSET ((uint32_t)0)
#define USERNAME_OFFSET ((uint32_t)ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET ((uint32_t)USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE ((uint32_t)ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define PAGE_SIZE ((uint32_t)4096)
#define ROWS_PER_PAGE ((uint32_t)PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS ((uint32_t)ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;

void* row_slot(Table* table, uint32_t row_num);
void print_row(Row*);

Table* new_table(void);
void free_table(Table*);

#endif