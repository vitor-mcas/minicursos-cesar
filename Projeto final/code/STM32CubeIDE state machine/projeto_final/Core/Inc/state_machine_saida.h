#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "common.h"

/*******************************************************************************
 * ENUMERATE
 ******************************************************************************/
// Machine status enumerate
typedef enum
{
	inicial = 0,
	validandoTicket,
	abrindoCancela,
	fechandoCancela,

}
eMACHINE_STATUS;

/*******************************************************************************
 * STRUCTURE
 ******************************************************************************/
// Define state machine structure
typedef struct _sSTATE_MACHINE
{
	void (*Initialize)(void);
	void (*veiculoChegouNoTotem)(void);
	void (*leitorTicket)(void);
}
sSTATE_MACHINE;

/*******************************************************************************
 * PUBLIC VARIABLES
 ******************************************************************************/
extern sSTATE_MACHINE sStateMachine;

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _STATE_MACHINE_H_ */
