# Core の記述について

## **自動整形・ビルド通してからコミットしましょう**
  * Clang-Format による自動整形が効くプロジェクトファイルを生成できるのでそちらを使用し、必ずビルドして整形してからコミットするようにしましょう。
    * 差分に無意味な変更が混ざってしまうので後で見づらくなります。

## クラス
* 基本すべてのクラスは BaseObject を継承する。
  * 生ポインタで管理せずshared_ptr を用いる。
  * 生成は std::make_shared ではなく AsdmakeShared を用いる。
* ~~メソッドのオーバーロードは使わない~~
  * ヘンな suffix のついた似たようなメソッドが生えるくらいならオーバーロードしたほうがシンプル
  * CBG は オーバーロード対応済み
  * 今後もしオーバーロード非対応な言語の Engine を作る場合は Binding Generator 側でヘンな suffix を付ける
    * そもそもCore側にある実装をすべてEngineを通してユーザに見せる必要はない


## 命名規則

| 種類 | 規則 |
| ---- | ---- |
|クラス<br>public メソッド |UpperCamelCase|
|public なプロパティ|UpperCamelCase<br>Get〜/Set〜（bool 型ならさらに Is〜など）|
|private なフィールド|lowerCamelCase_ （末尾にアンダバー）|
|ローカル変数|lowerCamelCase|
