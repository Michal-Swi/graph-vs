#include <cmath>
#include <raylib.h>

enum VertexLineType {
	NonDirection, DirectionOut, DirectionIn, DirectionBoth
};

enum VertexLineState {
	MOVING, DONE
};

class VertexLine {
	public:
	Vector2 begin, end; 
	VertexLineType type; 
	VertexLineState state; 

	private:
	Vector2 vertex_center;
	float vertex_radius;

	private:
	Vector2 calculate_begin() {
		Vector2 direction = {GetMouseX() - vertex_center.x, GetMouseY() - vertex_center.y};
		const float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction = {direction.x / distance, direction.y / distance};
		direction = {direction.x * vertex_radius, direction.y * vertex_radius};

		return {vertex_center.x + direction.x, vertex_center.y + direction.y};
	}

	public:
	VertexLine(const Vector2 &vertex_center, const float &vertex_radius) {
		this->vertex_center = vertex_center;
		this->vertex_radius = vertex_radius;

		begin = calculate_begin();
		end = GetMousePosition();
		state = VertexLineState::MOVING;
	}

	public:
	void update() {
		begin = calculate_begin();
		end = GetMousePosition();
	}

	public:
	void draw() {
		DrawLine(begin.x, begin.y, end.x, end.y, BLACK);
	}
};

