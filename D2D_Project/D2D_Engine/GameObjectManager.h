#pragma once

class GameObjectManager : public Subject<GameObject>
{
public:
	GameObjectManager();
	virtual ~GameObjectManager();

private:
	vector<GameObject*> m_GameObjects;

public:
	virtual void UpdateObserver();
	virtual void ResisterObserver(GameObject* observer);
	virtual void RemoveObserver(GameObject* observer);

	void Draw();
	void CheckCollision();
};

