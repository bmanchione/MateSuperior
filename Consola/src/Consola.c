/*
 * Consola.c
 *
 *
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>

#include "Consola.h"


void conectarKernel(){
	struct sockaddr_in direccionParaConectarseServidor = crearDireccionCliente(consola_config.PUERTO_KERNEL_CONSOLA, consola_config.IP_KERNEL_CONSOLA);
	socketConsola = crearSocket();
	conectar(socketConsola, &direccionParaConectarseServidor, KERNEL);

	iniciarHandshake(CONSOLA, KERNEL, socketConsola);

	while(1){
		char* mensaje;
		puts("Consola: Ingrese mensaje a enviar Kernel:");
		scanf("%s", mensaje);
		enviarMensajeConTamanioDinamico(socketConsola, mensaje);
	}
}

int main() {
	printf("Iniciando Consola...\n\n");
	//CARGAR ARCHIVO DE CONFIGURACIÓN
	cargarConfigConsola();
	//MOSTRAR ARCHIVO DE CONFIGURACIÓN
	mostrarConfigConsola();

	conectarKernel();

	return EXIT_SUCCESS;
}
