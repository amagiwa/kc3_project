# include <Siv3D.hpp> // OpenSiv3D v0.6.11
#include"Stage.h"
using namespace stg;

//ウィンドウサイズ800×600
void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	Stage* stage = new Stage(Vec2{ 500,500 }, Vec2{ 50,50 });

	const int FPS = 60;
	Stopwatch sw;
	sw.start();

	while (System::Update())
	{
		stage->update();
		while (sw.msF() < 1000.0 / FPS);
		sw.restart();
	}
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
