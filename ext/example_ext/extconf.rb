require "rbconfig"
if RbConfig::MAKEFILE_CONFIG["CFLAGS"].include?("-g -O2")
  fixed_CFLAGS = RbConfig::MAKEFILE_CONFIG["CFLAGS"].sub("-g -O2", "$(cflags)")
  puts("Fix CFLAGS: #{RbConfig::MAKEFILE_CONFIG["CFLAGS"]} -> #{fixed_CFLAGS}")
  RbConfig::MAKEFILE_CONFIG["CFLAGS"] = fixed_CFLAGS
end

require "mkmf"

CONFIG["optflags"] = "-O0"
CONFIG["debugflags"] = "-ggdb3"

create_makefile("example_ext/example_ext")
