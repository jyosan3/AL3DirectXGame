#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"MathUtilityForText.h"
#include<time.h>

//コンストラクタ
GameScene::GameScene() {

}


//デストラクタ
GameScene::~GameScene() {

	delete spriteBG_;
	delete modelStage_;
	delete modelPlayer_;
	delete modelBeam_;
	delete modelEnemy_;
	

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
	worldTransformStage_.Initialize();

	//行列変換
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_, 
		worldTransformStage_.rotation_,
	    worldTransformStage_.translation_);

	worldTransformStage_.TransferMatrix();

	//プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformPlayer_.Initialize();
	
	//ビーム
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();

	//エネミー
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();

	
	//乱数
	srand((unsigned int)time(NULL));

	//デバックテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

}

void GameScene::Update() { 
	
	switch(sceneMode_) 
	{
		
	case 0:
		GamePlayUpdate(); 
	break;

	}
}


void GameScene::GamePlayUpdate() {
	PlayerUpdate(); // プレイヤー
	BeamUpdate();   // ビーム
	EnemyUpdate();  // エネミー
	Collision();    // 衝突判定
}


//プレイヤー更新
void GameScene::PlayerUpdate() {
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);

	worldTransformPlayer_.TransferMatrix();

	// 移動

	// 右移動
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransformPlayer_.translation_.x += 0.1f;
	}

	// 左移動
	else if (input_->PushKey(DIK_LEFT)) {
		worldTransformPlayer_.translation_.x -= 0.1f;
	}

	worldTransformPlayer_.translation_.x = max(worldTransformPlayer_.translation_.x, -4);
	worldTransformPlayer_.translation_.x = min(worldTransformPlayer_.translation_.x, 4);
}

//ビーム
void GameScene::BeamUpdate() {

	BeamMove();
	BeamBorn();

	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);

	worldTransformBeam_.TransferMatrix();

}

void GameScene::BeamMove() {
	if (beamFlag_ == 0) return;
	worldTransformBeam_.translation_.z += 0.2f;
	worldTransformBeam_.rotation_.x += 0.1f;
	//画面外に行ったら
	if (worldTransformBeam_.translation_.z >= 40.0f) {
		beamFlag_ = 0;
	}
	
}

void GameScene::BeamBorn() {

	if (beamFlag_ == 1)	return;
	//スペースを押すと
	if (input_->TriggerKey(DIK_SPACE)) {
		beamFlag_ = 1;
		worldTransformBeam_.translation_.x = worldTransformPlayer_.translation_.x;
		worldTransformBeam_.translation_.z = worldTransformPlayer_.translation_.z;
		worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	}
}


//エネミー
void GameScene::EnemyUpdate() { 
	EnemyMove(); 
	EnemyBorn();
	
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	    worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	    worldTransformEnemy_.translation_);

	worldTransformEnemy_.TransferMatrix();

}

void GameScene::EnemyMove() { 
	if (enemyFlag_ == 0)return;
	worldTransformEnemy_.translation_.z -= 0.2f;
	worldTransformEnemy_.rotation_.x -= 0.1f;
	//エネミーが-5以下になったらflagがfalseになる。
	if (worldTransformEnemy_.translation_.z <= -5) {
	enemyFlag_ = 0;
	}
}

void GameScene::EnemyBorn() {

	if (enemyFlag_ == 1)return;
	enemyFlag_ = 1;
	//乱数でX座標の指定
	int x = rand() % 80;
	float x2 = (float)x / 10 - 4;
	worldTransformEnemy_.translation_.x = x2;
	worldTransformEnemy_.translation_.z = 40; 
	
}

void GameScene::Collision() {
	//衝突判定（プレイヤーと敵）
	CollisionPlayerEnemy();
	CollisionBeamEnemy();
}

void GameScene::CollisionPlayerEnemy() {
	//敵がいれば
	if (enemyFlag_ == 1) {
	// 差を求める
	float dx = abs(worldTransformPlayer_.translation_.x - worldTransformEnemy_.translation_.x);
	float dz = abs(worldTransformPlayer_.translation_.z - worldTransformEnemy_.translation_.z);

		if (dx < 1 && dz < 1) {
			enemyFlag_ = 0;
			playerLife_ -= 1;
		}
	}
}
void GameScene::CollisionBeamEnemy() {
	// 敵がいれば
	if (beamFlag_ == 1) {
		// 差を求める
		float dx = abs(worldTransformBeam_.translation_.x - worldTransformEnemy_.translation_.x);
		float dz = abs(worldTransformBeam_.translation_.z - worldTransformEnemy_.translation_.z);

		if (dx < 1 && dz < 1) {
			enemyFlag_ = 0;
			beamFlag_ = 0;
			gameScore_ += 1;
		}
	}
}

void GameScene::GamePlayDraw3D() {

	// ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);

	// プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);

	// ビーム
	if (beamFlag_ == 1) {
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}

	// エネミー
	if (enemyFlag_ == 1) {
		modelEnemy_->Draw(worldTransformEnemy_, viewProjection_, textureHandleEnemy_);
	}
}

void GameScene::GamePlay2DBack() { spriteBG_->Draw(); }

void GameScene::GamePlay2DNear() {

	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 900, 10, 2);
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
	
	switch (sceneMode_)
	{

	case 0:
		GamePlay2DBack();
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
		GamePlayDraw3D();
		break;
	}
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// デバックテキスト
	

	switch (sceneMode_) {

	case 0:
		GamePlay2DNear();
		break;
	}

	debugText_->DrawAll();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}