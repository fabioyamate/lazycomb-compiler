#include "vm.h"
#include "ski.h"

dqueue escopos = 0;
dqueue escopo_atual() {
	return (dqueue) dq_peek_back(escopos);
}

void novo_escopo() {
	dqueue nova_fila;
	if(escopos == 0) escopos = dq_create();
	nova_fila = dq_create();
	dq_enq_back(escopos, nova_fila);
}

char* char_from_heap(char c) {
	char* pc = (char*)malloc(sizeof(char));
	*pc = c;
	return pc;
}

void fecha_escopo() {
	dqueue fila_atual, fila_anterior;
	assert(!dq_empty(escopos));
	fila_atual = (dqueue)dq_deq_back(escopos);
	fila_anterior = (dqueue)dq_peek_back(escopos);
	dq_enq_front(fila_anterior, char_from_heap('('));
	while(!dq_empty(fila_atual))
	{
		dq_enq_front(fila_anterior, dq_deq_back(fila_atual));
	}
	dq_enq_front(fila_anterior,char_from_heap(')'));
}

void entra(char c) {
	assert(!dq_empty(escopos));
	dq_enq_front(escopo_atual(), char_from_heap(c));
}

void entra_string(char* str) {
	int n = strlen(str);
	int i;
	assert(!dq_empty(escopos));
	for(i = 0; i < n; i++) {
		entra(str[i]);
	}
}

char proxAcao() {
	char prox;
	assert(!dq_empty(escopo_atual()));
	prox = *(char*)dq_deq_back(escopo_atual());
	while(prox == '(') {
		assert(!dq_empty(escopo_atual()));
		prox = *(char*)dq_deq_back(escopo_atual());
	}
	return prox;
}

#define BUFFER_SIZE 1000
static char buffer[BUFFER_SIZE];

char* proxParam() {
	char primeiro;
	if(dq_empty(escopo_atual()))
		return 0;

	primeiro = *((char*)dq_peek_back(escopo_atual()));
	if(primeiro == ')')
		dq_deq_back(escopo_atual());

	if(primeiro != '(') {
		char* str;
		dq_deq_back(escopo_atual());
		if(!dq_empty(escopo_atual()) && *((char*)dq_peek_back(escopo_atual())) == ')')
			dq_deq_back(escopo_atual());
		str = (char*)malloc(sizeof(char) * 2);
		str[0] = primeiro; str[1] = 0;
		return strdup(str);
	} else {
		int n_chars = 0;
		dqueue pilha_parenteses = dq_create();
		memset(buffer, 0, sizeof(buffer[0]) * BUFFER_SIZE);
		while(!dq_empty(escopo_atual())) {
			char c = *((char*)dq_deq_back(escopo_atual()));
			if(c == '(') dq_enq_back(pilha_parenteses, 0);
			if(c == ')') dq_deq_back(pilha_parenteses);
			buffer[n_chars] = c;
			n_chars++;
			if(dq_empty(pilha_parenteses)) {
				char* str = (char*)malloc((n_chars + 1) * sizeof(char));
				memset(str, 0, (n_chars + 1) * sizeof(char));
				strcpy(str, buffer);
				return strdup(buffer);
			}
		}
		assert(0);
		return 0;
	}
}

void push_string(char* str) {
	if(str != 0) {
		int n = strlen(str);
		int i;
		for(i = n-1; i >= 0; i--) {
			dq_enq_back(escopo_atual(), char_from_heap(str[i]));
		}
	}
}

void S(char* p1, char* p2, char* p3) {
	int size = strlen(p3)*2 + strlen(p1) + strlen(p2) + 2 + 1;
	char* str = (char*)malloc(size * sizeof(char));
	memset(str, 0, size * sizeof(char));
	strcat(str, p1);
	strcat(str, p3);
	strcat(str, "(");
	strcat(str, p2);
	strcat(str, p3);
	strcat(str, ")");
	push_string(str);
}

void I(char* p1) {
	int n = strlen(p1);
	if(n > 0) {
		char c = p1[0];
		if(c == '(') {
			p1[n-1] = 0;
			push_string(p1 + 1);
		} else {
			push_string(p1);
		}
	}
}

void tenta_reduzir() {
	int reduziu = 0;
	do {
		reduziu = 0;
		if(!dq_empty(escopo_atual())) {
			char acao = proxAcao();
			char* param1, *param2, *param3;
			switch(acao) {
			case 'S':
			case 's':
				param1 = proxParam();
				param2 = proxParam();
				param3 = proxParam();
				if(param1 && param2 && param3) {
					S(param1, param2, param3);
					reduziu = 1;
				} else {
					push_string(param3); push_string(param2); push_string(param1); push_string("S");
				}
				break;
			case 'K':
      case 'k':
				param1 = proxParam();
				param2 = proxParam();
				if(param1 && param2) {
					push_string(param1);
					reduziu = 1;
				} else {
					push_string(param2); push_string(param1); push_string("K");
				}
				break;
			case 'I':
				param1 = proxParam();
				if(param1) {
					I(param1);
					reduziu = 1;
				} else {
					push_string("I");
				}
				break;
			}
		}
	} while(reduziu);
}

void imprime() {
	printf("%s\n", fila_atual());
}


char* strfila(dqueue fila) {
	int i = 0, j;
	memset(buffer, 0, sizeof(buffer[0]) * BUFFER_SIZE);
	while(!dq_empty(fila) && i < BUFFER_SIZE) {
		char* pc = (char*)(dq_deq_back(fila));
		char c = *pc;
		//free(pc);
		buffer[i] = c;
		i++;
	}
	for(j = 0; j < i; j++) {
		entra(buffer[j]);
	}
	return buffer;
}

char* fila_atual() {
	assert(!dq_empty(escopos));
	return strfila(escopo_atual());
}


