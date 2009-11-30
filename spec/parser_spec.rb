require File.dirname(__FILE__) + '/spec_helper'
require 'parser' 

describe Parser do
  it "should recognize a valid expr" do
    lexer = Lexer.new('valid.lazy')
    parser = Parser.new(lexer)
    parser.parse.should be_true
  end
  
  it "should recognize unlambda implementation" do
    lexer = Lexer.new('unlambda.lazy')
    parser = Parser.new(lexer)
    parser.parse.should be_true
  end
  
  it "should recognize jot implementation" do
    lexer = Lexer.new('jot.lazy')
    parser = Parser.new(lexer)
    parser.parse.should be_true
  end
end