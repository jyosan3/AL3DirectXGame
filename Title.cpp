#include "Title.h"

Title::Title() {}

Title::~Title() {
	
	delete spriteTitle_;
	delete spriteEnter_;

}

void Title::Initialize() {

	input_ = Input::GetInstance();

	// Title
	textureHandleTitle_ = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0, 0});

	// Enter
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	audio_ = Audio::GetInstance();
	soundDataHandleBGM_ = audio_->LoadWave("Audio/Ring05.wav");

	Start();

}

int Title::Update() {

	gameTimer_ ++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		audio_->StopWave(voiceHandleBGM_);
		return 0;
	}
	return 1;
}

void Title::Start() {

	voiceHandleBGM_ = audio_->PlayWave(soundDataHandleBGM_, true);

}



void Title::Draw2DNear() {

	spriteTitle_->Draw();
	if (gameTimer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}


}

