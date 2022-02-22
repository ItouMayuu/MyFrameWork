#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "../Scene/Parent/Scene.h"
#include <string>
#include <memory>
#include <unordered_map>
#include "../Library/NotChangingLibrary/Singleton.h"


class SceneManager : public Singleton<SceneManager>{
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void init();
	//毎フレームupdate
	void update();
	//描画
	void draw();
	//終了
	void fin();
	//シーン変更 (変更先のシーン名)
	void change_scene(std::string scene);
	//シーンの追加 (追加するシーン名 , 追加するシーンクラス)
	void add_scene(std::string SceneName, std::shared_ptr<Scene> sceneClass);

private:
	//追加したシーンを辞書登録してまとめておく
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;

	//現在のシーン
	std::shared_ptr<Scene> current_scene_;
};
#endif
