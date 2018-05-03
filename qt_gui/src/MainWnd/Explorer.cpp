//----------------------------------------------------------------------------
// Explorer.cpp : エクスプローラの管理を行う
//----------------------------------------------------------------------------
#include "Explorer.h"
#include <algorithm>
#include <QApplication>
#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFileIconProvider>
#include <QFileInfo>
#include "MainWnd.h"
#include "Platform.h"
#include "PlayListView_MainWnd.h"
#include "RMenu_Explorer.h"

#ifdef max
# undef max
#endif
//----------------------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------------------
CExplorer::CExplorer(QWidget * parent)
	: CListView(parent), m_rMainWnd(nullptr)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QWidget::customContextMenuRequested,
					this, &CExplorer::OnContextMenu);
	connect(this, &QTableWidget::cellDoubleClicked,
					this, &CExplorer::OnLButtonDoubleClick);
}
//----------------------------------------------------------------------------
// 作成
//----------------------------------------------------------------------------
BOOL CExplorer::Create(CMainWnd & mainWnd)
{
	m_rMainWnd = &mainWnd;

	setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);

	setColumnCount(4);
	InsertColumn(0, tr("Name"), LVCFMT_LEFT, 100, 0);
	InsertColumn(1, tr("Date Modified"), LVCFMT_LEFT, 80, 1);
	InsertColumn(2, tr("Type"), LVCFMT_LEFT, 80, 2);
	InsertColumn(3, tr("Size"), LVCFMT_RIGHT, 80, 3);

	ShowFiles();

	return TRUE;
}
//----------------------------------------------------------------------------
// 選択中のファイルを開く
//----------------------------------------------------------------------------
void CExplorer::OpenFiles(BOOL bClear)
{
	BOOL bAdd = FALSE;
	for (int nItem : GetSelectedRows()) {
		if(!bAdd) {
			if(bClear) {
				m_rMainWnd->ChangeCurPlayTab();
				m_rMainWnd->GetPlayList().DeleteAllItems();
			}
			m_rMainWnd->AddFile(filePaths[nItem]);
		}
		else m_rMainWnd->AddFile(filePaths[nItem]);
		bAdd = TRUE;
	}
	if(bAdd && bClear) {
		m_rMainWnd->GetSound().SetCurFileNum(0);
		m_rMainWnd->PlayNext(TRUE, FALSE);
		m_rMainWnd->SetPreviousNextMenuState();
	}
}
//----------------------------------------------------------------------------
// フォルダを開く
//----------------------------------------------------------------------------
void CExplorer::OpenFolder()
{
	for (int nItem : GetSelectedRows()) {
		QString chPath = filePaths[nItem];
		if(PathIsURL(chPath)) {
			continue;
		}
		QFileInfo fi(chPath);
		QDesktopServices::openUrl(
				QUrl("file:///" + fi.absoluteDir().absolutePath()));
	}
}
//----------------------------------------------------------------------------
// 選択中のディレクトリを開く
//----------------------------------------------------------------------------
BOOL CExplorer::OpenDirectory()
{
	auto rows = GetSelectedRows();
	if(rows.empty()) return FALSE;
	int itemNum = rows.front();

	QFileInfo fi(filePaths[itemNum]);
	if(!fi.exists() || !fi.isDir()) return false;

	QDir::setCurrent(filePaths[itemNum]);
	ShowFiles();
	return TRUE;
}
//----------------------------------------------------------------------------
// ファイルの表示
//----------------------------------------------------------------------------
BOOL CExplorer::ShowFiles()
{
	m_rMainWnd->GetExplorerBar().GetEdit().setText("");
	DeleteAllItems();

	QDir dir = QDir::current();
	m_rMainWnd->GetExplorerBar().GetEdit().setText(
		QDir::toNativeSeparators(dir.absolutePath()));

	// ファイルの列挙ループ
	QFileIconProvider provider;
	int i = 0;
	filePaths.clear();
	QListIterator<QFileInfo> it(dir.entryInfoList());
	while (it.hasNext()) {
		QFileInfo fi = it.next();
		if(fi.fileName() == ".." || fi.fileName() == ".")
			continue;

		// ファイルのパスを保持しておく
		QString filePath = fi.filePath();

		QString ext = fi.suffix();
		auto cs = Qt::CaseInsensitive;

		if(!fi.isDir() &&
			ext.compare("wav", cs) != 0 && ext.compare("cda", cs) != 0 &&
			ext.compare("mp3", cs) != 0 && ext.compare("mp2", cs) != 0 &&
			ext.compare("mp1", cs) != 0 && ext.compare("ogg", cs) != 0 &&
			ext.compare("wma", cs) != 0 && ext.compare("aiff", cs) != 0 &&
			ext.compare("aif", cs) != 0 && ext.compare("ape", cs) != 0 &&
			ext.compare("flac", cs) != 0 && ext.compare("m4a", cs) != 0 &&
			ext.compare("m4b", cs) != 0 &&
			ext.compare("mp4", cs) != 0 && ext.compare("aac", cs) != 0 &&
			ext.compare("avi", cs) != 0 && ext.compare("wmv", cs) != 0 &&
			ext.compare("mkv", cs) != 0 && ext.compare("flv", cs) != 0 &&
			ext.compare("ini", cs) != 0 && ext.compare("m3u", cs) != 0 &&
			ext.compare("m3u8", cs) != 0)
			continue;

		// 見つかったファイル用に新アイテムを追加
		InsertItem(i);

		int icon_idx;
		if (fi.isDir()) {
			if (m_folderIcon.isNull()) {
				m_folderIcon = provider.icon(QFileIconProvider::Folder);
			}
			icon_idx = kFolderIconIndex;
		} else {
			size_t j = 0;
			for (; j < m_extIconList.size(); j++) {
				if (std::get<0>(m_extIconList[j]) == ext) {
					break;
				}
			}
			if (j == m_extIconList.size()) {
				if (m_extIconList.empty()) {
					m_extIconList.resize(1);
				}
				icon_idx = static_cast<int>(m_extIconList.size());
				m_extIconList.push_back(std::make_pair(ext, provider.icon(fi)));
			} else {
				icon_idx = static_cast<int>(j);
			}
		}
		SetItem(i, 0, fi.fileName(), icon_idx);
		SetItem(i, 1, fi.lastModified().toString("yyyy/MM/dd hh:mm"));
		if (fi.isFile()) {
			qint64 bytes = fi.size();
			QLocale locale(QLocale::English);
			SetItem(i, 3, locale.toString(bytes / 1024.0, 'f', 0) + " KB");
		}

		filePaths.push_back(filePath);

		i++;
	}
	return TRUE;
}
//----------------------------------------------------------------------------
// コンテキストメニュー
//----------------------------------------------------------------------------
void CExplorer::OnContextMenu(const QPoint & pos)
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
	CRMenu_Explorer menu(*this, hit);
	menu.exec(this->mapToGlobal(pos));
}
//----------------------------------------------------------------------------
// ダブルクリックされた
//----------------------------------------------------------------------------
void CExplorer::OnLButtonDoubleClick(int row, int column)
{
	if(!OpenDirectory()) {
		bool ctrl = QApplication::keyboardModifiers() & Qt::ControlModifier;
		OpenFiles(ctrl);
	}
}
//----------------------------------------------------------------------------
