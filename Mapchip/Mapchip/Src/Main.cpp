#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include "Engine/Engine.h"
#include "Common/Vec.h"

// チップ配列のサイズ
const int MapChipHeight = 8;
const int MapChipWidth = 10;

// マップチップID配列
int MapChipIds[MapChipHeight][MapChipWidth] =
{
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

Vec2 g_ObjPos = Vec2(200.0f, 200.0f);

// ゲーム処理
void GameProcessing();
// 描画処理
void DrawProcessing();

bool OnCollisionRectAndMapChip02(Vec2 obj_pos, Vec2 obj_size)
{
	// 1-1 矩形の四頂点の座標を算出する
	Vec2 vertices[] =
	{
		// 左上
		obj_pos,
		// 右下
		Vec2(obj_pos.X + obj_size.X, obj_pos.Y + obj_size.Y),
	};

	// 座標を配列番号に変換する
	int width_ids[] =
	{
		vertices[0].X / 64.0f,	// 始点
		vertices[1].X / 64.0f	// 終点
	};

	int height_ids[] =
	{
		vertices[0].Y / 64.0f,	// 始点
		vertices[1].Y / 64.0f	// 終点
	};


	// 横と縦の配列番号をもとに始点～終点までチェックする
	for (int y = height_ids[0]; y < height_ids[1]; y++)
	{
		for (int x = width_ids[0]; x < width_ids[1]; x++)
		{
			// 配列の番号が有効な値かどうかをチェック
			if ((x < 0 || x >= MapChipWidth) &&
				(y < 0 || y >= MapChipHeight))
			{
				continue;
			}

			// 0以外は有効番号 => 有効番号 == マップチップが配置されている
			if (MapChipIds[y][x] != 0)
			{
				// 当たり
				return true;
			}
		}
	}

	return false;
}

bool OnCollisionRectAndMapChip(Vec2 obj_pos, Vec2 obj_size)
{
	// 1-1 矩形の四頂点の座標を算出する
	Vec2 vertices[] =
	{
		// 左上
		obj_pos,
		// 右上
		Vec2(obj_pos.X + obj_size.X, obj_pos.Y),
		// 右下
		Vec2(obj_pos.X + obj_size.X, obj_pos.Y + obj_size.Y),
		// 左下
		Vec2(obj_pos.X, obj_pos.Y + obj_size.Y),
	};

	// 1-2 座標を配列の要素番号に変換
	int vertex_mapchip_ids_w[4];
	int vertex_mapchip_ids_h[4];

	for (int i = 0; i < 4; i++)
	{
		vertex_mapchip_ids_w[i] = vertices[i].X / 64.0f;
		vertex_mapchip_ids_h[i] = vertices[i].Y / 64.0f;
	}

	// 矩形の各頂点の位置にあるチップが有効かどうかを判定する
	for (int i = 0; i < 4; i++)
	{
		int w = vertex_mapchip_ids_w[i];
		int h = vertex_mapchip_ids_h[i];
		
		// 配列の番号が有効な値かどうかをチェック
		if ((w < 0 || w >= MapChipWidth) &&
			(h < 0 || h >= MapChipHeight))
		{
			continue;
		}

		// 0以外は有効番号 => 有効番号 == マップチップが配置されている
		if (MapChipIds[h][w] != 0)
		{
			// 当たり
			return true;
		}
	}

	// 当たっていない
	return false;
}

/*
	エントリポイント
*/
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmpLine,
	_In_ INT       nCmdShow)
{
	// エンジンの初期化
	// ゲームループ開始前に1度だけ実行する
	if (Engine::Initialize(640, 480, "Sample") == false)
	{
		return 0;
	}

	// テクスチャ読み込み
	// 第一引数の文字列で読み込んだテクスチャを登録する
	// 描画や取得は登録した文字列で指定する
	Engine::LoadTexture("MapChip", "Res/MapChip.png");
	Engine::LoadTexture("Object", "Res/Enemy.png");

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// ゲーム処理
			GameProcessing();

			// 描画開始
			DrawProcessing();
		}
	}

	// エンジン終了
	// ゲームループ終了後に1度だけ実行する
	// テクスチャとサウンドファイルも全て解放する
	Engine::Release();

	// メモリリーク検出
	_CrtDumpMemoryLeaks();

	return 0;

} // プログラム終了

void GameProcessing()
{
	// 入力データの更新
	Engine::Update();

	// オブジェクトの移動量
	Vec2 vector = Vec2(0.0f, 0.0f);
	// 移動速度
	float speed = 2.0f;

	// オブジェクトの移動処理
	if (Engine::IsKeyboardKeyHeld(DIK_UPARROW))
	{
		vector.Y = -speed;
	}
	else if (Engine::IsKeyboardKeyHeld(DIK_DOWNARROW))
	{
		vector.Y = speed;
	}

	if (Engine::IsKeyboardKeyHeld(DIK_LEFTARROW))
	{
		vector.X = -speed;
	}
	else if (Engine::IsKeyboardKeyHeld(DIK_RIGHTARROW))
	{
		vector.X = speed;
	}

	Texture* tex = Engine::GetTexture("Object");
	Vec2 size = Vec2(tex->Width, tex->Height);

	// マップチップと矩形の当たり判定
	if (OnCollisionRectAndMapChip(
		// 現在値に移動量を加算した座標
		Vec2(g_ObjPos.X + vector.X, g_ObjPos.Y + vector.Y),
		// 矩形のサイズ
		size) == false)
	{
		g_ObjPos.X += vector.X;
		g_ObjPos.Y += vector.Y;
	}

}

void DrawProcessing()
{
	// 描画開始
	Engine::StartDrawing(0);

	Vec2 pos = Vec2(0, 0);
	Vec2 tex_pos = Vec2(0, 0);
	Vec2 chip_size = Vec2(64.0f, 64.0f);
	
	// Yサイズ(配列)
	for (int i = 0; i < MapChipWidth; i++)
	{
		// Xサイズ(配列)
		for (int j = 0; j < MapChipHeight; j++)
		{
			// 0だったら描画をしない
			if (MapChipIds[j][i] == 0)
			{
				continue;
			}

			// テクスチャ座標割り出し
			tex_pos.X = MapChipIds[j][i] % 4 * chip_size.X;
			tex_pos.Y = MapChipIds[j][i] / 4 * chip_size.Y;

			// 描画座標割り出し
			pos = Vec2(i * chip_size.X, j * chip_size.Y);
			
			Engine::DrawTextureUV(
				pos.X,
				pos.Y,
				"MapChip",
				tex_pos.X,
				tex_pos.Y,
				chip_size.X,
				chip_size.Y);
		}
	}

	Engine::DrawTexture(g_ObjPos.X, g_ObjPos.Y, "Object");

	// 描画終了
	Engine::FinishDrawing();
}
