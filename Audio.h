#pragma once
#include <irrKlang.h>
#include <string>
using namespace irrklang;

struct AudioEngine
{
	ISoundEngine* engine = createIrrKlangDevice();
	ISound* Play(std::string name, bool loop = false) {
		return engine->play2D(("assets/audio/" + name + ".mp3").c_str(), loop);
	}
	ISound* PlayTracked(std::string name, bool loop = false) {
		auto a = engine->play2D(("assets/audio/" + name + ".mp3").c_str(), loop, true, true, ESM_AUTO_DETECT, true);
		a->setIsPaused(false);
		return a;
	}
	ISound* SetAudio(std::string name, bool loop = false) {
		return engine->play2D(("assets/audio/" + name + ".mp3").c_str(), loop, true, true, ESM_AUTO_DETECT, true);
	}
};

struct AudioTracker {
	ISound* sound = nullptr;
	bool TryToTrack(std::string name, AudioEngine* ae, bool loop = false) {
		if (sound) {
			if (sound->isFinished() || sound->getIsPaused()) {
				sound->drop();
			}
			else return false;
		}
		sound = ae->PlayTracked(name, loop);
		return true;
	}

	bool isPlaying() {
		if (!sound)
			return false;
		return !sound->isFinished();
	}

	bool isPaused() {
		if (!sound)
			return true;
		return sound->getIsPaused();
	}

	void Stop() {
		if(sound)
			sound->setIsPaused(true);
	}
	void Resume() {
		if (sound)
			sound->setIsPaused(false);
	}

};



struct Audio
{
	AudioEngine sfx;
	AudioEngine music;
	AudioEngine voice;
	static Audio instance;
};
