#pragma once
#include"AssetManager.h"

class SoundManager
{
private:
		
	sf::Sound m_Fire1Sound;
	sf::Sound m_Fire2Sound;
	sf::Sound m_Fire3Sound;
	sf::Sound m_FallInFireSoundBear;
	sf::Sound m_FallInFireSoundMasha;
	sf::Sound m_FallInWaterSound;
	sf::Sound m_JumpSound;
	sf::Sound m_ReachGoalSound;
	// Какой звук использовать дальше, fire 1, 2 или 3 int
	int m_NextSound = 1;
public:
	SoundManager();
	void playFire(sf::Vector2f emitterLocation,sf::Vector2f listenerLocation);
	void playFallInFire(int character);
	void playFallInWater();
	void playJump();
	void playReachGoal();
};

