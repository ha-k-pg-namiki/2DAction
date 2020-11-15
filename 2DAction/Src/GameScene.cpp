#include "GameScene.h"
#include "enum.h"
#include "Engine/Engine.h"

void InitGameScene();
void RunGameScene();
void FinishGameScene();

int feadinAlpha = 255;

struct Slider
{
	Vec2 Position;		// ���W
	Size Size;			// �T�C�Y
	float MinValue;		// �ŏ��l
	float MaxValue;		// �ő�l
	float CurrentValue;	// ���ݒl
	float TargetValue;	// �ڕW�l
	float Speed;		// ���x
};

Slider g_Slider =
{
	Vec2(0.0f, 100.0f), Size(640.0f, 30.0f), 0.0f, 100.f, 0.0f, 100.0f, 0.046875f
};

void UpdateSlider()
{
	// �����`�F�b�N
	float vector = g_Slider.TargetValue - g_Slider.CurrentValue;

	if (vector == 0.0f)
	{
		return;
	}

	// ���ݒl�ϓ�
	float sign = 1.0f;
	if (vector < 0.0f)
	{
		sign = -1.0f;
	}

	g_Slider.CurrentValue += sign * g_Slider.Speed;

	// �ڕW�l�I�[�o�[�`�F�b�N
	if (g_Slider.Speed >= abs(vector))
	{
		// ���ݒl�ɃI�[�o�[�����l���ݒ肳��Ȃ��悤�ɂ���
		g_Slider.CurrentValue = g_Slider.TargetValue;

		// �A�̂��߂̐�p����
		// ���̖ڕW�l
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
	// �`���`�̃T�C�Y
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
	// ���̓f�[�^�̍X�V
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
	// ���̓f�[�^�̍X�V
	Engine::Update();

	UpdateSlider();

	DrawSlider();

	// ���s(���C������)
	Engine::DrawFont(200.0f, 200.0f, "Game Scene", Regular, White);

	int feadAlpha = 255;

	if (Engine::IsKeyboardKeyHeld(DIK_RETURN))
	{
		g_SceneStep = SceneStep::Finish;
	}
}

void FinishGameScene()
{
	// ���̓f�[�^�̍X�V
	Engine::Update();

	// ��n��

	// �X�e�b�v��Init�ɕύX(���̃V�[���̂��߂̏�����)
	g_SceneStep = SceneStep::Init;
	g_SceneKind = SceneKind::GameScene;
}
