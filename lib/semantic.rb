require File.dirname(__FILE__) + '/lazycomb_compiler'

class Semantic
  REDUCTIONS_TERMS_LENGTH = { :i => 2, :I => 2, :s => 4, :k => 3 }
  
  def self.reduce(list)
    return list unless REDUCTIONS_TERMS_LENGTH[list.first].eql? list.size
    
    case list.first
    when :s
      [list[1], list[3], :lpar, list[2], list[3], :rpar]
    when :i, :I
      [list.last]
    when :k
      [list[1]]
    end
  end
  
end