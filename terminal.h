#ifndef TERMINAL_H
#define TERMINAL_H

void terminal_init();
char terminal_read();
void terminal_print(const char* data, ...);
void terminal_flush();
void terminal_set_cursor(int x, int y);
void terminal_grayscale(float grayscale);
void terminal_hide_cursor();
void terminal_clear();
void terminal_get_size(int* width, int* height);

#endif