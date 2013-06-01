#pragma  once

// ����
// Ϊ���ܹ�ʵ�ֶ��󼶵����ô�ȡ, ÿ����Setting�̳еĶ��������״̬������ͨ��
// ǳ����ʵ��
// ���粻��������CString, std::string, �ȳ�Ա����

#include "Setting.h"

// ���ʺͺ���ĳ���ʱ��
struct ComeOutOccasion : public Setting
{
	struct ComeOutOcc
	{
		BOOL bTabbed;			// ��tab������
		UINT uTimerDelay;		// ��uTimerDelay����֮�����
	};
	ComeOutOcc word, meaning;

	IMPLEMENT_OBJSTORE()
};

// ��������
struct CharFormat : public Setting
{
	CHARFORMAT cfWord;
	CHARFORMAT cfPractise;
	CHARFORMAT cfMeaning;
	CHARFORMAT cfPhonetic;

	IMPLEMENT_OBJSTORE()
};

// ��ɫ����
struct MainColor : public Setting
{
	MainColor();

	COLORREF crWord;
	COLORREF crMeaning;
	COLORREF crPractise;
	COLORREF crPhonetic;

	COLORREF crWordBk;
	COLORREF crMeaningBk;
	COLORREF crPractiseBk;
	COLORREF crDlgBk;

	COLORREF crProgressBk;
	COLORREF crProgress1;
	COLORREF crProgress2;
	COLORREF crProgressFont;

	COLORREF crWordTypeInactive;
	COLORREF crWordTypeActive;
	COLORREF crWordTypeBorder;

	COLORREF crAccesstime;
	COLORREF crAccesstimeBk;

	// Meaning Scroll
	COLORREF crMsFace;
	COLORREF crMsHighlight;
	COLORREF crMsShadow;
	COLORREF crMsArrow;
	COLORREF crMsBase;
	COLORREF crMsDarkshadow;

	IMPLEMENT_OBJSTORE()
};

// ��������
// �����������Word_Order
#define WO_ASC					0x00000001		// Ascend
#define WO_DESC					0x00000002		// Descend
#define WO_RANDOM				0x00000003		// Random
#define WO_NOSORT				0x00000004		// No sort
#define WO_BY_WORD				0x00000010		// According to word
#define WO_BY_ACCESS_TIME		0x00000020		// According to access time
// ����ʱ�������ģʽ Mark_Accesstime_Mode
#define MAM_NERVER				0x00000000		// Never set access time
#define MAM_AUTO				0x00000001		// Auto set on new word
#define MAM_TYPED				0x00000002		// ֻ���û���practise������ϰ������
#define MAM_TYPEDRIGHT			0x00000003		// ֻ���û���practise������ϰ����ȷ������
#define MAM_TYPEDWRONG			0x00000004		// ֻ���û���practise������ϰ�����������

struct MiscSet : public Setting
{
	BOOL bShowDetailedMeaning;			// �Ƿ���ʾ��ϸ����
	DWORD dwWordOrder;					// ��ʾ���ʵ�����˳��
	int maMode;							// ����ʱ�������ģʽ
	BOOL bMovenextWhenTypeRight;		// ����ϰ����ƴд������ȷ��������һ����
	BOOL bShowPractiseWnd;				// �Ƿ���ʾ��ϰ����
	int nDelayWhenAutoSetAccessTime;	// ���Զ����õ��ʷ���ʱ��ʱ���Զ����õ��ӳ�
	IMPLEMENT_OBJSTORE()
};

// ����״̬
struct WndStatus : public Setting
{
	WINDOWPLACEMENT wndplMain;

	IMPLEMENT_OBJSTORE()
};

// ȫ������, Singletonģʽ
class GlobalSetting
{
public:
	~GlobalSetting();
	static GlobalSetting * Instance();

	const GlobalSetting * MarkRestorePoint();
	void Restore();

	ComeOutOccasion      Coo;
	CharFormat           Cf;
	MainColor            Cr;
	MiscSet              Ms;
	WndStatus            Ws;

	// ������Ϣ����ںδ�
	static BOOL m_bSaveInReg;

private:
	// ������ʱ���󣬲�ִ���κζ�ȡ�ͱ���Ĳ���
	GlobalSetting(BOOL bTemp = FALSE);
	void Init();
	BOOL LoadSetting(const char * file);
	BOOL SaveSetting(const char * file);
	GlobalSetting& operator = (GlobalSetting &gs);

	BOOL m_bTemp;
	static GlobalSetting m_gsOld;
};
