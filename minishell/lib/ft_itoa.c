/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:55:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/15 17:50:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	int		sign;
	char	*str;

	nbr = n;
	len = ft_numlen(nbr);
	sign = (n < 0);
	if (n < 0)
		n = -n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		if (len == 0 && sign)
			str[len] = '-';
	}
	return (str);
}
