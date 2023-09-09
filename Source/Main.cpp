# include <Siv3D.hpp> // OpenSiv3D v0.6.11
#include"Stage.h"
using namespace stg;
Stage* stage;

Vec2 getPlayerPosition();
Vec2 getEnemyPosition();
Vec2 getNearestBulletPosition();
Vec2 getNearestBulletVelocity();
void movePlayer(int, int, bool);
void shootShot();
void moveEnemyRandom();
void Regist(AngelScript::asIScriptEngine*);

//ウィンドウサイズ800×600
void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	stage = new Stage(Vec2{ 500,500 }, Vec2{ 50,50 });

	Regist(Script::GetEngine());
	//ManagedScript ai(U"../ai.as");
	ManagedScript ai(U"ai.as");
	//auto main = ai.getFunction<void()>(U"Main");

	//Stage stage;

	const int FPS = 60;
	Stopwatch sw;
	sw.start();

	while (System::Update())
	{
		stage->update();
		ai.run();
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

Vec2 getNearestBulletPosition() {
	return stage->getNearestBulletPosition();
}

Vec2 getNearestBulletVelocity() {
	return stage->getNearestBulletVelocity();
}

void movePlayer(int dx, int dy, bool isShift) {
	stage->movePlayer(dx, dy, isShift);
}

void shootShot() {
	stage->shootShot();
}

void moveEnemyRandom() {
	stage->moveEnemyRandom();
}

using namespace AngelScript;
void Regist(asIScriptEngine* engine) {
	int r = 0;
	r = engine->RegisterGlobalFunction("Vec2 getPlayerPosition()", asFUNCTION(getPlayerPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getEnemyPosition()", asFUNCTION(getEnemyPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getNearestBulletPosition()", asFUNCTION(getNearestBulletPosition), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("Vec2 getNearestBulletVelocity()", asFUNCTION(getNearestBulletVelocity), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void movePlayer(int, int, bool)", asFUNCTIONPR(movePlayer, (int, int, bool), void), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void shootShot()", asFUNCTION(shootShot), asCALL_CDECL); assert(r >= 0);
	r = engine->RegisterGlobalFunction("void moveEnemyRandom()", asFUNCTION(moveEnemyRandom), asCALL_CDECL); assert(r >= 0);
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
