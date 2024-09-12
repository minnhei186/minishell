/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:28:51 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 16:42:30 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[n])
		{
			while (haystack[i + n] == needle[n])
			{
				if (needle[n + 1] == '\0')
					return ((char *)(haystack + i));
				n++;
			}
			n = 0;
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*haystack = "Hello, World!";
// 	const char	*needle;
// 	char		*result;
// 	// Test 1: Find "World" in "Hello, World!"
// 	needle = "World";
// 	result = ft_strstr(haystack, needle);
// 	if (result)
// 		printf("Found '%s' in '%s': %s\n", needle, haystack, result);
// 	else
// 		printf("'%s' not found in '%s'.\n", needle, haystack);
// 	// Test 2: Find "Hello" in "Hello, World!"
// 	needle = "Hello";
// 	result = ft_strstr(haystack, needle);
// 	if (result)
// 		printf("Found '%s' in '%s': %s\n", needle, haystack, result);
// 	else
// 		printf("'%s' not found in '%s'.\n", needle, haystack);
// 	// Test 3: Find an empty string (should return the whole string)
// 	needle = "";
// 	result = ft_strstr(haystack, needle);
// 	if (result)
// 		printf("Found empty string in '%s': %s\n", haystack, result);
// 	else
// 		printf("Empty string not found in '%s'.\n", haystack);
// 	// Test 4: Try to find a string that is not present
// 	needle = "42";
// 	result = ft_strstr(haystack, needle);
// 	if (result)
// 		printf("Found '%s' in '%s': %s\n", needle, haystack, result);
// 	else
// 		printf("'%s' not found in '%s'.\n", needle, haystack);
// 	return (0);
// }
