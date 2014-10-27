#include <afxwin.h>
#include "Hard Ware Store.h"
#include "resource1.h"
#include "Dialog.h"


//Set the default values of the text boxes in the dialog
Dialog::Dialog(CWnd*pParent)
	:CDialog(Dialog::IDD,pParent)
	{
	Description = _T("");
	StockN = _T("");
	Qty = 0;
	price=0.0;
	}
//Destructor
Dialog::~Dialog()
{
}
//Pass values from the textboxes to variables
void Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, StockN);
	DDX_Text(pDX, IDC_EDIT2, Qty);
	DDX_Text(pDX, IDC_EDIT3, Description);
	DDX_Text(pDX, IDC_EDIT4, price);

}
BOOL Dialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;
}

BEGIN_MESSAGE_MAP(Dialog, CDialog)
	END_MESSAGE_MAP()
