require File.dirname(__FILE__) + '/spec_helper'
require 'semantic' 

describe Semantic do
  before(:each) do
    Semantic.reset_scope
  end
  
  it "should not reduce an empty tape" do
    reduction = Semantic.reduce
    reduction.should be_empty
  end
  
  it "should reduce SIII to II(II)" do
    Semantic.scope.concat([:s, :I, :I, :I])
    reduction = Semantic.reduce
    reduction.should == [:I, :I, :lpar, :I, :I, :rpar]
  end
  
  it "should reduce II to I" do
    Semantic.scope.concat([:I, :I])
    reduction = Semantic.reduce
    reduction.should == [:I]
  end
  
  it "should reduce KKI to K" do
    Semantic.scope.concat([:k, :k, :I])
    reduction = Semantic.reduce
    reduction.should == [:k]
  end
  
  it "should be able to differenciate inputs with scopes" do
    Semantic.scope << :s
    Semantic.scope.should include(:s)
    Semantic.new_scope
    Semantic.scope << :i
    Semantic.scope.should include(:i)
    Semantic.scope.should_not include(:s)
  end
  
  it "should concat reduced combinators when scopes are closed" do
    Semantic.scope << :s
    Semantic.scope.should include(:s)
    Semantic.new_scope
    Semantic.scope << :i
    Semantic.scope.should include(:i)
    Semantic.scope.should_not include(:s)
    Semantic.close_scope
    Semantic.scope.should include(:s, :i)
  end
  
  it "should not allow close global scope" do
    lambda {
      Semantic.close_scope
    }.should raise_error
  end
end