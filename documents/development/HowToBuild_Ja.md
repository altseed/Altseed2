# ビルド手順

## 必須

### Windows

- VisualStudio(2019以降)
- cmake(3.12以上)
- git

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

- 32bit

```
scripts/GenerateProjects.bat
```

- 64bit

```
scripts/GenerateProjects_x64.bat
```



