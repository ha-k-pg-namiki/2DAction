#include "Button.h"
#include "Engine/Engine.h"
#include "enum.h"

struct Button
{
	Vec2 Position = Vec2 (200.0f, 240.0f);
	int PushedCounter;
};

static Button g_Button;

//�I���J�[�\����Ԃ𔻕ʂ���֐�
bool StateOfOnCursor;

//�I���J�[�\�������ǂ����𔻒f����֐�
void OnCursor()
{
	//�}�E�X���W�̎擾
	Vec2 MousePos = Engine::GetMousePos();
	//�{�^���T�C�Y�̎擾
	Size button_size = Size(256.0f, 128.0f);

	//�͈͓��Ƀ}�E�X�J�[�\�����������ꍇ��true��Ԃ�
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

//�N���b�N��ɐ��b�v��p�J�E���^�[
int ButtonCounter = 0;

//�{�^���X�V�֐�
void UpdateButton()
{
	//�I���J�[�\����ԂłȂ��Ȃ�A�N�e�B�u��Ԃ̃{�^����\��
	if (StateOfOnCursor == false)
	{
		Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 0.0f, 0.0f, 256.0f, 128.0f);
	}
	//�I���J�[�\����ԂȂ�I���J�[�\����Ԃ̃{�^����\��
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
	//START�{�^�����N���b�N�����猈��{�^����\��
	/*if (Engine::IsMouseButtonReleased(MouseButton::Left))
	{
		Engine::DrawTextureUV(200.0f, 240.0f, "StartButton", 256.0f, 128.0f, 256.0f, 128.0f);
	}*/
}