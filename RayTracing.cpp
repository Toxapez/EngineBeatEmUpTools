#include "RayTracing.h"

RayTracing RayTracing::instance;
RandomStuffPutter RandomStuffPutter ::instance;




RayTracing::RayTracing() {
	nRays = 300;
	layer = 1;
	transform.position = Vector2(-500,0);
	isActive = false;
}

void RayTracing::AfterStaticStart() {

	//light = new Light(500);
}


void RandomStuffPutter::Update() {
	
}

void RayTracing::Update() {
	transform.position = Player::player.transform.position;
}


void RayTracing::Draw() {

	Color ambientLightColor = Color(0, 0, 0, 100);

	FigureDrawer::DrawTriangle(TriangleP(
		glm::vec3(0, 0, 0),
		glm::vec3(SDLClass::screenSizeX, 0, 0),
		glm::vec3(0, SDLClass::screenSizeY, 0),
		glm::vec4( ambientLightColor.r,  ambientLightColor.g,  ambientLightColor.b, ambientLightColor.a),
		glm::vec4(ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a),
		glm::vec4(ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a)));

	FigureDrawer::DrawTriangle(TriangleP(
		glm::vec3(SDLClass::screenSizeX, 0, 0),
		glm::vec3(SDLClass::screenSizeX, SDLClass::screenSizeY, 0),
		glm::vec3(0, SDLClass::screenSizeY, 0),
		glm::vec4(ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a),
		glm::vec4(ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a),
		glm::vec4(ambientLightColor.r, ambientLightColor.g, ambientLightColor.b, ambientLightColor.a)));

	glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	angle = (Meth::PI * 2) / nRays;
	Vector2 mousePos = transform.position;

	Vector2 lastlinepos;
	Vector2 firstlinepos;
	distance = 1000;
	Color lightColor = Color(255, 255, 255, 255);

	if (true)
	{
		int i = 0;
		Vector2 linepos = transform.position + Vector2::VectorFromAngle(distance, angle * i);
		Line l = Line(transform.position, linepos);
		bool touching = false;
		for (int i = 0; i < ShadowCaster::shadows.maxEntities; i++) {
			auto c = ShadowCaster::shadows[i];
			Vector2 crossPoint;
			if(c)
				if(c->isActive)
					if (c->gameobject)
						if (c->gameobject->isActive) {
							if (Line::CrossLinePoint(l, c->body, &crossPoint)) {
								touching = true;
								l.points.second = crossPoint;
							}
						}
		}
		linepos = l.points.second;
		firstlinepos = linepos;
		float d = (linepos - transform.position).Magnitude();
		float dc = lightColor.a -(lightColor.a * (d/distance));
		float d2 = (lastlinepos - transform.position).Magnitude();
		float dc2 = lightColor.a - (lightColor.a * (d2 / distance));
		if (lastlinepos != Vector2()) {
			Vector2 p1 = lastlinepos;
			Vector2 p2 = linepos;
			FigureDrawer::DrawTriangle(TriangleP(
				glm::vec3(p1.x, p1.y, 0),
				glm::vec3(p2.x, p2.y, 0),
				glm::vec3(mousePos.x, mousePos.y, 0),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - dc2),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - dc),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - lightColor.a)));
		}
		lastlinepos = linepos;
	}
	int nlineascol = 0;
	for (int i = 1; i < nRays; i++)
	{
		Vector2 linepos = transform.position + Vector2::VectorFromAngle(distance, angle * i);
		Line l = Line(transform.position, linepos);
		bool touching = false;
		for (int i = 0; i < ShadowCaster::shadows.maxEntities; i++) {
			auto c = ShadowCaster::shadows[i];
			Vector2 crossPoint;
			if(c)
				if (c->isActive)
					if (c->gameobject)
						if (c->gameobject->isActive) {
							nlineascol++;
							if (Line::CrossLinePoint(l, c->body, &crossPoint)) {
								touching = true;
								l.points.second = crossPoint;
							
							}
						}
		}
		linepos = l.points.second;
		float d = (linepos - transform.position).Magnitude();
		float dc = lightColor.a - (lightColor.a * (d / distance));
		float d2 = (lastlinepos - transform.position).Magnitude();
		float dc2 = lightColor.a - (lightColor.a * (d2 / distance));
		if (lastlinepos != Vector2()) {
			Vector2 p1 = lastlinepos;
			Vector2 p2 = linepos;
	
			FigureDrawer::DrawTriangle(TriangleP(
				glm::vec3(p1.x, p1.y, 0),
				glm::vec3(p2.x, p2.y, 0),
				glm::vec3(mousePos.x, mousePos.y, 0),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b,255 -dc2),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b,255 -dc),
				glm::vec4(lightColor.r, lightColor.g, lightColor.b,255 -lightColor.a)));
		}
		lastlinepos = linepos;
		
	}
	if (lastlinepos != Vector2()) {
		Vector2 p1 = lastlinepos;
		Vector2 p2 = firstlinepos;
		float d = (firstlinepos - transform.position).Magnitude();
		float dc = lightColor.a - (lightColor.a * (d / distance));
		float d2 = (lastlinepos - transform.position).Magnitude();
		float dc2 = lightColor.a - (lightColor.a * (d2 / distance));
	
		FigureDrawer::DrawTriangle(TriangleP(
			glm::vec3(p1.x, p1.y, 0),
			glm::vec3(p2.x, p2.y, 0),
			glm::vec3(mousePos.x, mousePos.y, 0),
			glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - dc2),
			glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - dc),
			glm::vec4(lightColor.r, lightColor.g, lightColor.b, 255 - lightColor.a)));
	
	}
	//RenderLights();
}

void RayTracing::RenderLights() {
	Shader* shader = OpenGLClass::shaders[4];
	shader->use();
	unsigned int n;
	for (int i = 0; i < ShadowCaster::shadows.maxEntities; i++) {
		auto s = ShadowCaster::shadows[i];

		bool b = s;
		if (s) {
			b = s->isActive;
			if (s->gameobject)
				b = s->gameobject->isActive;
		}

		n = glGetUniformLocation(shader->id, std::string("shadows[" + std::to_string(i) + "].active").c_str());
		glUniform1i(n, b);

		if (b) {
			glm::vec2 v = OpenGLClass::Vector2ToVec2(s->body.points.first);
			unsigned int n = glGetUniformLocation(shader->id, std::string("shadows[" + std::to_string(i) + "].first").c_str());
			glUniform2fv(n, 1, glm::value_ptr(v));

			v = OpenGLClass::Vector2ToVec2(s->body.points.second);
			n = glGetUniformLocation(shader->id, std::string("shadows[" + std::to_string(i) + "].second").c_str());
			glUniform2fv(n, 1, glm::value_ptr(v));

		}
	}
	glm::vec2 v = OpenGLClass::Vector2ToVec2(transform.position);
	n = glGetUniformLocation(shader->id, "lightPos");
	glUniform2fv(n, 1, glm::value_ptr(v));

	glm::vec4 c = glm::vec4(255,255,255,255);
	n = glGetUniformLocation(shader->id, "lightColor");
	glUniform2fv(n, 1, glm::value_ptr(c));

	n = glGetUniformLocation(shader->id, "angle");
	glUniform1f(n, angle);

	n = glGetUniformLocation(shader->id, "distance");
	glUniform1f(n, distance);

	light->Render();

	shader->unuse();

}