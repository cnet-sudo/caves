#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_Fire1Sound.setBuffer(AssetManager::GetSoundBuffer("sound/fire1.wav"));
	m_Fire2Sound.setBuffer(AssetManager::GetSoundBuffer("sound/fire1.wav"));
	m_Fire3Sound.setBuffer(AssetManager::GetSoundBuffer("sound/fire1.wav"));
	m_FallInFireSoundBear.setBuffer(AssetManager::GetSoundBuffer("fallBear.wav"));
	m_FallInFireSoundMasha.setBuffer(AssetManager::GetSoundBuffer("sound/fallMasha.wav"));
	m_FallInWaterSound.setBuffer(AssetManager::GetSoundBuffer("sound/fallinwater.wav"));
	m_JumpSound.setBuffer(AssetManager::GetSoundBuffer("sound/jump1.wav"));
	m_ReachGoalSound.setBuffer(AssetManager::GetSoundBuffer("sound/end1.wav"));
	// ����� ����� ��������� �� ���������� 50 ��������, ���� �� ������ ���������
	float minDistance = 150;
	// ���� ��������� ��������� �� ���� ����, ��� ����� ���������� �� ������ float
	float attenuation = 30;
	// ���������� ��� ������ ���������
	m_Fire1Sound.setAttenuation(attenuation);
	m_Fire2Sound.setAttenuation(attenuation);
	m_Fire3Sound.setAttenuation(attenuation);
	// ���������� ��� ������ ������������ ����������
	m_Fire1Sound.setMinDistance(minDistance);
	m_Fire2Sound.setMinDistance(minDistance);
	m_Fire3Sound.setMinDistance(minDistance);
	// ��������� ��� ����� ���� 
	// ��� �� ���������������
	m_Fire1Sound.setLoop(true);
	m_Fire2Sound.setLoop(true);
	m_Fire3Sound.setLoop(true);
}

void SoundManager::playFire(sf::Vector2f emitterLocation, sf::Vector2f listenerLocation)
{
	// ��� ���������?
	sf::Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.0f);
	switch (m_NextSound)
	{
	case 1:
		// �������/����������� �������� �����
		m_Fire1Sound.setPosition(emitterLocation.x,	emitterLocation.y, 0.0f);
		if (m_Fire1Sound.getStatus() == sf::Sound::Status::Stopped)
		{
			// ������������� ����, ���� �� ��� �� �������
			m_Fire1Sound.play();
		}
		break;
	case 2:
		
		m_Fire2Sound.setPosition(emitterLocation.x,	emitterLocation.y, 0.0f);
		if (m_Fire2Sound.getStatus() == sf::Sound::Status::Stopped)
		{
			m_Fire2Sound.play();
		}
		break;
	case 3:
		
		m_Fire3Sound.setPosition(emitterLocation.x,	emitterLocation.y, 0.0f);
		if (m_Fire3Sound.getStatus() == sf::Sound::Status::Stopped)
		{
			m_Fire3Sound.play();
		}
		break;
	}
	// ���������� � ���������� ����� ����
	m_NextSound++;
	// ��������� � 1, ����� ������ ���� ��� ������� if (m_NextSound > 3)
	if (m_NextSound > 3)
	{
		m_NextSound = 1;
	}
}

void SoundManager::playFallInFire(int character)
{
	if (character == 1) {
	
		m_FallInFireSoundBear.setRelativeToListener(true);
		m_FallInFireSoundBear.play();
	}
	if (character == 2) {
		
		m_FallInFireSoundMasha.setRelativeToListener(true);
		m_FallInFireSoundMasha.play();
	}
	
}
void SoundManager::playFallInWater()
{
	m_FallInWaterSound.setRelativeToListener(true);
	m_FallInWaterSound.play();
}
void SoundManager::playJump()
{
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}
void SoundManager::playReachGoal()
{
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}