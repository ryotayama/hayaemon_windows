聞々ハヤえもん for Windows
=======================

## 免責事項
このソフトは無保証・無責任です。以下の条件に同意していただける場合にのみ、このソフトをご利用いただくことができます。
- 作者は、このソフトによって発生した損害に関し、一切の責任を負わない。
- 作者は、このソフトのサポート ( 不具合修正・バージョンアップなど ) に関する一切の義務を負わない。

## 開発環境
- Visual Studio Community 2017
- サウンド関連の実装には、高性能オーディオライブラリ「BASS」を使用しています。有用なライブラリを公開なさっている Ian Luck 氏に、深く感謝致します。

  Un4seen Developments : http://www.un4seen.com/

## 開発環境の構築
- Visual Studio Community 2017 をインストールしておいてください。
　※インストーラをビルドする為に、Microsoft Visual Studio INstaller Projectという拡張機能が必要です。
![image](https://github.com/ryotayama/hayaemon_windows/assets/32073583/07b7c37f-cb3c-4d83-bb25-e88908ece686)
- git cloneコマンドを叩くか、ZIPファイルをダウンロードし、ハヤえもんのプロジェクトフォルダを入手してください。
- プロジェクトフォルダ直下にある getlibs.bat というバッチファイルを実行してください。
　※getlibs.bat を実行する事で、外部ライブラリのLIBファイルがプロジェクトフォルダ直下に保存され、DLLファイルがReleaseフォルダに保存されます。
　※getlibs.bat 実行時に以下のようなエラーが出て終了する場合は出力されたURLにアクセスしてMicrosoft Windows SDK for Windows 7 and .NET Framework 4 をインストールしてください。
 ```
必要なSDKが見つかりませんでした
Microsoft Windows SDK for Windows 7 and .NET Framework 4 をインストールしてください
https://www.microsoft.com/en-us/download/details.aspx?id=8279
```
- Hayaemon.sln を開く事で開発を始める事ができます。

## ライセンス
[GPL v3 ライセンス](https://www.gnu.org/licenses/gpl-3.0.html)
