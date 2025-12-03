# 42_tester
- A tester's platform used for reviews and test-driven development

レビュー、テスト駆動開発時に使うテスターのプラットフォームです

## Development progress
### version
- 1.0.0

### progress
- ft_printf, gnl のテストファイルをコンパイルするMakefileの作成
- ディレクトリの整合をとる 

### projects
- 42_tester



- ft_printf
```plain text
・テスト用のMakefileでなく、レビュイーのものを使用。
make -f /path/to/directory/Makefile
・その後、テスト用のシェルを起動して今まで通りのテストが実行できればいい
```

## memo
仕様メモ
- レビュー時に /tmp に `git clone` して使えるようにしたい
- 手動でテスト対象のパスを指定するのか？テスト対象の課題は？
- 

```plain text
# レビュー時に /tmp に git clone
　/tmp は一時フォルダと呼ばれ、「メモリ上にあり、高速（巨大ファイルは向かない）」
「削除を忘れてもシステム終了時に消える」などの仕様がある。使い捨て作業に向く
```
```plain text
# 手動でテスト対象のパスを指定するのか？テスト対象の課題は？
　git clone したあと bash tester/run.sh で実行して、レビュー対象のフォルダと
課題をそれぞれ入力するようにする（var.1,0）
```


# 提出時
以下のコマンドで余計なファイルを含まないクリーンなリポジトリを作成してください
```bash
cp -R . ../submit/<42project name>_submit
rm -rf .git
rm <extra files>
```
(.gitignoreを参照して、余計なファイルを全部消すってのもありかもしれない)

提出用の４２リポジトリと接続を行ってください
```bash
git init
git remote add origin <intraのプロジェクトページで公開されたURL>
git branch -M master
git add .
git commit -m "first submit"
git push -u origin master
```