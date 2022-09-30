/*******************************************************************************
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
}
sSTATE_MACHINE_PRO;
static sSTATE_MACHINE_PRO sStateMachinePro;

/*******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************/
static void GoToInicialStatus(void);
static void GoToVisualizandoVagasStatus(void);
static void GoToImprimindoTicketStatus(void);
static void GoToAbrindoCancelaStatus(void);
static void GoToFechandoCancelaStatus(void);
static void (*GoTo[])(void) =
{
	GoToInicialStatus,
	GoToVisualizandoVagasStatus,
	GoToImprimindoTicketStatus,
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

static void GoToImprimindoTicketStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = imprimindoTicket;
	HAL_Delay(3000);
	/* FUNÇAO DE IMPRESSAO USANDO IMPRESSORA TERMICA */

	/* Função para enviar dados para a nuvem pelo GATE, usando LORA*/
	HAL_Delay(3000);
	(*GoTo[abrindoCancela])();
}

static void GoToAbrindoCancelaStatus(void)
{
	sStateMachinePro.eCurrentMachineStatus = abrindoCancela;
	printf("Abrindo ...\n");
	/* Função para acionar motor pelo Driver */
	/* abrirCancela(); */
}

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
static void ImprimirTicketStatus(void);
static void (*ticketAction[])(void) =
{
	InsertCoinAtAcceptCoinMachineStatus,
};

static void ImprimirTicketStatus(void)
{
	if(sStateMachinePro.totalCarros_Vagas == MAX_VAGAS)
	{
		printf("Estacionamento Lotado\n");
		(*GoTo[inicial])();

	} else {
		printf("Imprimindo ticket\n");
		sStateMachinePro.totalCarros_Vagas++;
		int andar = sStateMachinePro.totalCarros_Vagas/200;
		printf("Número da vaga = %d, no andar %d\n", sStateMachinePro.totalCarros_Vagas);
		(*GoTo[imprimindoTicket])();
	}
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

static void botaoTicketPressionado(void)
{
	if(sStateMachinePro.eCurrentMachineStatus != imprimindoTicket)
	{
		(*ticketAction[sStateMachinePro.eCurrentMachineStatus])();
	}
	else
	{
		printf("Botão já foi pressionado, aguarde a impressão \n");
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
	botaoTicketPressionado,
};
