#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugText.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:

	void GamePlayUpdate();
	void GamePlayDraw3D();
	void GamePlay2DBack();
	void GamePlay2DNear();

	void TitleUpdate();
	void TitleDraw2DNear();

	void GameOverUpdate();
	void GameOverDraw2DNear();

	void GamePlayStart();

	void StageUpdate();

	void EnemyJump();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	 
	
	//背景
	uint32_t textureHandleBG_ = 0;
	Sprite* spriteBG_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;
	
	//ステージ
	uint32_t textureHandleStage_ = 0;
	Model* modelStage_ = 0;
	WorldTransform worldTransformStage_[20];


	//プレイヤー
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	void PlayerUpdate();

	//ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_[10];

	int beamFlag_[10] = {};

	int beamTimer_ = 0;

	void BeamUpdate();
	void BeamMove();
	void BeamBorn();


	//エネミー
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_[10];

	void EnemyUpdate();
	void EnemyMove();
	void EnemyBorn();

	int enemyFlag_[10] = {};

	float enemySpeed_[10] = {};

	float enemyJumpSpeed_[10] = {};

	//衝突判定

	void Collision();
	void CollisionPlayerEnemy();

	void CollisionBeamEnemy();

	DebugText* debugText_ = nullptr;

	int gameScore_ = 0;
	int playerLife_ = 3;


	int sceneMode_ = 1;

	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	int gameTimer_ = 0;

	uint32_t textureHandleGameOver_ = 0;
	Sprite* spriteGameOver_ = nullptr;

	uint32_t soundDataHandleTitleBGM_ = 0;
	uint32_t soundDataHandleGamePlayBGM_ = 0;
	uint32_t soundDataHandleGameOverBGM_ = 0;
	uint32_t soundDataHandleEnemyHitSE_ = 0;
	uint32_t soundDataHandlePlayerHitSE_ = 0;
	uint32_t voiceHandleBGM_ = 0;

};
