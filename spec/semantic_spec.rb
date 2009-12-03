require File.dirname(__FILE__) + '/spec_helper'
require 'semantic' 

describe Semantic do
  it "should not reduce an empty tape" do
    reduction = Semantic.reduce([])
    reduction.should be_empty
  end
  
  it "should reduce SIII to II(II)" do
    reduction = Semantic.reduce([:s, :I, :I, :I])
    reduction.should == [:I, :I, :lpar, :I, :I, :rpar]
  end
  
  it "should reduce II to I" do
    reduction = Semantic.reduce([:I, :I])
    reduction.should == [:I]
  end
  
  it "should reduce KKI to K" do
    reduction = Semantic.reduce([:k, :k, :I])
    reduction.should == [:k]
  end
end