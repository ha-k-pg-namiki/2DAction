#include "Update.h"
#include "enum.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneKind g_SceneKind = SceneKind::TitleScene;
SceneStep g_SceneStep = SceneStep::Init;


void UpdateScene()
{
	// シーンの種類によって各シーンのUpdate関数を実行する
	switch (g_SceneKind)
	{
	case SceneKind::TitleScene:
		UpdateTitleScene();
		break;
	case SceneKind::GameScene:
		UpdateGameScene();
		break;
	}
}



void UpdateTitleScene()
{
	// g_SceneStepの値から各ステップ関数を実行する
	switch (g_SceneStep)
	{
	case SceneStep::Init:
		InitTitleScene();
		break;
	case SceneStep::Run:
		RunTitleScene();
		break;
	case SceneStep::Finish:
		FinishTitleScene();
		break;
	}
}

void UpdateGameScene()
{
	// g_SceneStepの値から各ステップ関数を実行する
	switch (g_SceneStep)
	{
	case SceneStep::Init:
		InitGameScene();
		break;
	case SceneStep::Run:
		RunGameScene();
		break;
	case SceneStep::Finish:
		FinishGameScene();
		break;
	}
}