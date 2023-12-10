#include "Cell.h"
#include <stdlib.h>



t_sk_cell *CreateCell(int val,int niv) {
    t_sk_cell *cell = (t_sk_cell *)malloc(sizeof(t_sk_cell));
    cell->value = val;
    cell->level = niv;
    cell->next = (t_sk_cell **)malloc((niv + 1) * sizeof(t_sk_cell *));
    for (int i = 0; i <= niv; i++) {
        cell->next[i] = NULL;
    }
    return cell;

}
