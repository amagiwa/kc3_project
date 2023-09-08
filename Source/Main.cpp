# include <Siv3D.hpp> // OpenSiv3D v0.6.11
#include"Stage.h"
using namespace stg;
Stage* stage;

Vec2 getPlayerPosition();
Vec2 getEnemyPosition();
Array<Vec2> getBulletsPosition();
Array<Vec2> getBulletsVelocity();
void Regist(AngelScript::asIScriptEngine*);

//ウィンドウサイズ800×600
void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	stage = new Stage(Vec2{ 500,500 }, Vec2{ 50,50 });

	Regist(Script::GetEngine());
	ManagedScript ai(U"../ai.as");
	//auto main = ai.getFunction<void()>(U"Main");

	//Stage stage;

	const int FPS = 60;
	Stopwatch sw;
	sw.start();

	while (System::Update())
	{
		ai.run();
		stage->update();
		while (sw.msF() < 1000.0 / FPS);
		sw.restart();
	}
}

Vec2 getPlayerPosition() {
	return stage->getPlayerPosition();
}

Vec2 getEnemyPosition() {
	return stage->getEnemyPosition();
}

Array<Vec2> getBulletsPosition() {
	return stage->getBulletsPosition();
}

Array<Vec2> getBulletsVelocity() {
	return stage->getBulletsVelocity();
}

//TODO: Playerをスクリプトで動かすこと

using namespace AngelScript;
void Regist(asIScriptEngine* engine) {
	int r = 0;
	r = engine->RegisterGlobalFunction("Vec2 getPlayerPosition()", asFUNCTION(getPlayerPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getEnemyPosition()", asFUNCTION(getEnemyPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getBulletsPosition()", asFUNCTION(getBulletsPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getBulletsVelocity()", asFUNCTION(getBulletsVelocity), asCALL_CDECL); assert(r >= 0);
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
