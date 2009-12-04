#include <stdio.h>
#include "vm.h"

int main(void) {
  novo_escopo();
  entra('I');
  tenta_reduzir();
  novo_escopo();
  entra('k');
  tenta_reduzir();
  entra('k');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  fecha_escopo();
  tenta_reduzir();
  novo_escopo();
  entra('I');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  entra('k');
  tenta_reduzir();
  entra('s');
  tenta_reduzir();
  entra('I');
  tenta_reduzir();
  fecha_escopo();
  tenta_reduzir();

  imprime();
  return 0;
}
