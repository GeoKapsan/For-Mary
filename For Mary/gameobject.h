#pragma once
#include <string>


class GameObject
{
	static int m_next_id;

protected:
	class GameState * m_state;
	int m_id = 0;
	bool m_active = true;
public:
	GameObject(const std::string& name = "");
	std::string m_name;
	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
};
