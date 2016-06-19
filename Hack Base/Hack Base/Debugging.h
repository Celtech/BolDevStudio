#pragma once
#define DEBUG

#include <Windows.h>
#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Debugging
{
public:
	Debugging();
	~Debugging();
	void Message(const char *fmt, ...);

private:
	time_t rawtime;
	struct tm * timeinfo;
};