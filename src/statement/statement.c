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
  void* node = pager_get_page(table->pager, table->root_page_num);
  uint32_t num_cells = (*node_leaf_num_cells(node));
  if (num_cells >= NODE_LEAF_MAX_CELLS)
  {
    return EXECUTE_TABLE_FULL;
  }
  Row* row_to_insert = &(statement->row_to_insert);
  uint32_t key_to_insert = row_to_insert->id;
  Cursor* cursor = cursor_table_find(table, key_to_insert);
  if(cursor->cell_num < num_cells)
  {
    uint32_t key_at_index = *node_leaf_key(node, cursor->cell_num);
    if(key_at_index == key_to_insert)
    {
      return EXECUTE_DUPLICATE_KEY;
    }
  }

  cursor_node_insert(cursor, row_to_insert->id, row_to_insert);
  free(cursor);

  row_to_insert->id = 0;
  memset(row_to_insert->username, 0, USERNAME_MAX_SIZE);
  memset(row_to_insert->email, 0, EMAIL_MAX_SIZE);
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
  Row row;
  Cursor* cursor = cursor_table_start(table);
  while(!(cursor->end_of_table))
  {
    deserialize_row(cursor_value(cursor), &row);
    print_row(&row);
    cursor_advance(cursor);
  }
  free(cursor);
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