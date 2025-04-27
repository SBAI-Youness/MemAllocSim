#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../include/common/ui.h"

void print_header(const char *title) {
  printf("\n=== %s ===\n", title);
}

void print_menu(const char *title, const char *options[], int num_options) {
  print_header(title);
  for (int i = 0; i < num_options; i++)
    printf("%d. %s\n", i + 1, options[i]);

  printf("Choice: ");
}

int get_valid_input(int min, int max) {
  int choice;
  char input[100];

  while (true) {
    if (fgets(input, sizeof(input), stdin) == NULL)
      return -1;

    if (sscanf(input, "%d", &choice) != 1) {
      printf("Invalid input. Please enter a number.\n");
      continue;
    }

    if (choice < min || choice > max) {
      printf("Invalid choice. Please enter a number between %d and %d.\n", min, max);
      continue;
    }

    return choice;
  }
}

void print_error(const char *message) {
  printf("\n[ERROR] %s\n", message);
}

void print_success(const char *message) {
  printf("\n[SUCCESS] %s\n", message);
}

void print_info(const char *message) {
  printf("\n[INFO] %s\n", message);
}