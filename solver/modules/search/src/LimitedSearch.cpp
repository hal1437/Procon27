
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
		std::vector<Point> dead;

		inline int step(){return this->hands.size();}//使用手数
	};

	LimitedSearch::Answer answer; //回答
	std::random_device rd;        //乱数生成器
	std::deque<Node> queue;       //探索キュー
// 	std::vector<Point> dead;      //探索省略点

	int index = 0;
	int best_val = std::numeric_limits<int>::max();
	int old_val  = std::numeric_limits<int>::max();
	Node best_node;
	//初期状態追加
	queue.push_back(Node{prob.frame,old_val,std::vector<std::pair<TransParam,int>>()});

	//ステップが最後になるまで
	do{
		old_val = best_val;
	
		std::cout << "======= " << index << " =======" << std::endl;

		//深さループ
		for(int d = 0;d < DEPTH_LIMIT && index < prob.pieces.size();d++){
			int queue_size = queue.size();//キューのサイズ
			for(int q=0;q<queue_size;q++){
				int queue_tail = queue.size();//キュー末端位置
				Node node = queue.front(); //先頭取り出し
				
				queue.pop_front();         //先頭を削除

				//フレームの頂点について
				for(int j=0;j<node.frame.size();j++){ //配置頂点
					bool alive = false;//頂点の生存フラグ

					//頂点が無視リストに追加されていれば
					if(std::find(node.dead.begin(),node.dead.end(),node.frame.getNode(j)) != node.dead.end())continue;//以降探索しない

					//全ピースについて
					for(int i = 0;i < prob.pieces.size();i++){ //ピース
						//ピースが使用済みの場合はスキップ
						if(std::find_if(node.hands.begin(),node.hands.end(),[&](std::pair<TransParam,int>& v){
							return (v.second == i);
						})!=node.hands.end())continue;

						std::vector<TransParam> list;

						//配置位置が無視リストに追加されていなければ
						//リストアップ実施
						list = Listup(node.frame,j,prob.pieces[i]);

						//頂点にが1つ配置可能ならばでもしていれば、次も探索を行う
						if(list.size() > 0)alive=true;


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
						//頂点に何も追加されていない
						if(alive==false){
							//以降その頂点は探索を行わない
							node.dead.push_back(node.frame.getNode(j));

							//キューに追加したものも変更する
							if(queue.size() > queue_tail){
								for(int qq = queue.size();qq<queue_tail;qq++){
									queue[qq].dead.push_back(node.frame.getNode(j));
								}
							}
							break;
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
		
		best_val = queue.front().h_val;
		std::cout << "trim:"      << queue.size() << std::endl;
		std::cout << "BestScore:" << best_val     << std::endl;
		//探索幅まで縮小
		if(queue.size() > WIDTH_LIMIT){
			queue.erase(std::next(queue.begin() , WIDTH_LIMIT),queue.end());
		}
		//最高記録を保存
		if(queue.size() > 0){
			best_node = queue[0];
		}
		std::cout << "steped:" << queue.size() << " index:" << index << std::endl;

	}while(old_val!=best_val);

	std::cout << "finish" << std::endl;

	//回答に変換
	for(int i=0;i<prob.pieces.size();i++){
		auto it = std::find_if(best_node.hands.begin(),best_node.hands.end(),[&](std::pair<TransParam,int>& v){
			return (v.second == i);
		});
		if(it != best_node.hands.end()){
			answer.push_back(it->first);
		}else{
			answer.push_back(TransParam());
		}
	}
	
	return answer;
}



