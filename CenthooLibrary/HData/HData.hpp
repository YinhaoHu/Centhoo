#ifndef _HDATA_HPP_
#define _HDATA_HPP_

//	Centhoo Library: HData
//  Author: Henry Hoo
//  Note: More information is written in the README.md

#include<algorithm>
#include<string>
#include<vector>
#include<fstream>
#include<codecvt>


namespace ceh
{
	namespace Data
	{
		class HData;
		class HWData;
		class HDataItem;
		class HWDataItem;

		using HDataItem_key = std::string;
		using HDataItem_value = std::string;
		using HDataItem_values = std::vector<std::string>;

		using HWDataItem_key = std::wstring;
		using HWDataItem_value = std::wstring;
		using HWDataItem_values = std::vector<std::wstring>;

		std::wstring ceh::Data::utf8ToWstring(const std::string& utf8Str);
		std::string ceh::Data::wstringToUtf8(const std::wstring& wStr);
	};
}

std::wstring ceh::Data::utf8ToWstring(const std::string& utf8Str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}
std::string ceh::Data::wstringToUtf8(const std::wstring& wStr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

struct ceh::Data::HDataItem
{
	std::string key;
	std::vector<std::string> values;

	HDataItem();
	HDataItem(const HDataItem& rhs);
	HDataItem(std::string& k, std::vector<std::string>& values);
	HDataItem(std::string&& k, std::vector<std::string>&& values);
	~HDataItem();

	bool operator==(HDataItem& rhs);
	HDataItem& operator=(HDataItem& rhs);
	HDataItem& operator=(HDataItem&& rhs);


	static inline std::string toStdString(HDataItem& item, char delimeter = ' ')
	{
		std::string retString = item.key + delimeter;

		for (const std::string& value : item.values)
		{
			retString += value + delimeter;
		}
		retString.back() = '\0';

		return retString;
	}
	static inline std::string toStdString(const HDataItem& item, char delimeter = ' ') {
		return toStdString(const_cast<HDataItem&>(item));
	}
	static inline HDataItem fromStdString(std::string& str, char delimeter = ' ')
	{
		HDataItem item;
		HDataItem_key key;
		HDataItem_values values;
		HDataItem_value tempValue;

		auto beginIter = str.begin(), endIter = find(beginIter, str.end(), delimeter);
		key.resize(endIter - beginIter);
		copy(beginIter, endIter, key.begin());
		beginIter = endIter + 1;
		while (beginIter != str.end())
		{
			endIter = find(beginIter, str.end(), delimeter);
			tempValue.resize(endIter - beginIter);
			copy(beginIter, endIter, tempValue.begin());
			values.push_back(tempValue);

			beginIter = (endIter == str.end()) ? str.end() : endIter + 1;
		}
		item.key = key;
		item.values = values;

		return item;
	}
};

struct ceh::Data::HWDataItem
{
	HWDataItem_key key;
	HWDataItem_values values;

	HWDataItem();
	HWDataItem(const HWDataItem& rhs);
	HWDataItem(HWDataItem_key& k, HWDataItem_values& values);
	HWDataItem(HWDataItem_key&& k, HWDataItem_values&& values);
	~HWDataItem();

	bool operator==(HWDataItem& rhs);
	HWDataItem& operator=(HWDataItem& rhs);
	HWDataItem& operator=(HWDataItem&& rhs);


	static inline std::wstring toStdWString(HWDataItem& item, wchar_t delimeter = ' ')
	{
		std::wstring retString = item.key + delimeter;

		for (const std::wstring& value : item.values)
		{
			retString += value + delimeter;
		}
		retString.back() = L'\0';

		return retString;
	}
	static inline std::wstring toStdWString(const HWDataItem& item, wchar_t delimeter = ' ') {
		return toStdWString(const_cast<HWDataItem&>(item));
	}
	static inline HWDataItem fromStdWString(std::wstring& str, wchar_t delimeter = ' ')
	{
		HWDataItem item;
		HWDataItem_key key;
		HWDataItem_values values;
		HWDataItem_value tempValue;

		auto beginIter = str.begin(), endIter = find(beginIter, str.end(), delimeter);
		key.resize(endIter - beginIter);
		copy(beginIter, endIter, key.begin());
		beginIter = endIter + 1;
		while (beginIter != str.end())
		{
			endIter = find(beginIter, str.end(), delimeter);
			tempValue.resize(endIter - beginIter);
			copy(beginIter, endIter, tempValue.begin());
			values.push_back(tempValue);

			beginIter = (endIter == str.end()) ? str.end() : endIter + 1;
		}
		item.key = key;
		item.values = values;

		return item;
	}
};

class ceh::Data::HData
{
public:
	HData(const char* filename, int delimiter = ' ');
	~HData();

	HDataItem& operator[](int idx);

	void load();
	void save();

	bool fail();
	int size();

	int find(ceh::Data::HDataItem& x);
	HDataItem& access(int idx);
	bool modify(int idx, ceh::Data::HDataItem& newItem);
	bool remove(int idx);
	void append(ceh::Data::HDataItem& newItem);
	void append(ceh::Data::HDataItem&& newItem);
private:
	int delimiter;
	std::fstream fileObject;
	std::vector<HDataItem> dataBuffer;
};


class ceh::Data::HWData
{
public:
	HWData(const char* filename, wchar_t delimiter = ' ');
	~HWData();

	HWDataItem& operator[](int idx);

	void load();
	void save();

	bool fail();
	int size();

	int find(ceh::Data::HWDataItem& x);
	HWDataItem& access(int idx);
	bool modify(int idx, ceh::Data::HWDataItem& newItem);
	bool remove(int idx);
	void append(ceh::Data::HWDataItem& newItem);
	void append(ceh::Data::HWDataItem&& newItem);
private:
	wchar_t delimiter;
	std::wfstream fileObject;
	std::vector<HWDataItem> dataBuffer;
};

#endif