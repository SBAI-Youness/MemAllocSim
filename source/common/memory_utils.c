#include <stdlib.h>
#include "../include/common/memory_utils.h"

uint32_t align_to_page_size(uint32_t address, uint32_t page_size) {
    return (address + page_size - 1) & ~(page_size - 1);
}

uint32_t get_page_number(uint32_t address, uint32_t page_size) {
    return address / page_size;
}

uint32_t get_page_offset(uint32_t address, uint32_t page_size) {
    return address % page_size;
}

uint32_t get_physical_address(uint32_t page_number, uint32_t offset, uint32_t page_size) {
    return (page_number * page_size) + offset;
}

bool is_address_valid(uint32_t address, uint32_t total_memory_size) {
    return address < total_memory_size;
}

void* allocate_physical_memory(uint32_t size) {
    return malloc(size);
}

void free_physical_memory(void* ptr, uint32_t size) {
    free(ptr);
}
