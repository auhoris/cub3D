/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:48:18 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/09 18:38:29 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(t_sprite *arr, int low, int high)
{
	float	pivot;
	int	j;
	int	i;

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

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}
