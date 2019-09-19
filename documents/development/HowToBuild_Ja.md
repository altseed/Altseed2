
## 必須

### Windows

- VisualStudio(2019以降)
- cmake
- git

### Linux

- gcc

#### Ubuntu

```
libudev-dev
```

## サブモジュール取得

```
git submodule update --init
```

もしくは、

```
TortoiseGit -> Submodule Update -> OK
```

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



