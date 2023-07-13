#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {

	delete modelEnemy_;

}

void Enemy::Initialize(ViewProjection view) {

	viewProjection_ = view;

	// プレイヤー
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();

}

void Enemy::Start() {

	enemyFlag_ = 0;

}

void Enemy::Update() {

	// 移動
	Move();
	// 発生
	Born();

	// 変換行列を更新
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	    worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	    worldTransformEnemy_.translation_);
	//	変換行列を定数バッファに変換
	worldTransformEnemy_.TransferMatrix();

}

void Enemy::Draw3D() {

	if (enemyFlag_ == 1) {
		modelEnemy_->Draw(worldTransformEnemy_, viewProjection_, textureHandleEnemy_);
	}

}

void Enemy::Move() {

	if (enemyFlag_ == 1) {
		worldTransformEnemy_.translation_.z -= 0.2f;
		worldTransformEnemy_.rotation_.x -= 0.1f;
		worldTransformEnemy_.translation_.x += xSpeed_;
	
		if (worldTransformEnemy_.translation_.x > 4) {
			xSpeed_ = -0.1f;
		}
		if (worldTransformEnemy_.translation_.x < -4) {
			xSpeed_ = 0.1f;
		}
	
	}


	if (worldTransformEnemy_.translation_.z <= -5) {
		enemyFlag_ = 0;
	}

}

void Enemy::Born() {

	if (rand() % 10 == 0) {
		if (enemyFlag_ == 0) {
			enemyFlag_ = 1;

			if (rand() % 2 == 0){
				xSpeed_ = 0.1f;
			} else {
				xSpeed_ = -0.1f;
			}
			// 乱数でX座標の指定
			int x = rand() % 80;
			float x2 = (float)x / 10 - 4;
			worldTransformEnemy_.translation_.x = x2;
			worldTransformEnemy_.translation_.z = 40;
		}
	}


}

