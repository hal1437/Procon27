
#include <iostream>
#include <structure/Point.hpp>
#include <structure/Polygon.h>
#include <structure/Matrix.hpp>
#include <structure/ProblemMaker.h>
#include <structure/Drawer.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <search/Deproyment.h>

int main(int argc,char* argv[]){

	Problem prob = ProblemMaker::MakeTriangleProblem();
	for(auto& p: prob.pieces){
		p.normalize();
	}
	Deproyment dep;
	
	std::shuffle(prob.pieces.begin(), prob.pieces.end(), std::mt19937());
	dep.base = prob.pieces[0];
	prob.pieces.erase(prob.pieces.begin());
	dep.Run(prob.pieces);
}
