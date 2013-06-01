#pragma once


// CMyHotKeyCtrl

class CMyHotKeyCtrl : public CHotKeyCtrl
{
	DECLARE_DYNAMIC(CMyHotKeyCtrl)

public:
	CMyHotKeyCtrl();
	virtual ~CMyHotKeyCtrl();

    void SetHotKey(ACCEL acl);
    void GetHotKey(ACCEL &acl) const;
protected:
	DECLARE_MESSAGE_MAP()
};


