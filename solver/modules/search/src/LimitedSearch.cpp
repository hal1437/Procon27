
#include <search/LimitedSearch.h>


double LimitedSearch::GetHeuristic(const Polygon& poly)const{
	double sum = 0;
	for(int i=0;i<heuristic.size();i++){
		sum += (*heuristic[i])(poly);
	}
	return sum;
}


//評価関数追加
void LimitedSearch::AddHeuristic(Heuristic<Polygon>* h){
	this->heuristic.push_back(h);
}

//探索
LimitedSearch::Answer LimitedSearch::Search(const Problem& prob){


	//探索ノード
	struct Node{
		Polygon frame;
		int h_val;
		std::vector<std::pair<TransParam,int>> hands;
	};

	LimitedSearch::Answer answer;  //回答
	//Polygon frame = prob.frame; //フレーム
	std::random_device rd;      //乱数生成器
	std::list<Node> queue;//探索キュー


	//初期状態追加
	queue.push_back(Node{prob.frame,std::numeric_limits<int>::max(),std::vector<std::pair<TransParam,int>>()});
	queue.push_back(Node{prob.frame,std::numeric_limits<int>::max(),std::vector<std::pair<TransParam,int>>()});

	//全てのピースの設置位置まで探索を完了していなければ
	while(queue.front().hands.size() != prob.pieces.size() && queue.size() != 1){

		std::cout << queue.front().hands.size() << std::endl;
		Node node = queue.front(); //ノード取り出し
		queue.pop_front();    //先頭を削除
// 		std::cout << queue.front().hands.size();

		//全ピースの配置位置を計算
		for(int i=0;i<prob.pieces.size();i++){ //ピース
			//使用済みの場合は探索しない
			if(std::find_if(node.hands.begin(),node.hands.end(),[&](std::pair<TransParam,int>& v){
				return (v.second == i);
			})!=node.hands.end())continue;

			for(int j=0;j<node.frame.size();j++){      //配置位置

				//リストアップ実施
				std::vector<TransParam> list = Listup(node.frame,j,prob.pieces[i]);
// 				list.push_back(TransParam());

				//全てキューに追加
				for(int k=0;k<list.size();k++){
					//先頭の一つ目の変形を適用
					Node n;
					n.frame = Merge(node.frame,Transform(prob.pieces[i],list[k]));
					n.h_val = GetHeuristic(n.frame);
					n.hands = node.hands;
					n.hands.push_back(std::make_pair(list[k],i));
					queue.push_back(n);
				}
			}
		}

		//評価
		queue.sort([](const Node& lhs,const Node& rhs){
			return (lhs.h_val < rhs.h_val);
		});

		//探索幅まで縮小
		if(queue.size() > WIDTH_LIMIT){
			queue.erase(std::next(queue.begin() , WIDTH_LIMIT),queue.end());
		}
		std::cout << "steped" << std::endl;
	}
	std::cout << "finished" << std::endl;
	for(auto aa : queue.front().hands){
		std::cout << aa.second << std::endl;
	}
	for(int i=0;i<prob.pieces.size();i++){
		auto it = std::find_if(queue.front().hands.begin(),queue.front().hands.end(),[&](std::pair<TransParam,int>& v){
			return (v.second == i);
		});
		if(it != queue.front().hands.end()){
			answer.push_back(it->first);
		}else{
			answer.push_back(TransParam());
		}
	}
	
	return answer;
}



