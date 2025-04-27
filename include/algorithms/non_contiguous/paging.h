#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

#define FIFO 1
#define LRU 2

struct Page {
  int page_number;  // The page number
  int last_used;    // Time when the page was last used (for LRU)
  int loaded_time;  // Time when the page was loaded (for FIFO)
};

struct Memory {
  struct Page frames[MAX_FRAMES];  // Array of page frames
  int frame_count;                 // Total number of frames in use
  int page_faults;                 // Counter for page faults
};

// Initialize memory structure with empty frames
extern void init_memory(struct Memory *mem, int frame_count);

// Find the index of a page in memory frames, or return -1 if not found
extern int find_page_index(struct Memory *mem, int page_number);

// Find the index of an empty frame, or return -1 if none available
extern int find_empty_frame(struct Memory *mem);

// Replace a page using FIFO strategy
extern int fifo_page_replacement(struct Memory *mem, int page_number, int current_time);

// Replace a page using LRU strategy
extern int lru_page_replacement(struct Memory *mem, int page_number, int current_time);

// Print the current state of memory frames with detailed information
extern void simulate_paging(int *page_references, int ref_count, int frame_count, int algorithm);

// Print the current state of memory frames
extern void print_frame_state(const struct Memory *mem, int current_page, int hit, int current_time, int total_time);