#include "main.h"
#include "ui.h"
#include "Printer.h"
#include "cancela.h"


volatile int state = 0;
int programToRun = 0;

int main(){
    while(1){
        switch (state)
        {
            case MENU:
                state = updateMenu(MENU1);
                break;
            case PRINTING:
                state = printTicket();
            case OPENING_GATE:
                state = openCancela();
            case CLOSING_GATE:
                state = closeCancela();
            default:
                break;
        }
    }
    return 0;
}