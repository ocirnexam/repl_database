#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "input_buffer/input_buffer.h"
#include "meta_command/meta_command.h"
#include "statement/statement.h"
#include "table/table.h"

void print_promt(void);
void read_input(InputBuffer*);
void close_input_buffer(InputBuffer*);

int main(int argc, char *argv[])
{
    Table* table = new_table();
    InputBuffer* input_buffer = new_input_buffer();
    while(true)
    {
        print_promt();
        read_input(input_buffer);
        if(input_buffer->buffer[0] == '.')
        {
            switch(do_meta_command(input_buffer))
            {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command: %s\n", input_buffer->buffer);
            }
        }
        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_SYNTAX_ERROR):
                    printf("Syntax error. Could not parse statement.\n");
                    continue;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

    switch(execute_statement(&statement, table))
    {
        case (EXECUTE_SUCCESS):
            printf("Executed!\n");
            break;
        case (EXECUTE_TABLE_FULL):
            printf("Error. Table full!\n");
            break;
    }
    }
}

void print_promt(void)
{
    printf("db > ");
}

void read_input(InputBuffer *input_buffer)
{
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if(bytes_read <= 0)
    {
        printf("Error reading input!\n");
        exit(EXIT_FAILURE);
    }

    //ignore trailing newlines
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}