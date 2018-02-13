//----------------------------------------------------------------------------
// PlayListView_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PlayListView_MainWnd.h"
#include <algorithm>
#include <QDir>
#include <QFileInfo>
#include <QMimeData>
#include <QTableWidgetItem>
#include <QUrl>
#include "M3UFile.h"
#include "MainWnd.h"
#include "RMenu_ListView.h"
#include "Utility.h"

#ifdef max
# undef max
#endif
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CPlayListView_MainWnd::CPlayListView_MainWnd(CMainWnd & mainWnd,
																						 QWidget * parent /* = nullptr */)
	: QTableWidget(parent), m_rMainWnd(mainWnd)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QWidget::customContextMenuRequested,
					this, &CPlayListView_MainWnd::OnContextMenu);
	connect(this, &QTableWidget::itemDoubleClicked,
					this, &CPlayListView_MainWnd::OnLButtonDoubleClick);
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddDirectory(const QString & lpszDirectoryPath)
{
	QDir dir(lpszDirectoryPath);
	for (auto &info : dir.entryInfoList()) {
		QString fileName = info.fileName();
		
		if(fileName == "." || fileName == "..") {
			continue;
		}

		QString path = info.filePath();

		if(info.isDir()) {
			AddDirectory(path);
			continue;
		}

		AddFile(path);
	}
}
//----------------------------------------------------------------------------
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddFile(const QString & filePath,
																		int nPos /* = -1 */)
{
	if(!QUrl::fromUserInput(filePath).isLocalFile()) {
		AddURL(filePath);
		return;
	}

	QFileInfo file_info(filePath);

	if(file_info.isDir()) {
		AddDirectory(filePath);
		return;
	}

	QString ext = file_info.suffix();
	auto cs = Qt::CaseInsensitive;

	// 拡張子によっては、プレイリストとして読み込み
	int listType = 0;
	if(ext.compare("m3u", cs) == 0) listType = 1;
	else if (ext.compare("m3u8", cs) == 0) listType = 2;

	if(listType) {
		CM3UFile file;
		file.Init();
		file.Read(ToTstring(filePath).c_str(), listType == 2);
		for(int j = 0; j < file.GetLinesCount(); j++)
			AddFile(ToQString(file.GetFilePath(j)));
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
// ファイルの追加
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::AddURL(const QString & lpszFilePath, int nPos)
{
	QFileInfo file_info(lpszFilePath);
	QString ext = file_info.suffix();
	auto cs = Qt::CaseInsensitive;

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
		ext.compare("mkv", cs) != 0 && ext.compare("flv", cs) != 0)
		return;

	// No.
	int n = nPos < 0 ? GetItemCount() : nPos;
	InsertItem(n);
	SetItem(n, 1, QString("%1").arg(n + 1));

	SetItem(n, 0, _T(""), -1);

	// タイトル
	SetItem(n, 2, file_info.baseName());

	// ファイルパス
	SetItem(n, 7, lpszFilePath);

	orders.push_back(-1);
}
//----------------------------------------------------------------------------
// 選択中のファイルをコピー
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::CopySelectedItem(int nDst)
{
	m_rMainWnd.GetTab().SetCurrentFocus(nDst);
	int nItem = -1;
  for(int nItem : GetSelectedRows()) {
		QString chPath;
		GetItemText(nItem, 7, &chPath);
		m_rMainWnd.AddFile(chPath);
	}
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CPlayListView_MainWnd::Create()
{
	setAcceptDrops(true);
	setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);

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
// 新しい再生リストの作成
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::CreateNewList()
{
	auto rows = GetSelectedRows();
	m_rMainWnd.CreateNewList();
	for(int row : rows) {
		QString chPath;
		GetItemText(row, 7, &chPath);
		m_rMainWnd.AddFile(chPath);
	}
}
//----------------------------------------------------------------------------
// 選択アイテムを削除
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::DeleteSelectedItems()
{
	BOOL bPlayNext = FALSE;
	BOOL bStop = FALSE;
	BOOL bCurTab = &m_rMainWnd.GetCurPlayList() == this;
	for (int nItem : GetSelectedRows()) {
		FixPlayOrder(nItem);
		DeleteItem(nItem);
		if(bCurTab) {
			int nCurItem = m_rMainWnd.GetSound().GetCurFileNum();
			if(nItem < nCurItem - 1)
				// 再生中のアイテムより前のアイテムを削除する場合
				m_rMainWnd.GetSound().SetCurFileNum(nCurItem - 1);
			else if(nItem == nCurItem - 1) {
				// 再生中のアイテムを削除する場合
				if(GetItemCount() > 0) {
					bStop = FALSE;
					bPlayNext = TRUE;
					m_rMainWnd.GetSound().SetCurFileNum(nItem);
				}
				else {
					bPlayNext = FALSE;
					bStop = TRUE;
				}
			}
		}
	}
	if(GetItemCount() <= 0) {
		bPlayNext = FALSE;
		bStop = TRUE;
	}
	ResetNumber();
	if(bCurTab) {
		if(bPlayNext) m_rMainWnd.PlayNext(FALSE, TRUE);
		else if(bStop) {
			m_rMainWnd.GetSound().StreamFree();
			m_rMainWnd.Stop();
		}
	}
}
//----------------------------------------------------------------------------
// アイテムを削除
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::Delete(int nItem)
{
	BOOL bPlayNext = FALSE;
	BOOL bStop = FALSE;
	BOOL bCurTab = &m_rMainWnd.GetCurPlayList() == this;
	FixPlayOrder(nItem);
	DeleteItem(nItem);
	if(bCurTab) {
		int nCurItem = m_rMainWnd.GetSound().GetCurFileNum();
		if(nItem < nCurItem - 1) {
			// 再生中のアイテムより前のアイテムを削除する場合
			m_rMainWnd.GetSound().SetCurFileNum(nCurItem - 1);
		}
		else if(nItem == nCurItem - 1) {
			// 再生中のアイテムを削除する場合
			if(GetItemCount() > 0) {
				bStop = FALSE;
				bPlayNext = TRUE;
				m_rMainWnd.GetSound().SetCurFileNum(nItem);
			}
			else {
				bPlayNext = FALSE;
				bStop = TRUE;
			}
		}
	}
	if(GetItemCount() <= 0) {
		bPlayNext = FALSE;
		bStop = TRUE;
	}
	ResetNumber();
	if(bCurTab) {
		if(bPlayNext) m_rMainWnd.PlayNext(FALSE, TRUE);
		else if(bStop) {
			m_rMainWnd.GetSound().StreamFree();
			m_rMainWnd.Stop();
		}
	}
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
// 選択中のアイテムを再生
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::PlaySelectedItem()
{
	auto items = this->selectedItems();
	if(!items.isEmpty()) {
		m_rMainWnd.ChangeCurPlayTab();
		m_rMainWnd.Play(items.front()->row());
	}
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
// 与えられた項目より大きな再生順を持つ項目の再生順をひとつ下げる
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::FixPlayOrder(int iItem)
{
	int nCur = orders[iItem];
	for(int i = 0; i < (int)orders.size(); i++) {
		int n = orders[i];
		if(n > nCur) orders[i] = n - 1;
	}
	orders[iItem] = -1;
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
// コンテキストメニュー
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnContextMenu(const QPoint & pos)
{
	bool hit = false;
	for(int i = 0; i < rowCount(); i++) {
		QRect rect = visualItemRect(item(i, 0));
		for(int j = 1; j < columnCount(); j++) {
			if(item(i, j) != nullptr) {
				QRect rect2 = visualItemRect(item(i, j));
				rect.setRight(std::max(rect.right(), rect2.right()));
			}
		}
		hit = rect.contains(pos);
		if(hit) {
			break;
		}
	}
	CRMenu_ListView menu(*this, hit);
	menu.exec(this->mapToGlobal(pos));
}
//----------------------------------------------------------------------------
// ファイルがドロップされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnDropFiles(const QList<QUrl> & urls)
{
	m_rMainWnd.AddDropFiles(urls, FALSE);
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnLButtonDoubleClick(QTableWidgetItem * item)
{
	int n = item->row();
	if(n >= 0) {
		m_rMainWnd.ChangeCurPlayTab();
		m_rMainWnd.Play(n);
	}
}
//----------------------------------------------------------------------------
// すべての項目を選択
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SelectAll()
{
	if(GetItemCount() == 0) return;

	for(int i = 0; i < GetItemCount(); i++)
		SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	setFocus();
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
// 選択されたアイテムを取得する。ただし、列の重複はないリストを返す。
//----------------------------------------------------------------------------
std::vector<int> CPlayListView_MainWnd::GetSelectedRows()
{
	auto indexes = selectedIndexes();
	std::sort(indexes.begin(), indexes.end(),
						[] (auto lhs, auto rhs) { return lhs.row() < rhs.row(); });
	auto end = std::unique(indexes.begin(), indexes.end(),
												 [] (auto &lhs, auto &rhs) {
													 return lhs.row() == rhs.row();
												 });
	std::vector<int> rows;
	for(auto it = indexes.begin(); it != end; ++it) {
		rows.push_back(it->row());
	}
	return rows;
}
//----------------------------------------------------------------------------
