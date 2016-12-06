#include "stdafx.h"
#include "LoginPlayer.h"
#include <MyTools/CLPublic.h>

CLoginPlayer::CLoginPlayer()
{
	dwBase = NULL;
	uIndex = NULL;
}

CLoginPlayer::CLoginPlayer(_In_ DWORD dwBase_, _In_ UINT uIndex_) : dwBase(dwBase_), uIndex(uIndex_)
{

}

DWORD CLoginPlayer::GetBase() CONST throw()
{
	return dwBase;
}

cwstring CLoginPlayer::GetName() CONST throw()
{
	WCHAR wszName[64] = { 0 };
	if (ReadDWORD(GetBase() + 0x14 + 0x14) == 0xF)
	{
		if (ReadDWORD(ReadDWORD(GetBase() + 0x14)) != NULL)
			CCharacter::wstrcpy_my(wszName, (LPCWSTR)ReadDWORD(GetBase() + 0x14), _countof(wszName) - 1);
	}
	else
	{
		if (ReadDWORD(GetBase() + 0x14) != NULL)
			CCharacter::wstrcpy_my(wszName, (LPCWSTR)(GetBase() + 0x14), _countof(wszName) - 1);
	}

	return cwstring(wszName);
}

DWORD CLoginPlayer::GetLevel() CONST throw()
{
	return ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(CGameVariable::GetInstance().GetRefValue_By_Id(em_Base::em_Base_Person)) + CGameVariable::GetInstance().GetRefValue_By_Id(em_Base::em_Base_PersonOffset1) - 0x4) + 0x10) + uIndex * 4) + 0x12E) & 0xFF;
}

DWORD CLoginPlayer::GetServerId() CONST throw()
{
	return ReadDWORD(GetBase() + 0x2C) & 0xFFFF;
}

em_Player_Classes CLoginPlayer::GetLoginPlayerClasses() CONST throw()
{
	BYTE bClasses = ReadBYTE(ReadDWORD(ReadDWORD(ReadDWORD(ReadDWORD(CGameVariable::GetInstance().GetRefValue_By_Id(em_Base::em_Base_Person)) + CGameVariable::GetInstance().GetRefValue_By_Id(em_Base::em_Base_PersonOffset1) - 0x4) + 0x10) + uIndex * 4) + 0x2);
	return static_cast<em_Player_Classes>(bClasses);
}

UINT CLoginPlayer::GetIndex() CONST throw()
{
	return uIndex;
}

cwstring CLoginPlayer::GetServerText_By_Id(_In_ DWORD dwServerId) throw()
{
	struct StServer
	{
		std::wstring wsText;
		DWORD		 dwId;
	};

	CONST static vector<StServer> vlst =
	{
		{ L"�׺����",0x23FF },{ L"�屡����",0x23FB },{ L"ս����ԭ",0x2401 },
		{ L"һ������",0x245F },{ L"�鶯����",0x23FD },
	};

	auto p = CLPublic::Vec_find_if_Const(vlst, [&dwServerId](CONST StServer& StServer_) { return StServer_.dwId == dwServerId; });
	return p != nullptr ? p->wsText : cwstring(L"Empty");
}

cwstring CLoginPlayer::GetClassesText_By_Classes(_In_ em_Player_Classes emPlayerClasses) throw()
{
	struct PlayerClassText
	{
		em_Player_Classes	emClasses;
		std::wstring		wsClassText;
	};
	CONST static vector<PlayerClassText> Vec = {
		{ em_Player_Classes::em_Player_Classes_Assassin,			L"�̿�" },
		{ em_Player_Classes::em_Player_Classes_Destroyer,			L"��ʿ" },
		{ em_Player_Classes::em_Player_Classes_BladeMaster,			L"��ʿ" },
		{ em_Player_Classes::em_Player_Classes_Summoner,			L"�ٻ�ʦ" },
		{ em_Player_Classes::em_Player_Classes_ForceMaster,			L"����" },
		{ em_Player_Classes::em_Player_Classes_KongFuMaster,		L"ȭʦ" },
		{ em_Player_Classes::em_Player_Classes_Danncer,				L"�齣ʿ" },
		{ em_Player_Classes::em_Player_Classes_Warlock,				L"����ʦ" },
		{ em_Player_Classes::em_Player_Classes_KongFuForceMaster,	L"����" },
	};

	auto p = CLPublic::Vec_find_if_Const(Vec, [&emPlayerClasses](CONST PlayerClassText& PlayerClassText_) { return PlayerClassText_.emClasses == emPlayerClasses; });
	return p != nullptr ? p->wsClassText : cwstring(L"Empty");
}

