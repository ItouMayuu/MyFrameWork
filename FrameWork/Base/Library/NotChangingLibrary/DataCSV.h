#ifndef DATA_CSV_H_
#define DATA_CSV_H_

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

class CsvValue {
protected:
	//int , float , string型データを格納
	union {
		int IntData = 0;
		float FloatData;
	};
	std::string StringData{ "" };

public:
	enum class Type {
		Int,
		Float,
		String,
	};
	Type type = Type::String;

	//コンストラクタ
	CsvValue() = default;

	CsvValue(int intData) : type{ Type::Int } {
		this->IntData = intData;
		this->StringData = std::to_string(intData);
	}
	CsvValue(float floatData) : type{ Type::Float } {
		this->FloatData = floatData;
		this->StringData = std::to_string(floatData);
	}
	CsvValue(std::string stringData) : type{ Type::String } {
		this->StringData = stringData;
	}
	//仮想デストラクタ
	~CsvValue() {};

	//変換演算子
	operator int() {
		if (type == Type::Float) return (int)FloatData;
		else if (type == Type::String && IntData == 0)
			IntData = StringToInt();
		return IntData;
	}
	inline operator float() {
		if (type == Type::Int) return (float)IntData;
		else if (type == Type::String && IntData == 0)
			FloatData = StringToFloat();
		return FloatData;
	}
	inline operator std::string() const {
		return StringData;
	}

	//String -> int型へ
	int StringToInt() {
		std::istringstream ss(StringData);
		int num;
		ss >> num;
		return num;
	}
	//String -> float型へ
	float StringToFloat() {
		std::istringstream ss(StringData);
		float num;
		ss >> num;
		return num;
	}

	//自身のポインタを返す
	inline operator CsvValue* () const {
		return *this;
	}
};

struct DataCSV {
	enum class CsvType {
		IntMap,
		CsvValue
	};

	//読み込んだファイル情報
	std::string FilePath = "";
	int Width = 0;
	int Height = 0;
	std::vector<std::vector<CsvValue>> Data;
	//多重継承防止用flag
	bool isInitilezed = false;

	//書き込み
	std::vector<CsvValue>& operator [] (std::size_t index) {
		return Data[index];
	}
	//読み取り
	std::vector<CsvValue> operator[] (std::size_t index) const {
		return Data[index];
	}
	//サイズを返す
	std::size_t size() {
		return Data.size();
	}
	//コンストラクタ
	DataCSV(std::string FilePath = "", CsvType csvType = CsvType::IntMap) : FilePath{ FilePath } {
		if (FilePath != "") Load(FilePath);
	}
	//仮想デストラクタ
	virtual ~DataCSV(){
		Data.clear();
	}
	//削除
	virtual void clear() {
		Data.clear();
		isInitilezed = false;
	}
	//ロード
	void Load(std::string filepath, CsvType csvType = CsvType::IntMap) {
		if (filepath == "" || isInitilezed) return;
		this->FilePath = filepath;
		Data.clear();
		std::ifstream ifs_csv_file(filepath);//ファイルの入力(開く)
		std::string line;//1行

		int readWidth = 0;
		int maxWidth = 0;
		int readHeight = 0;          
		//高さ							 
		while (std::getline(ifs_csv_file, line)) {
			std::vector<CsvValue> valuelist;//1行ずつ入れるlist
			std::istringstream linestream(line);//lineをistringstream型に
			std::string splitted;
			int widthCount = 0;
			//幅								
			if (csvType == CsvType::IntMap) {            //[,]ごとに文字列を読みこむ
				while (std::getline(linestream, splitted, { ',' })) {
					std::istringstream ss;
					ss = std::istringstream(splitted);
					int num;
					ss >> num;//ssから値を受け取る
					valuelist.push_back(CsvValue(num));
					widthCount++;
				}
			}
			else if (csvType == CsvType::CsvValue) {
				while (std::getline(linestream, splitted, { ',' })) {
					valuelist.push_back(splitted);
					widthCount++;
				}
			}
			if (widthCount > maxWidth) maxWidth = widthCount;

			//1行分push
			if (valuelist.size() != 0) Data.push_back(valuelist);
			//幅終了で次の高さへ
			readHeight++;
		}
		readWidth = maxWidth;

		assert(readWidth > 0);
		assert(readHeight > 0);

		this->Width = readWidth;
		this->Height = readHeight;

		isInitilezed = true;//ロード済み
		return;
	}
};

#endif // !DATA_CSV_H_
