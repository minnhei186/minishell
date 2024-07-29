/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:14:31 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/29 23:15:43 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t src_len = strlen(src);
    if (size > 0) {
        size_t len = (src_len >= size) ? size - 1 : src_len;
        memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return src_len;
}

size_t strlcat(char *dst, const char *src, size_t size) {
    size_t dst_len = strnlen(dst, size);
    size_t src_len = strlen(src);

    if (dst_len == size) {
        return size + src_len;
    }

    if (src_len < size - dst_len) {
        memcpy(dst + dst_len, src, src_len + 1);
    } else {
        memcpy(dst + dst_len, src, size - dst_len - 1);
        dst[size - 1] = '\0';
    }

    return dst_len + src_len;
}
