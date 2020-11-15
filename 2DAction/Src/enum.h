#ifndef ENUM_H

extern enum SceneKind
{
	TitleScene,
	GameScene,
	ResultScene,
};

extern enum SceneStep
{
	Init,
	Run,
	Finish,
};

extern SceneKind g_SceneKind;
extern SceneStep g_SceneStep;

#endif ENUM_H    //#ifndef ENUM_H