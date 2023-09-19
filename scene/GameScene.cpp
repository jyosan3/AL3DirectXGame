#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete gamePlay_;
	delete title_;
	delete gameOver_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 各クラスの作成

	////カメラ初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	
	gamePlay_ = new GamePlay();
	gamePlay_->Initialize(viewProjection_);

	title_ = new Title();
	title_->Initialize();

	gameOver_ = new GameOver();
	gameOver_->Initialize();

	
}	


void GameScene::Update() {

	int oldSceneMode_ = sceneMode_;

	//ステージ更新
	switch (sceneMode_) {
	case 0:
		sceneMode_ = gamePlay_->Update();
	break;
	case 1:
		sceneMode_ = title_->Update();
	break;
	case 2:
		sceneMode_ = gameOver_->Update();
	break;
	}

	if (oldSceneMode_ != sceneMode_) {
	
		switch (sceneMode_) {
		case 0:
			gamePlay_->Start();
			break;
		case 1:
			title_->Start();
			break;
		case 2:
			gameOver_->Start();
			break;
	    }

	}

}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>


	switch (sceneMode_) {
	case 0:
	gamePlay_->Draw2DFar();
	break;
	case 2:
	gamePlay_->Draw2DFar();
	break;
	}
	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	switch (sceneMode_) {
	case 0:
	gamePlay_->Draw3D();
	break;
	case 2:
	gamePlay_->Draw3D();
	break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (sceneMode_) {
	case 0:
		gamePlay_->Draw2DNear();
	break;
	case 1:
		 title_->Draw2DNear();
	break;
	case 2: 
		gamePlay_->Draw2DNear();
		gameOver_->Draw2DNear();
	break;

	}

	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
