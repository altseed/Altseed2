
# ビルド方法とツールについて

[HowToBuild](HowToBuild_Ja.md)

[LibraryAndTools](LibraryAndTools_ja.md)

# タスクに取り掛かる
[`aTask`タグのついたIssue](https://github.com/altseed/Altseed2/labels/aTask)の中から選ぶのが、最も手っ取り早い方法でしょう。

Altseed2の開発はチケット駆動で行っています。タスクの分類は大きなものから

- `aDepartment`: 次のリリースに向けて解決すべき大きなタスクや問題
- `aFeature`: Department の機能的分割
- `aTask`: Feature を進捗(Core, Binding, Engine, Document, Test, Sample)別に分割したもの
- `aTicket`: 30分程度で終わる規模まで分割されたTask

の4つです。

# 開発手順

## C++のソースコードの追加

## バインディングの設定の記述

## ドキュメント

## サンプル

# PRについて

コメントが1行の場合、先頭は大文字の命令形の英語が好ましいです。
理由は、Linusがそう推奨したからです。

慣れている人は、gitのrebaseを使用しましょう。

# コメントについて

英語が望ましいです。苦手な人はGoogle翻訳を使用しても問題ありません。
もしくは、コメントが必要がないほど綺麗なコードを書きましょう。

