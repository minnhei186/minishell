/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:48:35 by geonwkim          #+#    #+#             */
/*   Updated: 2024/08/26 22:49:35 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;

	if (!dest || !src)
		return (NULL);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (n < src_len)
		total_len = dest_len + n;
	else
		total_len = dest_len + src_len;
	ft_strlcat(dest, src, total_len + 1);
	return (dest);
}

// int	main(void)
// {
// 	char dest[50] = "Hello, ";
// 	char src[] = "World!";
// 	size_t n = 3;  // Number of characters from src to append
// 	printf("Before strncat: %s\n", dest);
// 	ft_strncat(dest, src, n);
// 	printf("After strncat: %s\n", dest);
// 	return (0);
// }
