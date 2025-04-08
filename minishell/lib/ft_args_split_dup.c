/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:45:11 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/05 11:45:32 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_args_split_dup(char **args)
{
	int		i;
	char	**new;

	i = 0;
	while (args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (args[i])
	{
		new[i] = ft_strdup(args[i]);
		if (!new[i])
			return (ft_args_split_free(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}
