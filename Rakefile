require "bundler/gem_tasks"
require "rake/extensiontask"

task :build => :compile

Rake::ExtensionTask.new("example_ext") do |ext|
  ext.lib_dir = "lib/example_ext"
end

task :default => [:clobber, :compile, :spec]
