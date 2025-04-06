#include <stdlib.h>
#include <string.h>
#include "../include/common/memory_block.h"

MemoryBlock* create_memory_block(uint32_t base_address, uint32_t size) {
    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    if (!block) return NULL;

    block->base_address = base_address;
    block->size = size;
    block->is_allocated = false;
    block->data = malloc(size);
    if (!block->data) {
        free(block);
        return NULL;
    }
    memset(block->data, 0, size);
    return block;
}

void destroy_memory_block(MemoryBlock* block) {
    if (block) {
        free(block->data);
        free(block);
    }
}

PageTable* create_page_table(uint32_t total_pages, uint32_t page_size) {
    PageTable* table = (PageTable*)malloc(sizeof(PageTable));
    if (!table) return NULL;

    table->total_pages = total_pages;
    table->page_size = page_size;
    table->entries = (PageTableEntry*)calloc(total_pages, sizeof(PageTableEntry));
    if (!table->entries) {
        free(table);
        return NULL;
    }

    for (uint32_t i = 0; i < total_pages; i++) {
        table->entries[i].page_number = i;
        table->entries[i].frame_number = 0;
        table->entries[i].is_valid = false;
        table->entries[i].is_dirty = false;
        table->entries[i].last_access_time = 0;
    }

    return table;
}

void destroy_page_table(PageTable* table) {
    if (table) {
        free(table->entries);
        free(table);
    }
}
