#include "vertex.hpp"
#include <cstddef>
#include <functional>
#include <raylib.h>
#include <vector>
#include "raylib_limitations.hpp"

class StateMachine {
	private:
	std::vector<Vertex*> vertices; 
	std::vector<std::function<void()>> mouse_buttons; 

	private:
	bool any_lines_moving;
	size_t vertex_index, line_index; 

	private:
	void handle_left_click() {
		if (any_lines_moving) {
			vertices.at(vertex_index)->lines.at(line_index).state = VertexLineState::DONE;
			any_lines_moving = false;
		}

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
		if (any_lines_moving) {
			vertices.at(vertex_index)->lines.at(line_index).state = VertexLineState::DONE;
			any_lines_moving = false;
		}

		for (size_t i = 0; i < vertices.size(); ++i) {
			if (vertices.at(i)->is_point_inside(GetMousePosition())) {
				vertex_index = i;
				line_index = vertices.at(i)->spawn_line();
				any_lines_moving = true;
				return;
			}
		}
	}

	public:
	StateMachine() : 
		mouse_buttons(RaylibLimitations::MouseButtonLimit) 
	{
		mouse_buttons.at(MOUSE_LEFT_BUTTON) = [this](){handle_left_click();};
		mouse_buttons.at(MOUSE_BUTTON_RIGHT) = [this](){handle_right_click();};

		any_lines_moving = false; 
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

