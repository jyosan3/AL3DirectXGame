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
	void Draw2DNear();

private:
	uint32_t textureHandleGameOver_ = 0;
	Sprite* spriteGameOver_ = nullptr;

	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	int gameTimer_ = 0;

	Input* input_ = nullptr;
};
