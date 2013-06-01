#pragma  once

// 设置
// 为了能够实现对象级的设置存取, 每个从Setting继承的对象的所有状态必须能通过
// 浅拷贝实现
// 比如不能有类似CString, std::string, 等成员变量

#include "Setting.h"

// 单词和汉意的出现时机
struct ComeOutOccasion : public Setting
{
	struct ComeOutOcc
	{
		BOOL bTabbed;			// 按tab键出现
		UINT uTimerDelay;		// 在uTimerDelay毫秒之后出现
	};
	ComeOutOcc word, meaning;

	IMPLEMENT_OBJSTORE()
};

// 字体设置
struct CharFormat : public Setting
{
	CHARFORMAT cfWord;
	CHARFORMAT cfPractise;
	CHARFORMAT cfMeaning;
	CHARFORMAT cfPhonetic;

	IMPLEMENT_OBJSTORE()
};

// 颜色设置
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

// 其它设置
// 单词排序规则Word_Order
#define WO_ASC					0x00000001		// Ascend
#define WO_DESC					0x00000002		// Descend
#define WO_RANDOM				0x00000003		// Random
#define WO_NOSORT				0x00000004		// No sort
#define WO_BY_WORD				0x00000010		// According to word
#define WO_BY_ACCESS_TIME		0x00000020		// According to access time
// 访问时间的设置模式 Mark_Accesstime_Mode
#define MAM_NERVER				0x00000000		// Never set access time
#define MAM_AUTO				0x00000001		// Auto set on new word
#define MAM_TYPED				0x00000002		// 只有用户在practise窗口练习才设置
#define MAM_TYPEDRIGHT			0x00000003		// 只有用户在practise窗口练习并正确才设置
#define MAM_TYPEDWRONG			0x00000004		// 只有用户在practise窗口练习并错误才设置

struct MiscSet : public Setting
{
	BOOL bShowDetailedMeaning;			// 是否显示详细解释
	DWORD dwWordOrder;					// 显示单词的排序顺序
	int maMode;							// 访问时间的设置模式
	BOOL bMovenextWhenTypeRight;		// 在练习窗口拼写单词正确后跳到下一单词
	BOOL bShowPractiseWnd;				// 是否显示练习窗口
	int nDelayWhenAutoSetAccessTime;	// 当自动设置单词访问时间时，自动设置的延迟
	IMPLEMENT_OBJSTORE()
};

// 窗口状态
struct WndStatus : public Setting
{
	WINDOWPLACEMENT wndplMain;

	IMPLEMENT_OBJSTORE()
};

// 全局设置, Singleton模式
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

	// 配置信息存放于何处
	static BOOL m_bSaveInReg;

private:
	// 对于临时对象，不执行任何读取和保存的操作
	GlobalSetting(BOOL bTemp = FALSE);
	void Init();
	BOOL LoadSetting(const char * file);
	BOOL SaveSetting(const char * file);
	GlobalSetting& operator = (GlobalSetting &gs);

	BOOL m_bTemp;
	static GlobalSetting m_gsOld;
};
