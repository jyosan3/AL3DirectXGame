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
#include"Player.h"

class Beam {
public: // コンストラクタ
	Beam();
	// デストラクタ
	~Beam();

	// 初期化
	void Initialize(ViewProjection view,Player* player);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();

	void Move();


	void Born();

	float GetX() { return worldTransformBeam_.translation_.x; }
	float GetZ() { return worldTransformBeam_.translation_.z; }
	int GetFlag() { return beamFlag_; }

	void Hit() { beamFlag_ = 0; }
	
private:
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;

	// カメラ
	ViewProjection viewProjection_;

	Input* input_ = nullptr;

	int beamFlag_ = 0;

	Player* player_ = nullptr;

};