#include "student_api.h"

#include "syscall_names.h"

#include <stdio.h>

#include <string.h>

void student_debug_raw_event(const struct syscall_event *ev,
                             char *buf,
                             size_t bufsz)
{
    /*
     * Suporte de depuracao para a Semana 4:
     *
     * Esta funcao existe para inspecionar eventos crus depois que o runtime
     * ja consegue parar em syscalls e preencher struct syscall_event.
     * Ela nao e a formatacao final do projeto.
     *
     * Experimento sugerido:
     * - imprima o nome da syscall;
     * - imprima se o evento e entrada ou saida;
     * - imprima o pid;
     * - em eventos de entrada, observe os argumentos;
     * - em eventos de saida, observe o valor de retorno.
     *
     * Depois compare a saida de:
     *
     *   ./toytrace trace --raw-events -- ./tests/targets/hello_write
     *
     * A pergunta importante da Semana 4 e:
     * por que a mesma syscall aparece duas vezes?
     */
  if (ev->entering) {
        snprintf(buf,bufsz,
            "\n---DEBUG---\n"
            "|\n"
            "| Nome da syscall: %ld\n"
            "| Entrada: %d\n"
            "| Pid: %d\n"
            "| Eventos de entrada, argumentos: "
            "%lu, %lu, %lu, %lu, %lu, %lu\n"
            "|\n"
            "-----------\n",
            ev->syscall_no,
            ev->entering,
            ev->pid,
            ev->args[0],
            ev->args[1],
            ev->args[2],
            ev->args[3],
            ev->args[4],
            ev->args[5]);
    }
    else {
        snprintf(buf,bufsz,
            "\n---DEBUG---\n"
            "|\n"
            "| Nome da syscall: %ld\n"
            "| Entrada: %d\n"
            "| Pid: %d\n"
            "| Valor de retorno: %ld\n"
            "|\n"
            "-----------\n",
            ev->syscall_no,
            ev->entering,
            ev->pid,
            ev->ret);
    }
}

void student_format_event(const struct syscall_event *ev,
                          char *buf,
                          size_t bufsz)
{
    /*
     * TODO Semana 5:
     *
     * Primeiro, formate uma syscall completa em uma linha simples.
     *
     * Depois, adicione casos especiais para:
     *     read(fd, buf, count)
     *     write(fd, buf, count)
     *     openat(dirfd, "path", flags, mode)
     *     execve("path", ...)
     *     exit_group(status)
     *
     * Para caminhos do processo monitorado, use read_child_strings().
     * Se a leitura falhar, imprima "<ilegivel>".
    */

    // if read ->
    if (strcmp(syscall_name(ev->syscall_no), "read") == 0) {
        snprintf(buf, bufsz, "read(%#lx, %#lx, %#lx) = %ld",
                 ev->args[0], ev->args[1], ev->args[2], ev->ret);
        return;
    }

    // if write ->
    if (strcmp(syscall_name(ev->syscall_no), "write") == 0) {
        snprintf(buf, bufsz, "write(%#lx, %#lx, %#lx) = %ld",
                 ev->args[0], ev->args[1], ev->args[2], ev->ret);
        return;
    }

    // if openat ->
    if (strcmp(syscall_name(ev->syscall_no), "openat") == 0) {
        char path[256];
        if (read_child_string(ev->pid, ev->args[1], path, sizeof(path)) < 0)
            strcpy(path, "<ilegivel>");
        snprintf(buf, bufsz, "openat(%#lx, \"%s\", %#lx, %#lx) = %ld",
                 ev->args[0], path, ev->args[2], ev->args[3], ev->ret);
        return;
    }

    // if execve ->
    if (strcmp(syscall_name(ev->syscall_no), "execve") == 0) {
        char path[256];
        if (read_child_string(ev->pid, ev->args[0], path, sizeof(path)) < 0)
            strcpy(path, "<ilegivel>");
        snprintf(buf, bufsz, "execve(\"%s\", %#lx, %#lx) = %ld",
                 path, ev->args[1], ev->args[2], ev->ret);
        return;
    }

    // if exit_group ->
    if (strcmp(syscall_name(ev->syscall_no), "exit_group") == 0) {
        snprintf(buf, bufsz, "exit_group(%#lx) = %ld", ev->args[0], ev->ret);
        return;
    }

// if não é read, write, openat, execve ou exit_group ->
    snprintf(buf, bufsz, "%s(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx) = %ld",
             syscall_name(ev->syscall_no),
             ev->args[0],
             ev->args[1],
             ev->args[2],
             ev->args[3],
             ev->args[4],
             ev->args[5],
             ev->ret);
}
