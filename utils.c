#include "mini_paint.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void print_drawzone(t_set *set)
{
	int	i;
	int j;

	i = 0;
	while (i < set->height)
	{
		j = 0;
		while (j < set->width)
		{
			write(1, &set->drawzone[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	j = 0;
	while (j < set->height)
	{
		free(set->drawzone[j]);
		j++;
	}
	free(set->drawzone);
}

void	free_lst(t_cmd *head)
{
	t_cmd	*temp;

	if (!head)
		return ;
	while (head->next)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free(head);
}