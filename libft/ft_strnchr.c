/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:35:26 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 16:37:29 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strnchr(const char *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i < len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0' && i < len)
		return ((char *)(s + i));
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*result;
// 	// Example 1: Find 'o' within first 5 characters
// 	result = ft_strnchr(str, 'o', 5);
// 	if (result)
// 		printf("Found 'o' within first 5 characters: %s\n", result);
// 	else
// 		printf("'o' not found within first 5 characters.\n");
// 	// Example 2: Find 'o' within first 10 characters
// 	result = ft_strnchr(str, 'o', 10);
// 	if (result)
// 		printf("Found 'o' within first 10 characters: %s\n", result);
// 	else
// 		printf("'o' not found within first 10 characters.\n");
// 	// Example 3: Find 'W' within first 12 characters
// 	result = ft_strnchr(str, 'W', 12);
// 	if (result)
// 		printf("Found 'W' within first 12 characters: %s\n", result);
// 	else
// 		printf("'W' not found within first 12 characters.\n");
// 	// Example 4: Try to find 'z', which is not in the string
// 	result = ft_strnchr(str, 'z', 13);
// 	if (result)
// 		printf("Found 'z': %s\n", result);
// 	else
// 		printf("'z' not found.\n");
// 	// Example 5: Find null terminator within 13 characters
// 	result = ft_strnchr(str, '\0', 13);
// 	if (result)
// 		printf("Found null terminator at the end of the string.\n");
// 	else
// 		printf("Null terminator not found.\n");
// 	return (0);
// }
