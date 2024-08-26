/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:37:29 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/26 21:43:40 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	ft_strlcat(dest, src, ft_strlen(dest) + ft_strlen(src) + 1);
	return (dest);
}

// int	main(void)
// {
// 	char dest[50] = "Hello, ";
// 	char src[] = "World!";
// 	printf("Before strcat: %s\n", dest);
// 	ft_strcat(dest, src);
// 	printf("After strcat: %s\n", dest);
// 	return (0);
// }
