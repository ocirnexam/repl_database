#include "meta_command.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
    if(strncmp(input_buffer->buffer, ".exit", input_buffer->buffer_length) == 0)
    {
        db_close(table);
        exit(EXIT_SUCCESS);
    }
    else if (strncmp(input_buffer->buffer, ".constants", input_buffer->buffer_length) == 0)
    {
        printf("Constants:\n");
        node_print_constants();
        return META_COMMAND_SUCCESS;
    }
    else if (strncmp(input_buffer->buffer, ".btree", input_buffer->buffer_length) == 0)
    {
        printf("BTree:\n");
        node_print_leaf(pager_get_page(table->pager, 0));
        return META_COMMAND_SUCCESS;
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}