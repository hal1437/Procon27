
#pragma once

#include <structure/Point.hpp>
#include <vector>

//多角形クラス
class Polygon{
protected:

	std::vector<Point> v; //頂点座標

public:

	//頂点追加
	bool addNode(const Point& p);
	//正規化
	bool normalize();

	//面積算出
	double getArea()const;
	
	//頂点抽出
	Point getNode(int index)const;
	//頂点設定
	bool setNode(int index,const Point& pos);

};

