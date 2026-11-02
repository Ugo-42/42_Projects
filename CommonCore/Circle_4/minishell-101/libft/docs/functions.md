# Libft Functions

This document provides an overview of all the functions available in the `libft` library, organized by category.

---

## Allocation (`libft_allocation.h`)

- **`ft_calloc`**: Allocates memory for an array of elements and initializes it to zero.
- **`ft_calloc_2d`**: Allocates memory for a 2D array and initializes it to zero.
- **`ft_free_2d_char_array`**: Frees a 2D array of characters and sets the pointer to `NULL`.
- **`ft_free_null`**: Frees a pointer and sets it to `NULL`.
- **`ft_free_null_2d`**: Frees a 2D array and sets it to `NULL`.
- **`ft_malloc_2d`**: Allocates memory for a 2D array without initialization.
- **`ft_realloc`**: Reallocates memory for a block of memory.
- **`ft_recalloc`**: Reallocates memory for a block of memory and set the rest to '\0'.

---

## Cleanup (`libft_cleanup.h`)

- **`ft_cexit`**: Exits the program after performing a cleanup operation.

---

## Color (`libft_color.h`)

- **`ft_brighten_color`**: brighten the passed color with percentage.
- **`ft_change_color`**: Changes the terminal text color to the specified color.
- **`ft_darken_color`**: darken the passed color with percentage.
- **`ft_loop_color_value`**: Cycles through a set of predefined colors and returns the next color value.
- **`ft_loop_color`**: Loops through a set of colors and applies them to the terminal text.
- **`ft_print_colored`**: Prints a string in a specified color.
- **`ft_print_nl_colored`**: Prints a string in a specified color, followed by a newline.
- **`ft_print_rainbow`**: Prints a string in a rainbow gradient of colors.
- **`ft_print_shade`**: Prints a string with a gradient of colors between two specified values.
- **`ft_reset_color`**: Resets the terminal text color to the default.

---

## Conversion (`libft_conversion.h`)

- **`ft_atoi`**: Converts a string to an integer.
- **`ft_tolower`**: Converts an uppercase character to lowercase.
- **`ft_toupper`**: Converts a lowercase character to uppercase.
- **`ft_itoa`**: Converts an integer to a string.

---

## Count (`libft_count.h`)

- **`ft_count_words`**: Counts the number of words in a string separated by a given delimiter.
- **`ft_strlen`**: Calculates the length of a string.
- **`ft_strnlen`**: Calculates the length of a string up to `max_len`.
- **`ft_strlen_2d`**: Calculates the total length of a 2D array of strings.
- **`ft_utf8_strlen`**: Calculates the length of a UTF-8 encoded string.
- **`ft_utf8_charlen`**: Calculates the length of a single UTF-8 character.
- **`ft_utf8_visual_len`**: Calculates the visual length of a UTF-8 encoded string.
- **`ft_utf8_count_bytes`**: Counts the number of bytes in a UTF-8 string up to a given number of characters.
- **`ft_count_words_quoted`**: Counts the number of words in a string, considering quoted sections as single words.

---

## Error (`libft_error.h`)

- **`ft_fwarning`**: Prints a formatted warning message to the standard error stream.
- **`ft_warning`**: Prints a warning message to the standard error stream.
- **`ft_exit_error`**: Exits the program with an error message.
- **`ft_fexit_error`**: Exits the program with a formatted error message.
- **`ft_cexit_error`**: Exits the program with an error message after performing cleanup.
- **`ft_fcexit_error`**: Exits the program with a formatted error message after performing cleanup.

---

## Flexistr (`libft_flexistr.h`)

- **`fs_add`**: Add a string at a given index for a flexible string.
- **`fs_append`**: Appends a string to a flexible string, with an option to free the input string.
- **`fs_finalize`**: Finalizes a flexible string and returns the resulting string.
- **`fs_free`**: Frees the memory allocated for a flexible string.
- **`fs_init`**: Initializes a flexible string with a specified initial size.
- **`fs_remove`**: Removes a part of a flexible string.
- **`fs_resize`**: Resizes a flexible string to a new size.

---

## Is (`libft_is.h`)

- **`ft_is_cjk`**: Checks if a character is a CJK (Chinese, Japanese, Korean) character.
- **`ft_is_emoji`**: Checks if a character is an emoji.
- **`ft_is_in_set`**: Checks if a character is in a given set of characters.
- **`ft_is_not_in_set`**: Checks if a character is not in a given set of characters.
- **`ft_is_power_of_2`**: Checks if a number is a power of 2.
- **`ft_is_alnum`**: Checks if a character is alphanumeric.
- **`ft_is_alpha`**: Checks if a character is alphabetic.
- **`ft_is_ascii`**: Checks if a character is an ASCII character.
- **`ft_is_digit`**: Checks if a character is a digit.
- **`ft_is_print`**: Checks if a character is printable.
- **`ft_is_quote`**: Checks if a character is a quote character.
- **`ft_is_space`**: Checks if a character is a whitespace character.

---

## List (`libft_list.h`)

- **`ft_lstsize`**: Counts the number of nodes in a linked list.
- **`ft_lstadd_back`**: Adds a new node to the end of a linked list.
- **`ft_lstadd_front`**: Adds a new node to the beginning of a linked list.
- **`ft_lstclear`**: Deletes and frees all nodes in a linked list.
- **`ft_lstdelone`**: Deletes and frees a single node in a linked list.
- **`ft_lstiter`**: Iterates through a linked list and applies a function to each node.
- **`ft_lstlast`**: Returns the last node of a linked list.
- **`ft_lstmap`**: Creates a new linked list by applying a function to each node of an existing list.
- **`ft_lstnew`**: Creates a new node for a linked list.

