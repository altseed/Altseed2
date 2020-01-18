
# ツール

## clang-format

C++のソースコード自動整形ツールです。
指定したフォーマットに沿ってC++のソースコードを整形してくれます。
.clang-formatに設定ファイルを記述します。
ターミナルから使用しますが、VisualStudio では `Ctrl+K,　Ctrl+D` で自動的に整形してくれます。

## cmake

C++/C# のプロジェクトを生成するツールです。
CMakeLists.txt の設定をもとにVisualStudio、XCode のプロジェクトや makefile 等を生成します。
バージョンアップするごとに近代化が進んでいるので、可能な限り最新版の機能を使いましょう。

ディレクトリ名に記号等が含まれている失敗することがあります。わかりやすいディレクトリに配置しましょう。

VisualStudio、VSCode等には専用のサポートツールが存在します。それらを使用すると便利になります。

# ライブラリ(開発者向け)

## GoogleTest

C++用の単体テストライブラリです。

```
--gtest_filter=Foo.*
```

といった引数により、起動するテストを選択できますが、VisualStudio、VSCode等には専用のサポートツールが存在します。

VisualStudio では `テストエクスプローラー` を使用することで特定のテストのみを実行したり、各テストの合否やエラー箇所を確認したりすることができます。