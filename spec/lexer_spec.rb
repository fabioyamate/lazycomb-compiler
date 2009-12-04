require File.dirname(__FILE__) + '/spec_helper'
require 'lexer' 

describe Lexer do
  xit "should tokenize a valid source file" do
    io = StringIO.new %q{
      i ` k ( i s * 0 ( ` 1 i ) ) 0 0 1 0 1 0
      SII(SII(S(S(KS)K)I))
      * i I
    }
    lexer = Lexer.new(io)
    lambda {
      token = lexer.next_token
      while token != :eof
        token = lexer.next_token
      end
    }.should_not raise_error
  end
  
  xit "should not tokenize an invalid source file" do
    io = StringIO.new "a b"
    lexer = Lexer.new(io)
    lambda {
      token = lexer.next_token
      while token != :eof
        token = lexer.next_token
      end
    }.should raise_error
  end
  
  xit "should differenciate i from I" do
    io = StringIO.new "i I"
    lexer = Lexer.new(io)
    lexer.next_token.should == :i
    lexer.next_token.should == :I
  end
end