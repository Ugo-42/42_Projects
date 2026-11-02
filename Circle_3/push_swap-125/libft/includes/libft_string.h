/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/03 09:52:45 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include <stddef.h>

/*┌─────────┐
  │ string/ │
  └─────────┘*/

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split(const char *s, const char c);
char	**ft_split_quoted(const char *str);
char	**ft_strdup_2d(char **array, size_t nmemb);
char	*ft_str_ultimate_join(const char *first, ...);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_stringf(const char *str, ...);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);

void	ft_strcpy(char *dest, const char *src);
void	ft_strncpy(char *dest, const char *src, size_t n);
void	ft_utf8_strncpy(char *dest, const char *src, size_t n);
void	ft_utf8_visual_strncpy(char *dest, const char *src, size_t n);

#endif
