#include "Button.h"
#include "Engine/Engine.h"
#include "enum.h"

struct Button
{
	Vec2 Position = Vec2 (200.0f, 240.0f);
	int PushedCounter;
};

static Button g_Button;

//オンカーソル状態を判別する関数
bool StateOfOnCursor;

//オンカーソル中かどうかを判断する関数
void OnCursor()
{
	//マウス座標の取得
	Vec2 MousePos = Engine::GetMousePos();
	//ボタンサイズの取得
	Size button_size = Size(256.0f, 128.0f);

	//範囲内にマウスカーソルがあった場合にtrueを返す
	if (g_Button.Position.X <= MousePos.X &&
		g_Button.Position.X + button_size.Width >= MousePos.X &&
		g_Button.Position.Y <= MousePos.Y &&
		g_Button.Position.Y + button_size.Height >= MousePos.Y)
	{
		StateOfOnCursor = true;
	}
	else 
	{
		StateOfOnCursor = false;
	}
}

//クリック後に数秒計る用カウンター
int ButtonCounter = 0;

//ボタン更新関数
void UpdateButton()
{
	//オンカーソル状態でないならアクティブ状態のボタンを表示
	if (StateOfOnCursor == false)
	{
		Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 0.0f, 0.0f, 256.0f, 128.0f);
	}
	//オンカーソル状態ならオンカーソル状態のボタンを表示
	if (StateOfOnCursor == true)
	{
		Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 256.0f, 0.0f, 256.0f, 128.0f);

		if (Engine::IsMouseButtonPushed(MouseButton::Left))
		{
			Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 256.0f, 128.0f, 256.0f, 128.0f);

			ButtonCounter++;

			if (ButtonCounter > 10)
			{
				Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 0.0f, 128.0f, 256.0f, 128.0f);

				g_SceneStep = SceneStep::Init;
				g_SceneKind = SceneKind::GameScene;
			}
		}
	}
	//STARTボタンをクリックしたら決定ボタンを表示
	/*if (Engine::IsMouseButtonReleased(MouseButton::Left))
	{
		Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 256.0f, 128.0f, 256.0f, 128.0f);
	}*/
}