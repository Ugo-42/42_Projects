/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/07 15:15:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINT_H
# define LIBFT_PRINT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

/*┌────────┐
  │ print/ │
  └────────┘*/

int		ft_fprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);

void	ft_putstr_colored(uint32_t color, const char *str);
void	ft_putstr_nl_colored(uint32_t color, const char *str);

size_t	ft_print_address_fd(int fd, uintptr_t addr);
size_t	ft_print_hex_fd(int fd, unsigned long n, bool uppercase);
size_t	ft_print_left_fd(int fd, const char *s, size_t padding);
size_t	ft_print_middle_fd(int fd, const char *s, size_t padding);
size_t	ft_print_right_fd(int fd, const char *s, size_t padding);
size_t	ft_putchar_fd(int fd, const char c);
size_t	ft_putnbr_fd(int fd, int n);
size_t	ft_putnchar_fd(int fd, const char c, size_t n);
size_t	ft_putstr(const char *s);
size_t	ft_putstr_nl(const char *s);
size_t	ft_putstr_fd(int fd, const char *s);
size_t	ft_putstr_nl_fd(int fd, const char *s);
size_t	ft_putstrn_fd(int fd, const char *s, size_t n);
size_t	ft_putunbr_fd(int fd, unsigned int n);
size_t	ft_utf8_putnchar_fd(int fd, const char *wide_c, size_t n);

#endif
