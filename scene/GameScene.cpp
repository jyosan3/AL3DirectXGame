#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete model_;
	delete sprite_;
	delete debugCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//読み込み処理
	textureHandle_ = TextureManager::Load("sample.png");
	//生成
	sprite_ = Sprite::Create(textureHandle_, {10, 10});

	//モデル読み込み処理
	modelTextureHandle_ = TextureManager::Load("sample.png");
	//生成
	model_ = Model::Create();

	//ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	//ビュープロジェクション初期化
	viewProjection_.Initialize();

	//音声の読み込み
	soundHandle_ = audio_->LoadWave("fanfare.wav");
	//再生
	audio_->PlayWave(soundHandle_,true);

	//ライン
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	//デバックカメラ
	debugCamera_ = new DebugCamera(1280,720);

	//軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() 
{
	//スプライト移動
	Vector2 pos = sprite_->GetPosition();
	pos.x += 1;
	pos.y += 1;
	sprite_->SetPosition(pos);

	//入力
	if (input_->TriggerKey(DIK_SPACE)) {
		//音声停止
		audio_->StopWave(soundHandle_);
	}
	
	//デバックテキスト
	ImGui::ShowDemoWindow();

	ImGui::Begin("Test");
	ImGui::Text("Kamata tarou %d, %d, %d", 2023, 10, 23);

	ImGui::InputFloat3("InputFloat3", inputFloat);
	ImGui::SliderFloat3("SliderFloat3",inputFloat,0.0f,1.0f);


	ImGui::End();

	//デバックカメラ
	debugCamera_->Update();

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

	//スプライト
	sprite_->Draw();

	//ライン描画
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	


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
	//モデル描画
	//model_->Draw(worldTransform_,viewProjection_,modelTextureHandle_);

	// デバックカメラ
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), modelTextureHandle_);

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
