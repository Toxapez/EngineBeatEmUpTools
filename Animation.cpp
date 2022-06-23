#include "Animation.h"
std::vector<Animation*> Animation::animations;

Animation::Animation() {
	SetFPS(12);
	counter = 0;
	animations.push_back(this);
	loop = false;
	realFrames = 0;
}

Animation* Animation::Set(std::string _name, Vector2 os) {
	if (dir == "") {
		dir = std::string("assets/sprites/" + _name);
		offset = os;
	}
	return this;
}

void Animation::Load() {
	if (dir != "") {
		int i = 0;
		for (auto& p : std::filesystem::directory_iterator(dir)) {
			SDL_Surface* surface = IMG_Load(p.path().string().c_str());
			unsigned int texture = 0;
			OpenGLClass::LoadTextureFromSurface(surface,&texture);
			frames.push_back(texture);
			int x, y = 0;
			Vector2 spriteSize = Vector2(surface->w, surface->h);
			auto sr = RectTwoPoint(spriteSize * -.5, spriteSize);
			spriteRects.push_back(sr);
			i++;
		}
		if (index.empty())
			for (int j = 0; j < i; j++)
				index.push_back(j);
		if (repeat.empty())
			for (int j = 0; j < i; j++)
				repeat.push_back(1);

		Reset();
		SetRealFrames();
	}
}

void Animation::Play(float speed) {
	if (!HasEnded() || loop) {
		counter+= speed;
		if (counter > itIncrement) {
			counter -= itIncrement;
			framesPlayed++;
			frameRepeatCounter++;
			if (frameRepeatCounter == repeat[currentFrame]) {
				currentFrame++;
				frameRepeatCounter = 0;
			}
			if (currentFrame == realFrames || framesPlayed == realFrames) {
				if (loop) {
					it = frames[index[0]];
					currentFrame = 0;
				}
				else currentFrame--;
			}
			it = frames[index[currentFrame]];
		}
	}
}

int Animation::GetRealFrameBeingPlayed() {
	return index[currentFrame];
}

void Animation::SetRealFrames() {
	realFrames = 0;
	for (auto c : repeat)
		realFrames += c;

}

void Animation::ModifyTimeline(int* indexs, int* repeats, int n) {
	if (indexs) {
		index.clear();
		for (int i = 0; i < n; i++) {
			index.push_back(indexs[i]);
		}
	}
	if (repeats) {
		repeat.clear();
		for (int i = 0; i < n; i++) {
			repeat.push_back(repeats[i]);
		}
	}
}

bool Animation::HasEnded() {
	return framesPlayed >= realFrames;
}

void Animation::Reset() {
	it = frames[index[0]];
	currentFrame = 0;
	framesPlayed = 0;
	frameRepeatCounter = 0;
}

void Animation::SetFPS(int a) {
	itIncrement = 60 / a;
}

Animation::~Animation() {
	for (auto c : frames) {
		if (c) {
			//SDL_FreeSurface(c);
		}
	}
}

void Animation::Start() {
	for (auto c : animations) {
		if (c) {
			c->Load();
		}
	}
}