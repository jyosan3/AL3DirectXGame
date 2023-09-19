#include "Stage.h"

Stage::Stage() {}

Stage::~Stage() {

	delete spriteBG_; //BG

}

void Stage::Initialize(ViewProjection view) { 

	//メンバー変数に代入
	viewProjection_ = view;

	//BG(2Dスプライト)
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});

}

void Stage::Update() {}

void Stage::Draw2DFar() {
	//背景
	spriteBG_->Draw();
}

void Stage::Draw3D() {}
