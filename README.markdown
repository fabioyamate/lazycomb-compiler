LazyComb Compiler
-----------------

A LazyComb compiler using Stack Structured Automata.

[1] http://homepages.cwi.nl/~tromp/cl/lazy-k.html

[2] http://esoteric.sange.fi/essie2/download/lazy-k/lazier.scm


How to build an run
-------------------
We are building the project with [Rake](http://rake.rubyforge.org/). So, if you
still don't have it, go install ruby and rake. Now that you have ruby and rake installed, let's go to the next step.

In order to compile a lazy-k program, you can use one of our samples inside
samples/ or write your own program. Let me give you an example of how to compile
a lazy-k program: `rake compile[samples/sample.lazy]`.

After compiling from lazy-k to C, you will need to compile the C code now. In 
order to do this, just do `rake vm`. This rake task will generate a binary file,
called lazy, to run it, just do `./lazy`.

