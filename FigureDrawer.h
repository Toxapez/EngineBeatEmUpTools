#pragma once
#include "Rect.h"
#include "Line.h"
#include "Transform.h"
#include "RectFourPoint.h"
#include "Cam.h"
#include "OpenGLClass.h"
class FigureDrawer
{
public:
	static void Start();
	static void DrawRect(Rect _r, Color _c, bool camDependet = true);
	static void DrawRectRef(Rect _r, Color _c, Transform ref, bool camDependet = true);
	static void DrawRectFourPoint(RectFourPoint _r, Color _c);
	static void DrawRectFourPointRef(RectFourPoint _r, Color _c, Transform ref);
	static void DrawFillRect(Rect _r, Color c, bool camDependet = true);
	static void DrawFillRectRef(Rect _r, Color c, Transform ref, bool camDependet = true);
	static void DrawLine(Line _r, Color _c);
	static void DrawLineRef(Line _r, Color _c, Transform ref);
	static void DrawTriangle(TriangleP _r);
	static void DrawTexture(unsigned int texture, SDL_Rect _r, Color c = Color(255), bool flipHorizontal = false, bool flipVertical = false,
	float rot = 0, Vector2 rotPoint = Vector2(0,0));
	static Mesh lineM;
	static Mesh triangleM;
	static LineP line;
	static TriangleP triangle;
	static Mesh rectM;
	static RectP rect;
};

