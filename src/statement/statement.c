#include "statement.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if(strncmp(input_buffer->buffer, "insert", input_buffer->buffer_length) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    else if(strncmp(input_buffer->buffer, "select", input_buffer->buffer_length) == 0) 
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
      case (STATEMENT_INSERT):
        printf("This is where we would do an insert.\n");
        break;
      case (STATEMENT_SELECT):
        printf("This is where we would do a select.\n");
        break;
    }
  }
  