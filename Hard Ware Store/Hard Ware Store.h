
#define PRINT_INVENT		105
#define PRINT_CHECKOUT		106
#define PRINT_CART			107
#define PRINT_CHECK			108
#define ADD					109
#define SUBTRACT			110
#define BUTTON				200
#include "Dialog.h"

class HardWare: public CWinApp
{
public:
	virtual BOOL InitInstance();

};
class CMainWindow :public CWnd
{
protected:
	int PRINT;
	Dialog* dialog;
	CButton button;
	CEdit MFCText, MFCText2;
	CString sAddress,sName;
public:
	CMainWindow();
	void Populate_LinkedList();

protected:
	virtual void Destroy();

	afx_msg void OnPaint();
	afx_msg void OnExit();
	afx_msg void OnAddToCart();
	afx_msg void OnViewInventory();
	afx_msg void OnViewCart();
	afx_msg void OnRemoveCart();
	afx_msg void OnCheckOut();
	afx_msg void OnButton();
	DECLARE_MESSAGE_MAP();
};