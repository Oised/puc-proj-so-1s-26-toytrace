#include "student_api.h"

int student_pair_syscall(struct syscall_pairer *pairer,
                         const struct syscall_event *ev,
                         struct syscall_event *out)
{
    /*
     * TODO Semana 5:
     *
     * O runtime chama esta funcao duas vezes para cada syscall:
     *
     *   1. uma vez antes da syscall executar
     *   2. uma vez depois da syscall terminar
     *
     * Na primeira parada, os argumentos estao disponiveis.
     * Na segunda parada, o retorno esta disponivel.
     *
     * Seu trabalho e produzir um evento completo apenas quando ja existirem
     * as duas metades da syscall.
     *
     * Dicas:
     * - ev->entering == 1 indica entrada de syscall.
     * - ev->entering == 0 indica saida de syscall.
     * - para comecar, assuma apenas um processo monitorado.
     *
     * Retorne:
     *   1 se out contem uma syscall completa
     *   0 se ainda nao ha syscall completa
     *  -1 se a sequencia de eventos parece invalida
     */

    if(ev->entering){ //entrada
        pairer->entry = *ev; //guarda os dados da struct ev do runtime e guarda na struct entry (q tem os mesmos campos de ev)
        pairer->has_entry = 1; //avisa que a entrada esta salva
        return 0;
    }
    if(pairer->has_entry){
        pairer->entry.ret = ev->ret;
        pairer->entry.entering = ev->entering;
        pairer->has_entry = 0; //prepara para a proxima syscall
        *out = pairer->entry;
        return 1;
    }
    else{
        perror("DEU RUIM NO PAIRER\n");
        return -1;
    }
}
