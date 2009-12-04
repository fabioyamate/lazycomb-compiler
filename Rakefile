require 'rake/clean'
require 'lib/lazycomb_compiler'
CLEAN.include('*.o')

ARGS = "-std=c99 -Wall -O2 -g"

#####################
#   Compilations   ##
#####################

desc "Compile Lazy-K to VM in C"
task :compile, :file do |t, args|
  Lazy.compile(args.file)
end

desc "Compile code to VM"
task :vm do
  sh "gcc vm/dlist.c vm/dqueue.c vm/ski.c vm/lazy.c -o bin/lazy"
  puts "\nThe code was compiled with success."
end