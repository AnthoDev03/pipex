#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_node
{
	int				data;
	struct t_node	*next;
}					t_node;

typedef struct t_stack
{
	t_node			*head;
}					t_stack;
void				free_stack(t_stack *stack);
void				push(t_stack *stack, int data);
int					pop(t_stack *stack);
int					ft_lstsize2(t_stack *stack);
void				pa(t_stack *stack_a, t_stack *stack_b);
void				pb(t_stack *stack_a, t_stack *stack_b);
int					get_max_bits(t_stack *stack);
void				radix_sort(t_stack *stack_a, t_stack *stack_b);
void				rotate(t_stack *stack);
void				ra(t_stack *stack_a);
void				rb(t_stack *stack_b);
void				rr(t_stack *stack_a, t_stack *stack_b);
bool				issorted(t_stack *stack_a);
void				reverse_rotate(t_stack *stack);
void				rra(t_stack *stack_a);
void				rrb(t_stack *stack_b);
void				rrr(t_stack *stack_a, t_stack *stack_b);
void				stack_a_init(int *data, t_stack *stack_a, int argc);
void				swap_first_two(t_stack *stack);
void				sa(t_stack *stack);
void				sb(t_stack *stack);
void				ss(t_stack *stack_A, t_stack *stack_B);
t_stack				*stack_init(void);
int					test(int argc, char **argv);
int					*transform(int argc, char **argv);
void				fill_data_array(int argc, char **argv, int *data);
void				calculate_new_data_array(int *data, int *data2, int size);
void				push_two_smallest(t_stack *stack_a, t_stack *stack_b);
void				find_two_smallest(t_stack *stack_a, int *smallest1,
						int *smallest2);
void				perform_pushes(t_stack *stack_a, t_stack *stack_b,
						int smallest1, int smallest2);

#endif
