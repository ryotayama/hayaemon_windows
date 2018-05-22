//----------------------------------------------------------------------------
// PlayListView_MainWnd.cpp : 速度表示用ラベルの管理を行う
//----------------------------------------------------------------------------
#include "PlayListView_MainWnd.h"
#include <algorithm>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QMimeData>
#include <QTableWidgetItem>
#include <QUrl>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "M3UFile.h"
#include "MainWnd.h"
#include "Platform.h"
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
	: CListView(parent), m_rMainWnd(mainWnd)
{
	this->verticalHeader()->hide();
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QWidget::customContextMenuRequested,
					this, &CPlayListView_MainWnd::OnContextMenu);
	connect(this, &QTableWidget::itemDoubleClicked,
					this, &CPlayListView_MainWnd::OnLButtonDoubleClick);
	connect(this, &QTableWidget::itemChanged,
					this, &CPlayListView_MainWnd::SaveTag);
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
	auto rows = GetSelectedRows();
	for (size_t i = 0; i < rows.size(); i++) {
		int nItem = rows[i];
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
		for (size_t j = i + 1; j < rows.size(); j++) {
			--rows[j];
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
	return CListView::DeleteAllItems();
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
// フォルダを開く
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OpenFolder()
{
	for (int nItem : GetSelectedRows()) {
		QString chPath;
		GetItemText(nItem, 7, &chPath);
		if(PathIsURL(chPath)) {
			continue;
		}
		QFileInfo fi(chPath);
		QDesktopServices::openUrl(
				QUrl("file:///" + fi.absoluteDir().absolutePath()));
	}
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
// タグの設定
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::SaveTag(QTableWidgetItem * item)
{
	int nItem = item->row();
	int nSubItem = item->column();
	if(nSubItem != 2 && nSubItem != 3 && nSubItem != 4) {
		return;
	}

	QString chValue;
	GetItemText(nItem, nSubItem, &chValue);

	QString chPath;
	GetItemText(nItem, 7, &chPath);

	BOOL bPlaying = FALSE; // 再生中のファイルのタグ更新かどうか
	BOOL bStopped = FALSE, bPausing = FALSE;
	QWORD qwPos;
	if(&m_rMainWnd.GetCurPlayList() == this &&
			m_rMainWnd.GetSound().GetCurFileName() == ToTstring(chPath)) {
		bPlaying = TRUE;
		qwPos = m_rMainWnd.GetSound().ChannelGetPosition();
		bStopped = m_rMainWnd.GetSound().ChannelIsStopped();
		bPausing = m_rMainWnd.GetSound().ChannelIsPausing();
	}

	if(bPlaying) m_rMainWnd.GetSound().StreamFree();
#if _WIN32
	TagLib::FileRef f(chPath.toStdWString().c_str());
#elif __APPLE__
	TagLib::FileRef f(chPath.toUtf8().toStdString().c_str());
#endif
	if(!f.isNull() && f.tag() != nullptr) {
		TagLib::Tag * tag = f.tag();
		if(nSubItem == 2) {
			tag->setTitle(chValue.toStdWString());
		} else if(nSubItem == 3) {
			tag->setArtist(chValue.toStdWString());
		} else if(nSubItem == 4) {
			tag->setYear(chValue.toInt());
		}
		f.save();
	}
	if(bPlaying) {
		m_rMainWnd.GetSound().StreamCreateFile(ToTstring(chPath).c_str());
		m_rMainWnd.GetSound().ClearMarker();
		m_rMainWnd.SetAllEffects();
		m_rMainWnd.GetSound().ChannelSetPosition(qwPos);
		if(!bStopped && !bPausing) m_rMainWnd.GetSound().ChannelPlay();
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
// アイテムの情報をアップデート
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::UpdateItemInfo(int nItem)
{
	// パスを得る
	QString chPath;
	GetItemText(nItem, 7, &chPath);

	// ファイル名を取得
	QString chFileName = QFileInfo(chPath).fileName();
	QString chFileExt = QFileInfo(chPath).suffix();

	// ファイル名
	SetItem(nItem, 6, chFileName);

	if(PathIsURL(chPath)) return;

	if(chFileExt.compare("nsf", Qt::CaseInsensitive) == 0)
		return;

#if _WIN32
	TagLib::FileRef f(chPath.toStdWString().c_str());
#elif __APPLE__
	TagLib::FileRef f(chPath.toUtf8().toStdString().c_str());
#endif
	if(!f.isNull() && f.tag() != nullptr) {
		TagLib::Tag * tag = f.tag();
		// タイトル
		QString chTitle = ToQString(tag->title().toWString());
		SetItem(nItem, 2, !chTitle.isEmpty() ? chTitle : chFileName);

		// アーティスト
		QString chArtist = ToQString(tag->artist().toWString());
		SetItem(nItem, 3, chArtist);
	}

	// 年
	m_rMainWnd.GetSound().StartReadTag(ToTstring(chPath).c_str());
	LPCSTR t = (LPCSTR)m_rMainWnd.GetSound().ReadYearTag();
	QString chYear = ToQString(t);
	SetItem(nItem, 4, chYear);

	// 長さ
	double time = m_rMainWnd.GetSound().ReadTime();

	int hour = (int)(time / 3600) % 60;
	int second = (int)(time / 60) % 60;
	int minute = (int)time % 60;

	TCHAR chTime[255] = _T("");
	if(time >= 0.0) {
		if(hour > 0)
			_stprintf_s(chTime, _T("%02d:%02d:%02d"), hour, second, minute);
		else _stprintf_s(chTime, _T("%02d:%02d"), second, minute);
	}
	m_rMainWnd.GetSound().EndReadTag();

	SetItem(nItem, 5, ToQString(chTime));

	SetItemEditable(nItem, 2, true);
	SetItemEditable(nItem, 3, true);
	SetItemEditable(nItem, 4, true);
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
		hit = rect.top() <= pos.y() && pos.y() <= rect.bottom();
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
// キーボードが押された
//----------------------------------------------------------------------------
void CPlayListView_MainWnd::OnKeyDown(QKeyEvent * e)
{
	int vk = e->key();
	if((vk == Qt::Key_Return || vk == Qt::Key_Enter) && !e->isAutoRepeat())
		PlaySelectedItem();
	else if(vk == Qt::Key_Delete) DeleteSelectedItems();
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
void CPlayListView_MainWnd::dragEnterEvent(QDragEnterEvent * e)
{
	e->acceptProposedAction();
}
void CPlayListView_MainWnd::dropEvent(QDropEvent * e)
{
	OnDropFiles(e->mimeData()->urls());
}
void CPlayListView_MainWnd::keyPressEvent(QKeyEvent * e)
{
	OnKeyDown(e);
}
//----------------------------------------------------------------------------
