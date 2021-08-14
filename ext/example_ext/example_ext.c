#include "example_ext.h"

VALUE rb_mExampleExt;

static VALUE
example_hello(VALUE obj)
{
  printf("hello\n");

  return Qnil;
}

void
Init_example_ext(void)
{
  rb_mExampleExt = rb_define_module("ExampleExt");

  rb_define_module_function(rb_mExampleExt, "hello", example_hello, 0);
}
