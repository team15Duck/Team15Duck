#pragma once
#include "singletonBase.h"
#include <unordered_map>

#include "inc/fmod.hpp"	//fmod.hpp���� ��Ŭ���
#pragma comment(lib, "lib/fmodex64_vc.lib")	//���̺귯�� ���� ���

using namespace FMOD;

#define SOUNDBUFFER 100
#define EXTRACHANNELBUFFER 50

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef unordered_map<string, Sound**> arrSounds;
	typedef unordered_map<string, Sound**>::iterator arrSoundsIter;
	typedef unordered_map<string, Channel**> arrChannels;
	typedef unordered_map<string, Channel**>::iterator arrChannelsIter;

private:
	System * _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f -> 0 ~ 255
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);


	soundManager();
	~soundManager();
};

