#pragma once
#include"AssetManager.h"

class Character {

	protected:
		//  sprite ���������
		sf::Sprite m_Sprite;
		// �������� ������� ������
		// ��� ������ ��������, ��� ������ � ���� ������ �������� ��������
		float m_JumpDuration;
		// �������� ������ ������� ��� ������ bool
		// ����������� ������ � �������
		bool m_IsJumping;
		bool m_IsFalling;
		// � ����� ����������� �������� �������� � ������ ������
		bool m_LeftPressed;
		bool m_RightPressed;
		// ��� �����  ������ ������
		float m_TimeThisJump;
		// ����� ������ ��� �������� ������
		bool m_JustJumped = false;
		// ����������� ���������
		int m_identifier;
	private:
		// ����������
		float m_Gravity;
		// ��������� ����� ��������
		float m_Speed = 400;
		// ��� ��������� �����
		sf::Vector2f m_Position;
		// ��� ��������� ��������� ����� ���� ����������
		sf::FloatRect m_Feet;
		sf::FloatRect m_Head;
		sf::FloatRect m_Right;
		sf::FloatRect m_Left;
		// ��������
		sf::Texture m_Texture;
	public:
		void spawn(sf::Vector2f startPosition, float gravity);
		// ����� ����������� �������
		bool virtual handleInput() = 0;
		// ���� ����� ������ ����������� � �� ����� ���� ������
		// ��� ��������� �����
		sf::FloatRect getPosition();
		// �������������, �������������� ��������� 
		// ��������� ������ �������
		sf::FloatRect getFeet();
		sf::FloatRect getHead();
		sf::FloatRect getRight();
		sf::FloatRect getLeft();
		int getIdentifier();
		// ���������� ����� �������
		sf::Sprite getSprite();
		// ��������� ��������� ������ ������
		void stopFalling(float position);
		void stopRight(float position);
		void stopLeft(float position);
		void stopJump();
		// ��� ��������� ����� ��������� 
		sf::Vector2f getCenter();
		// �� ����� �������� ��� ������� ���� ��� � ������ �����
		void update(float elapsedTime);
};	