---

## Maths (`libft_maths.h`)

- **`ft_cmp_strnb`**: Compares two string-based numbers.
- **`ft_max_strnb`**: Finds the maximum value among an array of string-based numbers.
- **`ft_min_strnb`**: Finds the minimum value among an array of string-based numbers.
- **`ft_next_power_of_2`**: Calculates the next power of 2 greater than the given number.
- **`ft_normalize`**: Normalize nb within `min` and `max` bounds.
- **`ft_percentile_strnb`**: Calculates the percentile value from an array of string-based numbers.

---

## Memory (`libft_memory.h`)

- **`ft_memcmp`**: Compares two memory blocks.
- **`ft_memchr`**: Searches for a byte in a memory block.
- **`ft_memcpy`**: Copies memory from one location to another.
- **`ft_memmove`**: Moves memory from one location to another, handling overlap.
- **`ft_memset`**: Sets a memory block to a specified value.
- **`ft_bzero`**: Sets a memory block to zero.
- **`ft_ultimate_bzero`**: Sets multiple memory blocks to zero based on a format string.
- **`ft_swap_address`**: Swaps the addresses of two pointers.
- **`ft_swap_content`**: Swaps the contents of two memory blocks.

---

## Print (`libft_print.h`)

### On File Descriptors

- **`ft_fprintf`**: Prints a formatted string to a file descriptor.
- **`ft_putchar_fd`**: Writes a character to a file descriptor.
- **`ft_putnbr_fd`**: Writes an integer to a file descriptor.
- **`ft_putnchar_fd`**: Writes a character multiple times to a file descriptor.
- **`ft_putstr_fd`**: Writes a string to a file descriptor.
- **`ft_putstr_nl_fd`**: Writes a string followed by a newline to a file descriptor.
- **`ft_putstrn_fd`**: Writes a portion of a string to a file descriptor.
- **`ft_utf8_putnchar_fd`**: Writes a UTF-8 character multiple times to a file descriptor.

### On Standard Output

- **`ft_printf`**: Prints a formatted string to standard output.
- **`ft_putchar`**: Writes a character to standard output.
- **`ft_putstr`**: Writes a string to standard output.
- **`ft_putstr_nl`**: Writes a string followed by a newline to standard output.
- **`ft_putstrn`**: Writes a portion of a string to standard output.

---

## Skip (`libft_skip.h`)

- **`ft_skip_quoted`**: Skips over a quoted section in a string.
- **`ft_skip_chars`**: Skips over consecutive occurrences of a specific character.
- **`ft_skip_chars_in_set`**: Skips over consecutive characters that are part of a given set.
- **`ft_skip_not_chars`**: Skips over consecutive characters that are not a specific character.
- **`ft_skip_spaces`**: Skips over whitespace characters in a string.
- **`ft_skip_word`**: Skips over a single word in a string.

---

## String (`libft_string.h`)

- **`ft_strcspn`**: Calculates the length of the initial segment of `s` that does not contain any characters from `reject`.
- **`ft_strspn`**: Calculates the length of the initial segment of `s` that contains only characters from `accept`.
- **`ft_strcmp`**: Compares two strings lexicographically.
- **`ft_strncmp`**: Compares up to `n` characters of two strings lexicographically.
- **`ft_cmp_extension`**: Checks if a string has a specific file extension.
- **`ft_split_2d`**: Splits a 2D array of strings into smaller arrays based on a set of delimiters.
- **`ft_split`**: Splits a string into an array of strings using a delimiter character.
- **`ft_split_quoted`**: Splits a string into an array of strings, treating quoted sections as single tokens.
- **`ft_strdup_2d`**: Duplicates a 2D array of strings.
- **`ft_str_ultimate_join`**: Joins multiple strings into a single string.
- **`ft_strchr`**: Searches for the first occurrence of a character in a string.
- **`ft_strdup`**: Duplicates a string.
- **`ft_stringf`**: Formats a string using a format specifier and additional arguments.
- **`ft_strjoin`**: Joins two strings into a single string.
- **`ft_fstrjoin`**: Joins two strings into a single string and frees the input strings.
- **`ft_strcpy`**: Copies a string from source to destination.
- **`ft_strncpy`**: Copies up to `n` characters from source to destination.
- **`ft_strndup`**: Duplicates up to `n` characters of a string.
- **`ft_strnstr`**: Locates a substring within a string, searching up to `len` characters.
- **`ft_strrchr`**: Locates the last occurrence of a character in a string.
- **`ft_utf8_strncpy`**: Copies a UTF-8 string into a destination buffer.
- **`ft_utf8_visual_strncpy`**: Copies a UTF-8 string into a destination buffer, respecting visual width.

---

## Sorting (`libft_sort.h`)

- **`ft_is_sorted`**: Checks if an array is sorted.
- **`ft_qsort`**: Sorts an array using the quicksort algorithm.

---

## Other (`libft_other.h`)

- **`ft_segfault`**: Triggers a segmentation fault for debugging purposes.
- **`ft_timeout`**: Simulates a timeout by limiting the number of calls to a function.
