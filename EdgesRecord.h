#pragma once
#include "Meth.h"
#include <vector>

struct Trio {
	Vector2 vertex[3];
	Trio(Vector2 p1, Vector2 p2, Vector2 p3);
};

struct EdgeRecord
{
	EdgeRecord();
	EdgeRecord(Vector2 d1);
	bool type;
	Vector2 delta1;
	//static void DrawEdges(std::vector<EdgeRecord>* edges);
	static std::vector<Trio> Triangulate(std::vector<EdgeRecord>  edges);
};


struct CurveEdgeRecord : public EdgeRecord
{
	CurveEdgeRecord(Vector2 d1, Vector2 d2);
	Vector2 delta2;
	static std::vector<EdgeRecord> StraightLines(std::vector<EdgeRecord*>* edges, Vector2 drawingPos);
};

