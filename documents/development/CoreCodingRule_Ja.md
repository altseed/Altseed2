# Core の記述について

* 基本すべてのクラスは BaseObject を継承する
  * 生ポインタで管理せずshared_ptr を用いる。
  * 生成は std::make_shared ではなく AsdmakeShared を用いる
* メソッドのオーバーロードは使わない
* 自動整形・ビルド通してからコミットしましょう

TODO：書くこと。命名規則とかコメントとか