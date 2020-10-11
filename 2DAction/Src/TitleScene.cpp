#include "TitleScene.h"
#include "enum.h"
#include "Engine/Engine.h"

void InitTitleScene();
void RunTitleScene();
void FinishTitleScene();

void InitTitleScene()
{
	// 入力データの更新
	Engine::Update();

	g_SceneStep = SceneStep::Run;
}

int feadAlpha = 0;
bool fadeout = false;

void RunTitleScene()
{
	// 入力データの更新
	Engine::Update();

	//// 実行(メイン処理)
	//Engine::DrawFont(200.0f, 200.0f, "タイトルシーンの実行処理", Regular, White);
	Engine::DrawFont(200.0f, 200.0f, "Title Scene", Regular, White);

	Engine::DrawRect(0, 0, 640, 480, 0x000000, feadAlpha);

	// ステップをFinishに変更 => シーンの切り替えの条件が満たされたら変更
	if (Engine::IsKeyboardKeyHeld(DIK_Z))
	{
		fadeout = true;
	}

	if (fadeout == true)
	{
		feadAlpha++;

		if (feadAlpha == 255)
		{
			g_SceneStep = SceneStep::Finish;
		}
	}
}

void FinishTitleScene()
{
	// 入力データの更新
	Engine::Update();

	// 後始末

	// ステップをInitに変更(次のシーンのための初期化)
	g_SceneStep = SceneStep::Init;
	g_SceneKind = SceneKind::GameScene;
}
