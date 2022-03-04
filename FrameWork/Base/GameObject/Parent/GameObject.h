#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <string>

#include "../../Library/GameManager/GameManager.h"
#include "../../Library/Transform/Transform.h"
#include "../../Library/MyDraw/MyDraw.h"
#include "../../Resource/Image/Image.h"

class Component;

//ゲームオブジェクトクラス	　※Shared_ptrでthisが使えるように
class GameObject : public std::enable_shared_from_this<GameObject>{
public:
	//コンストラクタ
	GameObject() = default;
	//仮想デストラクタ
	virtual ~GameObject() = default;
	//ゲームオブジェクトの更新
	virtual void update();
	//描画
	virtual void draw() const;
	//半透明の描画
	virtual void draw_transparent() const;
	//GUIの描画
	virtual void draw_gui() const;
	//死亡処理
	void die();
	//死亡しているか？
	bool is_dead() const;
	//名前を取得
	const std::string& name() const;
	//タグ名を取得
	const std::string& tag() const;
	//トランスフォームを取得(const版)
	const Transform& transform() const;
	//トランスフォームを取得
	Transform& transform();

	//コンポーネントの更新
	void component_update();
	//コンポーネントの描画
	void component_draw();
	//コンポーネントを取得
	std::vector<std::shared_ptr<Component>> get_components();
	//直接コンポーネントを取得
	template<typename ComponentType>
	typename ComponentType* get_comp(const std::string& tag) const {
		//タグが一致したらコンポーネントを返す
			for (auto cp : components) {
				if (cp->tag == tag) {
					ComponentType* cps = (ComponentType*)&cp;
					return cps;
				}
			}//なにもなければnullを返す
		return nullptr;
	}
	
	//コピー禁止
	GameObject(const GameObject& other) = delete;
	GameObject& operator = (const GameObject& other) = delete;

protected:
	//タグ名
	std::string tag_;
	//名前
	std::string name_;
	//トランスフォーム
	Transform transform_;
	//死亡フラグ
	bool dead_{ false };
	//コンポーネントの配列
	std::vector<std::shared_ptr<Component>> components;

private:

	GameManager& gm = GameManager::GetInstance();
};

#endif // !GAME_OBJECT_H_