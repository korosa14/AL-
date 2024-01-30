#include "GameScene.h"
#include "MathUtilityForText.h"
#include "TextureManager.h"
#include "time.h"
#include <cassert>
GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete modelBox_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	// サウンドデータの読み込み
	soundTitleBGM_ = audio_->LoadWave("Audio/Title.mp3");
	soundStageSelectBGM_ = audio_->LoadWave("Audio/StageSelect.mp3");
	soundStage1_2BGM_ = audio_->LoadWave("Audio/Stage1_2.mp3");
	soundStage3BGM_ = audio_->LoadWave("Audio/Stage3.mp3");
	soundGameOverBGM_ = audio_->LoadWave("Audio/Gameover.mp3");
	soundGameClearBGM_ = audio_->LoadWave("Audio/GameClear.mp3");
	// タイトルBGMを再生
	audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
	VoiceHandleBGM_ = audio_->PlayWave(soundTitleBGM_, true);

	// テクスチャ
	textureHandleBlock_ = TextureManager::Load("block.png");
	textureHandleBlock2_ = TextureManager::Load("block2.png");
	textureHandleHole_ = TextureManager::Load("hole.png");
	textureHandleSpine_ = TextureManager::Load("spine.png");
	textureHandleGoalFlag_ = TextureManager::Load("goalflag.png");
	textureHandleGameClear_ = TextureManager::Load("GameClear.png");
	textureHandleGameOver_ = TextureManager::Load("GameOver.png");
	textureHandleStage1Map_ = TextureManager::Load("Stage1map.png");
	textureHandleStage2Map_ = TextureManager::Load("Stage2map.png");
	textureHandleStage3Map_ = TextureManager::Load("Stage3map.png");
	textureHandleStageSelect_ = TextureManager::Load("StageSelect.png");
	textureHandleManual_ = TextureManager::Load("Manual.png");
	spriteManual_ = Sprite::Create(textureHandleManual_, {0, 0});
	spriteStageSelect_ = Sprite::Create(textureHandleStageSelect_, {0, 0});
	spriteStage1Map_ = Sprite::Create(textureHandleStage1Map_, {0, 0});
	spriteStage2Map_ = Sprite::Create(textureHandleStage2Map_, {0, 0});
	spriteStage3Map_ = Sprite::Create(textureHandleStage3Map_, {0, 0});
	spriteGameClear_ = Sprite::Create(textureHandleGameClear_, {0, 0});
	spriteGameOver_ = Sprite::Create(textureHandleGameOver_, {0, 0});
	// タイトル
	textureHandleTitle1_ = TextureManager::Load("Title1.png");
	spriteTitle1_ = Sprite::Create(textureHandleTitle1_, {0, 0});
	// タイトル
	textureHandleTitle2_ = TextureManager::Load("Title2.png");
	spriteTitle2_ = Sprite::Create(textureHandleTitle2_, {0, 0});
	// タイトル
	textureHandleTitle3_ = TextureManager::Load("Title3.png");
	spriteTitle3_ = Sprite::Create(textureHandleTitle3_, {0, 0});
	// タイトル
	textureHandleTitle4_ = TextureManager::Load("Title4.png");
	spriteTitle4_ = Sprite::Create(textureHandleTitle4_, {0, 0});
	// タイトル
	textureHandleTitle5_ = TextureManager::Load("Title5.png");
	spriteTitle5_ = Sprite::Create(textureHandleTitle5_, {0, 0});
	// 3Dモデルも生産
	model_ = Model::Create();
	

	// ワールドトランスフォームの初期化
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {

			worldTransform_[y][x].translation_.x = (float)x * 2;
			worldTransform_[y][x].translation_.y = (float)y * 2;

			worldTransform_[y][x].Initialize();
		}
	}
	

	// 3Dモデルも生産
	model_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	textureHandleBox_ = TextureManager::Load("cube.jpg");
	modelBox_ = Model::Create();
	worldTransformBox_.translation_.x = 4.0f;
	worldTransformBox_.translation_.y = 4.0f;
	worldTransformBox_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {
	// 各シーンの更新処理
	switch (sceneMode_) {
	case 0:
		TitleUpdate(); // タイトル更新
		break;
	case 1:
		StageSelect(); // ステージセレクト
		break;
	case 2:
		ManualUpdate(); // マニュアル更新
		break;
	case 3:
		GameClearUpdate(); // ゲームクリア更新
		break;
	case 4:
		GameOverUpdate(); // ゲームオーバー更新
		break;
	case 5:
		Stage1();
		BoxUpdate();

		break;
	}
}

