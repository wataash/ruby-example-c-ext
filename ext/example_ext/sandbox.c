// SPDX-License-Identifier: Apache-2.0

// cd /home/wsh/qrb/ruby-example-c-ext/
// bundle exec rake install && bundle exec ruby -e 'require "example_ext"; ExampleExt.sandbox'

#include <signal.h> // put raise(SIGSTOP); to attach-debugging
#include <stdio.h>

#include <ruby.h>

#include "sandbox.h"

static void examples(void);

VALUE
sandbox(VALUE obj)
{
  printf("sandbox\n");

  examples();

  return Qnil;
}

// -----------------------------------------------------------------------------
// examples

// https://ruby-doc.org/core-2.7.4/doc/extension_ja_rdoc.html
// https://docs.ruby-lang.org/en/2.4.0/extension_ja_rdoc.html

static void examples_ruby(void);
static void examples_array(void);
static void examples_error(void);
static void examples_object(void);
static void examples_string(void);
static void examples_vm_eval(void);

static void
examples(void)
{
  // raise(SIGSTOP);

  examples_ruby();
  examples_array();
  examples_error();
  examples_object();
  examples_string();
  examples_vm_eval();

  // TODO: IDまたはシンボル 以降

  // draft
}

// /home/wsh/qc/ruby/ruby.h
static void
examples_ruby(void)
{
  VALUE v_nil = Qnil; // Quick nil?

  // integer
  // https://ruby-doc.org/core-2.7.4/doc/extension_ja_rdoc.html CのデータをVALUEに変換する
  {
    int i;
    long l;
    long long ll;
    unsigned int u;
    unsigned long ul;
    unsigned long long ull;
    VALUE num = INT2NUM(INT_MAX); // i, l, ll -> 2147483647
    // VALUE num = INT2NUM(INT_MAX + 1L); // i, l, ll -> -2147483648; BIGNUM になっていない？？
    i = NUM2INT(num); // ruby.h rb_num2int_inline()
    l = NUM2LONG(num); // ruby.h rb_num2long_inline()
    ll = NUM2LL(num); // ruby.h rb_num2ll_inline()
    (void)i, l, ll, u, ul, ull;
    asm("nop");
  }

  // print
  {
    printf("VALUE of nil: %"PRIdVALUE"\n", Qnil); // VALUE of nil: 8
  }

  // type
  {
    unsigned int bool_val;
    bool_val = FIXNUM_P(v_nil);
    bool_val = NIL_P(v_nil);
    (void)bool_val;

    // rb_type()
    switch (TYPE(v_nil)) {
      case T_NONE: printf("T_NONE: when?\n"); break;
      case T_NIL: printf("T_NIL: nil\n"); break;
      case T_OBJECT: printf("T_OBJECT: when?\n"); break;
      case T_CLASS: printf("T_CLASS: when?\n"); break;
      case T_ICLASS: printf("T_ICLASS: when?\n"); break;
      case T_MODULE: printf("T_MODULE: when?\n"); break;
      case T_FLOAT: printf("T_FLOAT: when?\n"); break;
      case T_STRING: printf("T_STRING: when?\n"); break;
      case T_REGEXP: printf("T_REGEXP: when?\n"); break;
      case T_ARRAY: printf("T_ARRAY: when?\n"); break;
      case T_HASH: printf("T_HASH: when?\n"); break;
      case T_STRUCT: printf("T_STRUCT: when?\n"); break;
      case T_BIGNUM: printf("T_BIGNUM: when?\n"); break;
      case T_FILE: printf("T_FILE: when?\n"); break;
      case T_FIXNUM: printf("T_FIXNUM: when?\n"); break;
      case T_TRUE: printf("T_TRUE: when?\n"); break;
      case T_FALSE: printf("T_FALSE: when?\n"); break;
      case T_DATA: printf("T_DATA: when?\n"); break;
      case T_MATCH: printf("T_MATCH: when?\n"); break;
      case T_SYMBOL: printf("T_SYMBOL: when?\n"); break;
      case T_RATIONAL: printf("T_RATIONAL: when?\n"); break;
      case T_COMPLEX: printf("T_COMPLEX: when?\n"); break;
      case T_IMEMO: printf("T_IMEMO: when?\n"); break;
      case T_UNDEF: printf("T_UNDEF: when?\n"); break;
      case T_NODE: printf("T_NODE: when?\n"); break;
      case T_ZOMBIE: printf("T_ZOMBIE: when?\n"); break;
      case T_MOVED: printf("T_MOVED: when?\n"); break;
      case T_MASK: printf("T_MASK: when?\n"); break;
      default:
        rb_bug("BUG: unknown BUILTIN_TYPE of v_nil: %d", BUILTIN_TYPE(v_nil)); // -e:1: [BUG] unknown BUILTIN_TYPE of v_nil: 9999
        /* NOTREACHED */
    }
    // or:
    if (!SPECIAL_CONST_P(v_nil)) {
      switch (BUILTIN_TYPE(v_nil)) {
        case T_NONE: printf("T_NONE: when?\n"); break;
        default:
          break;
      }
    }
  }

  asm("nop");
}

