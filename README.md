# kc3_project

このプログラムはフレームワークSiv3Dを用いて制作されています。  
https://siv3d.github.io/ja-jp/  

このプログラムの目的はAIスクリプトを読み込ませてSTGのゲームAIを動作させることです。  
ゲームオブジェクトはすべてSiv3Dの図形描画によって実装されています。  

ヘッダファイル.hにはclass定義、ソースファイル.cppにはその実装が記述されています。  

基本的にいじるファイルはStage.h/cpp, Manager.h/cppだけでOKです。  
Stage.h/cppはゲーム画面をオブジェクトとして扱うものでゲームオブジェクトの最大単位です。  
(UnityのSceneみたいなもの)  
Manager.h/cppはStageがもつオブジェクトを操作したり、便利な関数をもったりします。  
その他のファイル定義については各ヘッダファイルを参照。  

PlayerはZキーでShotを撃つことができ、矢印キーで位置を操作できます。  
EnemyはBulletを撃ちます。  

TODO:  
EnemyにShotが当たったときの処理の実装  
PlayerにBulletが当たったときの処理の実装  
(今はとりあえずShot/Bulletの存在フラグisActiveをfalseにするくらいでOK)  
(これら2つは流用したStageクラスの関数を使用しているがこれをManagerクラスに吐き出す)  
Managerクラス:  
Enemyがいい感じにBulletをばらまく機能  
(できれば)オブジェクトを現在地から指定の位置まで移動させる機能  

↑その他に思いついたものがあれば自由に実装してもらって大丈夫です。<br>
