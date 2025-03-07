#ifndef BTREE_H
#define BTREE_H

#include <stdint.h>
#include <string.h>
#include "../row/row.h"
#include "../utils/global_defines.h"

typedef enum {
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

/*
 * Common Node Header Layout
 */
#define NODE_TYPE_SIZE             ((uint32_t)sizeof(uint8_t))
#define NODE_TYPE_OFFSET           ((uint32_t)0)
#define NODE_IS_ROOT_SIZE          ((uint32_t)sizeof(uint8_t))
#define NODE_IS_ROOT_OFFSET        ((uint32_t)NODE_TYPE_SIZE)
#define NODE_PARENT_POINTER_SIZE   ((uint32_t)sizeof(uint32_t))
#define NODE_PARENT_POINTER_OFFSET ((uint32_t)(NODE_IS_ROOT_OFFSET + NODE_IS_ROOT_SIZE))
#define NODE_COMMON_HEADER_SIZE    ((uint8_t)(NODE_TYPE_SIZE + NODE_IS_ROOT_SIZE + NODE_PARENT_POINTER_SIZE))

/*
 * Leaf Node Header Layout
 */
#define NODE_LEAF_NUM_CELLS_SIZE   ((uint32_t)sizeof(uint32_t))
#define NODE_LEAF_NUM_CELLS_OFFSET ((uint32_t)NODE_COMMON_HEADER_SIZE)
#define NODE_LEAF_HEADER_SIZE      ((uint32_t)(NODE_COMMON_HEADER_SIZE + NODE_LEAF_NUM_CELLS_SIZE))

/*
 * Leaf Node Body Layout
 */
#define NODE_LEAF_KEY_SIZE        ((uint32_t)sizeof(uint32_t))
#define NODE_LEAF_KEY_OFFSET      ((uint32_t)0)
#define NODE_LEAF_VALUE_SIZE      ((uint32_t)ROW_SIZE)
#define NODE_LEAF_VALUE_OFFSET    ((uint32_t)(NODE_LEAF_KEY_OFFSET + NODE_LEAF_KEY_SIZE))
#define NODE_LEAF_CELL_SIZE       ((uint32_t)(NODE_LEAF_KEY_SIZE + NODE_LEAF_VALUE_SIZE))
#define NODE_LEAF_SPACE_FOR_CELLS ((uint32_t)PAGE_SIZE - NODE_LEAF_HEADER_SIZE)
#define NODE_LEAF_MAX_CELLS       ((uint32_t)(NODE_LEAF_SPACE_FOR_CELLS / NODE_LEAF_CELL_SIZE))

void node_print_constants(void);

/*
 * Accessing leaf node fields
 */
uint32_t* node_leaf_num_cells(void* node);
void* node_leaf_cell(void* node, uint32_t cell_num);
uint32_t* node_leaf_key(void* node, uint32_t cell_num);
uint32_t* node_leaf_value(void* node, uint32_t cell_num);
void node_initialize_leaf(void* node);
void node_print_leaf(void* node);

NodeType node_get_type(void*);
void node_set_type(void*, NodeType);

#endif