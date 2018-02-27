# ofxFavのインストール方法

インストール方法は下記のリンク先にも載っています。  
<http://fabble.cc/m0rya/ofxfavxxxx>

ofxFavを使うには"xerces"というxmlパーサをインストールする必要があります  
"xerces"のインストールにはhomebrewを使うのをおすすめします





## homebrewのインストール

下記のものをターミナルで実行するとhomebrewのインストールが行えます  
` $ ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"`

* * *

## homebrewを使ってxercesのインストール

下記のものをhomebrewの時と同様にターミナルで実行するとxercesのインストールが行えます  
` $ brew install xerces-c`

* * *

## ofxFavを使う上で必要なofxAddon

**ofxGui**と**ofxAssimpModelLoader**の２つのアドオンが必要なので、  
projectGeneratorでプロジェクトを作成するときにofxFavに加えて追加してください

* * *

## xercesを使うためにプロジェクトの設定に変更を加える必要があります
プロジェクト設定のTARGETS->BuildSettingsのページを開き

BuildSettings->Linking->Other Linker Flagsに  
**"-lxerces-c"**を追加します

BuildSettings->Search Paths->Header Search Pathsに  
xercesがインストールされている  
**"/usr/local/Cellar/xerces-c/3.2.0/include"**を追加します

現時点(2018/2/25)ではxerces-cのバージョンが3.2.0なのですが、インストールした時にバージョンが代わっている可能性があるので、適宜パスの**3.2.0**の数字をその時のバージョンに合わせてください

BuildSettings->Search Paths->Library Search Pathsに  
**"/usr/local/Cellar/xerces-c/3.2.0/lib"**を追加します  
この**3.2.0**というバージョンの数字なども上記のように環境に合わせて追加してください


