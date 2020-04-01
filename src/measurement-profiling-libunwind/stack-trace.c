#include <stdio.h>
#include <stdlib.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>


#define DEPTH 32


void print_stack () {
  unw_context_t context;
  unw_cursor_t cursor;
  unw_word_t ip;
  unw_word_t sp;
  char name [256];
  unw_word_t offset;

  unw_getcontext (&context);
  unw_init_local (&cursor, &context);

  int depth = 0;
  while (unw_step (&cursor) > 0) {
    unw_get_reg (&cursor, UNW_REG_IP, &ip);
    unw_get_reg (&cursor, UNW_REG_SP, &sp);
    unw_get_proc_name (&cursor, name, sizeof (name), &offset);
    for (int space = 0 ; space < depth ; space ++) printf (" ");
    printf ("%s+%lx IP %lx SP %lx\n", name, offset, ip, sp);
    depth ++;
  }
}


void function_0 (int);
void function_1 (int);
void function_2 (int);
void function_3 (int);

#define define_function(N) \
void function_##N (int depth) { \
  if (depth == 0) { \
    print_stack (); \
  } else { \
    switch (rand () % 4) { \
      case 0: function_0 (depth - 1); break; \
      case 1: function_1 (depth - 1); break; \
      case 2: function_2 (depth - 1); break; \
      case 3: function_3 (depth - 1); break; \
    } \
  } \
}

define_function (0)
define_function (1)
define_function (2)
define_function (3)


int main () {
  function_0 (DEPTH);
  return 0;
}
