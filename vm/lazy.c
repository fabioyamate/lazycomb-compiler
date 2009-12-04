#include <stdio.h>
#include "vm.h"

int main(void) {
  novo_escopo();
  entra('s');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  novo_escopo();
  entra('I');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  fecha_escopo();
  tenta_reduzir();

  imprime();
  return 0;
}
