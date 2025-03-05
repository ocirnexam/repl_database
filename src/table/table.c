#include "table.h"

void* row_slot(Table* table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    if(page == NULL)
    {
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
}

Table* new_table(void)
{
    Table* table = (Table*) malloc(sizeof(Table));
    table->num_rows = 0;
    for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}

void free_table(Table* table)
{
    for (uint32_t i = 0; i < (table->num_rows / ROWS_PER_PAGE) + 1; i++)
    {
        free(table->pages[i]);
    }
    free(table);
}

void print_row(Row* row)
{
    printf("(%d, %s %s)\n", row->id, row->username, row->email);
}