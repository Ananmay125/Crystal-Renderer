#include <iostream>
#include "Renderer.h"

int main() {

	Renderer crystalRenderer;

	crystalRenderer.init();

	while (true) {
	
		crystalRenderer.run();
	
	}

	crystalRenderer.clean();
	return 0;
}
