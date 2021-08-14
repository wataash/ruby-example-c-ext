#include "example_ext.h"

VALUE rb_mExampleExt;

void
Init_example_ext(void)
{
  rb_mExampleExt = rb_define_module("ExampleExt");
}
