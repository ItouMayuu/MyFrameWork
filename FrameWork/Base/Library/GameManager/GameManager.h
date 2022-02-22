#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "../NotChangingLibrary/Singleton.h"

#include <vector>
#include <memory>

//前方定義
class GameObjectManager;
class DataSave;
class Player;
class Input;
class Map;

class GameManager : public Singleton<GameManager> {
public:
	friend class Singleton<GameManager>;

	std::shared_ptr<GameObjectManager> game_object_manager_;

	std::shared_ptr<DataSave> data_save_{ nullptr };

	std::shared_ptr<Player> player_{ nullptr };

	std::shared_ptr<Input> input_{ nullptr };

	std::shared_ptr<Map> map_{ nullptr };

protected:
	//他の所にアクセスさせないため
	GameManager() {};
	virtual ~GameManager() {};
};

#endif // !GAME_MANAGER_H_
