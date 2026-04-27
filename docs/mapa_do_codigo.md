# Mapa do Código

## Onde o programa começa:

O programa começa na chamada da função `trace_program`, após o tratamento dos argumentos na própria main e depois na função `parse_args`.

## Onde o processo alvo é criado:

Atualmente a criação do processo não foi implementada, porém isso será feito na chamada da função `launch_tracee` no começo da função `trace_program` no arquivo `trace_runtime.c` após o tratamento dos argumentos.

## Onde o runtime chama o callback:

O runtime chama o callback na função `trace_program` no final do arquivo, depois da função `fill_event_from_regs`.

## Arquivos que o grupo deve modificar:

O grupo deve modificar somente o arquivo `trace_runtime.c`, os outros arquivos já estão prontos.

## TODO que aparece primeiro ao executar o scaffold:

Na função `launch_tracee`:

```
/*
     * TODO Semana 2:
     *
     * Crie o processo monitorado.
     *
     * Fluxo esperado:
     * - fork()
     * - no filho:
     *   - ptrace(PTRACE_TRACEME, ...)
     *   - raise(SIGSTOP)
     *   - execvp(argv[0], argv)
     * - no pai:
     *   - retornar o pid do filho
     *
     * Em erro, imprima uma mensagem com perror() e retorne -1.
     */
```

## Principal dúvida técnica do grupo neste momento:

O grupo sentiu bastante dificuldade com a nomenclatura, mas conseguimos ter uma boa noção (em alto nível) do funcionamento do programa. Agora a dúvida principal é em como implementar os `TODO`.