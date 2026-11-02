# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/04/30 10:28:22 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .makefile.conf/libft.mk

NAME   = libft.a

SRCS_DIR = srcs
OBJS_DIR = objs
HEADERS  = includes
INCLUDES = $(addprefix -I, $(HEADERS))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# Functions: 153
SRCS = allocation/ft_calloc.c                  allocation/ft_calloc_2d.c \
       allocation/ft_free_2d_char_array.c      allocation/ft_free_null.c \
       allocation/ft_close_null.c              allocation/ft_free_null_2d.c \
       allocation/ft_malloc_2d.c               allocation/ft_realloc.c \
       allocation/ft_recalloc.c                cleanup/ft_cexit.c \
       color/ft_brighten_color.c               color/ft_change_color.c \
       color/ft_darken_color.c                 color/ft_loop_color.c \
       color/ft_loop_color_value.c             color/ft_print_colored.c \
       color/ft_print_nl_colored.c             color/ft_print_rainbow.c \
       color/ft_print_shade.c                  color/ft_reset_color.c \
       comparison/ft_iternary.c                comparison/ft_ternary.c \
       conversion/ft_atoi.c                    conversion/ft_itoa.c \
       conversion/ft_tolower.c                 conversion/ft_toupper.c \
       count/ft_count_words.c                  count/ft_count_words_quoted.c \
       count/ft_strlen.c                       count/ft_strlen_2d.c \
       count/ft_strnlen.c                      count/ft_utf8_charlen.c \
       count/ft_utf8_count_bytes.c             count/ft_utf8_strlen.c \
       count/ft_utf8_visual_len.c              error/ft_cexit_error.c \
       error/ft_exit_error.c                   error/ft_fcexit_error.c \
       error/ft_fexit_error.c                  error/ft_fwarning.c \
       error/ft_warning.c                      flexible_string/fs_add.c \
       flexible_string/fs_append.c             flexible_string/fs_appendf.c \
       flexible_string/fs_append_char.c        flexible_string/fs_append_nb.c \
       flexible_string/fs_finalize.c           flexible_string/fs_free.c \
       flexible_string/fs_init.c               flexible_string/fs_n_append.c \
       flexible_string/fs_remove.c             flexible_string/fs_resize.c \
       flexible_string_2d/flexistr2d_add.c     flexible_string_2d/flexistr2d_append.c \
       flexible_string_2d/flexistr2d_close.c   flexible_string_2d/flexistr2d_dup.c \
       flexible_string_2d/flexistr2d_find.c    flexible_string_2d/flexistr2d_get.c \
       flexible_string_2d/flexistr2d_init.c    flexible_string_2d/flexistr2d_join.c \
       flexible_string_2d/flexistr2d_move.c    flexible_string_2d/flexistr2d_njoin.c \
       flexible_string_2d/flexistr2d_pop.c     flexible_string_2d/flexistr2d_realloc.c \
       flexible_string_2d/flexistr2d_remove.c  flexible_string_2d/flexistr2d_replace.c \
       flexible_string_2d/flexistr2d_reverse.c is/ft_is_alnum.c \
       is/ft_is_alpha.c                        is/ft_is_ascii.c \
       is/ft_is_cjk.c                          is/ft_is_digit.c \
       is/ft_is_emoji.c                        is/ft_is_in_set.c \
       is/ft_is_not_in_set.c                   is/ft_is_power_of_2.c \
       is/ft_is_print.c                        is/ft_is_quote.c \
       is/ft_is_space.c                        list/ft_lstadd_back.c \
       list/ft_lstadd_front.c                  list/ft_lstclear.c \
       list/ft_lstdelone.c                     list/ft_lstiter.c \
       list/ft_lstlast.c                       list/ft_lstmap.c \
       list/ft_lstnew.c                        list/ft_lstsize.c \
       maths/ft_cmp_strnb.c                    maths/ft_max_strnb.c \
       maths/ft_min_strnb.c                    maths/ft_next_power_of_2.c \
       maths/ft_normalize.c                    maths/ft_percentile_strnb.c \
       memory/ft_bzero.c                       memory/ft_memchr.c \
       memory/ft_memcmp.c                      memory/ft_memcpy.c \
       memory/ft_memmove.c                     memory/ft_memset.c \
       memory/ft_swap_address.c                memory/ft_swap_content.c \
       memory/ft_ultimate_bzero.c              other/ft_random.c \
       other/ft_segfault.c                     other/ft_timeout.c \
       print/ft_fprintf.c                      print/ft_putchar_fd.c \
       print/ft_putnbr_fd.c                    print/ft_putnchar_fd.c \
       print/ft_putstr_fd.c                    print/ft_putstr_nl_fd.c \
       print/ft_putstrn_fd.c                   print/ft_utf8_putnchar_fd.c \
       print/stdout/ft_printf.c                print/stdout/ft_putchar.c \
       print/stdout/ft_putstr.c                print/stdout/ft_putstr_nl.c \
       print/stdout/ft_putstrn.c               read/get_next_line.c \
       read/gnl_reset_fd.c                     skip/ft_skip_chars.c \
       skip/ft_skip_chars_in_set.c             skip/ft_skip_not_chars.c \
       skip/ft_skip_quoted.c                   skip/ft_skip_spaces.c \
       skip/ft_skip_word.c                     sorting/ft_is_sorted.c \
       sorting/ft_qsort.c                      string/ft_cmp_extension.c \
       string/ft_fstrjoin.c                    string/ft_split.c \
       string/ft_split_quoted.c                string/ft_str_ultimate_join.c \
       string/ft_strchr.c                      string/ft_strcmp.c \
       string/ft_strcpy.c                      string/ft_strcspn.c \
       string/ft_strdup.c                      string/ft_strdup_2d.c \
       string/ft_stringf.c                     string/ft_vstringf.c \
       string/ft_strjoin.c                     string/ft_strncmp.c \
       string/ft_strncpy.c                     string/ft_strndup.c \
       string/ft_strnstr.c                     string/ft_strrchr.c \
       string/ft_strspn.c                      string/ft_utf8_strncpy.c \
       string/ft_utf8_visual_strncpy.c         string/internal/internal_append.c \
       string/internal/internal_padding.c

#=- RULES -=#
all: $(NAME)

$(NAME): $(OBJS)
	$(call build_archive,$(NAME),$(OBJS),$(BOLD)$(GREEN))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed $(NAME)$(RESET_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
