/*
 * Copyright (c) 2015-2017 Annemarie Mattmann, Johannes Mattmann,
 * Matthias Gazzari, Moritz Hagemann, Sebastian Artz
 * 
 * Licensed under the MIT license. See the LICENSE file for details.
 */

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>

// SFML allows at least 256 sound sources (including music!)
#define MAX_SOUND_INSTANCES 128

class SoundManager {
private:
	std::map<std::string, sf::SoundBuffer*> bufferedSounds;
	std::vector<sf::Sound*> playingSounds;
	sf::Music* bkgMusic;
	float musicVolume;
	float soundVolume;
public:
	SoundManager(float soundVolume, float musicVolume);
	~SoundManager();
	void playSound(std::string name);
	void playMusic(std::string fileName);
	void stopMusic();
	void pause();
	void resume();
	// inline definitions of volume getter and setter functions
	void setMusicVolume(float volume) {
		musicVolume = volume;
		bkgMusic->setVolume(volume);
	}
	void setSoundVolume(float volume) {
		soundVolume = volume;
		for (auto& sound: playingSounds) {
			sound->setVolume(volume);
		}
	}
	float getMusicVolume() {
		return musicVolume;
	}
	float getSoundVolume() {
		return soundVolume;
	}
};
