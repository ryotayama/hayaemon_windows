//----------------------------------------------------------------------------
// PlayListView_MainWnd.h : プレイリスト用リストビューの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayListView_MainWndH
#define PlayListView_MainWndH

class CMainWnd;
#include <stdint.h>
#include <vector>
#include <QIcon>
#include <QList>
#include <QTableWidget>
#include "../Common/Define.h"
class QUrl;
//----------------------------------------------------------------------------
// プレイリスト用リストビューの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayListView_MainWnd : public QTableWidget
{
	Q_OBJECT

public: // 関数
	CPlayListView_MainWnd(CMainWnd & mainWnd, QWidget * parent = nullptr);

	virtual void AddDirectory(const QString & lpszDirectoryPath);
	virtual void AddFile(const QString & filePath, int nPos = -1);
	virtual void AddURL(const QString & lpszFilePath, int nPos = -1);
	virtual void CopySelectedItem(int nDst);
	virtual BOOL Create();
	virtual void CreateNewList();
	virtual BOOL DeleteAllItems();
	virtual void DeleteSelectedItems();
	virtual void Delete(int nItem);
	virtual int GetMaxPlayOrder() const;
	virtual void PlaySelectedItem();
	virtual void SetPlaying(int iItem);
	virtual void SetPausing(int iItem);
	virtual void SetPlayOrder(int iItem);
	virtual void SetPlayOrder(int iItem, int nOrder);
	virtual void ClearPlayOrder();
	virtual void FixPlayOrder(int iItem);
	virtual void ResetNumber();
	virtual void ScrollToItem(int nItem);
	virtual void SelectAll();

	virtual void OnContextMenu(const QPoint & pos);
	virtual void OnDropFiles(const QList<QUrl> & urls);
	virtual void OnKeyDown(QKeyEvent * e);
	virtual void OnLButtonDoubleClick(QTableWidgetItem * item);

public: // メンバ変数の取得・設定

	virtual std::vector<int> GetOrders() const
	{
		return orders;
	}
	CMainWnd & GetMainWnd() { return m_rMainWnd; }

public:
	// Qtのラッパー
	virtual BOOL DeleteItem(int nItem) {
		if (nItem < this->rowCount()) {
			this->removeRow(nItem);
		}
		return nItem < this->rowCount();
	}
	virtual BOOL EnsureVisible(int nItem, BOOL fPartialOK) {
		if (nItem < this->rowCount()) {
			this->scrollToItem(this->item(nItem, 0));
		}
		return nItem < this->rowCount();
	}
	virtual int GetItemCount() const { return rowCount(); }
	virtual void GetItemText(int iItem, int iSubItem, QString * pszText) const {
		*pszText = this->item(iItem, iSubItem)->text();
	}
	virtual void SetItem(int i, int iSubItem, const QString & pszText) {
		SetItem(i, iSubItem, pszText, -1);
	}
	virtual void SetItem(int i, int iSubItem, const char16_t * pszText,
											 int iImage) {
		SetItem(i, iSubItem, QString::fromUtf16(pszText), iImage);
	}
	virtual void SetItem(int i, int iSubItem, const wchar_t * pszText,
											 int iImage) {
		SetItem(i, iSubItem, QString::fromWCharArray(pszText), iImage);
	}
	virtual void SetItem(int i, int iSubItem, const QString & pszText,
											 int iImage) {
		auto item = this->item(i, iSubItem);
		if (item == nullptr) {
			item = new QTableWidgetItem();
			setItem(i, iSubItem, item);
		}
		item->setText(pszText);
		item->setIcon(iImage >= 0 ? m_icons[iImage] : QIcon());
	}
	virtual void SetItemState(int i, UINT state, UINT mask) {
		if (state == LVIS_SELECTED) {
			for (int j = 0; j < this->columnCount(); j++) {
				auto item = this->item(i, j);
				if (item != nullptr) {
					item->setSelected(true);
				}
			}
		}
	}
	virtual int InsertColumn(int nCol, const QString & lpszColumnHeading,
								int nFormat = LVCFMT_LEFT, int nWidth = -1,
								int nSubItem = -1);
	virtual int InsertItem(int nItem) {
		insertRow(nItem);
		return nItem;
	}
	virtual void Show(int nCmdShow) {
		this->setVisible(nCmdShow != SW_HIDE);
	}

protected:
	void dragEnterEvent(QDragEnterEvent * e) override;
	void dropEvent(QDropEvent * e) override;
	QStringList mimeTypes() const override {
		return QTableWidget::mimeTypes() << QStringLiteral("text/uri-list");
	}
	void keyPressEvent(QKeyEvent * e) override;

private:

	std::vector<int> GetSelectedRows();

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	std::vector<int> orders; // 再生順
	QIcon m_icons[2];
};
//----------------------------------------------------------------------------

#endif
