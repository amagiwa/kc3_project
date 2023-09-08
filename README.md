# kc3_project

このプログラムはフレームワークSiv3Dを用いて制作されています。<br>
https://siv3d.github.io/ja-jp/ <br>

このプログラムの目的はAIスクリプトを読み込ませてSTGのゲームAIを動作させることです。<br>
ゲームオブジェクトはすべてSiv3Dの図形描画によって実装されています。<br>

ヘッダファイル.hにはclass定義、ソースファイル.cppにはその実装が記述されています。<br>

基本的にいじるファイルはStage.h/cpp, Manager.h/cppだけでOKです。<br>
Stage.h/cppはゲーム画面をオブジェクトとして扱うものでゲームオブジェクトの最大単位です。<br>
(UnityのSceneみたいなもの)<br>
Manager.h/cppはStageがもつオブジェクトを操作したり、便利な関数をもったりします。<br>
その他のファイル定義については各ヘッダファイルを参照。<br>

PlayerはZキーでShotを撃つことができ、矢印キーで位置を操作できます。<br>
EnemyはBulletを撃ちます。<br>

TODO:<br>
EnemyにShotが当たったときの処理の実装<br>
PlayerにBulletが当たったときの処理の実装<br>
(今はとりあえずShot/Bulletの存在フラグisActiveをfalseにするくらいでOK)<br>
(これら2つは流用したStageクラスの関数を使用しているがこれをManagerクラスに吐き出す)<br>
Managerクラス:<br>
Enemyがいい感じにBulletをばらまく機能<br>
(できれば)オブジェクトを現在地から指定の位置まで移動させる機能<br>

↑その他に思いついたものがあれば自由に実装してもらって大丈夫です。<br>
