/*
 * Memoria.h
 *
 *  Created on: 2/4/2017
 *      Author: utnso
 */

#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <SharedLibrary/ServerCommons.h>
#include <SharedLibrary/Hilos.h>

#include "ConfigMemoria.h"

struct sockaddr_in direccionServidorMemoria;
int socketServidorMemoria;

int activadoKernel;

#endif /* MEMORIA_H_ */
