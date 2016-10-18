#ifndef __AUTOLOGINBYBNSCHINA_BNSDLL_GAMESTRUCT_H__
#define __AUTOLOGINBYBNSCHINA_BNSDLL_GAMESTRUCT_H__

#include <memory>
#include <algorithm>
#include <vector>
#include <MyTools/CLLog.h>
#include <MyTools/ClassInstance.h>


enum em_Player_Classes
{
	// ��ʿ
	em_Player_Classes_Destroyer = 0x5,
	// �̿�
	em_Player_Classes_Assassin = 0x7,
	// ��ʿ
	em_Player_Classes_BladeMaster = 0x1,
	// �ٻ�ʦ
	em_Player_Classes_Summoner = 0x6,
	// ����
	em_Player_Classes_ForceMaster = 0x3,
	// ȭʦ
	em_Player_Classes_KongFuMaster = 0x2,
	// �齣ʿ
	em_Player_Classes_Danncer = 0x8,
	// ����ʦ
	em_Player_Classes_Warlock = 0x9,
	// ����
	em_Player_Classes_KongFuForceMaster = 0xA

};

struct AccountConfig
{
	std::wstring		wsAccountName;
	std::wstring		wsAccountPass;

	VOID Clear()
	{
		wsAccountName = wsAccountPass = L"";
	}
};

struct AccountPlayerConfig
{
	UINT				uIndex;
	UINT				uLevel;
	em_Player_Classes	emPlayerClass;
	std::wstring		wsPlayerName;

	VOID Clear()
	{
		uIndex = uLevel = NULL;
		wsPlayerName = L"";
	}
};

struct TextAccountSchedule
{
	AccountConfig				AccountContent;
	BOOL						bFinish;
	UINT						uVolume;
	vector<AccountPlayerConfig> AccountPlayerConfigVec;

	VOID Clear()
	{
		bFinish = FALSE;
		uVolume = NULL;
		AccountContent.Clear();
		AccountPlayerConfigVec.clear();
	}
};

enum em_Console_Variable
{

};

///////////////�ʺ�///////////////////////////////////////////////////////////
typedef struct _Account_Info
{
	WCHAR szUserName[64];			//	�ʺ�
	WCHAR szPassWord[32];			//	����
	DWORD dwServerId;				//	������
	DWORD dwOrderIndex;				//	��ɫ�б�
	WCHAR szPlayerName[32];			//	�������
	BOOL bAlive;					//	���ʶ�����ڼ��һ�δ˱�ʶ�����û������ΪTRUE��ʾĿ����̳������ˡ�
	BOOL bLogin;					//	��¼���=FALSE
	WCHAR szCardNo[64];				//	����
	DWORD dwClasses;				// ְҵ
}ACCOUNT_INFO, *PACCOUNT_INFO;

typedef enum _em_Close_Result
{
	em_Close_Result_None,			// ����״̬
	em_Close_Result_ReStart,		// �����Ϻ�
	em_Close_Result_LoseConnect,	// ����
	em_Close_Result_FixPoint,		// 5����
	em_Close_Result_CloseConsole,	// �رտ���̨
	em_Close_Result_UnExistTime,	// �㿨û��
}em_Close_Result;

typedef struct _AccountRunStatus
{
	BOOL bDone;												// �Ƿ�ˢ���������
	BOOL bExist;											// ���ʺ��Ѿ���ռ����
	BOOL bLogining;											// �Ƿ��¼��
	BOOL bClose;											// �Ƿ�ǿ�ƹرո��ʺ�
	em_Close_Result	emCloseResult;							// �ر�����
}AccountRunStatus;

typedef struct _AccountLog
{
	BOOL bOccupy;											// �Ƿ�ռ��
	WCHAR szMsg[64];										// ��־
}AccountLog;

typedef struct _Account_Info_GAME
{
	ACCOUNT_INFO MyAcount_Info;								// �ʺ���Ϣ
	AccountLog   AccountLog_;								// �ʺ���־
	DWORD dwPid;											// ����ID
	HWND hGameWnd;											// ���ھ��
	AccountRunStatus AccountStatus;							// �ʺ�״̬

	LPCWSTR GetAccName()
	{
		return this->GetAccountInfo()->szUserName;
	}
	DWORD& GetOrderIndex()
	{
		return this->GetAccountInfo()->dwOrderIndex;
	}
	PACCOUNT_INFO GetAccountInfo()
	{
		return &this->MyAcount_Info;
	}
}ACCOUNT_INFO_GAME, *PACCOUNT_INFO_GAME;


#define MAX_GAME_COUNT				1000
typedef struct _Shared_Info
{
	WCHAR szConsolePath[MAX_PATH];							// ����̨·��
	WCHAR wszGamePath[MAX_PATH];							// ��Ϸ·��
	int nAccountCount;										// Size
	ACCOUNT_INFO_GAME arrGameInfo[MAX_GAME_COUNT];			// ����

	PACCOUNT_INFO_GAME ExistEmptyArrGameInfo()
	{
		auto itr = std::find_if(std::begin(arrGameInfo), std::end(arrGameInfo), [](ACCOUNT_INFO_GAME& AccountGame) {
			return !AccountGame.AccountStatus.bExist;
		});

		if (itr == std::end(arrGameInfo))
			return nullptr;
		return itr;
	}
	PACCOUNT_INFO_GAME GetCurrentAccountGame(_In_ DWORD dwPid)
	{
		auto itr = std::find_if(std::begin(arrGameInfo), std::end(arrGameInfo), [&dwPid](ACCOUNT_INFO_GAME& AccountGame) {
			return AccountGame.dwPid == dwPid;
		});

		if (itr == std::end(arrGameInfo))
			return nullptr;

		return itr;
	}
}SHARED_INFO, *PSHARED_INFO;

#endif