#include "meta_command.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
    if(strncmp(input_buffer->buffer, ".exit", input_buffer->buffer_length) == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}