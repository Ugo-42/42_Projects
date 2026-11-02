/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/28 14:50:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <cerrno>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <exception>
#include <ctime>

/* ************************************************************************** */
/*                                   Helper                                   */
/* ************************************************************************** */

static std::string trunc(const char *s)
{
	const size_t max_len = 80;

	std::string out(s);
	if (out.size() > max_len)
		out = out.substr(0, max_len) + "...";
	return out;
}

template <typename Container>
static void fill_container(Container &c, int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		char *end = NULL;
		errno = 0;

		long value = std::strtol(argv[i], &end, 10);

		if (end == argv[i] || *end != '\0')
			throw std::invalid_argument("Non-numeric argument: `" + trunc(argv[i]) + "`.");
		if (errno == ERANGE)
			throw std::invalid_argument("Integer `" + trunc(argv[i]) + "` is out of range.");
		if (value > INT_MAX)
			throw std::invalid_argument("Integer `" + trunc(argv[i]) + "` is too large.");
		if (value < 0)
			throw std::invalid_argument("Integer `" + trunc(argv[i]) + "` is negative.");

		c.push_back(static_cast<int>(value));
	}
}

/* ************************************************************************** */
/*                                   Printer                                  */
/* ************************************************************************** */

void print_duration(clock_t start, clock_t end, const char* label, size_t n_elem)
{
    double sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    if (sec >= 1.0)
        ECHO(label << " sort time (" << n_elem << " nb): " << sec << " seconds");
    else if (sec >= 0.001)
        ECHO(label << " sort time (" << n_elem << " nb): " << sec * 1000.0 << " ms");
    else
        ECHO(label << " sort time (" << n_elem << " nb): " << sec * 1000000.0 << " µs");
}

static void color_shade(int value, int max_value, int &r, int &g, int &b)
{
	int r_start = 0, g_start = 111, b_start = 177;
	int r_end   = 77, g_end   = 0, b_end   = 177;

	double t = (max_value > 0) ? (double)value / max_value : 0.0;

	r = r_start + int(t * (r_end - r_start));
	g = g_start + int(t * (g_end - g_start));
	b = b_start + int(t * (b_end - b_start));
}

static void print_array(const char *label, const std::vector<int> &v)
{
	PRINT(B(label));

	int max_value = 0;
	for (size_t i = 0; i < v.size(); ++i)
		if (v[i] > max_value) max_value = v[i];

	for (size_t i = 0; i < v.size(); ++i)
	{
		int r, g, b;
		color_shade(v[i], max_value, r, g, b);
		PRINT(rgb(r,g,b)(B(to_string(v[i]))) << " ");
	}
	NEW_LINE;
}

/* ************************************************************************** */
/*                                    Main                                    */
/* ************************************************************************** */

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		ECHO("Usage: " << argv[0] << " <positive_integer> [<positive_integer> ...]");
		return 0;
	}

	std::vector<int> base;

	try
	{
		fill_container(base, argc, argv);
	}
	catch (std::exception &e)
	{
		ECHO(rgb(255,0,0)("Error: ") << e.what());
		return 1;
	}

	print_array("Before: ", base);

	/* ********************************************** */
	/*                     Vector                     */
	/* ********************************************** */

	std::vector<int> v = base;

	clock_t start_v = clock();
	ford_johnson(v);
	clock_t end_v = clock();

	print_array("After : ", v);
	print_duration(start_v, end_v, "Vector", v.size());

	/* ********************************************** */
	/*                     Deque                      */
	/* ********************************************** */

	std::deque<int> d(base.begin(), base.end());

	clock_t start_d = clock();
	ford_johnson(d);
	clock_t end_d = clock();

	print_duration(start_d, end_d, "Deque", d.size());

	return 0;
}