// /home/wsh/qc/ruby/array.c
// https://ruby-doc.org/core-2.7.4/doc/extension_ja_rdoc.html 配列に対する関数
static void
examples_array(void)
{
  (void)rb_ary_new;
  (void)rb_ary_new_capa;
  (void)rb_ary_new_from_args;
  (void)rb_ary_new_from_values;
  (void)rb_ary_to_ary; // Object#to_ary
  (void)rb_ary_aref; // Array#[]
  (void)rb_ary_entry; // ary[offset]
  (void)rb_ary_store; // ary[offset] = obj
  (void)rb_ary_subseq; // ary[beg, len]
  (void)rb_ary_push; // ary.push
  (void)rb_ary_pop; // ary.pop
  (void)rb_ary_shift; // ary.shift
  (void)rb_ary_unshift; // ary.unshift
  (void)rb_ary_cat;
}

// /home/wsh/qc/ruby/error.c
static void
examples_error(void)
{
  Check_Type(Qnil, T_NIL);
  if (0)
    Check_Type(Qnil, T_STRING); // -e:1:in `examples': wrong argument type nil (expected String) (TypeError)

  if (0) {
    rb_raise(rb_eArgError, "invalid argument"); // -e:1:in `examples': invalid argument (ArgumentError)
    (void)rb_raise;
    (void)rb_eException;
    (void)rb_eStandardError;
    (void)rb_eInterrupt;
    (void)rb_eArgError;
    (void)rb_eRuntimeError;
    (void)rb_eTypeError;
  }
}

// /home/wsh/qc/ruby/object.c
static void
examples_object(void)
{
  VALUE tmp = rb_inspect(Qnil);
  (void)tmp;
}

// /home/wsh/qc/ruby/string.c
// https://ruby-doc.org/core-2.7.4/doc/extension_ja_rdoc.html
//   VALUEをCのデータに変換する
//   文字列に対する関数
static void
examples_string(void)
{
  VALUE s;
  const char *cp;

  s = rb_str_new("xxx", strlen("xxx")); // string.c rb_str_new_static() -> str_new_static()
  s = rb_str_new_cstr("xxx"); // same
  s = rb_str_new("xxx", sizeof("xxx") - 1);
  s = rb_str_new_literal("xxx"); // same
  s = rb_sprintf("s: id:%"PRIdVALUE" str:%"PRIsVALUE, s, s); // snprintf.c rb_sprintf(); StringValueCStr(s): "s: id:94668869585480 str:xxx"
  // rb_str_cat_cstr;
  (void)rb_str_catf;
  // rb_utf8_str_new_cstr;
  // rb_utf8_str_new_literal;
  (void)rb_str_resize;

  s = rb_str_new_literal("xxx");
  s = StringValue(s); // string.c rb_string_value() (may call rb_str_to_str())
  cp = StringValuePtr(s); // rb_string_value() + RSTRING_PTR(); "xxx"
  cp = StringValueCStr(s); // rb_string_value() + str_null_check() (calls RSTRING_PTR()); "xxx"
  // とにかく StringValueCStr() を使っておけば良さそう
  (void)cp;

  long len = RSTRING_LEN(s); // これは使わず
  size_t len2 = strlen(StringValueCStr(s)); // こっちでいいかな
  (void)len, len2;

  asm("nop");
}

// /home/wsh/qc/ruby/vm_eval.c Rubyのプログラムをevalする
static void
examples_vm_eval(void)
{
  VALUE v = rb_eval_string("'xxx' * 3"); // vm_eval.c rb_eval_string()
  const char *cp = StringValueCStr(v); // "xxxxxxxxx"
  (void)cp;

  // v = rb_eval_string("nil * 3"); // eval:1:in `<main>': undefined method `*' for nil:NilClass (NoMethodError)

  int pstate;
  v = rb_eval_string_protect("nil * 3", &pstate); // 8, pstate: 6
  v = rb_sprintf("%"PRIsVALUE, v);
  cp = StringValueCStr(v); // ""
  (void)cp;

  // TODO: IDまたはシンボル
}
