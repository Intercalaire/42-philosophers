/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:30:01 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/01 16:39:02 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*stock;

	i = 0;
	stock = (char *)s;
	while (i < n)
	{
		stock[i] = '\0';
		i++;
	}
}

void	*ft_calloc( size_t nmemb, size_t size)
{
	void	*total;

	if (nmemb != 0 && size != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	total = malloc(nmemb * size);
	if (total == NULL)
		return (NULL);
	ft_bzero(total, nmemb * size);
	return (total);
}
