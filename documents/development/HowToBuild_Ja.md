# ビルド手順

## 必須

### 共通

- cmake(3.15以上)
- git
- python3.x

### Windows

- VisualStudio(2019以降)

### Linux

- gcc

#### Ubuntu

```
libudev-dev
libssl-dev # to save and load a package with a password
```

## サブモジュール取得

スクリプト `scripts/Pull.bat` を実行します。

もしくは下記のコマンドを実行します。

```
git pull
git submodule update --init

cd thirdparty/LLGI
git submodule update --init
```

## プロジェクト生成

スクリプトを実行します。
下記のスクリプトでは Clang-Format が有効になったプロジェクトを生成します。
ビルド時にコードの自動整形が実行されるため、通常Altseed2 の開発を行う際はこちらを使用してください。

- Windows の場合： `scripts/GenerateProjects_ClangFormat.bat`
- macOS の場合： `scripts/GenerateProjects_ClangFormat_Mac.sh`
- Linux の場合： `scripts/GenerateProjects_ClangFormat_Linux.sh`

開発を行わない、もしくは何らかの事情によりClang-Format による自動成型が有効でないプロジェクトを生成するには下記のスクリプトを実行します。

- Windows の場合： `scripts/GenerateProjects.bat`
- macOS の場合： `scripts/GenerateProjects_Mac.sh`
- Linux の場合： `scripts/GenerateProjects_Linux.sh`

## Wrapper生成

### Dockerを使用する(推奨)

`docker` と　`docker-compose`をインストールしてください．

以下コマンドを実行します．
```
docker-compose build
docker-compose up
```

### Dockerを使用しない

まず、ヘッダファイルからCBG定義を出力するために 下記のコマンドを実行します。

```
python scripts/generate_cbg_definition.py --clang "C:\Program Files\LLVM\bin"
```

また、実行するときには LLVMとpythonパッケージ `clang`で、LLVMのbinディレクトリを指定する必要があります。

次にスクリプト `python scripts/generate_wrapper.py` を実行します。

## ビルド

### Windows

`build\Altseed_Core.sln` （もしくは `build_clang_format\Altseed_Core.sln`） を開き、ソリューションをビルドします。プロジェクト `Altseed_Core_Test` を実行し、テストが走ったら成功です。
