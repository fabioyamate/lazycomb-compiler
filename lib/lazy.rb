require File.dirname(__FILE__) + '/lazycomb_compiler'

class Lazy
  def self.compile(source_file)
    file = File.new(source_file, 'r')
    lexer = Lexer.new(file)
    parser = Parser.new(lexer)
    parser.parse
    out = File.new('vm/lazy.c', 'w')
    out << Semantic.code
    out.close
    file.close
  end
end