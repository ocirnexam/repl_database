#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <stdlib.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    size_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer(void);

#endif