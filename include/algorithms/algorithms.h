#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGE_REFERENCES 100
#define MIN_PAGE_REFERENCES 1

#define MAX_FRAMES 10
#define MIN_FRAMES 1

enum ALGORITHM_CATEGORY {
  CONTIGUOUS = 1,
  NON_CONTIGUOUS,
};

enum CONTIGUOUS_ALGORITHMS {
  FIRST_FIT = 1,
  NEXT_FIT,
  BEST_FIT,
  WORST_FIT,
};

enum NON_CONTIGUOUS_ALGORITHMS {
  PAGING = 1,
  SEGMENTATION,
  SEGMENTED_PAGING,
};

struct PagingParams {
  int *page_references;
  int ref_count;
  int frame_count;
  int algorithm_type;  // FIFO or LRU
};

struct Algorithm {
  int category;                    // CONTIGUOUS or NON_CONTIGUOUS 
  int type;                        // Specific algorithm type
  const char *name;                // Algorithm name
  void (*simulate)(void *params);  // Simulation function
};

extern void init_algorithms(void);

extern void print_algorithm_menu(int category);

extern int validate_paging_params(const struct PagingParams *params);

extern void run_algorithm(int category, int type, void *params);