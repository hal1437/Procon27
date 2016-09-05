
#pragma once
#include<search/BasicSearch.h>

//簡易回答再生装置
class InstantViewer{
private:
	BasicSearch* solver;
	Problem problem;
	std::vector<TransParam> ans;

public:

	void SetSolver(BasicSearch* solver);
	void SetProblem(const Problem& problem);

	//問題解決
	bool Solve();
	//再生開始
	void View();

	InstantViewer();
	
};
