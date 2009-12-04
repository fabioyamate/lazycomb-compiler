require File.dirname(__FILE__) + '/lazycomb_compiler'

class Semantic
  @@source = ""
  
  def self.read token
    @@source << "  entra('#{token}');\n"
    @@source << "  tenta_reduzir();\n"
  end
  
  def self.new_scope
    @@source << "  novo_escopo();\n"
  end
  
  def self.close_scope
    @@source << "  fecha_escopo();\n"
    @@source << "  tenta_reduzir();\n"
  end
  
  def self.code
    TEMPLATE_SOURCE_CODE.sub('%LAZY_K_CODE%', @@source);
  end
  
  private
  TEMPLATE_SOURCE_CODE = <<-CODE
#include "environment.h"
#include <stdio.h>

int main(void) {
  novo_escopo();
%LAZY_K_CODE%
  imprime();
  return 0;
}
  CODE
end