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

class GameOver {

public:
	GameOver();
	~GameOver();

	void Initialize();
	int Update();
	void Sound();
	void Draw2DNear();
	void Start();

private:
	uint32_t textureHandleGameOver_ = 0;
	Sprite* spriteGameOver_ = nullptr;

	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	Audio* audio_ = nullptr;
	uint32_t soundDataHandleBGM_ = 0;
	uint32_t voiceHandleBGM_ = 0;

	int gameTimer_ = 0;

	Input* input_ = nullptr;
};
