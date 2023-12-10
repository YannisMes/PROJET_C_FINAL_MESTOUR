

#ifndef UNTITLED5_STRUCT_H
#define UNTITLED5_STRUCT_H


typedef struct s_d_cell
{
    int value;
    struct s_d_cell *next_0;
    struct s_d_cell *next_1;
} t_d_cell;

typedef struct s_sk_cell{
    int value;
    int level;
    struct s_sk_cell ** next;
}t_sk_cell;



#endif //UNTITLED5_STRUCT_H