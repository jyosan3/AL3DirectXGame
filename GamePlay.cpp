#include"GamePlay.h"

GamePlay::GamePlay() {}

GamePlay::~GamePlay() {
	delete stage_;
	delete player_;
	delete beam_;
	delete enemy_; 

}

void GamePlay::Initialize(ViewProjection view) {

	viewProjection_ = view;

	stage_ = new Stage();
	stage_->Initialize(viewProjection_);

	// プレイヤー
	player_ = new Player();
	player_->Initialize(viewProjection_);

	// ビーム
	beam_ = new Beam();
	beam_->Initialize(viewProjection_, player_);

	// エネミー
	enemy_ = new Enemy();
	enemy_->Initialize(viewProjection_);

	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();
	
}

void GamePlay::Update() {
	stage_->Update();
	player_->Update();
	beam_->Update();
	enemy_->Update();
	CollisionBeamEnemy();
	CollisionPlayerEnemy();
}

void GamePlay::CollisionPlayerEnemy() {

	if (enemy_->GetFlag() == 1) {
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());
		if (dx < 1 && dz < 1) {
			enemy_->Hit();
			playerLife_ -= 1;
		}
	}
}

void GamePlay::CollisionBeamEnemy() {

	if (beam_->GetFlag() == 1) {
		// 差を求める
		float dx = abs(beam_->GetX() - enemy_->GetX());
		float dz = abs(beam_->GetZ() - enemy_->GetZ());

		if (dx < 1 && dz < 1) {
			enemy_->Hit();
			beam_->Hit();
			gameScore_ += 1;
		}
	}
}

void GamePlay::Draw() {}

void GamePlay::Draw2DFar() {

	stage_->Draw2DFar();

}

void GamePlay::Draw3D() {

	stage_->Draw3D();
	player_->Draw3D();
	beam_->Draw3D();
	enemy_->Draw3D();

}

void GamePlay::Draw2DNear() {

	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 1000, 10, 2);

	debugText_->DrawAll();

}