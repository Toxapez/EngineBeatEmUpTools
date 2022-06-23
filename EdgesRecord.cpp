#include "EdgesRecord.h"

EdgeRecord::EdgeRecord() {
	type = 0;
}
EdgeRecord::EdgeRecord(Vector2 d1) : delta1(d1) {
	type = 0;
}

CurveEdgeRecord::CurveEdgeRecord(Vector2 d1, Vector2 d2) : EdgeRecord(d1) , delta2(d2) {
	type = 1;
}

std::vector<EdgeRecord> CurveEdgeRecord::StraightLines(std::vector<EdgeRecord*>* edges, Vector2 drawingPos) {
	std::vector<EdgeRecord*>::iterator it = edges->begin();
	std::vector<EdgeRecord> r;
	Vector2 origin = drawingPos/20;
	r.push_back(drawingPos/20);
	do {
		if ((*it)->type == 1) {

			if (true) {
				Vector2 p[3];
				p[0] = drawingPos;
				p[1] = p[0] + ((CurveEdgeRecord*)(*it))->delta1;
				p[2] = p[1] + ((CurveEdgeRecord*)(*it))->delta2;
				int n = 8;
				float increment = 1.0 / n;
				float t = 0;
				for (int i = 0; i < n; i++)
				{
					t += increment;
					float x = ((1 - t) * (1 - t) * p[0].x) + (2 * (1 - t) * t * p[1].x) + t * t * p[2].x;
					float y = ((1 - t) * (1 - t) * p[0].y) + (2 * (1 - t) * t * p[1].y) + t * t * p[2].y;

					r.push_back(Vector2(x, y) / 20);
				}
				drawingPos = p[2];
			}
			else {
				std::vector<CurveEdgeRecord> curves;
				curves.push_back(CurveEdgeRecord( (*it)->delta1, ((CurveEdgeRecord*)(*it))->delta2));
				while (!curves.empty())
				{
					auto c = curves.back();
					curves.pop_back();
					Vector2 p[3];
					p[0] = drawingPos;
					p[1] = p[0] + c.delta1;
					p[2] = p[1] + c.delta2;
					double n1 = (double)p[0].x * ((double)p[1].y - p[2].y);
					double n2 = (double)p[1].x * ((double)p[2].y - p[0].y);
					double n3 = (double)p[2].x * ((double)p[0].y - p[1].y);
					double n = n1 + n2 + n3;
					double curveArea = n / 2;
					double size = ((double)(p[2] - p[0]).Magnitude());
					double lineArea = size / 10;

					if (curveArea * curveArea <= lineArea) {
						r.push_back(EdgeRecord(p[2] / 20));
						drawingPos = p[2];
					}
					else {
						float t = .5;
						float x = ((1 - t) * (1 - t) * p[0].x) + (2 * (1 - t) * t * p[1].x) + t * t * p[2].x;
						float y = ((1 - t) * (1 - t) * p[0].y) + (2 * (1 - t) * t * p[1].y) + t * t * p[2].y;
						auto a1 =  (p[0] * (1 - t)) + (p[1] * t);
						auto a2 = Vector2(x, y) - a1;
						a1 -= drawingPos;
						auto b1 = (p[1] * (1 - t)) + (p[2] * t);
						auto b2 = p[2] - b1;
						b1 -= Vector2(x, y);
						curves.push_back(CurveEdgeRecord(a1, a2));
						curves.push_back(CurveEdgeRecord(b1, b2));
					}

				}
			}
			
		}
		else {
		    drawingPos = (*it)->delta1 + drawingPos;
			r.push_back(drawingPos/20);
		}
		it++;
	}
	while (it != edges->end());

	if (!(origin == r[r.size()-1].delta1)) {
		r.push_back(EdgeRecord(origin));
	}

	return r;
}


std::vector<Trio> EdgeRecord::Triangulate(std::vector<EdgeRecord>  edges) {
	
	std::vector<std::vector<EdgeRecord>> polygons;
	std::vector<Trio> r;
	polygons.push_back(edges);
	while (polygons.size() > 0) {
		auto p = polygons.back();
		polygons.pop_back();
		if (p.size() > 4) {
			for (int j = 0; j < p.size()-2; j++) {
				Vector2 points[2];
				points[0] = p[0+j].delta1 - p[1+j].delta1;
				points[1] = p[2+j].delta1 - p[1+j].delta1;

				std::pair<int, int> diagonal;
				float angle = Meth::AngleBetween(points[0], points[1], true);
				if (abs(angle) < Meth::PI) {
					float rot = (points[1] - points[0]).GetAngle(true);
					Vector2 a2 = (points[1] - points[0]).Rotate(rot);
					Vector2 mov1 = (points[0] * -1) .Rotate(rot);
					Vector2 a1 = mov1 * -1;
					a2 = a2 - mov1;

					std::vector<Vector2> vertex;
					vertex.push_back(a1);
					vertex.push_back(a2);
					for (int i = 0; i < p.size(); i++) {
						if (i != j && i != j + 1 && i != j + 2) {
							vertex.push_back(p[i].delta1 - p[1+j].delta1);
						}
					}
					for (int i = 2; i < vertex.size(); i++) {
						vertex[i] = (vertex[i] - points[0]).Rotate(rot) - mov1;
					}
					std::vector<int> possibleDiagonals;
					for (int i = 2; i < vertex.size(); i++) {
						auto diagonal = vertex[i];
						if (vertex[0].x < diagonal.x && diagonal.x < vertex[1].x) {
							if (diagonal.y > 0 && diagonal.y < vertex[0].y) {
								possibleDiagonals.push_back(i);
							}
						}
					}
					if (possibleDiagonals.size() > 0) {
						int actualdiagonal = possibleDiagonals[0];
						for (int i = 1; i < possibleDiagonals.size(); i++) {
							if (vertex[i].y < vertex[actualdiagonal].y) {
								actualdiagonal = i;
							}
						}
						diagonal = std::pair(1 + j, actualdiagonal + 1);
					}
					else {
						diagonal = std::pair(0 + j, 2 + j);
					}

					std::vector<EdgeRecord> newPolygon;

					for (int i = diagonal.first; i < diagonal.second + 1; i++)
						newPolygon.push_back(p[i]);
					newPolygon.push_back(p[diagonal.first]);
					polygons.push_back(newPolygon);
					newPolygon.clear();

					if (diagonal.second < p.size()) {
						for (int i = diagonal.second; i < p.size(); i++)
							newPolygon.push_back(p[i]);
					}
					if (diagonal.first > 0) {
						for (int i = 0; i < diagonal.first + 1; i++)
							newPolygon.push_back(p[i]);
					}
					newPolygon.push_back(p[diagonal.second]);
					polygons.push_back(newPolygon);
					break;
				}
			}
		}
		else {
			float scale = 1;
			r.push_back(Trio(p[0].delta1 * scale,p[1].delta1 *scale ,p[2].delta1 * scale));
		}

	}
 	return r;
}

Trio::Trio(Vector2 p1, Vector2 p2, Vector2 p3) {
	vertex[0] = p1;
	vertex[1] = p2;
	vertex[2] = p3;
}

//void EdgeRecord::DrawEdges(std::vector<EdgeRecord>* edges) {
//	for (int i = 1; i < edges->size(); i++) {
//		FigureDrawer::DrawLine(Line((*edges)[i - 1].delta1, (*edges)[i].delta1), Color(255, 0, 0));
//	}
//}