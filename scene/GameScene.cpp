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
	delete spriteTitle_;
	delete spriteEnter_;
	delete spriteGameOver_;
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
	for (int i = 0; i < 10; i++) {
		worldTransformBeam_[i].scale_ = {0.3f, 0.3f, 0.3f};
		worldTransformBeam_[i].Initialize();
	}

	//エネミー
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();
	for (int i = 0; i < 10; i++) {
		worldTransformEnemy_[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransformEnemy_[i].Initialize();
	}
	
	//乱数
	srand((unsigned int)time(NULL));

	//デバックテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	//Title
	textureHandleTitle_ = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0, 0});


	//Enter
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	//GameOver
	textureHandleGameOver_ = TextureManager::Load("gameover.png");
	spriteGameOver_ = Sprite::Create(textureHandleGameOver_, {0, 0});

}

void GameScene::Update() { 
	
	switch(sceneMode_) 
	{
		
	case 0:
	GamePlayUpdate(); 
	break;

	case 1:
	TitleUpdate();
	break;

	case 2:
	GameOverUpdate();
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

	if (playerLife_ <= 0) {
		sceneMode_ = 2;
	}

}

//ビーム
void GameScene::BeamUpdate() {

	BeamMove();
	BeamBorn();

	for (int i = 0; i < 10; i++) {
		worldTransformBeam_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformBeam_[i].scale_, worldTransformBeam_[i].rotation_,
		    worldTransformBeam_[i].translation_);

		worldTransformBeam_[i].TransferMatrix();
	}
}

void GameScene::BeamMove() {
	for (int i = 0; i < 10; i++) {
		if (beamFlag_[i] == 0)continue;

		worldTransformBeam_[i].translation_.z += 0.2f;
		worldTransformBeam_[i].rotation_.x += 0.1f;
		// 画面外に行ったら
		if (worldTransformBeam_[i].translation_.z >= 40.0f) {
			beamFlag_[i] = 0;
		}
	}
}

void GameScene::BeamBorn() {
	if (beamTimer_ == 0) {
		for (int i = 0; i < 10; i++) {
			if (beamFlag_[i] == 0) {
				// スペースを押すと
				if (input_->TriggerKey(DIK_SPACE)) {
					beamFlag_[i] = 1;
					worldTransformBeam_[i].translation_.x = worldTransformPlayer_.translation_.x;
					worldTransformBeam_[i].translation_.z = worldTransformPlayer_.translation_.z;
					worldTransformBeam_[i].scale_ = {0.3f, 0.3f, 0.3f};
					beamTimer_ = 1;
				}
				break;
			}
		}
	} 
	else {
		beamTimer_++;
		if (beamTimer_ > 10) {
			beamTimer_ = 0;
		}
	}
}


//エネミー
void GameScene::EnemyUpdate() { 
	EnemyMove(); 
	EnemyBorn();
	for (int e = 0; e < 10; e++) {
		worldTransformEnemy_[e].matWorld_ = MakeAffineMatrix(
		    worldTransformEnemy_[e].scale_, worldTransformEnemy_[e].rotation_,
		    worldTransformEnemy_[e].translation_);

		worldTransformEnemy_[e].TransferMatrix();
	}
}

void GameScene::EnemyMove() { 
	for (int e = 0; e < 10; e++) {

		if (enemyFlag_[e] == 0)continue;
		worldTransformEnemy_[e].rotation_.x -= 0.2f;
		worldTransformEnemy_[e].translation_.x += enemySpeed_[e];

		worldTransformEnemy_[e].translation_.z -= 0.4f;
		
		if (worldTransformEnemy_[e].translation_.x > 4) {
			enemySpeed_[e] = -0.1f;
		}
		if (worldTransformEnemy_[e].translation_.x < -4) {
			enemySpeed_[e] = 0.1f;
		}
		// エネミーが-5以下になったらflagがfalseになる。
		if (worldTransformEnemy_[e].translation_.z <= -5) {
			enemyFlag_[e] = 0;
		}
	}
}

