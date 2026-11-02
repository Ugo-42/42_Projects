/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 11:53:52 by ugwentzi         ###   ########.fr       */
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

/*┌────────┐
  │ on FDs │
  └────────┘*/

/**
 * @brief Prints a formatted string to a file descriptor.
 *
 * Supported format specifiers:
 * - %c : character
 * - %s : string
 * - %p : pointer address
 * - %i / %d : signed int
 * - %u : unsigned int
 * - %l : signed long
 * - %x : unsigned long in lowercase hexadecimal
 * - %X : unsigned long in uppercase hexadecimal
 * - %b : convert the nb with given base (..., nb, "base", ...)
 * - %% : literal '%'
 *
 * Color format specifiers: (uint32_t color)
 * - %F : forground color
 * - %B : background color
 * - %R : reset color
 *
 * Alignment formats: (..., width, content, ...)
 * - %<x : left-align with padding
 * - %>x : right-align with padding
 * - %^x : center-align with padding
 *
 * @param fd The file descriptor to write to.
 * @param format The format string.
 * @param ... Additional arguments for the format string.
 * @return The number of characters printed.
 */
int		ft_fprintf(int fd, const char *format, ...);

/**
 * @brief Writes a character to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param c The character to write.
 * @return The number of characters written.
 */
ssize_t	ft_putchar_fd(int fd, const char c);

/**
 * @brief Writes an integer to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param n The integer to write.
 * @return The number of characters written.
 */
ssize_t	ft_putnbr_fd(int fd, int n);

/**
 * @brief Writes a character multiple times to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param c The character to write.
 * @param n The number of times to write the character.
 * @return The number of characters written.
 */
ssize_t	ft_putnchar_fd(int fd, const char c, size_t n);

/**
 * @brief Writes a string to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstr_fd(int fd, const char *s);

/**
 * @brief Writes a string followed by a newline to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstr_nl_fd(int fd, const char *s);

/**
 * @brief Writes a portion of a string to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to write.
 * @param n The maximum number of characters to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstrn_fd(int fd, const char *s, size_t n);

/**
 * @brief Writes a UTF-8 character multiple times to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param wide_c The UTF-8 character to write.
 * @param n The number of times to write the character.
 * @return The number of characters written.
 */
ssize_t	ft_utf8_putnchar_fd(int fd, const char *wide_c, size_t n);

/*┌───────────┐
  │ on STDOUT │
  └───────────┘*/

/**
 * @brief Prints a formatted string to standard output.
 *
 * Supported format specifiers:
 * - %c : character
 * - %s : string
 * - %p : pointer address
 * - %i / %d : signed int
 * - %u : unsigned int
 * - %l : signed long
 * - %x : unsigned long in lowercase hexadecimal
 * - %X : unsigned long in uppercase hexadecimal
 * - %b : convert the nb with given base (..., nb, "base", ...)
 * - %% : literal '%'
 *
 * Color format specifiers: (uint32_t color)
 * - %F : forground color
 * - %B : background color
 * - %R : reset color
 *
 * Supported alignment formats: (..., width, content, ...)
 * - %<x : left-align with padding
 * - %>x : right-align with padding
 * - %^x : center-align with padding
 *
 * @param format The format string.
 * @param ... Additional arguments for the format string.
 * @return The number of characters printed.
 */
int		ft_printf(const char *format, ...);

/**
 * @brief Writes a character to standard output.
 * @param c The character to write.
 * @return The number of characters written.
 */
ssize_t	ft_putchar(const char c);

/**
 * @brief Writes a string to standard output.
 * @param s The string to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstr(const char *s);

/**
 * @brief Writes a string followed by a newline to standard output.
 * @param s The string to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstr_nl(const char *s);

/**
 * @brief Writes a portion of a string to standard output.
 * @param s The string to write.
 * @param n The maximum number of characters to write.
 * @return The number of characters written.
 */
ssize_t	ft_putstrn(const char *s, size_t n);

#endif
/*** legacy ***/
/**
 * @brief Writes an unsigned integer to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param n The unsigned integer to write.
 * @return The number of characters written.
 */
//ssize_t	ft_putunbr_fd(int fd, unsigned int n);

/**
 * @brief Prints a string left-aligned with padding to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to print.
 * @param padding The total width of the output.
 * @return The number of characters printed.
 */
//ssize_t	ft_print_left_fd(int fd, const char *s, size_t padding);

/**
 * @brief Prints a string center-aligned with padding to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to print.
 * @param padding The total width of the output.
 * @return The number of characters printed.
 */
//ssize_t	ft_print_middle_fd(int fd, const char *s, size_t padding);

/**
 * @brief Prints a string right-aligned with padding to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param s The string to print.
 * @param padding The total width of the output.
 * @return The number of characters printed.
 */
//ssize_t	ft_print_right_fd(int fd, const char *s, size_t padding);

/**
 * @brief Prints a memory address to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param addr The memory address to print.
 * @return The number of characters printed.
 */
//ssize_t	ft_print_address_fd(int fd, uintptr_t addr);

/**
 * @brief Prints a hexadecimal number to a file descriptor.
 * @param fd The file descriptor to write to.
 * @param n The number to print.
 * @param uppercase Whether to use uppercase letters for hexadecimal digits.
 * @return The number of characters printed.
 */
//ssize_t	ft_print_hex_fd(int fd, unsigned long n, bool uppercase);
