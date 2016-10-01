
#include <structure/Matrix.hpp>

Point   operator* (const Point&   p,const cMat& mat){
	vMat v,after;
	v.setElement(0,0,p.x);
	v.setElement(1,0,p.y);
	v.setElement(2,0,1.0);
	after = v * mat;
	return Point(after(0,0),after(1,0));
}
Polygon operator* (const Polygon& p,const cMat& mat){
	Polygon ans;
	for(int i=0;i<p.size();i++)ans.addNode(p.getNode(i)*mat);
	return ans;
}
Point&   operator*=(Point&   p,const cMat& mat){
	p = p * mat;
	return p;
}
Polygon& operator*=(Polygon& p,const cMat& mat){
	p = p * mat;
	return p;
}

