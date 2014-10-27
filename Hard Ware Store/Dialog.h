#pragma once

#include "resource1.h"
class Dialog : public CDialog
{
public:
	Dialog(CWnd* pParent=NULL);
	enum { IDD = IDD_DIALOG1 };
	virtual ~Dialog();

protected:
	virtual void DoDataExchange(CDataExchange *pDx);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CString StockN, Description;
	int Qty;
	double price;
};