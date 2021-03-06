// MVCobserver_hovig.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class time
{
	vector<class Observer*> views;
	int hour, minute, second, timezone;
public:
	void attach(Observer* obs)
	{
		views.push_back(obs); 
	}
	void setVal(int hr, int min, int sec, int zone)
	{
		hour = hr;
		minute = min; 
		second = sec; 
		timezone = zone;
		notify();
	}

	int gethour()
	{
		return  hour;
	}
	int getmin()
	{
		return  minute;
	}
	int getsec()
	{
		return second;
	}
	int getzone()
	{
		return  timezone;
	}
	void notify();

};

// observer
class Observer
{
	time* model;
	int hr, minu, sec, timez;

public:
	Observer(time* mode, int hour, int minute, int second, int timezone)
	{
		model = mode;
		hr = hour;
		minu = minute;
		sec = second;
		timezone = timez;
		model->attach(this);
	}

	virtual void update() = 0;

protected:
	time *gettime() { return model; }
	int gethr(){ return  hr; }
	int getmin() { return  minu; }
	int getsec() { return  sec; }
	int getzone() { return  timez; }
};

void time::notify()
{
	for (int i = 0; i < views.size(); i++)
	{
		views[i]->update();
	}
}

//civilian

class civilian :public Observer
{
public:
	civilian(time* mode, int hour, int minute, int second, int timezone) :Observer(mode, hour, minute, second, timezone) {
		cout << "Civilian time is " << hour << ":" << minute << ":" << second << endl;
	}

	void update()
	{
		int h = gettime()->gethour();
		int m = gettime()->getmin();
		int s = gettime()->getsec();
		int zo = gettime()->getzone();
		cout << "Civilian time is :" << h << ":" << m << ":" << s << endl;
	}
};

//MILITAN

class military :public Observer
{
public:
	military(time* mode, int hour, int minute, int second, int timezone) :Observer(mode, hour, minute, second, timezone) {
		cout << "Military time is " << hour + 12 << ":" << minute << ":" << second << endl;
	}

	void update()
	{
		int h = gettime()->gethour();
		int m = gettime()->getmin();
		int s = gettime()->getsec();
		int zo = gettime()->getzone();
		cout << "Military time is " << h+12 << ":" << m << ":" << s << "zone:" << zo << endl;
	}
};

//ZULU
class Zulu :public Observer
{
public:
	Zulu(time* mode, int hour, int minute, int second, int timezone) :Observer(mode, hour, minute, second, timezone) {
		cout << "Zulu time is " << hour << ":" << minute << ":" << second << "zone:" << timezone << endl;
	}

	void update()
	{
		int h = gettime()->gethour();
		int m = gettime()->getmin();
		int s = gettime()->getsec();
		int zo = gettime()->getzone();
	}
};




int main(void)
{
	time tim;
	tim.setVal(6, 15, 33, 5);
	civilian civilian(&tim, 6, 15, 33, 5);
	military military(&tim, 5, 45, 22, 6);
	Zulu zulu(&tim, 3, 23, 15, 2);

};

