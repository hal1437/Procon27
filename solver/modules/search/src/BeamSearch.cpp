
#include <search/BeamSearch.h>
#define LoopRenge(x,r) ((x+r)%r)
#define LR(x,r) (LoopRenge(x,r))

std::vector<BeamSearch::Hand> BeamSearch::Listup(const Problem& prob,const Log& log){
	//多角形の頂点を枠の頂点に一致させる。
	std::vector<BeamSearch::Hand> answer;

	//3重ループ
	//i:フレームの頂点数
	//j:残りピース数
	//k:ピースの頂点数


	for(int i=0;i<prob.frame.size();i++){
		for(int j=0;j<prob.pieces.size();j++){
			//j番目がすでにLOGに入ってなければ
			if(std::find_if(log.begin(),log.end(),[&](const Hand& hand){
				return (j == hand.index);
			}) != log.end())continue;
			
			//ピースの頂点数に対して
			for(int k=0;k<prob.pieces[j].size();k++){
				
				//ピース角度が小さければ
				if(prob.frame.getAngle(i) < prob.pieces[j].getAngle(k)){
					bool fitting;
					//角度差が極限まで小さければ
					if(std::abs(prob.frame.getAngle(i) - prob.pieces[j].getAngle(k)) < SAME_ANGLE_EPS){
						//固定設置
						fitting=true;
					}else {
						//非固定設置
						fitting=false;
					}

					//変換を記録
					const Polygon& pol    = prob.pieces[j];
					const Polygon  re_pol = prob.pieces[j].getReverse();
					const Polygon& frame  = prob.frame;
							
					//角度一致(2種類)
					Point v1 = pol   .getNode(LR(k-1,pol   .size())) - pol   .getNode(k);
					Point r1 = re_pol.getNode(LR(k-1,re_pol.size())) - re_pol.getNode(k);
					Point f1 = frame .getNode(LR(i-1,frame .size())) - frame  .getNode(i);
					answer.push_back(Hand{j,prob.frame.getNode(i),false,Point::getAngle2Vec(v1,f1)});
					answer.push_back(Hand{j,prob.frame.getNode(i),true ,Point::getAngle2Vec(r1,f1)});
					
					//角度不一致(追加2種類)
					if(fitting==false){
						Point v2 = pol   .getNode(LR(k+1,pol   .size())) - pol   .getNode(k);
						Point r2 = re_pol.getNode(LR(k+1,re_pol.size())) - re_pol.getNode(k);
						Point f2 = frame .getNode(LR(i+1,frame .size())) - frame  .getNode(i);
						answer.push_back(Hand{j,prob.frame.getNode(i),false,Point::getAngle2Vec(v2,f2)});
						answer.push_back(Hand{j,prob.frame.getNode(i),true ,Point::getAngle2Vec(r2,f2)});
					}
				}
			}
			
			
		}
	}
	return answer;
}

BeamSearch::Answer BeamSearch::Search(const Problem& prob){
	BeamSearch::Answer answer;
	std::vector<BeamSearch::Hand> list = Listup(prob,Log());

	for(int i=0;i<list.size();i++){
		std::cout << "#" << i << std::endl;
		std::cout << "  index   = " << list[i].index   << std::endl;
		std::cout << "  pos     = " << list[i].pos     << std::endl;
		std::cout << "  reverse = " << list[i].reverse << std::endl;
		std::cout << "  angle   = " << list[i].angle   << std::endl;
	}

	return answer;
}

