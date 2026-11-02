# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 12:30:00 by ugwentzi          #+#    #+#              #
#    Updated: 2025/02/07 15:15:14 by ugwentzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include makefile.conf/progress_bar.mk
include makefile.conf/config.mk
include makefile.conf/color.mk
include makefile.conf/compilation.mk

#=- Name -=#
NAME   = libft.a

#=- Directories -=#
SRCS_DIR = srcs
OBJS_DIR = objs

#=- Sources -=#
INCLUDES = -Iincludes

SRCS = allocation/ft_calloc.c					allocation/ft_free_2d_array.c \
       allocation/ft_free_null.c				allocation/ft_realloc.c \
       conversion/ft_addrtoa.c					conversion/ft_atoi.c \
       conversion/ft_ctoa.c						conversion/ft_itoa.c \
       conversion/ft_tolower.c					conversion/ft_toupper.c \
       conversion/ft_utoa.c						conversion/ft_xtoa.c \
       count/ft_count_words.c					count/ft_count_words_quoted.c \
       count/ft_strlen.c						count/ft_utf8_charlen.c \
       count/ft_utf8_strlen.c					count/ft_utf8_visual_len.c \
       count/ft_utf8_count_bytes.c				error/ft_exit_error.c \
       error/ft_cexit_error.c					error/ft_fexit_error.c \
       error/ft_fcexit_error.c					error/ft_fwarning.c \
       error/ft_warning.c						is/ft_is_alnum.c \
       is/ft_is_alpha.c							is/ft_is_ascii.c \
       is/ft_is_cjk.c							is/ft_is_digit.c \
       is/ft_is_emoji.c							is/ft_is_print.c \
       is/ft_is_quote.c							is/ft_is_space.c \
       list/ft_lstadd_back.c					list/ft_lstadd_front.c \
       list/ft_lstclear.c						list/ft_lstdelone.c \
       list/ft_lstiter.c						list/ft_lstlast.c \
       list/ft_lstmap.c							list/ft_lstnew.c \
       list/ft_lstsize.c						maths/ft_cmp_strnb.c \
       maths/ft_max_strnb.c						maths/ft_min_strnb.c \
       maths/ft_percentile_strnb.c				memory/ft_bzero.c \
       memory/ft_memchr.c						memory/ft_memcmp.c \
       memory/ft_memcpy.c						memory/ft_memmove.c \
       memory/ft_memset.c						memory/ft_swap_address.c \
       memory/ft_swap_content.c					other/ft_color.c \
       other/ft_segfault.c						other/ft_timeout.c \
       print/ft_fprintf.c						print/ft_print_address_fd.c \
       print/ft_print_hex_fd.c					print/ft_print_left_fd.c \
       print/ft_print_middle_fd.c				print/ft_print_right_fd.c \
       print/ft_printf.c						print/ft_putchar_fd.c \
       print/ft_putnbr_fd.c						print/ft_putnchar_fd.c \
       print/ft_putstr_fd.c						print/ft_putstr_nl_fd.c \
       print/ft_putstrn_fd.c					print/ft_putunbr_fd.c \
       print/ft_utf8_putnchar_fd.c				print/stdout/ft_putstr.c \
       print/stdout/ft_putstr_colored.c			print/stdout/ft_putstr_nl.c \
       print/stdout/ft_putstr_nl_colored.c		read/get_next_line.c \
       read/gnl_reset_fd.c						skip/ft_skip_chars.c \
       skip/ft_skip_not_chars.c					skip/ft_skip_quoted.c \
       skip/ft_skip_spaces.c					skip/ft_skip_word.c \
       sorting/ft_is_sorted.c					sorting/ft_qsort.c \
       string/ft_split.c						string/ft_split_quoted.c \
       string/ft_str_ultimate_join.c			string/ft_strchr.c \
       string/ft_strcmp.c						string/ft_strcpy.c \
       string/ft_strdup.c						string/ft_strdup_2d.c \
       string/ft_stringf.c						string/ft_strjoin.c \
       string/ft_strncmp.c						string/ft_strncpy.c \
       string/ft_strndup.c						string/ft_strnstr.c \
       string/ft_strrchr.c						string/ft_utf8_strncpy.c \
       string/ft_utf8_visual_strncpy.c	

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#=- RULES -=#
all: $(NAME)

#=- Archive Creation -=#
$(NAME): $(OBJS)
	$(call build_archive,$(NAME),$(OBJS),$(BOLD)$(GREEN))

#=- Objects Compilation -=#
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(call create_objs_tree,$(SRCS_DIR),$(OBJS_DIR))
	$(call compile_object,$(NAME),$(INCLUDES),$(SRCS),$(BOLD)$(YELLOW))

#=- Clean Rules -=#
clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(RED)$$ $(NAME): Removed objects$(RESET_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$$ $(NAME): Removed $(NAME)$(RESET_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
