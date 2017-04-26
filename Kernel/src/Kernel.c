#include <stdio.h>
#include <stdlib.h>

#include "Kernel.h"

void recibirConsolas() {

	configurarServidor(&direccionServidorKernel, &socketServidorKernel,
			kernel_config.PUERTO_PROG, &activadoConsola);
	//printf("IP = %s\n", inet_ntoa(direccionServidorKernel.sin_addr));
	printf("Esperando Consolas...\n");

	//recibirClientes(socketServidorKernel, 'n');
	while (1) {
		int socketConsola = recibirCliente(socketServidorKernel);
		pthread_t hilo;
		devolverHandshake(socketConsola, KERNEL);
		crearHiloConParametro(&hilo, recibirMensajesYReplicar,
				socketConsola);
	}

}

void recibirCPUs() {

	configurarServidor(&direccionServidorKernel, &socketServidorKernel,
			kernel_config.PUERTO_CPU, &activadoCPU);

	printf("Esperando CPUs...\n");

	while (1) {
			int socketCPU = recibirCliente(socketServidorKernel);
			pthread_t hilo;
			devolverHandshake(socketCPU, KERNEL);
			crearHiloConParametro(&hilo, quedarEsperaRecibirMensajes, socketCPU);
		}
}

void conectarFileSystem() {
	struct sockaddr_in direccionParaConectarseServidor = crearDireccionCliente(
			kernel_config.PUERTO_FS, kernel_config.IP_FS);
	socketKernel = crearSocket();
	conectar(socketKernel, &direccionParaConectarseServidor, FILE_SYSTEM);

	iniciarHandshake(KERNEL, FILE_SYSTEM, socketKernel);
}

void conectarMemoria() {
	struct sockaddr_in direccionParaConectarseServidor = crearDireccionCliente(
			kernel_config.PUERTO_MEM, kernel_config.IP_MEMORIA);
	socketKernel = crearSocket();
	conectar(socketKernel, &direccionParaConectarseServidor, MEMORIA);

	iniciarHandshake(KERNEL, MEMORIA, socketKernel);
}

int main(void) {
	printf("Iniciando Kernel...\n\n");
//	logger("Iniciando Kernel", "INFO");

	//CARGAR ARCHIVO DE CONFIGURACIÓN
	cargarConfigKernel();
	//MOSTRAR ARCHIVO DE CONFIGURACIÓN
	mostrarConfigKernel();


	inicializarClientes();
	inicializarServidores();

	puts("FileSystem");
	conectarFileSystem();
	puts("Memoria");
	conectarMemoria();

	pthread_t hiloConsolas;
	crearHilo(&hiloConsolas, recibirConsolas);
	pthread_t hiloCPUs;
	crearHilo(&hiloCPUs, recibirCPUs);

	while (1);
	//SetupServer();

	return 0;
}
