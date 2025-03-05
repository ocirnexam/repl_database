#include "statement.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if(strncmp(input_buffer->buffer, "insert", input_buffer->buffer_length) == 0)
    {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(
          input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
          &(statement->row_to_insert.username), &(statement->row_to_insert.email)
        );
        if (args_assigned < 3)
        {
          return PREPARE_SYNTAX_ERROR;
        }
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
  

void serialize_row(Row* source, void* destination)
{
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
  memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination)
{
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}