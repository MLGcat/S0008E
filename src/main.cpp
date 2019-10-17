#include <iostream>
#include <chrono>
#include <string.h>
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
	if(argc > 6 && !strcmp(argv[1], "-w") && !strcmp(argv[3], "-h") && !strcmp(argv[5], "-s"))
	{
		width = stoi(argv[2]);
		height = stoi(argv[4]);
		samples = stoi(argv[6]);
		PathTracer tracer(width, height);
		tracer.Render(samples, 50);
	}
}