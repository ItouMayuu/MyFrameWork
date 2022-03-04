#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <list>
#include <vector>
#include <string>
#include <memory>

#include "../GameManager.h"

//前方定義
class GameObject;
class Component;

//ゲームオブジェクト全体を管理するマネージャークラス
class GameObjectManager {
public:
	//デフォルトコンストラクタ
	GameObjectManager() = default;
	//デストラクタ
	~GameObjectManager();
	//アクターの追加
	void add(std::shared_ptr<GameObject> gameobject);
	//アクター全体の更新
	void update();
	//アクター全体の描画
	void draw();
	//死亡しているアクターの削除
	void remove();
	//キャストなしで直接アクターを取得
	template<typename GameObjectType>
	GameObjectType* get(const std::string& tag) const {
		//名前が一致したらそのゲームオブジェクトを返す
		for (auto go : game_objects_) {
			if (go->name() == tag) {
				GameObjectType* gos = (GameObjectType*)&go;
				return gos;
			}
		}//なにもなければnullを返す
		return nullptr;
	}
	//アクターの検索
	std::shared_ptr<GameObject> find(const std::string& name) const;
	//指定したタグ名を持つアクターの検索
	std::vector<std::shared_ptr<GameObject>> find_with_tag(const std::string& tag) const;
	//全体のアクター数を返す
	int count() const;
	//指定したタグ名を持つアクターを返す
	int count_with_tag(const std::string& tag) const;
	//全アクターを削除
	void clear();

	//特定のコンポーネントの削除
	void component_clear(GameObject* owner, std::string tag);
	//コンポーネントの追加
	void component_add(GameObject* owner,std::shared_ptr<Component> comp);
	//全てのコンポーネントの削除
	void component_clear_all(GameObject* owner);

	//コピー防止
	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
	//全アクターのリスト
	std::list<std::shared_ptr<GameObject>> game_objects_;
	//ゲームマネージャー保持
	GameManager& gm = GameManager::GetInstance();
};

#endif // !GAME_OBJECT_MANAGER_H_