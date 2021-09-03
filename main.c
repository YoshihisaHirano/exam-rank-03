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



int	main(int argc, char **argv)
{
	FILE	*file;
	t_set	set;

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

	print_drawzone(&set);
	fclose(file);
	return (0);
}
