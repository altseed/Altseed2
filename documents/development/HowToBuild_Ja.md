# ビルド手順

## 必須

### 共通

- cmake(3.12以上)
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

```
git submodule update --init
```

もしくは、

`TortoiseGit` -> `Submodule Update` -> `OK`

## プロジェクト生成

### Windows

下記のスクリプトを実行します。

```
scripts/GenerateProjects.bat
```



