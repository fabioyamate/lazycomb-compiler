require File.dirname(__FILE__) + '/lazycomb_compiler'

class Lazy
  def self.compile(source_file, output_file)
    file = File.new(source_file, 'r')
    lexer = Lexer.new(file)
    parser = Parser.new(lexer)
    parser.parse
    out = File.new(output_file, 'w')
    out << Semantic.code
    out.close
    file.close
  end
end

Lazy.compile ('samples/sample.lazy', 'bin/out.c')