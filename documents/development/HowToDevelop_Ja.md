
# 開発方法について

## ビルド方法とツールについて

[HowToBuild](HowToBuild_Ja.md)

## 開発手順

### C++のソースコードの追加

[CoreCodingRule](CoreCodingRule_Ja.md)

新しいファイルを追加した場合は `core/src/CMakeFile.txt` もしくは `core/test/CMakeFile.txt` にファイル名を追記する。

### バインディングの設定の記述

* `scripts\bindings` 以下の `py` ファイルに記述します。 

1. `input.py` や `io.py` など機能ごとのファイル（場合によってはファイルを追加）に各クラスの情報（どのようなプロパティがあるか、基底クラスはなにか、静的クラスかなど）やメソッドの情報（戻り値は何型か、引数は何型かなど）を記述します。

2.  `define.py` 内に上で追加したクラスや列挙体などの append を追加します。

詳細は [CBG の HowToUse](https://github.com/altseed/CppBindingGenerator/blob/master/docs/HowToUse.md)

3. `scripts/generate_wrapper.py`を実行し、再度コアをビルドします。この時エラーが出ず正常にビルドできることを確認します。

#### 自動生成ファイルについて

これらの設定はC++のファイルとJsonファイルから自動生成することもできます。

clangのpythonバインディングをインストールします。

```
pip install clang
```

Windowsの場合、Clangをインストールします。Macの場合、XCodeをインストールします。

[clang(LLVM)](https://releases.llvm.org/download.html)

そして、下記のコマンドで生成します。

Windowsの場合、

```
cd scripts
python generate_cbg_definition.py --clang (libclang.dllが存在するディレクトリ)
```

ただしLLVMをデフォルトのディレクトリにインストールした場合は引数は必要ありません。

Macの場合、

```
cd scripts
python generate_cbg_definition.py --xcode (xcodeが存在するディレクトリ)
```

ただしxcodeをApplication/にインストールした場合は引数は必要ありません。

新しくC++のファイルの増やした場合は、``` generate_cbg_definition.py ``` を編集する必要があります。

### ドキュメント

TODO: Core 部分に関する開発者向けの仕様解説ドキュメントを用意

### サンプル


## PRについて

コメントが1行の場合、先頭は大文字の命令形の英語が好ましいです。
理由は、Linusがそう推奨したからです。

~~慣れている人は、git の rebase を使用しましょう。~~
無意味なコミットが大量に生成されるのを抑制する場合を除いて、 merge するようにします。どのような変更をしたか、どのように変更を打ち消したかをすべて記録し、それぞれの状態に戻せるようにしておくことがバージョン管理です。とくに誤って作成してしまった変更をもみ消す（パスワードなど秘匿すべき情報を混入させてしまったなどの場合は除く）目的での merge は厳禁。

## コメントについて

* ~~英語が望ましいです。苦手な人はGoogle翻訳を使用しても問題ありません。~~
コメントは日本語でおｋ。（今後必要そうなら Google 翻訳なりを使って英語コメントを追加挿入するようなスクリプトを使う）。 ただしちゃんと UTF-8 で保存すること。

* もしくは、コメントが必要がないほど綺麗なコードを書きましょう。

