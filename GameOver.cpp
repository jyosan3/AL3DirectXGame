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

}

int GameOver::Update() { 

	gameTimer_++;

	if (input_->TriggerKey(DIK_RETURN)) {

		return 1;
	}
	return 2; 
}

void GameOver::Draw2DNear() {

	spriteGameOver_->Draw();
	if (gameTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}
