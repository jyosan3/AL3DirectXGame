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

class Player {

public : // コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 初期化
	void Initialize(ViewProjection view);
	// 更新
	void Update();
	// 3D描画
	void Draw3D();

	void Start();

	float GetX() { return worldTransformPlayer_.translation_.x; }
	float GetZ() { return worldTransformPlayer_.translation_.z; }

private:
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	// カメラ
	ViewProjection viewProjection_;

	Input* input_ = nullptr;

};
