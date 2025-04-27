#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "../include/common/ui.h"
#include "../include/algorithms/algorithms.h"
#include "../include/algorithms/contiguous/first_fit.h"
#include "../include/algorithms/contiguous/next_fit.h"
#include "../include/algorithms/contiguous/best_fit.h"
#include "../include/algorithms/contiguous/worst_fit.h"
#include "../include/algorithms/non_contiguous/paging.h"
#include "../include/algorithms/non_contiguous/segmentation.h"
#include "../include/algorithms/non_contiguous/segmented_paging.h"

const char* MAIN_MENU_OPTIONS[] = {
  "Contiguous Memory Allocation",
  "Non-contiguous Memory Allocation",
  "Exit"
};

const char* CONTIGUOUS_OPTIONS[] = {
  "First Fit",
  "Next Fit",
  "Best Fit",
  "Worst Fit",
};

const char* NON_CONTIGUOUS_OPTIONS[] = {
  "Paging",
  "Segmentation",
  "Segmented Paging"
};

void handle_contiguous_menu(void) {
  int choice = get_valid_input(1, sizeof(CONTIGUOUS_OPTIONS) / sizeof(CONTIGUOUS_OPTIONS[0]));
  if (choice == -1)
    return;

  run_algorithm(CONTIGUOUS, choice, NULL);
}

void handle_non_contiguous_menu(void) {
  int choice = get_valid_input(1, sizeof(NON_CONTIGUOUS_OPTIONS) / sizeof(NON_CONTIGUOUS_OPTIONS[0]));
  if (choice == -1)
    return;

  struct PagingParams params = {0};

  print_info("Enter the number of page references");
  params.ref_count = get_valid_input(MIN_PAGE_REFERENCES, MAX_PAGE_REFERENCES);
  if (params.ref_count == -1)
    return;

  params.page_references = malloc(params.ref_count * sizeof(int));
  if (params.page_references == NULL) {
    print_error("Memory allocation failed");
    return;
  }

  print_info("Enter the reference sequence (separated by spaces)");
  for (int i = 0; i < params.ref_count; i++) {
    if (scanf("%d", &params.page_references[i]) != 1) {
      print_error("Invalid input. Please enter numbers only");
      free(params.page_references);
      return;
    }
  }
  // Clear the input buffer
  while (getchar() != '\n');

  print_info("Enter the number of frames");
  params.frame_count = get_valid_input(MIN_FRAMES, MAX_FRAMES);
  if (params.frame_count == -1) {
    free(params.page_references);
    return;
  }

  const char* REPLACEMENT_OPTIONS[] = {"FIFO", "LRU"};
  print_menu("Choose replacement algorithm", REPLACEMENT_OPTIONS, 2);
  params.algorithm_type = get_valid_input(1, 2);
  if (params.algorithm_type == -1) {
    free(params.page_references);
    return;
  }

  // Convert the user choice to the algorithm type
  params.algorithm_type = (params.algorithm_type == 1) ? FIFO : LRU;

  run_algorithm(NON_CONTIGUOUS, choice, &params);
  free(params.page_references);
}

int main(void) {
  // Initialize algorithms
  init_algorithms();

  int choice;
  do {
    print_menu(PROJECT_NAME, MAIN_MENU_OPTIONS, 
               sizeof(MAIN_MENU_OPTIONS) / sizeof(MAIN_MENU_OPTIONS[0]));

    choice = get_valid_input(1, sizeof(MAIN_MENU_OPTIONS) / sizeof(MAIN_MENU_OPTIONS[0]));
    if (choice == -1)
      continue;

    switch (choice) {
      case 1:
        print_menu("Contiguous Memory Allocation", CONTIGUOUS_OPTIONS, 
                          sizeof(CONTIGUOUS_OPTIONS) / sizeof(CONTIGUOUS_OPTIONS[0]));
        handle_contiguous_menu();
        break;

      case 2:
        print_menu("Non-contiguous Memory Allocation", NON_CONTIGUOUS_OPTIONS, 
                          sizeof(NON_CONTIGUOUS_OPTIONS) / sizeof(NON_CONTIGUOUS_OPTIONS[0]));
        handle_non_contiguous_menu();
        break;

      case 3:
        print_success("Goodbye!");
        break;

      default:
        print_error("Invalid choice. Please try again.");
    }
  } while (choice != 3);

  return EXIT_SUCCESS;
}