void GameScene::TitleUpdate() {
	// ステージセレクトへ
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneMode_ = 1;
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundStageSelectBGM_, true);
	}
	TitleTimer_ += 1;
	if (TitleTimer_ >= 25) {
		TitleTimer_ = 0;
	}
}
void GameScene::StageSelect() {

	// 操作説明へ
	if (input_->TriggerKey(DIK_F)) {
		sceneMode_ = 2;
	}
	// タイトルへ
	if (input_->TriggerKey(DIK_Q)) {
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundTitleBGM_, true);
		sceneMode_ = 0;
	}
	// ステージ１
	if (input_->TriggerKey(DIK_1)) {
		GamePlayStart();
		viewProjection_.translation_.z = -70;
		viewProjection_.translation_.y = 25;
		viewProjection_.translation_.x = 47;
		viewProjection_.rotation_.y = 0;
		viewProjection_.Initialize();
		sceneMode_ = 5;
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundStage1_2BGM_, true);
	}
	
}
void GameScene::ManualUpdate() {
	// ステージセレクトへ
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneMode_ = 1;
	}
}

void GameScene::GamePlayStart() {

	worldTransformBox_.translation_.x = 4.0f;
	worldTransformBox_.translation_.y = 4.0f;
	SpeedX_ = 0;
	SpeedY_ = 0;
	SpineTimer_ = 0;
}

void GameScene::Stage1() {

	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			worldTransform_[y][x].matWorld_ = MakeAffineMatrix(
			    worldTransform_[y][x].scale_, worldTransform_[y][x].rotation_,
			    worldTransform_[y][x].translation_);
			// 変換行列を定数バッファに転送
			worldTransform_[y][x].TransferMatrix();
		}
	}
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 棘の切り替え
	SpineTimer_ += 1;
	if (SpineTimer_ >= 100) {
		SpineTimer_ = 0;
	}
	// ステージセレクトへ
	if (input_->TriggerKey(DIK_Q)) {
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundStageSelectBGM_, true);
		sceneMode_ = 1;
	}
}


