/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** instruction xor for the VM
*/

#include <stdlib.h>
#include "instructions.h"

/*
Similar to and, but performing a binary XOR (exclusive OR).
*/
static void xor_to_reg(vm_t *vm, process_t *process, unsigned char *type,
                        int *size)
{
    int first = 0;
    int second = 0;

    process->index += 2;
    first = param_getter(process, vm, type[0], size[0]);
    second = param_getter(process, vm, type[1], size[1]);
    if (type[0] == REG_CODE) {
        if (first < 1 || first > REG_NUMBER) return;
        first = process->registr[first - 1];
    }
    if (type[1] == REG_CODE) {
        if (second < 1 || second > REG_NUMBER) return;
        second = process->registr[second - 1];
    }
    if (set_reg(process, vm, first ^ second) == -1) return;
    process->carry = (first ^ second) ? 0 : 1;
}

void cmd_xor(vm_t *vm, process_t *process)
{
    unsigned char coding_byte = '\0';
    char command = 8;
    unsigned char *type = NULL;
    int *size = NULL;
    int future_index = 0;

    coding_byte = cbuffer_getb(vm->arena, process->index + 1);
    type = get_coding_byte(coding_byte);
    size = get_size(type, command - 1);
    future_index = process->index + 2;
    for (int i = 0; i < op_tab[command - 1].nbr_args; i++)
        future_index += size[i];
    if (param_checker(type, command - 1)) {
        xor_to_reg(vm, process, type, size);
    }
    process->index = future_index;
    free(type);
    free(size);
}
