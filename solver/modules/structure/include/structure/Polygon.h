
#pragma once

#include <structure/Point.hpp>
#include <util/Printable.h>
#include <vector>

//多角形クラス
class Polygon:public Printable{
/*
 * ・反時計周りに番号を振ること
 *
 *　 　7
 *  1　┏━━━┓6
 * 　┏┛0　 　┃
 * 　┃　　 4　┃
 * 　┃　　　┏┛5
 * 　┗━━━┛
 *  2         3
 *
 * */

protected:

	std::vector<Point> v; //頂点座標

public:

	//正規化
	bool normalize();
	Polygon getNormalize()const;
	//反転
	bool reverse();
	Polygon getReverse()const;

	//面積算出
	double getArea()const;
	//角度算出
	double getAngle(int index)const;

	//番号調整
	bool ConfirmNumbers();

	//内包
	bool isComprehension(const Point& p)const;

	//頂点数取得
	size_t size()const;
	//頂点追加
	bool addNode(const Point& p);
	bool addNode(size_t index,const Point& p);
	//頂点抽出
	Point getNode(int index)const;
	//頂点設定
	bool setNode(int index,const Point& pos);
	//頂点削除
	bool removeNode(int index);

	//出力
	virtual void Print(std::ostream& ost)const;

};

