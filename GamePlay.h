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
	int Update();
	void Draw();
	void Draw2DFar();
	void Draw3D();
	void Draw2DNear();
	void CollisionPlayerEnemy();
	void CollisionBeamEnemy();
	void Start();
	void Shot();
	void Sound();

private:

	Stage*  stage_  = nullptr;
	Player* player_ = nullptr;
	Beam* beamTable_[10] = {};
	Enemy* enemyTable_[10] = {};

	Audio* audio_ = nullptr;
	uint32_t soundDataHandleBGM_ = 0;
	uint32_t voiceHandleBGM_ = 0;
	uint32_t soundDataHandleEnemySE_ = 0;
	uint32_t soundDataHandlePlayerSE_ = 0;

	ViewProjection viewProjection_;

	DebugText* debugText_ = nullptr;

	int ShotTimer_ = 0;
	int gameScore_ = 0;
	int playerLife_ = 3;
	Input* input_ = nullptr;



};
