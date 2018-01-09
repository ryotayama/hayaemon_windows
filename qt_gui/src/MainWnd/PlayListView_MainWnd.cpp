//----------------------------------------------------------------------------
// PlayListView_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PlayListView_MainWnd.h"
#include <QFileInfo>
#include <QMimeData>
#include <QTableWidgetItem>
#include <QUrl>
#include "MainWnd.h"
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPlayListView_MainWnd::CPlayListView_MainWnd(CMainWnd & mainWnd,
																						 QWidget * parent /* = nullptr */)
	: QTableWidget(parent), m_rMainWnd(mainWnd)
{
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddFile(const QString & filePath,
																		int nPos /* = -1 */)
{
	if(!QUrl::fromUserInput(filePath).isLocalFile()) {
		// TODO add URL
		return;
	}

	QFileInfo file_info(filePath);

	if(file_info.isDir()) {
		// TODO add directory
		return;
	}

	QString ext = file_info.suffix();
	auto cs = Qt::CaseInsensitive;

	// 拡張子によっては、プレイリストとして読み込み
	int listType = 0;
	if(ext.compare("m3u", cs) == 0) listType = 1;
	else if (ext.compare("m3u8", cs) == 0) listType = 2;

	if(listType) {
		// TODO read playlist
		return;
	}

	// 読み込めない拡張子の場合、何もしない
	if( ext.compare("wav", cs) != 0 && ext.compare("cda", cs) != 0 &&
		ext.compare("mp3", cs) != 0 && ext.compare("mp2", cs) != 0 &&
		ext.compare("mp1", cs) != 0 && ext.compare("ogg", cs) != 0 &&
		ext.compare("wma", cs) != 0 && ext.compare("aiff", cs) != 0 &&
		ext.compare("aif", cs) != 0 && ext.compare("ape", cs) != 0 &&
		ext.compare("flac", cs) != 0 && ext.compare("m4a", cs) != 0 &&
		ext.compare("m4b", cs) != 0 &&
		ext.compare("mp4", cs) != 0 && ext.compare("aac", cs) != 0 &&
		ext.compare("avi", cs) != 0 && ext.compare("wmv", cs) != 0 &&
		ext.compare("mkv", cs) != 0 && ext.compare("flv", cs) != 0 &&
		ext.compare("nsf", cs) != 0)
		return;

	// No.
	int n = nPos < 0 ? GetItemCount() : nPos;
	InsertItem(n);
	SetItem(n, 1, QString("%1").arg(n + 1));

	SetItem(n, 0, "", -1);

	// タイトル
	SetItem(n, 2, QFileInfo(filePath).baseName());

	// ファイルパス
	SetItem(n, 7, filePath);

	orders.push_back(-1);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPlayListView_MainWnd::Create()
{
	setAcceptDrops(true);

	setColumnCount(8);
	InsertColumn(0, "", LVCFMT_LEFT, 17, 0);
	InsertColumn(1, tr("No."), LVCFMT_RIGHT, 30, 1);
	InsertColumn(2, tr("Title"), LVCFMT_LEFT, 200, 2);
	InsertColumn(3, tr("Artist"), LVCFMT_LEFT, 150, 3);
	InsertColumn(4, tr("Year"), LVCFMT_LEFT, 40, 4);
	InsertColumn(5, tr("Length"), LVCFMT_RIGHT, 50, 5);
	InsertColumn(6, tr("File Name"), LVCFMT_LEFT, 150, 6);
	InsertColumn(7, tr("Path"), LVCFMT_LEFT, 200, 7);

	m_icons[0].addFile(":/icon/resource/play.ico");
	m_icons[1].addFile(":/icon/resource/pause.ico");

	return TRUE;
}
//----------------------------------------------------------------------------
// 全て削除
//----------------------------------------------------------------------------
BOOL CPlayListView_MainWnd::DeleteAllItems()
{
	orders.clear();
	clearContents();
	setRowCount(0);
	return TRUE;
}
//----------------------------------------------------------------------------
// 再生順の最大値を得る
//----------------------------------------------------------------------------
int CPlayListView_MainWnd::GetMaxPlayOrder() const
{
	int nMax = -1;
	for(int i = 0; i < (int)orders.size(); i++)
		if(orders[i] > nMax) nMax = orders[i];
	return nMax;
}
//----------------------------------------------------------------------------
// 再生中の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlaying(int iItem)
{
	for(int i = 0; i < GetItemCount(); i++)
		SetItem(i, 0, _T(""), -1);
	if(this == &m_rMainWnd.GetCurPlayList() && iItem >= 0)
		SetItem(iItem, 0, _T(""), 0);
}
//----------------------------------------------------------------------------
// 一時停止中の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPausing(int iItem)
{
	for(int i = 0; i < GetItemCount(); i++)
		SetItem(i, 0, _T(""), -1);
	if(this == &m_rMainWnd.GetCurPlayList() && iItem >= 0)
		SetItem(iItem, 0, _T(""), 1);
}
//----------------------------------------------------------------------------
// 再生順の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlayOrder(int iItem)
{
	if(iItem < 0) return;
	orders[iItem] = GetMaxPlayOrder() + 1;
}
//----------------------------------------------------------------------------
// 再生順の設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SetPlayOrder(int iItem, int nOrder)
{
	orders[iItem] = nOrder;
}
//----------------------------------------------------------------------------
// 再生順をクリア
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ClearPlayOrder()
{
	for(int i = 0; i < (int)orders.size(); i++) orders[i] = -1;
}
//----------------------------------------------------------------------------
// 「No.」のリセット
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ResetNumber()
{
	for(int i = 0; i < GetItemCount(); i++) {
		SetItem(i, 1, QString("%1").arg(i + 1));
	}
}
//----------------------------------------------------------------------------
// 指定された項目までスクロール
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::ScrollToItem(int nItem)
{
	EnsureVisible(nItem, TRUE);
}
//----------------------------------------------------------------------------
// ファイルがドロップされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnDropFiles(const QList<QUrl> & urls)
{
	m_rMainWnd.AddDropFiles(urls, FALSE);
}
//----------------------------------------------------------------------------
// Qtのラッパー
//----------------------------------------------------------------------------
int CPlayListView_MainWnd::InsertColumn(
		int nCol, const QString & lpszColumnHeading,
		int nFormat /*= LVCFMT_LEFT*/, int nWidth /*= -1*/,
		int nSubItem /*= -1*/)
{
	auto item = new QTableWidgetItem(lpszColumnHeading);
	item->setTextAlignment(
			nFormat == LVCFMT_RIGHT ? Qt::AlignRight : Qt::AlignLeft);
	this->setHorizontalHeaderItem(nCol, item);
	this->setColumnWidth(nCol, nWidth);
	return nCol;
}
void CPlayListView_MainWnd::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}
void CPlayListView_MainWnd::dropEvent(QDropEvent * e)
{
	OnDropFiles(e->mimeData()->urls());
}
//----------------------------------------------------------------------------
