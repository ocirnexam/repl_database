#include "statement.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if(strncmp(input_buffer->buffer, "insert", 6) == 0)
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

ExecuteResult execute_insert(Statement* statement, Table* table)
{
  if (table->num_rows >= TABLE_MAX_ROWS)
  {
    return EXECUTE_TABLE_FULL;
  }
  Row* row_to_insert = &(statement->row_to_insert);
  serialize_row(row_to_insert, row_slot(table, table->num_rows));
  table->num_rows += 1;
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
  Row row;
  for (uint32_t i = 0; i < table->num_rows; i++)
  {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      return execute_insert(statement, table);
      break;
    case (STATEMENT_SELECT):
      return execute_select(statement, table);
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