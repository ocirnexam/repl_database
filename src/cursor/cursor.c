#include "cursor.h"

Cursor* cursor_table_start(Table* table)
{
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void* root_node = pager_get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *node_leaf_num_cells(root_node);
    cursor->end_of_table = (num_cells == 0);

    return cursor;
}

Cursor* cursor_table_end(Table* table)
{
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;

    void* root_node = pager_get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *node_leaf_num_cells(root_node);
    cursor->cell_num = num_cells;
    cursor->end_of_table = true;

    return cursor;
}

void* cursor_value(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* page = pager_get_page(cursor->table->pager, page_num);
    return node_leaf_value(page, cursor->cell_num);  
}

void cursor_advance(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* node = pager_get_page(cursor->table->pager, page_num);
    cursor->cell_num += 1;
    if (cursor->cell_num >= (*node_leaf_num_cells(node)))
    {
        cursor->end_of_table = true;
    }
}

void cursor_node_leaf_insert(Cursor* cursor, uint32_t key, Row* value)
{
    void* node = pager_get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *node_leaf_num_cells(node);
    if(num_cells >= NODE_LEAF_MAX_CELLS)
    {
        printf("Need to implement node splitting!\n");
        exit(EXIT_FAILURE);
    }
    if(cursor->cell_num < num_cells)
    {
        for(uint32_t i = num_cells; i > cursor->cell_num; i--)
        {
            memcpy(node_leaf_cell(node, i), node_leaf_cell(node, i - 1), NODE_LEAF_CELL_SIZE);
        }
    }
    *node_leaf_num_cells(node) += 1;
    *node_leaf_key(node, cursor->cell_num) = key;
    serialize_row(value, node_leaf_value(node, cursor->cell_num));
}


Table* db_open(const char* filename)
{
    Pager* pager = pager_open(filename);
    if(pager == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Table* table = (Table*) malloc(sizeof(Table));
    table->pager = pager;
    table->root_page_num = 0;

    if(pager->num_pages == 0)
    {
        // New database file
        void* root_node = pager_get_page(table->pager, 0);
        node_initialize_leaf(root_node);
    }
    return table;
}

void db_close(Table* table)
{
    Pager* pager = table->pager;

    for(uint32_t i = 0; i < pager->num_pages; i++)
    {
        if(pager->pages[i] == NULL)
        {
            continue;
        }
        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    int result = close(pager->file_descriptor);
    if(result == -1)
    {
        printf("Error closing file!\n");
        exit(EXIT_FAILURE);
    }
    for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        void* page = pager->pages[i];
        if(page)
        {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}