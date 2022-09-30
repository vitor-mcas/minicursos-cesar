/****************************************************************************
 * Filename:			state_machine.c
 * Revised:				Date: 2020.02.20
 * Revision:			V001
 * Description:		    State machine function
*******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "state_machine.h"
//#include "software_timer.h"

/*******************************************************************************
 * CONSTANTS
 ******************************************************************************/
#define MAX_VAGAS	800

/*******************************************************************************
 * LOCAL VARIBLES
 ******************************************************************************/
/*******************************************************************************
 * STRUCTURE
 ******************************************************************************/
// Define state machine property structure
typedef struct
{
	eMACHINE_STATUS eCurrentMachineStatus;
	int totalCarros_Vagas;
	unit8_t valido = 0;
}
sSTATE_MACHINE_PRO;
static sSTATE_MACHINE_PRO sStateMachinePro;

/*******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************/
static void GoToInicialStatus(void);
static void GoToValidandoTicketStatus(void);
static void GoToAbrindoCancelaStatus(void);
static void GoToFechandoCancelaStatus(void);
static void (*GoTo[])(void) =
{
	GoToInicialStatus,
	GoToValidandoTicketStatus,
	GoToAbrindoCancelaStatus,
	GoToFechandoCancelaStatus,
};

static void GoToVisualizandoVagasStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = visualizandoVagas;
	printf("Verifique a disponibilidade de vagas abaixo\n");
	if(sStateMachinePro.totalCarros_Vagas >= MAX_VAGAS)
	{
		printf("Estacionamento Lotado\n");
		(*GoTo[inicial])();

	} else {
		/* Função Visualizar vagas no display */
	}
}

static void GoToValidandoTicketStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = imprimindoTicket;
	HAL_Delay(3000);
	/* FUNÇAO DE VALIDAÇAO - REQUISIÇÃO DO SISTEMA */
	/* Função de requisição do sistema
	sStateMachinePro.valido = validarTicket(); */
	if(sStateMAchinePro.valido == 1){
		sStateMachinePro.totalCarros_Vagas--;
		HAL_Delay(3000);
		(*GoTo[abrindoCancela])();

	}else{
		printf("Ticket não validado, por favor efetue pagamento\n");
	}

	/* Função para enviar dados para a nuvem pelo GATE, usando LORA*/
}

static void GoToAbrindoCancelaStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = abrindoCancela;
	printf("Abrindo ...\n");
	/* Função para acionar motor pelo Driver */
	/* abrirCancela(); */
}


/* GoToFechandoCancelaStatus AGUARDA INTERRUPT DO SENSOR DE BARREIRA DA CANCELA */
static void GoToFechandoCancelaStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = fechandoCancela;
	printf("Fechando ...\n");
	/* Função para acionar motor pelo Driver */
	/* fecharCancela(); */
}

static void GoToFechandoCancelaStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = Lotado;
	printf("Pause Dispense status setup completed\n");
	printf("Press button to continue dispense\n");
}

/********************************************************************************************/
static void ValidarTicket(void);
static void (*ticketAction[])(void) =
{
	ValidarTicket,
};

static void ValidarTicket(void)
{
	printf("Validando ticket, aguarde\n");
	(*GoTo[validandoTicket])();


}


/*********************************************************************************/
static void MostrarVagasDisponiveis(void);
static void (*VisualizarVagasAçoes[])(void) =
{
	NULL,
	MostrarVagasDisponiveis,
};



static void MostrarVagasDisponiveis(void)
{
	printf("Vagas disponíveis: -->\n");
	(*GoTo[visualizandoVagas])();
}

/*----------------------------------------------------------------------------------------*/
static void Initialize(void);
static void veiculoChegouNoTotem(void);
static void botaoTicketPressionado(void);

static void Initialize(void)
{
	(*GoTo[inicial])();
}

static void leitorTicket(void)
{
	if(sStateMachinePro.eCurrentMachineStatus == NULL)
	{
		(*ticketAction[sStateMachinePro.eCurrentMachineStatus])();
	}

}

static void veiculoChegouNoTotem(void)
{

	(*VisualizarVagasAçoes[sStateMachinePro.eCurrentMachineStatus])();

}

// State machine
sSTATE_MACHINE sStateMachine =
{
	Initialize,
	veiculoChegouNoTotem,
	leitorTicket,
};
