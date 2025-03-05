#ifndef STATEMENT_H
#define STATEMENT_H

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../input_buffer/input_buffer.h"

#define USERNAME_MAX_SIZE 32
#define EMAIL_MAX_SIZE 255

#define size_of_attribute(Struct, Attriute) sizeof(((Struct*)0)->Attriute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;


typedef struct {
    uint32_t id,
    char username[USERNAME_MAX_SIZE],
    char email[EMAIL_MAX_SIZE]
} Row;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer*, Statement*);
void execute_statement(Statement*);

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

#endif