#include "GameScene.h"
#include "enum.h"
#include "Engine/Engine.h"

void InitGameScene();
void RunGameScene();
void FinishGameScene();

int feadinAlpha = 255;

struct Slider
{
	Vec2 Position;		// 座標
	Size Size;			// サイズ
	float MinValue;		// 最小値
	float MaxValue;		// 最大値
	float CurrentValue;	// 現在値
	float TargetValue;	// 目標値
	float Speed;		// 速度
};

Slider g_Slider =
{
	Vec2(0.0f, 100.0f), Size(640.0f, 30.0f), 0.0f, 100.f, 0.0f, 100.0f, 0.046875f
};

void UpdateSlider()
{
	// 方向チェック
	float vector = g_Slider.TargetValue - g_Slider.CurrentValue;

	if (vector == 0.0f)
	{
		return;
	}

	// 現在値変動
	float sign = 1.0f;
	if (vector < 0.0f)
	{
		sign = -1.0f;
	}

	g_Slider.CurrentValue += sign * g_Slider.Speed;

	// 目標値オーバーチェック
	if (g_Slider.Speed >= abs(vector))
	{
		// 現在値にオーバーした値が設定されないようにする
		g_Slider.CurrentValue = g_Slider.TargetValue;

		// ②のための専用処理
		// 次の目標値
		if (g_Slider.TargetValue == 0.0f)
		{
			g_Slider.TargetValue = 100.0f;
		}
		else
		{
			g_Slider.TargetValue = 0.0f;
		}
	}
}

void DrawSlider()
{
	float percent = (g_Slider.CurrentValue - g_Slider.MinValue) / (g_Slider.MaxValue - g_Slider.MinValue);
	// 描画矩形のサイズ
	float width = g_Slider.Size.Width * percent;

	Engine::DrawRect(
		g_Slider.Position.X,
		g_Slider.Position.Y,
		width,
		g_Slider.Size.Height,
		0xffffff
	);
}

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

	UpdateSlider();

	DrawSlider();

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
