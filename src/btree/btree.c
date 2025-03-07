#include "btree.h"

uint32_t* node_leaf_num_cells(void* node)
{
    return node + NODE_LEAF_NUM_CELLS_OFFSET;
}

void* node_leaf_cell(void* node, uint32_t cell_num)
{
    return node + NODE_LEAF_HEADER_SIZE + (cell_num * NODE_LEAF_CELL_SIZE);
}

uint32_t* node_leaf_key(void*node, uint32_t cell_num)
{
    return node_leaf_cell(node, cell_num);
}

uint32_t* node_leaf_value(void* node, uint32_t cell_num)
{
    return node_leaf_cell(node, cell_num) + NODE_LEAF_KEY_SIZE;
}

void node_initialize_leaf(void* node)
{
    *node_leaf_num_cells(node) = 0;
}

void node_print_constants(void) {
    printf("ROW_SIZE: %d\n", ROW_SIZE);
    printf("COMMON_NODE_HEADER_SIZE: %d\n", NODE_COMMON_HEADER_SIZE);
    printf("LEAF_NODE_HEADER_SIZE: %d\n", NODE_LEAF_HEADER_SIZE);
    printf("LEAF_NODE_CELL_SIZE: %d\n", NODE_LEAF_CELL_SIZE);
    printf("LEAF_NODE_SPACE_FOR_CELLS: %d\n", NODE_LEAF_SPACE_FOR_CELLS);
    printf("LEAF_NODE_MAX_CELLS: %d\n", NODE_LEAF_MAX_CELLS);
}

void node_print_leaf(void* node)
{
    uint32_t num_cells = *node_leaf_num_cells(node);
    printf("leaf (size %d)\n", num_cells);
    for(uint32_t i = 0; i < num_cells; i++)
    {
        uint32_t key = *node_leaf_key(node, i);
        printf(" - %d : %d\n", i, key);
    }
}