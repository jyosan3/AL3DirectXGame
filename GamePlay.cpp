#include"GamePlay.h"

GamePlay::GamePlay() {}

GamePlay::~GamePlay() {
	delete stage_;
	delete player_;
	for (Beam* beam : beamTable_) {
		delete beam;
	}
	for (Enemy* enemy : enemyTable_) {
		delete enemy;
	}
	
}

void GamePlay::Initialize(ViewProjection view) {

	viewProjection_ = view;

	stage_ = new Stage();
	stage_->Initialize(viewProjection_);

	// プレイヤー
	player_ = new Player();
	player_->Initialize(viewProjection_);

	// ビーム

	for (int j = 0; j < 10; j++) {
		beamTable_[j] = new Beam();
	}
	for (Beam* beam : beamTable_) {
		beam->Initialize(viewProjection_, player_);
	}
	// エネミー
	for (int i = 0; i < 10; i++) {
		enemyTable_[i] = new Enemy();
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Initialize(viewProjection_);
	}

	

	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();
	
	input_ = Input::GetInstance();

	// サウンド
	audio_ = Audio::GetInstance();
	soundDataHandleBGM_ = audio_->LoadWave("Audio/Ring08.wav");

	soundDataHandleEnemySE_ = audio_->LoadWave("Audio/chord.wav");

	soundDataHandlePlayerSE_ = audio_->LoadWave("Audio/tada.wav");

	


}

int GamePlay::Update() {
	player_->Update();
	for (Beam* beam : beamTable_) {
		beam->Update();
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Update();
	}
	

	CollisionBeamEnemy();
	CollisionPlayerEnemy();
	
	Shot();
	

	if (playerLife_ <= 0) {
		audio_->StopWave(voiceHandleBGM_);
		return 2;
	}
	return 0;
}

void GamePlay::Start() {

	player_->Start();
	
	for (Enemy* enemy : enemyTable_) {
		enemy->Start();
	}
	for (Beam* beam : beamTable_) {
		beam->Start();
	}



	// プレイヤーライフ
	playerLife_ = 3;

	// ゲームスコア
	gameScore_ = 0;

	Sound();

}

void GamePlay::Shot() {

	if (ShotTimer_ == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			for (Beam* beam : beamTable_) {
				if (beam->GetFlag() == 0) {
					beam->Born();
					beam->Update();
					ShotTimer_ = 1;
					break;
				}
			}
		}
	} 
	else {
		ShotTimer_++;

		if (ShotTimer_ > 10) {
			ShotTimer_ = 0;
		}
	}
}



void GamePlay::Sound() {
	voiceHandleBGM_ = audio_->PlayWave(soundDataHandleBGM_, true); 
}


void GamePlay::CollisionPlayerEnemy() {
	for (Enemy* enemy : enemyTable_) {
		if (enemy->GetFlag() == 1) {
			float dx = abs(player_->GetX() - enemy->GetX());
			float dy = abs(player_->GetY() - enemy->GetY());
			float dz = abs(player_->GetZ() - enemy->GetZ());
			if (dx < 1 && dz < 1 && dy < 1) {
				enemy->Hit();
				audio_->PlayWave(soundDataHandlePlayerSE_); 
				playerLife_ -= 1;
			}
		}
	}
}

void GamePlay::CollisionBeamEnemy() {
	for (Enemy* enemy : enemyTable_) {
		for (Beam* beam : beamTable_) {
			if (beam->GetFlag() == 1) {
				// 差を求める
				float dx = abs(beam->GetX() - enemy->GetX());
				float dy = abs(beam->GetY() - enemy->GetY());
				float dz = abs(beam->GetZ() - enemy->GetZ());


				if (dx < 1 && dz < 1 && dy < 1 ) {
					enemy->Hit();
					beam->Hit();
					audio_->PlayWave(soundDataHandleEnemySE_); 
					gameScore_ += 1;
				}
			}
		}
	}
}


void GamePlay::Draw() {}

void GamePlay::Draw2DFar() {

	stage_->Draw2DFar();

}

void GamePlay::Draw3D() {

	player_->Draw3D();
	for (Beam* beam : beamTable_) {
		beam->Draw3D();
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Draw3D();
	}
}

void GamePlay::Draw2DNear() {

	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 1000, 10, 2);

	debugText_->DrawAll();

}