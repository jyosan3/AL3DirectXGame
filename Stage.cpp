#include "Stage.h"

Stage::Stage() {}

Stage::~Stage() {

	delete modelStage_;
	delete spriteBG_; //BG

}

void Stage::Initialize(ViewProjection view) { 

	//メンバー変数に代入
	viewProjection_ = view;

	//BG(2Dスプライト)
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});

	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelStage_ = Model::Create();
	worldTransformStage_.Initialize();

	//ステージの位置を変更
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	//変換行列を更新
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_,
		worldTransformStage_.rotation_,
	    worldTransformStage_.translation_);
	//変換行列を定数バッファに転送
	worldTransformStage_.TransferMatrix();
}

void Stage::Update() {}

void Stage::Draw2DFar() {
	//背景
	spriteBG_->Draw();
}

void Stage::Draw3D() {
	//ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);

}
