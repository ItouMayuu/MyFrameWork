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
	//int , float , string�^�f�[�^���i�[
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

	//�R���X�g���N�^
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
	//���z�f�X�g���N�^
	~CsvValue() {};

	//�ϊ����Z�q
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

	//String -> int�^��
	int StringToInt() {
		std::istringstream ss(StringData);
		int num;
		ss >> num;
		return num;
	}
	//String -> float�^��
	float StringToFloat() {
		std::istringstream ss(StringData);
		float num;
		ss >> num;
		return num;
	}

	//���g�̃|�C���^��Ԃ�
	inline operator CsvValue* () const {
		return *this;
	}
};

struct DataCSV {
	enum class CsvType {
		IntMap,
		CsvValue
	};

	//�ǂݍ��񂾃t�@�C�����
	std::string FilePath = "";
	int Width = 0;
	int Height = 0;
	std::vector<std::vector<CsvValue>> Data;
	//���d�p���h�~�pflag
	bool isInitilezed = false;

	//��������
	std::vector<CsvValue>& operator [] (std::size_t index) {
		return Data[index];
	}
	//�ǂݎ��
	std::vector<CsvValue> operator[] (std::size_t index) const {
		return Data[index];
	}
	//�T�C�Y��Ԃ�
	std::size_t size() {
		return Data.size();
	}
	//�R���X�g���N�^
	DataCSV(std::string FilePath = "", CsvType csvType = CsvType::IntMap) : FilePath{ FilePath } {
		if (FilePath != "") Load(FilePath);
	}
	//���z�f�X�g���N�^
	virtual ~DataCSV(){
		Data.clear();
	}
	//�폜
	virtual void clear() {
		Data.clear();
		isInitilezed = false;
	}
	//���[�h
	void Load(std::string filepath, CsvType csvType = CsvType::IntMap) {
		if (filepath == "" || isInitilezed) return;
		this->FilePath = filepath;
		Data.clear();
		std::ifstream ifs_csv_file(filepath);//�t�@�C���̓���(�J��)
		std::string line;//1�s

		int readWidth = 0;
		int maxWidth = 0;
		int readHeight = 0;          
		//����							 
		while (std::getline(ifs_csv_file, line)) {
			std::vector<CsvValue> valuelist;//1�s�������list
			std::istringstream linestream(line);//line��istringstream�^��
			std::string splitted;
			int widthCount = 0;
			//��								
			if (csvType == CsvType::IntMap) {            //[,]���Ƃɕ������ǂ݂���
				while (std::getline(linestream, splitted, { ',' })) {
					std::istringstream ss;
					ss = std::istringstream(splitted);
					int num;
					ss >> num;//ss����l���󂯎��
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

			//1�s��push
			if (valuelist.size() != 0) Data.push_back(valuelist);
			//���I���Ŏ��̍�����
			readHeight++;
		}
		readWidth = maxWidth;

		assert(readWidth > 0);
		assert(readHeight > 0);

		this->Width = readWidth;
		this->Height = readHeight;

		isInitilezed = true;//���[�h�ς�
		return;
	}
};

#endif // !DATA_CSV_H_
