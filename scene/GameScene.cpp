#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"MathUtilityForText.h"

//コンストラクタ
GameScene::GameScene() {

}


//デストラクタ
GameScene::~GameScene() {

	delete spriteBG_;
	delete modelStage_;
	delete modelPlayer_;

}

//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//背景
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});

	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	//ステージ
	textureHandleStage_ = TextureManager::Load("stage.jpg");
	modelStage_ = Model::Create();
	worldTranceformStage_.Initialize();

	//行列変換
	worldTranceformStage_.translation_ = {0, -1.5f, 0};
	worldTranceformStage_.scale_ = {4.5f, 1, 40};
	worldTranceformStage_.matWorld_ = MakeAffineMatrix(
	    worldTranceformStage_.scale_, 
		worldTranceformStage_.rotation_,
	    worldTranceformStage_.translation_);

	worldTranceformStage_.TransferMatrix();

	//プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTranceformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTranceformPlayer_.Initialize();
	
	
}

void GameScene::Update() {

	PlayerUpdate();

}

//プレイヤー更新
void GameScene::PlayerUpdate() {
	worldTranceformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTranceformPlayer_.scale_, worldTranceformPlayer_.rotation_,
	    worldTranceformPlayer_.translation_);

	worldTranceformPlayer_.TransferMatrix();


	//移動

	//右移動
	if (input_->PushKey(DIK_RIGHT)) {
		worldTranceformPlayer_.translation_.x += 0.1f;
	}

	//左移動
	if (input_->PushKey(DIK_LEFT)) {
		worldTranceformPlayer_.translation_.x -= 0.1f;
	}

	if (worldTranceformPlayer_.translation_.x > 4) {
		worldTranceformPlayer_.translation_.x = 4;
	}

	if (worldTranceformPlayer_.translation_.x < -4) {
		worldTranceformPlayer_.translation_.x = -4;
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

	spriteBG_->Draw();

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

	//ステージ
	modelStage_->Draw(worldTranceformStage_, viewProjection_, textureHandleStage_);

	//プレイヤー
	modelPlayer_->Draw(worldTranceformPlayer_, viewProjection_, textureHandlePlayer_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
