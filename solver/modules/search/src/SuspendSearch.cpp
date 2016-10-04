
#include <search/SuspendSearch.h>


double SuspendSearch::GetHeuristic(const Polygon& poly)const{
	double sum = 0;
	for(int i=0;i<heuristic.size();i++){
		sum += (*heuristic[i])(poly);
	}
	return sum;
}


//評価関数追加
void SuspendSearch::AddHeuristic(Heuristic<Polygon>* h){
	this->heuristic.push_back(h);
}

bool CheckHit(Polygon frame,Polygon trans){
	for(int j=0;j<frame.size();j++){
		for(int k=0;k<trans.size();k++){
			//点が近すぎる場合は免除
			if(BasicSearch::Length(frame.getNode(j)                 ,trans.getNode(k)                 ) > BasicSearch::SAME_POINT_EPS &&
			   BasicSearch::Length(frame.getNode((j+1)%frame.size()),trans.getNode(k)                 ) > BasicSearch::SAME_POINT_EPS && 
			   BasicSearch::Length(frame.getNode(j)                 ,trans.getNode((k+1)%trans.size())) > BasicSearch::SAME_POINT_EPS &&
			   BasicSearch::Length(frame.getNode((j+1)%frame.size()),trans.getNode((k+1)%trans.size())) > BasicSearch::SAME_POINT_EPS ){
				//交差していれば
				if(isCrossed(frame.getNode(j),frame.getNode((j+1)%frame.size()),
				             trans.getNode(k),trans.getNode((k+1)%trans.size()))){
					return true;
				}
			}
		}
	}
	return false;
}

//探索
SuspendSearch::Answer SuspendSearch::Search(const Problem& prob){


	//探索ノード
	struct Node{
		Polygon frame; //状態
		int h_val;     //評価値
		std::vector<std::pair<TransParam,int>> hands; //履歴
		int suspend;   //サスペンドレベル

		inline int step(){return this->hands.size();}//使用手数
	};

	SuspendSearch::Answer answer; //回答
	std::random_device rd;        //乱数生成器
	
	Polygon          old_frame;   //前回のフレーム
	std::deque<Node> queue;       //探索キュー
	std::vector<int> retake_list; //Listup実施頂点番号

	int index = 0;
	//初期状態追加
	queue.push_back(Node{prob.frame,std::numeric_limits<int>::max(),std::vector<std::pair<TransParam,int>>()});

	//最終ステップまで
	while(index < prob.pieces.size()){
	
		std::cout << "======= " << index << " =======" << std::endl;

		int queue_size = queue.size();//キューのサイズ

		for(int w=0;w<std::min(queue_size,WIDTH_LIMIT);w++){ // キュー展開

			Node node = queue.front(); //先頭取り出し
			queue.pop_front();         //先頭を削除

			for(int j=0;j<node.frame.size();j++){ //フレーム配置位置

				//全ピースの配置位置を計算
				for(int i = 0;i < prob.pieces.size();i++){ //ピース

					//使用済みの場合はスキップ
					if(std::find_if(node.hands.begin(),node.hands.end(),[&](std::pair<TransParam,int>& v){
						return (v.second == i);
					})!=node.hands.end())continue;

					//リストアップ実施
					std::vector<TransParam> list = Listup(node.frame,j,prob.pieces[i]);
					//「置かない」を追加
					TransParam empty;
					empty.sub_index=-1;
					list.push_back(empty);

					//全てキューに追加
					for(int k=0;k<list.size();k++){
						Node n;
						if(list[k].sub_index != -1){
							//k番目の変形を適用
							n.frame = Merge(node.frame,Transform(prob.pieces[i],list[k]));
							n.h_val = GetHeuristic(n.frame);
							n.hands = node.hands;
							n.hands.push_back(std::make_pair(list[k],i));
						}else{
							//パスはパラメータ継承
							n.h_val = node.h_val;
							n.hands = node.hands;
							n.frame = node.frame;
						}
						queue.push_back(n);
					}
				}
			}
		}

		//評価順に昇順ソート
		std::sort(queue.begin(),queue.end(),[](const Node& lhs,const Node& rhs){
			return (lhs.h_val < rhs.h_val);
		});
		
		//探索幅まで縮小
		if(queue.size() > RECORD_LIMIT){
			queue.erase(std::next(queue.begin() , RECORD_LIMIT),queue.end());
		}
		std::cout << "BestScore:" << queue.front().h_val << std::endl;
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




