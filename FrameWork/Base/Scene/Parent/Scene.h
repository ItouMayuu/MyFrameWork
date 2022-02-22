#ifndef SCENE_H_
#define SCENE_H_

//各Sceneの親クラス
class Scene {
public:
	//仮想デストラクタ
	virtual ~Scene() = default;

	//継承シーンの初期化
	virtual void init() = 0;

	//継承シーンの更新
	virtual void update() = 0;

	//継承シーンの描画
	virtual void draw() = 0;

	//継承シーンの終了
	virtual void fin() = 0;
};

#endif // !SCENE_H_
