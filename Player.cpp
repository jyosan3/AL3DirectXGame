#include "Player.h"

Player::Player() {}

Player::~Player() { delete modelPlayer_; }



void Player::Initialize(ViewProjection view) {
	// メンバー変数に代入
	viewProjection_ = view;

	// プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();

	// インプットクラス
	input_ = Input::GetInstance();
}

void Player::Start() {

	worldTransformPlayer_.translation_ = {0, 0, 0};

	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);

	worldTransformPlayer_.TransferMatrix();
}

void Player::Update() {
	// 変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	//	変換行列を定数バッファに変換
	worldTransformPlayer_.TransferMatrix();

	if (input_->PushKey(DIK_RIGHT)) {
		worldTransformPlayer_.translation_.x += 0.1f;
	}

	// 左移動
	if (input_->PushKey(DIK_LEFT)) {
		worldTransformPlayer_.translation_.x -= 0.1f;
	}

	//上移動
	if (input_->PushKey(DIK_UP)) {
		worldTransformPlayer_.translation_.y += 0.1f;
	}

	// 下移動
	if (input_->PushKey(DIK_DOWN)) {
		worldTransformPlayer_.translation_.y -= 0.1f;
	}

	if (worldTransformPlayer_.translation_.x > 4) {
		worldTransformPlayer_.translation_.x = 4;
	}

	if (worldTransformPlayer_.translation_.x < -4) {
		worldTransformPlayer_.translation_.x = -4;
	}

	if (worldTransformPlayer_.translation_.y > 2) {
		worldTransformPlayer_.translation_.y = 2;
	}

	if (worldTransformPlayer_.translation_.y < -1) {
		worldTransformPlayer_.translation_.y = -1;
	}
}

void Player::Draw3D() {
	// プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
}