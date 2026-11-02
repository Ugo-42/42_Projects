/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_emoji.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:23:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/06 09:43:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  CJK codepoints:
 } 0x3040  to 0x309F  => Hiragana
 } 0x30A0  to 0x30FF  => Katakana
 } 0x4E00  to 0x9FFF  => CJK Unified Ideographs
 } 0x3400  to 0x4DBF  => CJK Unified Ideographs Extension A
 } 0x20000 to 0x2A6DF => CJK Unified Ideographs Extension B
 } 0x2A700 to 0x2B73F => CJK Unified Ideographs Extension C
 } 0x2B740 to 0x2B81F => CJK Unified Ideographs Extension D
 } 0x2B820 to 0x2CEAF => CJK Unified Ideographs Extension E
 } 0x2CEB0 to 0x2EBEF => CJK Unified Ideographs Extension F
 } 0x3000  to 0x303F  => CJK Symbols and Punctuation
 } 0x31C0  to 0x31EF  => CJK Strokes
 } 0x3200  to 0x32FF  => Enclosed CJK Letters and Months
 } 0x3300  to 0x33FF  => CJK Compatibility
 } 0xF900  to 0xFAFF  => CJK Compatibility Ideographs
 } 0xFE30  to 0xFE4F  => CJK Compatibility Forms
 } 0x2E80  to 0x2EFF  => CJK Radicals Supplement
 } 0x2F00  to 0x2FDF  => Kangxi Radicals
 } 0x2FF0  to 0x2FFF  => Ideographic Description Characters
 } 0x2F800 to 0x2FA1F => CJK Compatibility Ideographs Extension
*/

// Convert UTF-8 bytes to a Unicode codepoint
static unsigned int	ft_utf8_to_codepoint(const char *wide_c)
{
	unsigned char	*bytes;

	bytes = (unsigned char *)wide_c;
	if ((*bytes & 0x80) == 0)
		return (*bytes);
	else if ((*bytes & 0xE0) == 0xC0)
		return (((bytes[0] & 0x1F) << 6) | (bytes[1] & 0x3F));
	else if ((*bytes & 0xF0) == 0xE0)
		return (((bytes[0] & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6)
			| (bytes[2] & 0x3F));
	else if ((*bytes & 0xF8) == 0xF0)
		return (((bytes[0] & 0x07) << 18) | ((bytes[1] & 0x3F) << 12)
			| ((bytes[2] & 0x3F) << 6) | (bytes[3] & 0x3F));
	return (0);
}

bool	ft_is_cjk(const char *wide_c)
{
	unsigned int	codepoint;

	codepoint = ft_utf8_to_codepoint(wide_c);
	if ((codepoint >= 0x3040 && codepoint <= 0x309F)
		|| (codepoint >= 0x30A0 && codepoint <= 0x30FF)
		|| (codepoint >= 0x4E00 && codepoint <= 0x9FFF)
		|| (codepoint >= 0x3400 && codepoint <= 0x4DBF)
		|| (codepoint >= 0x20000 && codepoint <= 0x2A6DF)
		|| (codepoint >= 0x2A700 && codepoint <= 0x2B73F)
		|| (codepoint >= 0x2B740 && codepoint <= 0x2B81F)
		|| (codepoint >= 0x2B820 && codepoint <= 0x2CEAF)
		|| (codepoint >= 0x2CEB0 && codepoint <= 0x2EBEF)
		|| (codepoint >= 0x3000 && codepoint <= 0x303F)
		|| (codepoint >= 0x31C0 && codepoint <= 0x31EF)
		|| (codepoint >= 0x3200 && codepoint <= 0x32FF)
		|| (codepoint >= 0x3300 && codepoint <= 0x33FF)
		|| (codepoint >= 0xF900 && codepoint <= 0xFAFF)
		|| (codepoint >= 0xFE30 && codepoint <= 0xFE4F)
		|| (codepoint >= 0x2E80 && codepoint <= 0x2EFF)
		|| (codepoint >= 0x2F00 && codepoint <= 0x2FDF)
		|| (codepoint >= 0x2FF0 && codepoint <= 0x2FFF)
		|| (codepoint >= 0x2F800 && codepoint <= 0x2FA1F))
		return (true);
	return (false);
}
