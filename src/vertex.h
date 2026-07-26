#include "vertex_menu.h"
#include "global_variables.h"
#include <raymath.h>
#include <cmath>
#include <raylib.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <iostream>
#include <utility>

enum class VertexState {
	DRAGGING, IDLE 
};

class Vertex {
	private:
	Vector2 loc; 
	std::string text; 
	float radius; 

	public:
	VertexMenu menu; 
	VertexState state; 
	Vector2 movement_offset;

	public:
	void calculate_movement_offset() {
		movement_offset.x = GetMouseX() - loc.x;
		movement_offset.y = GetMouseY() - loc.y;
	}

	public:
	Vertex() {
		radius = 100; 
		loc = GetMousePosition();
		movement_offset = {0, 0};
	}

	public:
	Vector2 get_loc() {
		return loc; 
	}

	public: 
	void set_loc(const Vector2 &loc) {
		this->loc = loc; 
	}

	public:
	std::string get_text() {
		return text;
	}

	public:
	void set_text(const std::string &text) {
		this->text = text; 
	}

	public:
	void update_text(char ch) {
		text += ch; 
	}

	public:
	float get_radius() {
		return radius;
	}

	public: 
	void set_radius(float radius) {
		if (radius < 0) {
			throw std::runtime_error("Radius can't be less than 0");
		}

		this->radius = radius; 
	}

	private:
	float get_distance(const Vector2 &point1, const Vector2 &point2) {
		return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
	}

	public:
	bool is_point_inside(const Vector2 &point) {
		return get_distance(point, loc) <= radius;
	}

	public:
	void draw() {
		DrawCircle(loc.x, loc.y, radius, WHITE);
		DrawCircleLines(loc.x, loc.y, radius, BLACK);
		if (menu.visible) menu.draw();
	}

	public:
	void update(const float &delta_time) {
		if (state == VertexState::IDLE) {
			return; 
		}

		loc.x = GetMouseX() - movement_offset.x;
		loc.y = GetMouseY() - movement_offset.y;
	}
};

