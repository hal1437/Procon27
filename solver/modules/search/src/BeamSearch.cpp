
#include <search/BeamSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))

std::vector<BeamSearch::Hand> BeamSearch::Listup(const Problem& prob,const Log& log){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<BeamSearch::Hand> answer;
	//フレームの頂点に対して、
	for(int i=0;i<prob.frame.size();i++){
		//残りピースに対して、
		for(int j=0;j<prob.pieces.size();j++){
			//j番目がすでにLOGに入ってなければ
			if(std::find_if(log.begin(),log.end(),[&](const Hand& hand){
				return (j == hand.index);
			}) != log.end())continue;
			
			//ピースの頂点数に対して
			for(int k=0;k<prob.pieces[j].size();k++){
				
				
				//ピース角度が小さければ
				if(prob.frame.getAngle(i) < prob.pieces[j].getAngle(k)){
					BeamSearch::Hand hand;
					//角度差が極限まで小さければ
					if(std::abs(prob.frame.getAngle(i) - prob.pieces[j].getAngle(k)) < SAME_ANGLE_EPS){
						//固定設置
						hand.fixing=false;
					}else {
						//非固定設置
						hand.fixing=false;
					}
					
					//座標
					hand.pos = prob.frame.getNode(i);
					//回転
					if(hand.fixing==true){
						//2種類
						
						
					}else{
						//4種類
						const Polygon& polygon = prob.pieces[j];
						const Polygon& frame   = prob.frame;
						Point v1 = polygon.getNode(LR(k-1,polygon.size())) - polygon.getNode(k);
						Point v2 = polygon.getNode(LR(k+1,polygon.size())) - polygon.getNode(k);
						Point k1 = frame  .getNode(LR(i-1,frame  .size())) - frame  .getNode(i);
						Point k2 = frame  .getNode(LR(i+1,frame  .size())) - frame  .getNode(i);
						hand.angle.push_back(Point::getAngle2Vec(v1,k1));
						hand.angle.push_back(Point::getAngle2Vec(v2,k1));
						hand.angle.push_back(Point::getAngle2Vec(v1,k2));
						hand.angle.push_back(Point::getAngle2Vec(v2,k2));
					}
					answer.push_back(hand);
				}
			}
			
			
		}
	}
	return answer;
}

BeamSearch::Answer BeamSearch::Search(BeamSearch::Argment arg){
	BeamSearch::Answer answer;
	auto a = Listup(Problem(),Log());


	return answer;
}

