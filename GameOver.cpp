#include "GameOver.h"

GameOver::GameOver() {}

GameOver::~GameOver() {
	delete spriteGameOver_;
	delete spriteEnter_;
}

void GameOver::Initialize() {

	input_ = Input::GetInstance();

	// Title
	textureHandleGameOver_ = TextureManager::Load("gameover.png");
	spriteGameOver_ = Sprite::Create(textureHandleGameOver_, {0, 0});

	// Enter
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	//サウンド
	audio_ = Audio::GetInstance();
	soundDataHandleBGM_ = audio_->LoadWave("Audio/Ring09.wav");

	Start();

}

int GameOver::Update() { 

	gameTimer_++;

	if (input_->TriggerKey(DIK_RETURN)) {

		audio_->StopWave(voiceHandleBGM_);

		return 1;
	}
	return 2; 
}

void GameOver::Sound() {

	voiceHandleBGM_ = audio_->PlayWave(soundDataHandleBGM_, true); 

}

void GameOver::Draw2DNear() {

	spriteGameOver_->Draw();
	if (gameTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}

void GameOver::Start() { 
	Sound();
}
