#include <raylib.h>
#include <vector>
#include "src/state_machine.h"
#include <iostream>

int main() {
	InitWindow(800, 800, "Graph-vs");

	Vertex* v = new Vertex; 
	v->set_loc(Vector2({100, 100}));
	std::vector<Vertex*> vertices; 
	std::cout << "Pushing" << std::endl; 
	vertices.push_back(v);

	StateMachine sm; 
	sm.start(vertices);

	float delta_time;
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_ESCAPE) or
				IsKeyDown(KEY_ESCAPE)) {
			return 0;
		}

		delta_time = GetFrameTime();
		sm.update(delta_time);
		sm.draw();
	}

	return 0;
}

