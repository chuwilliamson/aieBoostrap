#include "GridApp.h"

int main() {
	
	auto app = new GridApplication();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}