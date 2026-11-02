/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:02:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/09 12:02:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45)
	, _target("Default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", 72, 45)
	, _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other)
	, _target(other._target) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


RobotomyRequestForm::~RobotomyRequestForm() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


/* =============================== helper =================================== */
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED   "\033[1;31m"

static void simulateWork(const std::string& description, int durationMs, bool ok)
{
    const int frames = durationMs / 200;
    const int width = 6;
    int dir = 1;
    int pos = 0;

    for (int t = 0; t < frames; t++)
    {
        std::cout << "\r[ ";

        for (int i = 0; i < width; i++) {
            std::cout << (i == pos ? YELLOW "*" : " ") << RESET;
        }

        std::cout << " ] " << description << "... " << std::flush;
        usleep(200000);

        pos += dir;
        if (pos == width - 1 || pos == 0)
            dir = -dir;
    }

    std::cout << "\r[" << (ok ? GREEN "   OK   " : RED " FAILED ") << RESET << "] "
              << description << "... " << std::endl;
}

static int randWorkTime(int max)
{
	const int r = rand() % (max + 1);
	return (r > 250 ? r : 250);
}


/* ========================================================================== */

#define REINTER_ULONG( ptr ) reinterpret_cast<unsigned long>(ptr)
#define CAST_UINT( ptr ) static_cast<unsigned int>(ptr)

void	RobotomyRequestForm::action() const
{
	static bool init;
	if (!init)
	{
		int dummy;
		srand(CAST_UINT(time(NULL) ^ CAST_UINT(REINTER_ULONG(&dummy))));
		init = true;
	}

	bool success = rand() % 2;

	ECHO(I("Starting robotomy procedure on " + _target + "..."));
	simulateWork("Robotomy init", randWorkTime(3000), true);
	simulateWork("Checking systems", randWorkTime(500), true);
	simulateWork("Calibrating sensors", randWorkTime(500), true);
	simulateWork("Calibrating drill", randWorkTime(500), true);
	simulateWork("Positioning on " + I(_target), randWorkTime(1000), true);
	simulateWork("Drilling into " + I(_target), randWorkTime(3000), success);
	simulateWork("Finalizing robotomy", randWorkTime(1000), success);

	if (success)
		ECHO("\n$ " + rgb(125,255,125)(_target + " has been robotomized successfully!"));
	else
		ECHO("\n$ " + rgb(255,125,125)("The robotomy on " + _target + " has failed!"));
}

