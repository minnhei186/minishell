/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:28:51 by geonwkim          #+#    #+#             */
/*   Updated: 2024/09/12 16:38:04 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	return (ft_strnchr(s, c, ft_strlen(s) + 1));
}

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*result;
// 	// Test 1: Use ft_strchr to find 'o'
// 	result = ft_strchr(str, 'o');
// 	if (result)
// 		printf("Found 'o' using ft_strchr: %s\n", result);
// 	else
// 		printf("'o' not found using ft_strchr.\n");
// 	// Test 2: Use ft_strnchr to find 'o' within first 5 characters
// 	result = ft_strnchr(str, 'o', 5);
// 	if (result)
// 		printf("Found 'o' using ft_strnchr (within 5 chars): %s\n", result);
// 	else
// 		printf("'o' not found within 5 characters using ft_strnchr.\n");
// 	// Test 3: Use ft_strnchr to find 'o' within first 10 characters
// 	result = ft_strnchr(str, 'o', 10);
// 	if (result)
// 		printf("Found 'o' using ft_strnchr (within 10 chars): %s\n", result);
// 	else
// 		printf("'o' not found within 10 characters using ft_strnchr.\n");
// 	// Test 4: Try to find 'z', which is not in the string using ft_strchr
// 	result = ft_strchr(str, 'z');
// 	if (result)
// 		printf("Found 'z' using ft_strchr: %s\n", result);
// 	else
// 		printf("'z' not found using ft_strchr.\n");
// 	// Test 5: Use ft_strchr to find the null terminator '\0'
// 	result = ft_strchr(str, '\0');
// 	if (result)
// 		printf("Found null terminator using ft_strchr.\n");
// 	else
// 		printf("Null terminator not found using ft_strchr.\n");
// 	// Test 6: Compare with the standard library strchr function for 'o'
// 	result = strchr(str, 'o');
// 	if (result)
// 		printf("Found 'o' using standard strchr: %s\n", result);
// 	else
// 		printf("'o' not found using standard strchr.\n");
// 	return (0);
// }
