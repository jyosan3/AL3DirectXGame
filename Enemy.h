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
#include "Player.h"
#include <time.h>


class Enemy {

public:

	Enemy();
	// デストラクタ
	~Enemy();

	// 初期化
	void Initialize(ViewProjection view);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();

	void Move();

	void Born();

	void Start();

	float GetX() { return worldTransformEnemy_.translation_.x; }
	float GetZ() { return worldTransformEnemy_.translation_.z; }
	int GetFlag() { return enemyFlag_; }

	void Hit() {enemyFlag_ = 0;	}

private:

	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_;

	// カメラ
	ViewProjection viewProjection_;

	Input* input_ = nullptr;

	int enemyFlag_ = 0;
	float xSpeed_ = 0;
	
};

