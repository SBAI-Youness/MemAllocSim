#include "../include/algorithms/algorithms.h"
#include "../include/algorithms/non_contiguous/paging.h"
#include "../../include/common/ui.h"

static struct Algorithm algorithms[] = {
  // Contiguous algorithms
  {CONTIGUOUS, 1, "First Fit", NULL},  // To be implemented
  {CONTIGUOUS, 2, "Next Fit", NULL},   // To be implemented
  {CONTIGUOUS, 3, "Best Fit", NULL},   // To be implemented
  {CONTIGUOUS, 4, "Worst Fit", NULL},  // To be implemented

  // Non-contiguous algorithms
  {NON_CONTIGUOUS, 1, "Paging", (void (*)(void *))simulate_paging}, // Already implemented
  {NON_CONTIGUOUS, 2, "Segmentation", NULL},                        // To be implemented
  {NON_CONTIGUOUS, 3, "Segmented Paging", NULL},                    // To be implemented
};

// Number of algorithms
#define NUM_ALGORITHMS (sizeof(algorithms) / sizeof(algorithms[0]))

static int count_ready_algorithms(void) {
  int count = 0;
  for (int i = 0; i < NUM_ALGORITHMS; i++)
    if (algorithms[i].simulate != NULL)
      count++;

  return count;
}

void init_algorithms(void) {
  printf("\nInitializing memory allocation algorithms...\n");
  printf("----------------------------------------\n");

  // Check each algorithm's status
  for (int i = 0; i < NUM_ALGORITHMS; i++) {
    printf("%s algorithm (%s): ", 
            (algorithms[i].category == CONTIGUOUS)? "Contiguous" : "Non-Contiguous",
            algorithms[i].name);

    if (algorithms[i].simulate != NULL) 
      printf("Ready\n");
    else
      printf("Not implemented yet\n");
  }

  printf("----------------------------------------\n");
  printf("Total algorithms: %d\n", NUM_ALGORITHMS);
  printf("Ready algorithms: %d\n", count_ready_algorithms());
  printf("----------------------------------------\n\n");
}

void print_algorithm_menu(int category) {
  printf("\nAvailable %s Algorithms:\n", 
          (category == CONTIGUOUS) ? "Contiguous" : "Non-contiguous");
  printf("----------------------------------------\n");

  for (int i = 0; i < NUM_ALGORITHMS; i++)
    if (algorithms[i].category == category)
      printf("%d. %s\n", algorithms[i].type, algorithms[i].name);

  printf("----------------------------------------\n");
  printf("Choice: ");
}

int validate_paging_params(const struct PagingParams *params) {
  char error_msg[256];

  if (params == NULL) {
    print_error("Null parameters");
    return 0;
  }

  if (params->page_references == NULL) {
    print_error("Null page references array");
    return 0;
  }

  if (params->ref_count < MIN_PAGE_REFERENCES || params->ref_count > MAX_PAGE_REFERENCES) {
    snprintf(error_msg, sizeof(error_msg), 
                        "Invalid number of references. Must be between %d and %d",
                        MIN_PAGE_REFERENCES, MAX_PAGE_REFERENCES);
    print_error(error_msg);
    return 0;
  }

  if (params->frame_count < MIN_FRAMES || params->frame_count > MAX_FRAMES) {
    snprintf(error_msg, sizeof(error_msg),
                        "Invalid number of frames. Must be between %d and %d",
                         MIN_FRAMES, MAX_FRAMES);
    print_error(error_msg);
    return 0;
  }

  for (int i = 0; i < params->ref_count; i++) {
    if (params->page_references[i] < 0) {
      snprintf(error_msg, sizeof(error_msg),
                          "Invalid page reference at index %d: %d",
                          i, params->page_references[i]);
      print_error(error_msg);
      return 0;
    }
  }

  return 1;
}

void run_algorithm(int category, int type, void *params) {
  char error_msg[256];

  printf("\nDebug: Category=%d, Type=%d\n", category, type);

  for (int i = 0; i < NUM_ALGORITHMS; i++) {
    printf("Checking algorithm %d: category=%d, type=%d\n", 
            i, algorithms[i].category, algorithms[i].type);

    if ((algorithms[i].category == category) && (algorithms[i].type == type)) {
      if (algorithms[i].simulate != NULL) {
        if ((category == NON_CONTIGUOUS) && (type == PAGING)) {
          struct PagingParams *paging_params = (struct PagingParams *)params;

          if (!validate_paging_params(paging_params)) {
            print_error("Invalid paging parameters. Aborting simulation.");
            return;
          }

          simulate_paging(paging_params->page_references,
                          paging_params->ref_count,
                          paging_params->frame_count,
                          paging_params->algorithm_type);
        }
        else
          algorithms[i].simulate(params);
      }
      else {
        snprintf(error_msg, sizeof(error_msg),
                            "Algorithm %s is not yet implemented.",
                            algorithms[i].name);
        print_error(error_msg);
      }
      return;
    }
  }

  print_error("Invalid algorithm selection.");
}