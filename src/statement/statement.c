#include "statement.h"

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement)
{
  statement->type = STATEMENT_INSERT;

  char* keyword = strtok(input_buffer->buffer, " ");
  char* id_string = strtok(NULL, " ");
  char* username = strtok(NULL, " ");
  char* email = strtok(NULL, " ");

  if (id_string == NULL || username == NULL || email == NULL)
  {
    return PREPARE_SYNTAX_ERROR;
  }
  int id = atoi(id_string);
  if (strlen(username) > USERNAME_MAX_SIZE || strlen(email) > EMAIL_MAX_SIZE)
  {
    return PREPARE_STRING_TOO_LONG;
  }
  if (id < 0)
  {
    return PREPARE_NEGATIVE_ID;
  }
  statement->row_to_insert.id = id;
  strncpy(statement->row_to_insert.username, username, strlen(username));
  strncpy(statement->row_to_insert.email, email, strlen(email));

  return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if(strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        return prepare_insert(input_buffer, statement);
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
  row_to_insert->id = 0;
  memset(row_to_insert->username, 0, USERNAME_MAX_SIZE);
  memset(row_to_insert->email, 0, EMAIL_MAX_SIZE);
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