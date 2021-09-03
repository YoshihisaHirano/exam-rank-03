#include "mini_paint.h"

int	set_init(t_set *set, FILE *file)
{
	int num;
	int	i;

	num = fscanf(file, "%d %d %c\n", &set->width, &set->height, &set->chr);
	if (num < 3 || set->height < 0 || set->height > 300 || set->width < 0 ||
	set->width > 300)
	{
		write(1, FILE_ERROR, ft_strlen(FILE_ERROR));
		return (1);
	}
	i = 0;
	set->drawzone = malloc(sizeof(char *) * set->height);
	while (i < set->height)
	{
		set->drawzone[i] = malloc(set->width);
		memset(set->drawzone[i], set->chr, set->width);
		i++;
	}
	return (0);
}

//c X Y RADIUS CHAR
int	add_cmds(t_set *set, FILE *file)
{
	t_cmd	*elt;
	int		num;
	t_cmd	*temp;

	elt = malloc(sizeof(t_cmd));
	*elt = (t_cmd){.type = 'j', .next = NULL, .rad = -1.0};
	num = fscanf(file, "%c %f %f %f %c\n", &elt->type, &elt->x, &elt->y,
				 &elt->rad, &elt->chr);
	if (num == -1)
		return (1);
	if ((num != 5 && num > 0) || (elt->type != 'c' && elt->type != 'C')
	|| elt->rad <= 0)
	{
		write(1, FILE_ERROR, ft_strlen(FILE_ERROR));
		printf("%c\n", elt->chr);
		free_lst(set->first_cmd);
		return (1);
	}
	if (!set->first_cmd)
		set->first_cmd = elt;
	else
	{
		temp = set->first_cmd;
		while (temp->next)
			temp = temp->next;
		temp->next = elt;
	}
	return (0);
}

void	draw_circles(t_set *set, t_cmd *cmd)
{
	int 	i;
	int 	j;
	float dst;

	i = 0;
	while (i < set->height)
	{
		j = 0;
		while (j < set->width)
		{ //a - center, b - point
			dst = sqrtf(powf((j - cmd->x), 2) + powf((i - cmd->y), 2));
			if (dst <= cmd->rad)
			{
				if (cmd->type == 'C')
					(set->drawzone)[i][j] = cmd->chr;
				else if (sqrtf((powf((dst - cmd->rad), 2))) <= 1.0)
				{
//					printf("%f -- border\n", dst - cmd->rad);
					(set->drawzone)[i][j] = cmd->chr;
				}
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	FILE	*file;
	t_set	set;
	int		res;

	(void)argv;
	if (argc != 2)
	{
		write(1, "Error: argument\n", ft_strlen("Error: argument\n"));
		return (1);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		write(1, FILE_ERROR, ft_strlen(FILE_ERROR));
		return (1);
	}
	set = (t_set){.width = 400, .height = 400, .first_cmd = NULL};
	if (set_init(&set, file))
		return (1);
	res = 0;
	while (!res)
		res = add_cmds(&set, file);
	while (set.first_cmd)
	{
		draw_circles(&set, set.first_cmd);
//		printf("%c\n", set.first_cmd->chr);
		set.first_cmd = set.first_cmd->next;
	}
	print_drawzone(&set);
	fclose(file);
	return (0);
}
