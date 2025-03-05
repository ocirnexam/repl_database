#ifndef STATEMENT_H
#define STATEMENT_H

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../input_buffer/input_buffer.h"
#include "../table/table.h"

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
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