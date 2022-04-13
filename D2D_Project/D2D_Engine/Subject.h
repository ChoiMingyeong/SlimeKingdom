#pragma once

template<typename Observer>
class Subject
{
public:
	virtual ~Subject() {}

private:
	std::vector<Observer*> m_pObserver;

public:
	virtual void UpdateObserver() = 0;
	virtual void ResisterObserver(Observer*)=0;
	virtual void RemoveObserver(Observer*)=0;
};