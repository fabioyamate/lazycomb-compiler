require File.dirname(__FILE__) + '/spec_helper'
require 'lexer' 

describe Lexer do
  it "should tokenize a valid source file" do
    lexer = Lexer.new('valid.lazy')
    lambda {
      token = lexer.next_token
      while token != :eof
        token = lexer.next_token
      end
    }.should_not raise_error
  end
  
  it "should not tokenize an invalid source file" do
    lexer = Lexer.new('invalid.lazy')
    lambda {
      token = lexer.next_token
      while token != :eof
        token = lexer.next_token
      end
    }.should raise_error
  end
end