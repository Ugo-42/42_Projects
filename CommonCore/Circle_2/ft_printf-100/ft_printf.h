/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:45:21 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/11/13 12:33:05 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

typedef unsigned char	t_byte;

char	*ft_strchr(const char *s, int c);
int		ft_printf(const char *str, ...);
size_t	ft_handle_format(va_list args, const char *format);
size_t	ft_print_address(uintptr_t addr);
size_t	ft_print_hex(unsigned long n, bool uppercase);
size_t	ft_putchar(char c);
size_t	ft_putnbr(int n);
size_t	ft_putstr(const char *s);
size_t	ft_putstrn(const char *s, size_t n);
size_t	ft_putunbr(unsigned int n);
size_t	ft_strlen(const char *str);

#endif
