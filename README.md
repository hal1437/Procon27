
##依存

* C++11 
* openCV3 
* cmake  

## 導入
クローン、作業ディレクトリへ移動
```
git clone https://github.com/hal1437/Procon27
cd Procon27
```

ビルドディレクトリを作成、移動
```
mkdir build
cd build
```

ビルド
```
cmake ../solver
make
```
プロジェクトの管理はcmakeで構築されているため、ソースコードの追加はCMakeLists.txtを編集すること。


##注意点
* ソースコードの配置、ディレクトリ構造、CMakeLists.txtの記述は既存のもの、または[procon2014_ut](https://github.com/natrium11321/procon2014_ut)
に準拠する。
* コーディング規約について詳しくは決定しないが、関数はローワーキャメルケース変数はスネークケースを推奨する。ただし関数のconst修飾のみは厳密に行うこと。
* 現実の1mmをプログラム上の実数値1として扱う。
* 枠の左下を原点とし、左方向にX軸の正、上方向にY軸の正と置く。


---

その他不明な点があれば@hal1437(halstroemeria@gmail.com)に連絡を入れてほしい
