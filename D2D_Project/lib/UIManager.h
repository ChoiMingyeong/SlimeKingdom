#pragma once

class UIManager : public Subject<UI>
{
public:
	UIManager();
	virtual ~UIManager();

private:
	vector<UI*> m_UIs;

public:
	virtual void UpdateObserver();
	virtual void ResisterObserver(UI* observer);
	virtual void RemoveObserver(UI* observer);

	void Draw();
};

