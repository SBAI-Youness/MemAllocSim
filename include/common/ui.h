#pragma once

extern void print_header(const char *title);

extern void print_menu(const char *title, const char *options[], int num_options);

extern int get_valid_input(int min, int max);

extern void print_error(const char *message);

extern void print_success(const char *message);

extern void print_info(const char *message);