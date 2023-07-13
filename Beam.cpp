#include "Beam.h"

Beam::Beam() {}

Beam::~Beam() {
	
	delete modelBeam_;

}

void Beam::Initialize(ViewProjection view,Player* player) {

	viewProjection_ = view;
	player_ = player;


	// ビーム
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();

	// インプットクラス
	input_ = Input::GetInstance();

}

void Beam::Start() {

	beamFlag_ = 0;

}

void Beam::Update() {
	//移動
	Move();
	
	// 変換行列を更新
		worldTransformBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	//	変換行列を定数バッファに変換
	worldTransformBeam_.TransferMatrix();



}

void Beam::Draw3D() {
	if (beamFlag_ == 1) {
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}
}

void Beam::Move() {

	if (beamFlag_ == 1) {
		worldTransformBeam_.translation_.z += 0.2f;
		worldTransformBeam_.rotation_.x += 0.1f;
	}
	
	if (worldTransformBeam_.translation_.z >= 40) {
		beamFlag_ = 0;
	}

}

void Beam::Born() {

	if (input_->TriggerKey(DIK_SPACE) && beamFlag_ == 0 ) {
		beamFlag_ = 1;
		worldTransformBeam_.translation_.x = player_->GetX();
		worldTransformBeam_.translation_.z = player_->GetZ();
		worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	}
}

