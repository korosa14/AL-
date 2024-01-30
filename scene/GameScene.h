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
#include "DebugCamera.h"
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
	bool CheckStage(float x, float y);
	

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// テクスチャハンドル
	uint32_t textureHandleBlock_ = 0;
	uint32_t textureHandleBlock2_ = 0;
	uint32_t textureHandleHole_ = 0;
	uint32_t textureHandleSpine_ = 0;
	uint32_t textureHandleGoalFlag_ = 0;
	
	// 3Dモデル
	Model* model_ = nullptr;
	
	// ワールドトランスフォーム
	WorldTransform worldTransform_[50][50];
	// ビュープロジェクション
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	int sceneMode_ = 0;
	void TitleUpdate();     // タイトル更新
	void ManualUpdate();    // マニュアル更新
	void GameOverUpdate();  // ゲームオーバー更新
	void GameClearUpdate(); // ゲームクリア更新
	void GamePlayStart();
	void StageSelect();
	void Stage1();
	void BoxUpdate();
	void BoxMove();
	uint32_t textureHandleBox_ = 0;
	
	Model* modelBox_ = nullptr;
	
	WorldTransform worldTransformBox_;
	
	float SpeedX_ = 0;
	float SpeedY_ = 0;
	int SpineTimer_ = 0;
	static const int StageXMax = 50;
	static const int StageYMax = 50;

	int mapData[50][50] = {
	    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	    {1, 0, 0, 0, 3, 3, 3, 1, 0, 0, 0, 3, 3, 3, 3, 1, 3, 3, 0, 3, 3, 1, 3, 0, 3, 1, 0, 1, 3, 3, 3, 3, 3, 0, 0, 0, 3, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, 0, 4, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 3, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 1, 3, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 3, 0, 0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 1, 0, 3, 3, 3, 3, 1, 0, 0, 0, 1, 0, 1, 3, 3, 0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 4, 1, 4, 1, 4, 1, 4, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 3, 3, 0, 0, 0, 3, 3, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 3, 3, 3, 3, 0, 0, 1, 1, 1, 1, 1, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 0, 0, 0, 1, 3, 3, 3, 3, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 3, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 1, 3, 0, 3, 1, 0, 1, 0, 0, 0, 0, 0, 3, 3, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 3, 3, 1, 3, 0, 0, 0, 0, 3, 0, 1, 0, 3, 3, 3, 3, 1, 0, 0, 0, 1, 0, 1, 3, 3, 3, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 4, 1, 4, 1, 4, 1, 4, 1},
	    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 3, 3, 3, 3, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 1, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 1, 3, 0, 0, 0, 3, 1, 3, 3, 3, 3, 3, 0, 0, 1, 0, 3, 3, 3, 3, 1, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	    {1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 0, 1, 0, 4, 0, 1},
	    {1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	
	// タイトル
	uint32_t textureHandleTitle1_ = 0;
	Sprite* spriteTitle1_ = nullptr;
	// タイトル
	uint32_t textureHandleTitle2_ = 0;
	Sprite* spriteTitle2_ = nullptr;
	// タイトル
	uint32_t textureHandleTitle3_ = 0;
	Sprite* spriteTitle3_ = nullptr;
	// タイトル
	uint32_t textureHandleTitle4_ = 0;
	Sprite* spriteTitle4_ = nullptr;
	// タイトル
	uint32_t textureHandleTitle5_ = 0;
	Sprite* spriteTitle5_ = nullptr;
	int TitleTimer_ = 0;
	uint32_t textureHandleGameClear_ = 0;
	Sprite* spriteGameClear_ = nullptr;
	uint32_t textureHandleGameOver_ = 0;
	Sprite* spriteGameOver_ = nullptr;
	uint32_t textureHandleStageSelect_ = 0;
	Sprite* spriteStageSelect_ = nullptr;
	uint32_t textureHandleManual_ = 0;
	Sprite* spriteManual_ = nullptr;
	uint32_t textureHandleStage1Map_ = 0;
	Sprite* spriteStage1Map_ = nullptr;
	uint32_t textureHandleStage2Map_ = 0;
	Sprite* spriteStage2Map_ = nullptr;
	uint32_t textureHandleStage3Map_ = 0;
	Sprite* spriteStage3Map_ = nullptr;
	// サウンド
	uint32_t VoiceHandleBGM_ = 0;    // 音声再生ハンドル
	uint32_t soundTitleBGM_ = 0;     // タイトルBGM
	uint32_t soundStageSelectBGM_ = 0;  // ステージセレクトBGM
	uint32_t soundStage1_2BGM_ = 0;  // ステージ1,2BGM
	uint32_t soundStage3BGM_ = 0;  // ステージ3BGM
	uint32_t soundGameOverBGM_ = 0;  // ゲームオーバーBGM
	uint32_t soundGameClearBGM_ = 0; // ゲームクリアBGM
};
