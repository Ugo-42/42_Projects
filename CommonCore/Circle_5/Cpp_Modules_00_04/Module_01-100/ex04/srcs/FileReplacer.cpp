/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:21:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/13 10:22:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <fstream>

/* ************************************************************************** */
/*                              Constructors                                  */
/* ************************************************************************** */


FileReplacer::FileReplacer(const t_string& filename, const t_string& s1, const t_string& s2)
	: _filename(filename), _s1(s1), _s2(s2),
	  _afterLines(NULL), _lineCount(0)
{
	if (_s1.empty())
	{
		ERROR("Error: String to replace cannot be empty.");
		return;
	}

	_lineCount = countLines();
	_afterLines = new t_string[_lineCount];
}


/* ************************************************************************** */
/*                                Helpers                                     */
/* ************************************************************************** */
 

static t_string replaceLine(const t_string &src, const t_string &s1, const t_string &s2)
{
	if (s1.empty())
		return src;

	t_string result;
	size_t pos = 0;
	size_t last = 0;

	while ((pos = src.find(s1, last)) != t_string::npos)
	{
		result += src.substr(last, pos - last);
		result += s2;
		last = pos + s1.length();
	}
	result += src.substr(last);
	return result;
}


/* ************************************************************************** */
/*                            Member Functions                                */
/* ************************************************************************** */


int FileReplacer::countLines() const
{
	std::ifstream inputFile(_filename.c_str());
	if (!inputFile.is_open())
	{
		ERROR("Error: Could not open file " << _filename);
		return 0;
	}

	int count = 0;
	t_string line;
	while (std::getline(inputFile, line))
		count++;
	inputFile.close();
	return count;
}

void FileReplacer::readAndReplace()
{
	std::ifstream inputFile(_filename.c_str());
	if (!inputFile.is_open())
	{
		ERROR("Error: Could not open file " << _filename);
		return;
	}

	std::ofstream outputFile((_filename + ".replace").c_str());
	if (!outputFile.is_open())
	{
		ERROR("Error: Could not create file " << _filename << ".replace");
		return;
	}

	t_string line;
	for (int i = 0; i < _lineCount; ++i)
	{
		if (!std::getline(inputFile, line))
			break;

		_afterLines[i] = replaceLine(line, _s1, "\033[31m" + _s2 + "\033[0m");
		outputFile << replaceLine(line, _s1, _s2) << "\n";
	}

	inputFile.close();
	outputFile.close();
}

void FileReplacer::printChanges() const
{
	ECHO(rgb(175,0,0) << BOLD << ">>> ___CHANGES___: " << RESET
		<< rgb(175,0,0) << "(" << _filename + ".replace)" << RESET);

	for (int i = 0; i < _lineCount; ++i)
		ECHO(_afterLines[i]);
}

FileReplacer::~FileReplacer()
{
	if (_afterLines)
		delete[] _afterLines;
}
