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