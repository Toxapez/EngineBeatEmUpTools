#include "Loop.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	Loop::Start();
	while (Loop::Looping());
	Loop::Finish();
	return 0;
}