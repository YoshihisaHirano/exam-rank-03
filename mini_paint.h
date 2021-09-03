#ifndef MINI_PAINT_H
#define MINI_PAINT_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define FILE_ERROR "Error: Operation file corrupted\n"

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			chr;
	int				type; //1 - c, 2 - C
	float			rad; // > 0
	float 			x;
	float			y;
} t_cmd;

typedef struct s_set
{
	int		height;
	int		width;
	char	chr;
	char	**drawzone;
	t_cmd	*first_cmd;
} t_set;

int		ft_strlen(char *str);
void	print_drawzone(t_set *set);

#endif
