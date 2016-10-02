
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
		Polygon frame; //状態
		int h_val;     //評価値
		std::vector<std::pair<TransParam,int>> hands; //履歴

		inline int step(){return this->hands.size();}//使用手数
	};

	//Polygon frame = prob.frame; //フレーム
	LimitedSearch::Answer answer;  //回答
	std::random_device rd;        //乱数生成器
	std::deque<Node> queue;//探索キュー

	int index = 0;
	//初期状態追加
	queue.push_back(Node{prob.frame,std::numeric_limits<int>::max(),std::vector<std::pair<TransParam,int>>()});

	//ステップが最後になるまで
	while(index < prob.pieces.size()){
	
		std::cout << "======= " << index << " =======" << std::endl;

		//深さループ
		for(int d = 0;d < DEPTH_LIMIT && index < prob.pieces.size();d++){
			int queue_size = queue.size();//キューのサイズ
			for(int q=0;q<queue_size;q++){
				Node node = queue.front(); //先頭取り出し
				queue.pop_front();         //先頭を削除

				//全ピースの配置位置を計算
				for(int i = 0;i < prob.pieces.size();i++){ //ピース
					//使用済みの場合はスキップ
					if(std::find_if(node.hands.begin(),node.hands.end(),[&](std::pair<TransParam,int>& v){
						return (v.second == i);
					})!=node.hands.end())continue;

					for(int j=0;j<node.frame.size();j++){ //配置位置

						//リストアップ実施
						std::vector<TransParam> list = Listup(node.frame,j,prob.pieces[i]);
						//「置かない」を追加
						TransParam empty;
						empty.sub_index=-1;
						list.push_back(empty);

						//全てキューに追加
						for(int k=0;k<list.size();k++){
							//k番目の変形を適用
							Node n;
							if(list[k].sub_index != -1){
								n.frame = Merge(node.frame,Transform(prob.pieces[i],list[k]));
								n.h_val = GetHeuristic(n.frame);
								n.hands = node.hands;
								n.hands.push_back(std::make_pair(list[k],i));
							}else{
								//パス
								n.h_val = node.h_val;
								n.hands = node.hands;
								n.frame = node.frame;
							}
							queue.push_back(n);
						}
					}
				}
			}
			std::cout << "経過:" << index + d << ":" << queue.size()<< std::endl;
			index++;
		}

		//評価順に昇順ソート
		std::sort(queue.begin(),queue.end(),[](const Node& lhs,const Node& rhs){
			return (lhs.h_val < rhs.h_val);
		});
		
		std::cout << "trim:" << queue.size() << std::endl;
		std::cout << "BestScore:" << queue.front().h_val << std::endl;
		//探索幅まで縮小
		if(queue.size() > WIDTH_LIMIT){
			queue.erase(std::next(queue.begin() , WIDTH_LIMIT),queue.end());
		}
		std::cout << "steped:" << queue.size() << " index:" << index << std::endl;
	}

	std::cout << "finished" << std::endl;
	if(queue.size()==0){
		while(1);
	}
	for(auto aa : queue.front().hands){
		std::cout << aa.second << std::endl;
	}
	std::cout << "next" << std::endl;
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


