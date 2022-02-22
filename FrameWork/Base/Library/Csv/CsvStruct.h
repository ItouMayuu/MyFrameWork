#ifndef CSV_STRUCT_H_
#define CSV_STRUCT_H_

#include "../NotChangingLibrary/DataCSV.h"

struct CsvString : public DataCSV {

	CsvString(std::string filepath = "")
		: DataCSV(filepath, CsvType::CsvValue) {}

	~CsvString() { clear(); }

	void Load(std::string filepath) {
		assert(filepath != "" && "ファイル名filepathを設定してください" != "");
		DataCSV::Load(filepath, CsvType::CsvValue);
	}
};

struct CsvInt : public DataCSV {

	int None = -1;
	int CellSize = 1;

	CsvInt(int cellSize = 1, std::string filepath = "")
		: DataCSV(filepath) {}

	~CsvInt() { clear(); }

	void Load(int cellSize, std::string filepath) {
		assert(filepath != "" && "ファイル名filepathを設定してください" != "");
		DataCSV::Load(filepath);
	}
};

#endif // !CSV_STRUCT_H_
