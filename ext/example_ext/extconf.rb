# /home/wsh/.rbenv/versions/2.7.1/lib/ruby/2.7.0/mkmf.rb

require "rbconfig"
if RbConfig::MAKEFILE_CONFIG["CFLAGS"].include?("-g -O2")
  fixed_CFLAGS = RbConfig::MAKEFILE_CONFIG["CFLAGS"].sub("-g -O2", "$(cflags)")
  puts("Fix CFLAGS: #{RbConfig::MAKEFILE_CONFIG["CFLAGS"]} -> #{fixed_CFLAGS}")
  RbConfig::MAKEFILE_CONFIG["CFLAGS"] = fixed_CFLAGS
end

require "mkmf"

# module MakeMakefile -> MakeMakefile.init_mkmf -> $objs = nil

CONFIG["optflags"] = "-O0"
CONFIG["debugflags"] = "-ggdb3"

$objs = [
  "example_ext.o",
  "sandbox.o",
]
$objs = nil

# MakeMakefile.create_makefile -> if not $objs -> $objs: ["example_ext.o", ...]
create_makefile("example_ext/example_ext")
