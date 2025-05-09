/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:20 by garside           #+#    #+#             */
/*   Updated: 2024/10/28 21:02:17 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	total_len(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*convt(int nbr, int len)
{
	char	*size_n;

	size_n = (char *)malloc(sizeof(char) * (len + 1));
	if (!size_n)
		return (NULL);
	size_n[len] = '\0';
	if (nbr < 0)
	{
		size_n[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
		size_n[0] = '0';
	while (nbr)
	{
		size_n[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (size_n);
}

char	*ft_itoa(int n)
{
	int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = total_len(n);
	return (convt(n, len));
}