void GameScene::BoxUpdate() {

	BoxMove();

	// 変換行列を更新
	worldTransformBox_.matWorld_ = MakeAffineMatrix(
	    worldTransformBox_.scale_, worldTransformBox_.rotation_, worldTransformBox_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformBox_.TransferMatrix();
}

void GameScene::BoxMove() {

	// 移動操作
	if (input_->PushKey(DIK_RIGHT)) {
		float x = worldTransformBox_.translation_.x + 0.15f;
		float y = worldTransformBox_.translation_.y;
		if (CheckStage(x, y) == false) {
			worldTransformBox_.translation_.x += 0.15f;
		}
	}
	if (input_->PushKey(DIK_LEFT)) {
		float x = worldTransformBox_.translation_.x - 0.15f;
		float y = worldTransformBox_.translation_.y;
		if (CheckStage(x, y) == false) {
			worldTransformBox_.translation_.x -= 0.15f;
		}
	}
	if (input_->PushKey(DIK_UP)) {
		float x = worldTransformBox_.translation_.x;
		float y = worldTransformBox_.translation_.y + 0.15f;
		if (CheckStage(x, y) == false) {
			worldTransformBox_.translation_.y += 0.15f;
		}
	}
	if (input_->PushKey(DIK_DOWN)) {
		float x = worldTransformBox_.translation_.x;
		float y = worldTransformBox_.translation_.y - 0.15f;
		if (CheckStage(x, y) == false) {
			worldTransformBox_.translation_.y -= 0.15f;
		}
	}
	worldTransformBox_.rotation_.x -= 0.1f;
}



// 壁との当たり判定
bool GameScene::CheckStage(float px, float py) {
	if (sceneMode_ == 5) {
		for (int y = 0; y < 50; y++) {
			for (int x = 0; x < 50; x++) {
				// 壁
				if (mapData[y][x] == 1) {
					float x2 = worldTransform_[y][x].translation_.x;
					float y2 = worldTransform_[y][x].translation_.y;
					if (abs(x2 - px) < 1.9 && abs(y2 - py) < 1.9) {
						return true;
					}
				}
				// ゴール
				if (mapData[y][x] == 2) {
					float x2 = worldTransform_[y][x].translation_.x;
					float y2 = worldTransform_[y][x].translation_.y;
					if (abs(x2 - px) < 1.9 && abs(y2 - py) < 1.9) {
						// ゲームBGMを再生
						audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
						VoiceHandleBGM_ = audio_->PlayWave(soundGameClearBGM_, true);
						sceneMode_ = 3;
					}
				}
				// 穴
				if (mapData[y][x] == 3) {
					float x2 = worldTransform_[y][x].translation_.x;
					float y2 = worldTransform_[y][x].translation_.y;
					if (abs(x2 - px) < 1.9 && abs(y2 - py) < 1.9) {
						// ゲームBGMを再生
						audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
						VoiceHandleBGM_ = audio_->PlayWave(soundGameOverBGM_, true);
						sceneMode_ = 4;
					}
				}
				// 棘
				if (mapData[y][x] == 4 && SpineTimer_ <= 50) {
					float x2 = worldTransform_[y][x].translation_.x;
					float y2 = worldTransform_[y][x].translation_.y;
					if (abs(x2 - px) < 1.9 && abs(y2 - py) < 1.9) {
						// ゲームBGMを再生
						audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
						VoiceHandleBGM_ = audio_->PlayWave(soundGameOverBGM_, true);
						sceneMode_ = 4;
					}
				}
			}
		}
	}
	
	return false; // 通路
}


void GameScene::GameOverUpdate() {

	// ステージセレクトへ
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneMode_ = 1;
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundStageSelectBGM_, true);
	}
}

void GameScene::GameClearUpdate() {

	// ステージセレクトへ
	if (input_->TriggerKey(DIK_SPACE)) {
		sceneMode_ = 1;
		// ゲームBGMを再生
		audio_->StopWave(VoiceHandleBGM_); // 現在のBGMを停止
		VoiceHandleBGM_ = audio_->PlayWave(soundStageSelectBGM_, true);
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	switch (sceneMode_) {
	case 0:
		if (TitleTimer_ <= 5) {
			spriteTitle1_->Draw();
		}
		if (TitleTimer_ >= 5 && TitleTimer_ <= 10) {
			spriteTitle2_->Draw();
		}
		if (TitleTimer_ >= 10 && TitleTimer_ <= 15) {
			spriteTitle3_->Draw();
		}
		if (TitleTimer_ >= 15 && TitleTimer_ <= 20) {
			spriteTitle4_->Draw();
		}
		if (TitleTimer_ >= 20) {
			spriteTitle5_->Draw();
		}
		break;
	case 1:
		spriteStageSelect_->Draw();
		break;
	case 2:
		spriteManual_->Draw();
		break;
	case 3:
		spriteGameClear_->Draw();
		break;
	case 4:
		spriteGameOver_->Draw();
		break;
	case 5:
		spriteStage1Map_->Draw();
		break;
	}
	/// </summary>

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
	switch (sceneMode_) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:
		for (int y = 0; y < 50; y++) {
			for (int x = 0; x < 50; x++) {
				if (mapData[y][x] == 1) { // 壁
					model_->Draw(worldTransform_[y][x], viewProjection_, textureHandleBlock_);
				}
				if (mapData[y][x] == 2) { // ゴール
					model_->Draw(worldTransform_[y][x], viewProjection_, textureHandleGoalFlag_);
				}
				if (mapData[y][x] == 3) { // 穴
					model_->Draw(worldTransform_[y][x], viewProjection_, textureHandleHole_);
				}
				if (mapData[y][x] == 4 && SpineTimer_ <= 50) { // 棘
					model_->Draw(worldTransform_[y][x], viewProjection_, textureHandleSpine_);
				}
			}
		}

		modelBox_->Draw(worldTransformBox_, viewProjection_, textureHandleBox_);

		break;
	}

	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (sceneMode_) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
