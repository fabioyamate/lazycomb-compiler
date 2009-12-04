require File.dirname(__FILE__) + '/lazycomb_compiler'

class Parser
  FIRST_EXPR = [ :i, :I, :s, :k, :lpar, :apply, :output, :zero, :one ]
  @@is_output = false
  @@level = 0
  
  attr_reader :output

  def initialize(lexer)
    @lexer = lexer
    @token = nil
    @output = ""
  end
  
  def parse
    @token = @lexer.next_token
    if program?
      p Semantic.code
      return true
    else
      return false
    end
  end
  
  def program?
    return true if @token == :eof
    
    while FIRST_EXPR.include?(@token)
      return false if !expr?
    end
    true
  end
  
  def expr?
    current_state = 0
    while true
      #p "#{'  '*@@level}Expr, current_state: #{current_state}, #{@token}:#{@@level}"
      case current_state
      when 0
        case @token
        when :i
          Semantic.read @token
          current_state = 1
        when :I
          Semantic.read @token
          current_state = 1
        when :k
          Semantic.read @token
          current_state = 1
        when :s
          Semantic.read @token
          current_state = 1
        when :apply
          current_state = 2
        when :output
          current_state = 2
        when :lpar
          Semantic.new_scope
          current_state = 3
        else
          if non_empty_jot_expr?
            current_state = 1
            next
          else
            return false
          end
        end
      when 1
        return true
      when 2
        if expr?
          current_state = 4
          next
        else
          return false
        end
      when 3
        if @token == :rpar
          Semantic.close_scope
          current_state = 1
        elsif expr?
          current_state = 3
          next
        else
          return false
        end
      when 4
        if expr?
          current_state = 1
          next
        else
          return false
        end
      end
      @token = @lexer.next_token
    end
  end
  
  def non_empty_jot_expr?
    current_state = 0
    while true
      #p "NotEmptyJotExpr, current_state: #{current_state}, #{@token}"
      case current_state
      when 0
        case @token
        when :zero
          current_state = 1
        when :one
          current_state = 1
        else
          if non_empty_jot_expr?
            current_state = 0
            next
          else
            return false
          end
        end
      when 1
        return true
      end
      @token = @lexer.next_token
    end
  end
end