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
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteResult;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer*, Statement*);
PrepareResult prepare_insert(InputBuffer*, Statement*);
ExecuteResult execute_statement(Statement*, Table*);
ExecuteResult execute_insert(Statement*, Table*);
ExecuteResult execute_select(Statement*, Table*);

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

#endif