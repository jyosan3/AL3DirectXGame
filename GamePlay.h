#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include"Stage.h"
#include "Player.h"
#include"Beam.h"
#include"Enemy.h"
#include"DebugText.h"


class GamePlay {

public:

	GamePlay();
	~GamePlay();

	void Initialize(ViewProjection view);
	void Update();
	void Draw();
	void Draw2DFar();
	void Draw3D();
	void Draw2DNear();
	void CollisionPlayerEnemy();
	void CollisionBeamEnemy();


private:

	Stage*  stage_  = nullptr;
	Player* player_ = nullptr;
	Beam*   beam_   = nullptr;
	Enemy*  enemy_  = nullptr;

	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;

	int gameScore_ = 0;
	int playerLife_ = 3;

};
