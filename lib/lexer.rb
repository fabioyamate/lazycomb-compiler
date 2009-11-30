require File.dirname(__FILE__) + '/lazycomb_compiler'

class Lexer
  def initialize(file_path)
    @source_stream = File.new(file_path, 'r')
    @column = 1
    @line = 1
  end
  
  def tokenize(code)
    case code
    when /i/
      return :i
    when /I/
      return :I
    when /k/i
      return :k
    when /s/i
      return :s
    when /\(/
      return :lpar
    when /\)/
      return :rpar
    when /`/
      return :apply
    when /\*/
      return :output
    when /0/
      return :zero
    when /1/
      return :one
    when nil
      return :eof
    else
      raise "Invalid token at line #{@line} and column #{@column}"
    end
  end
  
  def peek
    next_char = @source_stream.getc    
    if next_char != nil
      @source_stream.ungetc(next_char)
      next_char = next_char.chr
    end
    return tokenize(next_char)
  end

  def next_token
    consume
    # p "token consumed #{@current_char}"
    return tokenize(@current_char)
  end

  protected
  def consume
    @current_char = @source_stream.getc
    @current_char = @current_char.chr if @current_char != nil
    
    @column += 1

    if @current_char == '\n'
      @column = 1
      @line  += 1
    end

    # This line should be here because of possible tail recursion optimization
    consume if @current_char =~ /\r|\s/
  end
end