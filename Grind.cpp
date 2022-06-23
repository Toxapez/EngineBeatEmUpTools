#include "Grind.h"

void Grind::Draw(Transform transform) {
	Color c = color;
	int maxY = size.y * cellSize.y * Cam::currentCam->zoom;
	for (int i = 0; i < size.x +1; i++) {
		int d = i * cellSize.x * Cam::currentCam->zoom;
		if (-transform.position.x <= d) {
			if (-transform.position.x + SDLClass::screenSizeX >= d) {
				FigureDrawer::DrawLineRef(Line(Vector2(d, 0), Vector2(d, maxY)), c, transform);
			}
		}
	}
	int maxX = size.x * cellSize.x * Cam::currentCam->zoom;
	for (int i = 0; i < size.y +1; i++) {
		int d = i * cellSize.x * Cam::currentCam->zoom;
		if (-transform.position.y <= d) {
			if (-transform.position.y + SDLClass::screenSizeY >= d) {
				FigureDrawer::DrawLineRef(Line(Vector2(0, d), Vector2(maxX, d)), c, transform);
			}
		}
	}
}

std::vector<Vector2> Grind::GetCenteredPositions(Transform transform) {
	std::vector<Vector2> r;
	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			r.push_back(transform.position + Vector2((i + .5) * cellSize.x, (j + .5) * cellSize.y));
		}
	}
	return r;
}