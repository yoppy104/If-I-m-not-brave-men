# If-I-m-not-brave-men

変更点

・Battleクラスを実装
	→以前のプログラムはBattle.hの上部にコメントとして保存している。

・vectorを導入。
	→battle中のplayer、enemyをvectorで管理することで死亡すると配列から削除することが可能である。
	→playerを削除する場合、ゲーム本体で持っているplayerベクターからは削除しないようにする工夫が必要。（コピーを使用する手法を検討中）

・Draw.hを廃止
	→描画系はそれぞれのオブジェクトに持たせる。（独自のアニメ等をやりやすくするため）

・Main関数のモーダル化
	→基本的にモードで管理（IDs.h内部で定義している。）


要望

・Battle_Stageはキャラの配置や死体の管理、マップの管理をお願い。

・呼び出しは、Battleクラスのコンストラクタ内部で行い。専用のメンバ変数に持たせる。

・描画系を変更する場合は、基本的にUpdateの中身を書き換え。そこで関数を呼んでいる場合はそこを書き換え。

・移動や攻撃に干渉する場合は、それぞれのmoveやattackが持っているstage変数をintではなく、そのクラスの型に変更して使用し、内部を書き換えるとよい。



質問があったら、遠慮なく
