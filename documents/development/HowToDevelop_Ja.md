
# 開発方法について

## ビルド方法とツールについて

[HowToBuild](HowToBuild_Ja.md)


## タスクに取り掛かる
[`aTask`タグのついたIssue](https://github.com/altseed/Altseed2/labels/aTask)の中から選ぶのが、最も手っ取り早い方法でしょう。

Altseed2の開発はチケット駆動で行っています。タスクの分類は大きなものから

- `aDepartment`: 次のリリースに向けて解決すべき大きなタスクや問題
- `aFeature`: Department の機能的分割
- `aTask`: Feature を進捗(Core, Binding, Engine, Document, Test, Sample)別に分割したもの
- `aTicket`: 30分程度で終わる規模まで分割されたTask

の4つです。

## 開発手順

### C++のソースコードの追加

TODO：書く

[CoreCodingRule](CoreCodingRule_Ja.md)

### バインディングの設定の記述

* `scripts\bindings` 以下の `py` ファイルに記述します。 

1. `input.py` や `io.py` など機能ごとのファイル（場合によってはファイルを追加）に各クラスの情報（どのようなプロパティがあるか、基底クラスはなにか、静的クラスかなど）やメソッドの情報（戻り値は何型か、引数は何型かなど）を記述します。

2.  `define.py` 内に上で追加したクラスや列挙体などの append を追加します。

詳細は [CBG の HowToUse](https://github.com/altseed/CppBindingGenerator/blob/master/docs/HowToUse.md)

3. `scripts/generate_wrapper.py`を実行し、再度コアをビルドします。この時エラーが出ず正常にビルドできることを確認します。

### ドキュメント

Core 部分に関する開発者向けの仕様解説ドキュメントを用意

### サンプル


## PRについて

コメントが1行の場合、先頭は大文字の命令形の英語が好ましいです。
理由は、Linusがそう推奨したからです。

慣れている人は、gitのrebaseを使用しましょう。

## コメントについて

* ~~英語が望ましいです。苦手な人はGoogle翻訳を使用しても問題ありません。~~
コメントは日本語でおｋ。（今後必要そうなら Google 翻訳なりを使って英語コメントを追加挿入するようなスクリプトを使う）

* もしくは、コメントが必要がないほど綺麗なコードを書きましょう。

