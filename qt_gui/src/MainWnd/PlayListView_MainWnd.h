//----------------------------------------------------------------------------
// PlayListView_MainWnd.h : プレイリスト用リストビューの管理を行う
//----------------------------------------------------------------------------
#ifndef PlayListView_MainWndH
#define PlayListView_MainWndH

class CMainWnd;
#include <stdint.h>
#include <vector>
#include <QList>
#include "../Common/Define.h"
#include "../Common/ListView.h"
class QTableWidgetItem;
class QUrl;
//----------------------------------------------------------------------------
// プレイリスト用リストビューの管理を行うクラス
//----------------------------------------------------------------------------
class CPlayListView_MainWnd : public CListView
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
	virtual void OpenFolder();
	virtual void ResetNumber();
	virtual void ScrollToItem(int nItem);
	virtual void SaveTag(QTableWidgetItem * item);
	virtual void SelectAll();
	virtual void UpdateItemInfo(int nItem);

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
		auto item = this->item(iItem, iSubItem);
		if (item == nullptr) {
			*pszText = "";
		} else {
			*pszText = this->item(iItem, iSubItem)->text();
		}
	}

protected:
	void dragEnterEvent(QDragEnterEvent * e) override;
	void dropEvent(QDropEvent * e) override;
	QStringList mimeTypes() const override {
		return QTableWidget::mimeTypes() << QStringLiteral("text/uri-list");
	}
	void keyPressEvent(QKeyEvent * e) override;

private:

	QIcon GetItemIcon(int idx) const override {
		return idx >= 0 ? m_icons[idx] : QIcon();
	}
	void SetItemEditable(int i, int iSubItem, bool editable) {
		auto item = this->item(i, iSubItem);
		if (item != nullptr) {
			auto flags = item->flags();
			if (editable) {
				item->setFlags(flags | Qt::ItemIsEditable);
			} else {
				item->setFlags(flags & (~Qt::ItemIsEditable));
			}
		}
	}

private: // メンバ変数

	CMainWnd & m_rMainWnd;

	std::vector<int> orders; // 再生順
	QIcon m_icons[2];
};
//----------------------------------------------------------------------------

#endif
