#include <raylib.h>

struct VertexMenu {
	Vector2 loc; 
	bool visible; 
	int width = 100, height = 100; 
	
	void draw() {
		if (!visible) return;
		DrawRectangle(loc.x, loc.y, width, height, BLUE);
	}
};

