/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:17:04 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/04 19:35:21 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

void	print_error(t_config *all, int e_code)
{
	ft_putendl_fd("Error\nInvalid argumetns", 2);
	exit(1);
}