void GameScene::EnemyBorn() {

	if (rand() % 10 == 0) {

		for (int e = 0; e < 10; e++) {

			if (enemyFlag_[e] == 0) {

				enemyFlag_[e] = 1;
				// 乱数でX座標の指定
				int x = rand() % 80;
				float x2 = (float)x / 10 - 4;

				worldTransformEnemy_[e].translation_.x = x2;
				worldTransformEnemy_[e].translation_.y = 0;
				worldTransformEnemy_[e].translation_.z = 40;

				// 速度
				if (rand() % 2 == 0) {
					enemySpeed_[e] = 0.1f;
				} else {
					enemySpeed_[e] = -0.1f;
				}
				break;
			}
		}
	}
}

void GameScene::Collision() {
	//衝突判定（プレイヤーと敵）
	CollisionPlayerEnemy();
	CollisionBeamEnemy();
}

void GameScene::CollisionPlayerEnemy() {
	//敵がいれば
	for (int e = 0; e < 10; e++) {
		if (enemyFlag_[e] == 1) {
		// 差を求める
		float dx = abs(worldTransformPlayer_.translation_.x - worldTransformEnemy_[e].translation_.x);
		float dz = abs(worldTransformPlayer_.translation_.z - worldTransformEnemy_[e].translation_.z);

			if (dx < 1 && dz < 1) {
			 enemyFlag_[e] = 0;
			 playerLife_ -= 1;
			}
		}
	}
}
void GameScene::CollisionBeamEnemy() {
	
	// 敵がいれば
	for (int e = 0; e < 10; e++) {
		if (enemyFlag_[e] == 1) {
			for (int i = 0; i < 10; i++) {
			 if (beamFlag_[i] == 1) {
				 // 差を求める
				 float dx = abs(worldTransformBeam_[i].translation_.x - worldTransformEnemy_[e].translation_.x);
				 float dz = abs(worldTransformBeam_[i].translation_.z - worldTransformEnemy_[e].translation_.z);

				 if (dx < 1 && dz < 1) {
					 enemyFlag_[e] = 0;
					 beamFlag_[i] = 0;
					 gameScore_ += 1;
				 }
			 }
			}
		}
	}
}

void GameScene::GamePlayDraw3D() {

	// ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);

	// プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);

	// ビーム
	for (int i = 0; i < 10; i++) {
		if (beamFlag_[i] == 1) {
			modelBeam_->Draw(worldTransformBeam_[i], viewProjection_, textureHandleBeam_);
		}
	}
	// エネミー
	for (int e = 0; e < 10; e++) {
		if (enemyFlag_[e] == 1) {
			modelEnemy_->Draw(worldTransformEnemy_[e], viewProjection_, textureHandleEnemy_);
		}
	}
}

void GameScene::GamePlay2DBack() {
	spriteBG_->Draw(); 
}

void GameScene::GamePlay2DNear() {

	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 900, 10, 2);
}


void GameScene::TitleUpdate() 
{
	
	gameTimer_ += 1; 

	if (input_->TriggerKey(DIK_RETURN)) 
	{
		sceneMode_ = 0;
		GamePlayStart();
	}

}


void GameScene::TitleDraw2DNear() 
{ 
	spriteTitle_->Draw(); 

	if (gameTimer_ % 40 >= 20) 
	spriteEnter_->Draw();

}

void GameScene::GameOverUpdate() 
{
	gameTimer_ += 1;

	if (input_->TriggerKey(DIK_RETURN)) {
	sceneMode_ = 1;
	}
}

void GameScene::GameOverDraw2DNear() 
{ 
	spriteGameOver_->Draw();

	if (gameTimer_ % 40 >= 20)
	spriteEnter_->Draw();

}

void GameScene::GamePlayStart() 
{
	//プレイヤー
	worldTransformPlayer_.translation_ = {0, 0, 0};


	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);

	worldTransformPlayer_.TransferMatrix();

	//プレイヤーライフ
	playerLife_ = 3;

	// ビーム
	for (int i = 0; i < 10; i++) {
	beamFlag_[i] = 0;
	}
	// エネミー
	for (int e = 0; e < 10; e++) {
	enemyFlag_[e] = 0;
	}
	//ゲームスコア
	gameScore_ = 0;
	
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

	case 2:
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
	case 2:
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

	case 1:
		TitleDraw2DNear();
		break;
	case 2:
		GamePlay2DNear();
		GameOverDraw2DNear();
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