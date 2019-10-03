#pragma once
#include <iostream>
#include <chrono>
#include "pathtracer.h"

auto callback = [] ()
{
};

int main(int argc, const char** argv)
{
	int width;
	int height;
	unsigned int samples;

	for(int i = 0; i < argc; i++)
	{
		std::cout << "ARG[" << i << "]: " << argv[i] << std::endl;
	}
	if(argc > 7 && argv[1] == "-w" && argv[3] == "-h" && argv[5] == "-s")
	{
		width = stoi(argv[2]);
		height = stoi(argv[4]);
		samples = stoi(argv[6]);
		PathTracer tracer(width, height);
		tracer.Render(samples, width, height);
	}
}