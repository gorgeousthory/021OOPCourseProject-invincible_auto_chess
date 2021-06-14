#pragma once

#ifndef __CSV_PARSER_H__
#define __CSV_PARSER_H__

#include "cocos2d.h"
USING_NS_CC;

#define D_STAR1				0
#define D_STAR2				1
#define D_STAR3				2

#define D_NUMBER			0
#define D_EN_NAME			1
#define D_CH_NAME			2
#define D_PATH				3
#define D_COST				4
#define D_HP_LEVEL			5
#define D_HP				6
#define D_MP				7
#define D_ATK_LEVEL			8
#define D_ATK				9
#define D_DFC_LEVEL			10
#define D_DFC				11
#define D_ATK_SPD			12
#define D_ATK_SCP			13
#define D_CRT_CHC			14
#define D_CRT_DMG			15


class LineString
{
public:
	LineString(const std::string& str);
	virtual ~LineString();

	size_t getColumnCount() const { return _lineStr.size(); }

	std::string& operator[](size_t index)
	{
		CCASSERT(index < this->getColumnCount(), "invalid index in lineInfo");
		return _lineStr[index];
	}

protected:
	void initWithString(const std::string& str);

private:
	std::vector<std::string> _lineStr;
};

class CsvParser
{
public:
	CsvParser();
	virtual ~CsvParser();

	void parseWithFile(const std::string& csvFilename);	//��ȡ���ݱ��

	size_t getRowCount() const { return _dataInfo.size(); }	//��ȡ�����ֵ
	size_t getColumnCount() const { return _titles.size(); }	//��ȡ�����ֵ
	size_t findRowOfItem(const std::string& src) const;	//�ҵ�ĳ���������ڵ���

	LineString& operator[](size_t index)
	{
		CCASSERT(index < this->getRowCount(), "invalid index in lineInfo"); //this need discussing
		return _dataInfo[index];
	}

private:
	std::vector<std::string> _titles;
	std::vector<LineString> _dataInfo;
};
#endif // __CSV_PARSER_H__