聞々ハヤえもん for macOS
=======================

## 免責事項
このソフトは無保証・無責任です。以下の条件に同意していただける場合にのみ、このソフトをご利用いただくことができます。
- 作者は、このソフトによって発生した損害に関し、一切の責任を負わない。
- 作者は、このソフトのサポート ( 不具合修正・バージョンアップなど ) に関する一切の義務を負わない。

## ビルドと実行

### 開発環境
- Apple LLVM version 6.0以上
- [Qt](https://www.qt.io/download) 5.6.3以上
- [CMake](https://cmake.org/download/) 3.0.2以上
- サウンド関連の実装には、高性能オーディオライブラリ「BASS」を使用しています。有用なライブラリを公開なさっている Ian Luck 氏に、深く感謝致します。

  Un4seen Developments : http://www.un4seen.com/

### ビルド
聞々ハヤえもんをビルドするディレクトリでターミナルから、以下のコマンドを実行します。ビルドするディレクトリは任意。
```
cmake (クローンした聞々ハヤえもんのリポジトリ)/qt_gui
make
```
Qtが見つからない場合は
```
cmake (クローンした聞々ハヤえもんのリポジトリ)/qt_gui -DCMAKE_PREFIX_PATH=/opt/Qt5.9/5.9.5/clang
```
のようにCMakeのコマンドラインオプションでQtのパスを指定します。

### 実行
```
./Hayaemon
```

## ライセンス
[MITライセンス](https://opensource.org/licenses/mit-license.php)