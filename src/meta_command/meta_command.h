#ifndef METACOMMAND_H
#define METACOMMAND_H

#include <string.h>
#include "../input_buffer/input_buffer.h"
#include "../table/table.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


MetaCommandResult do_meta_command(InputBuffer*, Table*);

#endif