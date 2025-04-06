#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/memory_block.h"
#include "../common/memory_utils.h"

typedef struct {
    uint32_t total_memory_size;
    uint32_t page_size;
    uint32_t total_pages;
    uint32_t total_frames;
    PageTable* page_table;
    MemoryBlock* physical_memory;
    uint32_t* free_frames;
    uint32_t free_frames_count;
} PagingSystem;

PagingSystem* paging_init(uint32_t total_memory_size, uint32_t page_size);
void paging_destroy(PagingSystem* system);

bool paging_allocate(PagingSystem* system, uint32_t size, uint32_t* virtual_address);
bool paging_deallocate(PagingSystem* system, uint32_t virtual_address);
bool paging_read(PagingSystem* system, uint32_t virtual_address, void* buffer, uint32_t size);
bool paging_write(PagingSystem* system, uint32_t virtual_address, const void* data, uint32_t size);

uint32_t paging_get_physical_address(PagingSystem* system, uint32_t virtual_address);
bool paging_handle_page_fault(PagingSystem* system, uint32_t virtual_address);

#endif // PAGING_H
