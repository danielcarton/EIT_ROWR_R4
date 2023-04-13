#include <terminal.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUFFER_SIZE (1024 * 1024)

static char buffer[BUFFER_SIZE];
static int buffer_size;
static int width, height;

static struct termios saved_terminal;

void terminal_print(const char* data, ...) {
  va_list arguments;
  va_start(arguments, data);
  buffer_size += vsnprintf(buffer + buffer_size, BUFFER_SIZE - buffer_size, data, arguments);
}

void terminal_flush() {
  printf("%.*s", buffer_size, buffer);
  buffer_size = 0;
}

void terminal_set_cursor(int x, int y) {
  terminal_print("\33[%d;%dH", y + 1, 2 * x + 1);
}

void terminal_grayscale(float grayscale) {
  terminal_print("\033[38;5;%dm", 232 + (int)(grayscale * 23));
}

void terminal_hide_cursor() {
  terminal_print("\033[?25l");
}

void terminal_clear() {
  terminal_print("\33[2J");
}

static void get_cursor(int* x, int* y) {
  char data[32];
  int size = 0;

  terminal_print("\x1b[6n");
  terminal_flush();

  while (size < sizeof(data)) {
    read(STDIN_FILENO, &data[size], 1);
    if (data[size] == 'R') break;
    size++;
  }

  data[size] = 0;

  assert(data[0] == '\x1b' && data[1] == '[');
  assert(sscanf(&data[2], "%d;%d", y, x) == 2);
}

static void update_terminal_size() {
  int x, y;
  get_cursor(&x, &y);

  terminal_set_cursor(500, 500);
  terminal_flush();

  get_cursor(&width, &height);

  terminal_set_cursor(x, y);
  terminal_flush();
}

void terminal_get_size(int* w, int* h) {
  *w = width;
  *h = height;
}

static void resize_event() {
  update_terminal_size();
}

static void terminal_deinit() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_terminal);
}

void terminal_init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  tcgetattr(STDIN_FILENO, &saved_terminal);
  atexit(terminal_deinit);

  struct termios terminal = saved_terminal;

  terminal.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON);
  terminal.c_lflag &= ~(ICANON | ECHO);
  terminal.c_oflag &= ~(OPOST);
  terminal.c_cc[VMIN] = 0;
  terminal.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
  signal(SIGWINCH, (void* )resize_event);

  terminal_clear();
  terminal_hide_cursor();
  terminal_flush();
  update_terminal_size();
}

char terminal_read() {
  char keys[64];
  int size = read(STDIN_FILENO, keys, sizeof(keys));
  return size ? keys[0] : 0;
}