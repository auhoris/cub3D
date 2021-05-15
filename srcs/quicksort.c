/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:48:18 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:26:10 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

void	swap(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		partition(t_sprite *arr, int low, int high)
{
	float	pivot;
	int		j;
	int		i;

	pivot = arr[high].dist;
	i = low - 1;
	j = low - 1;
	while (++j < high)
	{
		if (arr[j].dist >= pivot)
		{
			i++;
			swap(&arr[j], &arr[i]);
		}
	}
	swap(&arr[high], &arr[i + 1]);
	return (i + 1);
}

void	quicksort(t_sprite *arr, int low, int high)
{
	int	pi;

	while (low < high)
	{
		pi = partition(arr, low, high);
		if (pi - low < high - pi)
		{
			quicksort(arr, low, pi - 1);
			low = pi + 1;
		}
		else
		{
			quicksort(arr, pi + 1, high);
			high = pi - 1;
		}
	}
}
