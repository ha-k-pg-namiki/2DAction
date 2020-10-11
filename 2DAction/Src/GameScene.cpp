#include "GameScene.h"
#include "enum.h"
#include "Engine/Engine.h"

void InitGameScene();
void RunGameScene();
void FinishGameScene();

int feadinAlpha = 255;

void InitGameScene()
{
	// 入力データの更新
	Engine::Update();

	Engine::DrawFont(200.0f, 200.0f, "InitGameScene", Regular, White);

	Engine::DrawRect(0, 0, 640, 480, 0x000000, feadinAlpha);

	feadinAlpha--;

	if (feadinAlpha == 0)
	{
		g_SceneStep = SceneStep::Run;
	}
}

void RunGameScene()
{
	// 入力データの更新
	Engine::Update();

	// 実行(メイン処理)
	Engine::DrawFont(200.0f, 200.0f, "Game Scene", Regular, White);

	int feadAlpha = 255;

	if (Engine::IsKeyboardKeyHeld(DIK_RETURN))
	{
		g_SceneStep = SceneStep::Finish;
	}
}

void FinishGameScene()
{
	// 入力データの更新
	Engine::Update();

	// 後始末

	// ステップをInitに変更(次のシーンのための初期化)
	g_SceneStep = SceneStep::Init;
	g_SceneKind = SceneKind::GameScene;
}
