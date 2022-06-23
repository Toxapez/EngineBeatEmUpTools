#include "FigureDrawer.h"

LineP FigureDrawer::line;
TriangleP FigureDrawer::triangle;

Mesh FigureDrawer::lineM;
Mesh FigureDrawer::triangleM;

Mesh FigureDrawer::rectM;
RectP FigureDrawer::rect;

void FigureDrawer::Start() {
	lineM = Mesh(&line,
		glm::vec3(0, 0, 0),//pos
		glm::vec3(0),//origin
		glm::vec3(0),//rot
		glm::vec3(1),//scale
		"");
	triangleM = Mesh(&triangle,
		glm::vec3(0, 0, 0),//pos
		glm::vec3(0),//origin
		glm::vec3(0),//rot
		glm::vec3(1),//scale
		"");

	rectM = Mesh(&rect,
		glm::vec3(0, 0, 0),//pos
		glm::vec3(0),//origin
		glm::vec3(0),//rot
		glm::vec3(1),//scale
		"");
}

void FigureDrawer::DrawRect(Rect r, Color _c, bool camDependet) {
	if (camDependet) {
		r.w *= Cam::currentCam->zoom;
		r.h *= Cam::currentCam->zoom;
		r.x -= r.w / 2;
		r.y -= r.h / 2;
	}

	DrawLine(Line(Vector2(r.x, r.y), Vector2(r.x + r.w, r.y)), _c);
	DrawLine(Line(Vector2(r.x, r.y), Vector2(r.x, r.y + r.h)), _c);
	DrawLine(Line(Vector2(r.x + r.w, r.y), Vector2(r.x + r.w, r.y + r.h)), _c);
	DrawLine(Line(Vector2(r.x, r.y + r.h), Vector2(r.x + r.w, r.y + r.h)), _c);
}

void FigureDrawer::DrawRectRef(Rect _r, Color _c, Transform ref, bool camDependet) {
	DrawRect(_r + ref.position, _c, camDependet);
}



void FigureDrawer::DrawRectFourPoint(RectFourPoint _r, Color _c) {
	Line lines[4];
	_r.GetLines(lines);
	for (int i = 0; i < 4; i++) {
		FigureDrawer::DrawLine(lines[i], _c);
	}
}
void FigureDrawer::DrawRectFourPointRef(RectFourPoint _r, Color _c, Transform ref) {
	Line lines[4];
	_r.GetLines(lines);
	for (int i = 0; i < 4; i++) {
		FigureDrawer::DrawLineRef(lines[i], _c, ref);
	}
}

void FigureDrawer::DrawFillRect(Rect r, Color _c, bool camDependet) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (camDependet) {
		r.w *= Cam::currentCam->zoom;
		r.h *= Cam::currentCam->zoom;
		r.x -= r.w / 2;
		r.y -= r.h / 2;
	}
	
	rect = RectP(glm::vec3(r.x,r.y,0), glm::vec3(r.x + r.w, r.y, 0), glm::vec3(r.x, r.y + r.h, 0), glm::vec3(r.x + r.w, r.y + r.h,0),
		glm::vec3(_c.r, _c.g, _c.b), glm::vec3(_c.r, _c.g, _c.b), glm::vec3(_c.r, _c.g, _c.b), glm::vec3(_c.r, _c.g, _c.b));
	rectM.render(OpenGLClass::shaders[3]);
}

void FigureDrawer::DrawFillRectRef(Rect r, Color _c, Transform ref, bool camDependet) {
	DrawFillRect(r + ref.position, _c,camDependet);
}


void FigureDrawer::DrawLine(Line r, Color _c) {
	line = LineP(glm::vec3(r.points.first.x, r.points.first.y, 0), glm::vec3(r.points.second.x, r.points.second.y, 0), glm::vec3(_c.r, _c.g, _c.b));
	lineM.render(OpenGLClass::shaders[1]);
}

void FigureDrawer::DrawLineRef(Line _r, Color _c, Transform ref) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DrawLine(Line(_r.points.first+ref.position, _r.points.second + ref.position),_c);
}

void FigureDrawer::DrawTriangle(TriangleP _r) {
	triangle = _r;
	triangleM.render(OpenGLClass::shaders[0]);
}

void FigureDrawer::DrawTexture(unsigned int texture, SDL_Rect _r, Color c, bool flipHorizontal, bool flipVertical,
	float rot, Vector2 rotPoint) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::vec2 uv1 = glm::vec2(flipHorizontal, 0);
	glm::vec2 uv2 = glm::vec2(!flipHorizontal, 0);
	glm::vec2 uv3 = glm::vec2(flipHorizontal, 1);
	glm::vec2 uv4 = glm::vec2(!flipHorizontal, 1);

	glm::vec3 color = glm::vec3(c.r,c.g,c.b);

	Vector2 v1 = Vector2(_r.x, _r.y);
	Vector2 v2 = Vector2(_r.x + _r.w, _r.y + _r.h);

	Vector2 p1 = Vector2(v1.x, v1.y);
	Vector2 p2 = Vector2(v2.x, v1.y);
	Vector2 p3 = Vector2(v1.x, v2.y);
	Vector2 p4 = Vector2(v2.x, v2.y);

	if (rot != 0) {
		p1 = p1.RotateRef(rot, v1 + rotPoint);
		p2 = p2.RotateRef(rot, v1 + rotPoint);
		p3 = p3.RotateRef(rot, v1 + rotPoint);
		p4 = p4.RotateRef(rot, v1 + rotPoint);
	}

	rect = RectP(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0),
		glm::vec3(p3.x, p3.y, 0), glm::vec3(p4.x, p4.y, 0),
		color, color, color, color, uv1, uv2, uv3, uv4);

	rectM.texture = texture;

	rectM.render(OpenGLClass::shaders[2]);
}