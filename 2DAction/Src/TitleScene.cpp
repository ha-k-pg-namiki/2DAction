#include "TitleScene.h"
#include "enum.h"
#include "Engine/Engine.h"
#include "Button.h"

void InitTitleScene();
void RunTitleScene();
void FinishTitleScene();

void InitTitleScene()
{
	// ���̓f�[�^�̍X�V
	Engine::Update();

	// �e�N�X�`���ǂݍ���
	Engine::LoadTexture("StartButton", "Res/Button.png");

	g_SceneStep = SceneStep::Run;
}

int feadAlpha = 0;
bool fadeout = false;

void RunTitleScene()
{
	// ���̓f�[�^�̍X�V
	Engine::Update();

	//// ���s(���C������)
	//Engine::DrawFont(200.0f, 200.0f, "�^�C�g���V�[���̎��s����", Regular, White);
	Engine::DrawFont(200.0f, 200.0f, "Title Scene", Regular, White);

	Engine::DrawRect(0, 0, 640, 480, 0x000000, feadAlpha);

	// �X�e�b�v��Finish�ɕύX => �V�[���̐؂�ւ��̏������������ꂽ��ύX
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

	OnCursor();

	UpdateButton();

}

void FinishTitleScene()
{
	// ���̓f�[�^�̍X�V
	Engine::Update();

	// ��n��
	// �ǂݍ��񂾃e�N�X�`���̉��
	Engine::ReleaseTexture("StartButton");

	// �X�e�b�v��Init�ɕύX(���̃V�[���̂��߂̏�����)
	g_SceneStep = SceneStep::Init;
	g_SceneKind = SceneKind::GameScene;
}
