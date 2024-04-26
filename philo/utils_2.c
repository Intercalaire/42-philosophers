/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:59:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/10 14:59:08 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_bzero(void *s, size_t n);

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
size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}