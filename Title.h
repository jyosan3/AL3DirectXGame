#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "DebugText.h"


class Title {

public:

	Title();
	~Title();

	void Initialize();
	int Update();
	void Draw2DNear();
	void Sound();

	void Start();


private:

	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	Audio* audio_ = nullptr;
	uint32_t soundDataHandleBGM_ = 0;
	uint32_t voiceHandleBGM_ = 0;

	int gameTimer_ = 0;
	Input* input_ = nullptr;

};


