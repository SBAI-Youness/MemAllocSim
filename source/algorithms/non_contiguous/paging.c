#include "../../../include/algorithms/non_contiguous/paging.h"
#include "../../../include/common/ui.h"
#include <unistd.h>
#include <windows.h>

void delay(int milliseconds) {
  #ifdef _WIN32
    Sleep(milliseconds);
  #else
    usleep(milliseconds * 1000);
  #endif
}

void wait_for_enter(void) {
  printf("Press Enter to continue...");
  fflush(stdout);
  while (getchar() != '\n');
}

void init_memory(struct Memory *mem, int frame_count) {
  if (mem == NULL || frame_count <= 0 || frame_count > MAX_FRAMES) {
    print_error("Invalid memory initialization parameters");
    return;
  }

  mem->frame_count = frame_count;
  mem->page_faults = 0;
  for (int i = 0; i < MAX_FRAMES; i++) {
    mem->frames[i].page_number = -1;
    mem->frames[i].last_used = -1;
    mem->frames[i].loaded_time = -1;
  }
}

int find_page_index(struct Memory *mem, int page_number) {
  if (mem == NULL)
    return -1;

  for (int i = 0; i < mem->frame_count; i++)
    if (mem->frames[i].page_number == page_number)
      return i;

  return -1;
}

int find_empty_frame(struct Memory *mem) {
  if (mem == NULL)
    return -1;

  for (int i = 0; i < mem->frame_count; i++)
    if (mem->frames[i].page_number == -1)
      return i;

  return -1;
}

int fifo_page_replacement(struct Memory *mem, int page_number, int current_time) {
  if (mem == NULL)
    return -1;

  int victim = 0;
  int oldest_time = mem->frames[0].loaded_time;

  for (int i = 1; i < mem->frame_count; i++) {
    if (mem->frames[i].loaded_time < oldest_time) {
      oldest_time = mem->frames[i].loaded_time;
      victim = i;
    }
  }

  mem->frames[victim].page_number = page_number;
  mem->frames[victim].loaded_time = current_time;
  mem->frames[victim].last_used = current_time;

  return victim;
}

int lru_page_replacement(struct Memory *mem, int page_number, int current_time) {
  if (mem == NULL)
    return -1;

  int victim = 0;
  int least_recent = mem->frames[0].last_used;

  for (int i = 1; i < mem->frame_count; i++) {
    if (mem->frames[i].last_used < least_recent) {
      least_recent = mem->frames[i].last_used;
      victim = i;
    }
  }

  mem->frames[victim].page_number = page_number;
  mem->frames[victim].last_used = current_time;
  mem->frames[victim].loaded_time = current_time;

  return victim;
}

void print_frame_state(const struct Memory *mem, int current_page, int hit, int current_time, int total_time) {
  printf("\n=== Current Memory State ===\n\n");

  printf("Current Page Reference: %d\n", current_page);
  printf("Frame Status:\n");
  printf("+--------+--------+-----------+----------+\n");
  printf("| Frame  | Page   | Last Used | Load Time|\n");
  printf("|        |        |           |          |\n");
  printf("+--------+--------+-----------+----------+\n");

  for (int i = 0; i < mem->frame_count; i++) {
    printf("|   %2d   |", i);
    if (mem->frames[i].page_number != -1) {
      printf("   %2d   |", mem->frames[i].page_number);
      printf("    %2d    |", mem->frames[i].last_used);
      printf("    %2d   |\n", mem->frames[i].loaded_time);
    }
    else
      printf("   -    |    -    |    -    |\n");
  }
  printf("+--------+--------+-----------+----------+\n");

  printf("\nResult: %s\n", hit ? "Page Hit (Page present in memory)" : "Page Fault (Page not present)");
  printf("Total Page Faults: %d\n", mem->page_faults);

  // Progress bar
  printf("\nProgress: [");
  int progress = (current_time * 20) / total_time;
  for (int i = 0; i < 20; i++)
    printf("%c", i < progress ? '=' : ' ');

  printf("] %d%%\n", (current_time * 100) / total_time);

  delay(2000);
}

void simulate_paging(int *page_references, int ref_count, int frame_count, int algorithm) {
  if (page_references == NULL || ref_count <= 0 || frame_count <= 0 || frame_count > MAX_FRAMES)
    return;

  struct Memory mem;
  init_memory(&mem, frame_count);

  printf("\n=== Paging Simulation ===\n\n");
  printf("Algorithm used: %s\n", (algorithm == FIFO) ? "FIFO (First In First Out)" : "LRU (Least Recently Used)");
  printf("Number of frames: %d\n", frame_count);
  printf("Number of page references: %d\n", ref_count);

  printf("\nPage reference sequence: ");
  for (int i = 0; i < ref_count; i++)
    printf("%d ", page_references[i]);

  printf("\n");

  printf("\nPress Enter to start simulation...");
  fflush(stdout);
  while (getchar() != '\n');

  for (int time = 0; time < ref_count; time++) {
    int page = page_references[time];
    int hit = 0;

    int index = find_page_index(&mem, page);
    if (index != -1) {
      hit = 1;
      mem.frames[index].last_used = time;
    }
    else {
      mem.page_faults++;
      
      int empty = find_empty_frame(&mem);
      if (empty != -1) {
        mem.frames[empty].page_number = page;
        mem.frames[empty].loaded_time = time;
        mem.frames[empty].last_used = time;
      }
      else {
        if (algorithm == FIFO) {
          fifo_page_replacement(&mem, page, time);
        }
        else if (algorithm == LRU) {
          lru_page_replacement(&mem, page, time);
        }
        else {
          print_error("Invalid algorithm selected");
          return;
        }
      }
    }

    print_frame_state(&mem, page, hit, time + 1, ref_count);
  }

  printf("\n=== Simulation Complete ===\n\n");
  printf("Final Statistics:\n");
  printf("Total page faults: %d\n", mem.page_faults);
  printf("Page fault rate: %.2f%%\n", (float)mem.page_faults / ref_count * 100);

  printf("\nDetailed Summary:\n");
  printf("+----------------------+------------+\n");
  printf("| Metric               | Value      |\n");
  printf("+----------------------+------------+\n");
  printf("| Total References     | %-10d |\n", ref_count);
  printf("| Page Faults          | %-10d |\n", mem.page_faults);
  printf("| Page Fault Rate      | %-10.2f%% |\n", (float)mem.page_faults / ref_count * 100);
  printf("| Algorithm Used       | %-10s |\n", (algorithm == FIFO) ? "FIFO" : "LRU");
  printf("+----------------------+------------+\n");

  printf("\nPress Enter to continue...");
  fflush(stdout);
  while (getchar() != '\n');
}