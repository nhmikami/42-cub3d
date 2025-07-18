/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:23 by cayamash          #+#    #+#             */
/*   Updated: 2025/06/12 16:30:23 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	handle_error(char *error, char *str)
{
	int	len;

	ft_printf_fd(2, error);
	if (str)
	{
		len = ft_strlen(str);
		ft_printf_fd(2, "-> ");
		ft_printf_fd(2, str);
		if (str[len - 1] != '\n')
			ft_printf_fd(2, "\n");
	}
	clear_mem();
	exit(EXIT_FAILURE);
}

void	validate_file_extension(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		handle_error(INVALID_FORMAT, file_name);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf_fd(2, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	validate_file_extension(argv[1]);
	game = init(argv[1]);
	parse_file(game, argv[1]);
	render_img(game);
	set_hooks(game);
	clear_mem();
	return (EXIT_SUCCESS);
}
