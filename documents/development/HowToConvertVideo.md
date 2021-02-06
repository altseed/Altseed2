# Webサイトなどに貼り付ける動画の変換について

## 必要なもの

- 適当なスクリーンキャプチャソフト
  - Windows 10 の場合はゲームバーのキャプチャ機能でおｋ
- ffmpeg 
  - 一部 OS ではコーデックの扱いがややこしそうなので Windows 用ビルド済みバイナリでやるの推奨
    - https://github.com/BtbN/FFmpeg-Builds/releases

## 撮影する

- 適当ななスクリーンキャプチャソフトで撮影する
- 後でクロップできるので、ウインドウ全体など広めに撮影しても問題なし

## ffmpeg で Web 用に変換する

- Web 用なのでなるべく軽くしたい
  - 画質設定よりもフレームレート、解像度、時間で対応
    - ビットレート不足が画が汚くなるので
    - 動画のファイルサイズは 100 KiB 程度にする
- ブラウザによって再生できる動画コーデックが違うので複数種類用意する。
  - H.264
  - WebM
  - png （動画ではないがどちらも再生できなかった時のため。あとロード中はこれを表示できる）


## ffmpeg のパラメータ

> ffmpeg -i {入力ファイル名} {クロップなどの設定} {加工の設定} -an {出力ファイル名}

`-an` は音声を削除する指定

### 加工の設定

省略可能

#### クロップ

> -vf crop={出力動画の幅}:{出力動画の高さ}:{左上のX座標}:{左上のY座標} 


#### フレームレート

25 くらいでおｋ

> -r {フレームレート}

#### 時間切り出しの設定はいろいろ出来るのでリンク参照

https://nico-lab.net/cutting_ffmpeg/


### コーデックの設定

画質は整数値で指定（小さいほどキレイ）。デフォルトは23。

#### H.264 で出力

> -c:v libx264 -crf {画質} -preset veryslow -movflags +faststart

#### WebM で出力

> -c:v libvpx-vp9 -crf {画質} -preset veryslow -movflags +faststart

#### PNG で出力

連番画像が全部出てくるので出力ファイル名は `Hoge%d.png` などフォーマット指定子を入れる。
好きなフレームの画像を採用

> -c:v png 


## 要するに

> ffmpeg -i captured.mp4 -vf crop=640:480:100:200 -r 25 -c:v libx264 -crf 20 -preset veryslow -movflags +faststart -an converted.mp4

> ffmpeg -i captured.mp4 -vf crop=640:480:100:200 -r 25 -c:v libvpx-vp9 -crf 20 -preset veryslow -movflags +faststart -an converted.webm

> ffmpeg -i captured.mp4 -vf crop=640:480:100:200 -r 25 -c:v png converted_%03d.png

などする。
ビットレートやフレームレート切り出し位置・時間は微調整がんばる。