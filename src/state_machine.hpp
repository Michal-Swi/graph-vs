#include "vertex.h"
#include <cstddef>
#include <functional>
#include <raylib.h>
#include <vector>
#include "raylib_limitations.h"

class StateMachine {
	private:
	std::vector<Vertex*> vertices; 
	std::vector<std::function<void()>> mouse_buttons; 

	private:
	void handle_left_click() {
		for (auto &vertex : vertices) {
			if (vertex->is_point_inside(GetMousePosition())) {
				vertex->state = VertexState::DRAGGING;
				vertex->calculate_movement_offset();
				return;
			} else {
				vertex->state = VertexState::IDLE;
			}
		}
	}

	private:
	void handle_right_click() {
		for (auto &vertex : vertices) {
			if (vertex->is_point_inside(GetMousePosition())) {
			}
		}
	}

	public:
	StateMachine() : 
		mouse_buttons(RaylibLimitations::MouseButtonLimit) 
	{
		mouse_buttons.at(MOUSE_LEFT_BUTTON) = [this](){handle_left_click();};
		mouse_buttons.at(MOUSE_BUTTON_RIGHT) = [this](){handle_right_click();};
	};

	private:
	void make_all_idle() {
		for (auto &v : vertices) {
			v->state = VertexState::IDLE;
		}
	}

	public:
	void update(float &delta_time) {
		for (size_t mouse_button = 0; mouse_button < RaylibLimitations::MouseButtonLimit; ++mouse_button) {
			if (IsMouseButtonPressed(mouse_button) and mouse_buttons.at(mouse_button)) {
				mouse_buttons.at(mouse_button)();
			}
		}

		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			make_all_idle();
		}
			
		for (auto &v : vertices) {
			v->update(delta_time);
		}
	}

	public:
	void draw() {
		ClearBackground(WHITE);
		BeginDrawing();

		for (auto &v : vertices) {
			v->draw();
		}

		EndDrawing();
	}

	public:
	void start(std::vector<Vertex*> &vertices) {
		this->vertices = vertices;
	}

	public:
	void clean() {
		for (auto &v : vertices) {
			delete v; 
		}
	}
};

