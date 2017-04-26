/*
 * Memoria.c
 *
 *
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>


#include "Memoria.h"

void recibirKernel() {

	configurarServidor(&direccionServidorMemoria, &socketServidorMemoria,
			memoria_config.PUERTO_MEMORIA, &activadoKernel);

	printf("Esperando Kernel...\n");

	while (1) {
		int socketKernel = recibirCliente(socketServidorMemoria);
		devolverHandshake(socketKernel, KERNEL);
		quedarEsperaRecibirMensajes(socketKernel, KERNEL, MEMORIA);
	}

}

int main(void) {
	printf("Iniciando Memoria...\n\n");

	cargarConfigMemoria();
	mostrarConfigMemoria();

	recibirKernel();

	return EXIT_SUCCESS;
}
