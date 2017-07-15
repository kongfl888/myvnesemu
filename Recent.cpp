//
// Recent File class
//
#include <TCHAR.h>

#include "DebugOut.h"
#include "PathLib.h"

#include "VirtuaNESres.h"
#include "Recent.h"

CHAR	CRecent::m_RecentName[RECENT_MAX][_MAX_PATH];
CHAR	CRecent::m_RecentPath[RECENT_MAX][_MAX_PATH];
CHAR	CRecent::m_TempPath[_MAX_PATH];

LPCSTR	CRecent::GetName( INT nID )
{
	// CRecent::Add Because it may come back pointing at the same pointer at once temporary copy
	::strcpy_s( m_TempPath, m_RecentName[nID] );
	return	(LPCSTR)m_TempPath;
}

LPCSTR	CRecent::GetPath( INT nID )
{
	return	(LPCSTR)m_RecentPath[nID];
}

void	CRecent::MakeManuPath( LPSTR lpszPath )
{
	string	FullPath = lpszPath;
	string	FileName = CPathlib::SplitFnameExt( lpszPath );

	// 30 characters or less is left intact
	if( FullPath.size() <= 30 )
		return;

	// When the file name is 30 characters or more
	if( ::strlen( FileName.c_str() ) >= 30 ) {
		::strcpy_s(lpszPath, FileName.length() + 1, FileName.c_str());
		return;
	}

	LPCSTR lpszCur = lpszPath + 2;
	if( lpszPath[0] == '\\' && lpszPath[1] == '\\' ) {
		while (*lpszCur != '\\') {
			lpszCur = _tcsinc(lpszCur);
		}
	}

	if( ::strlen(FullPath.c_str()) - ::strlen(FileName.c_str()) > 3 ) {
		lpszCur = _tcsinc(lpszCur);
		while( *lpszCur != '\\' ) {
			lpszCur = _tcsinc(lpszCur);
		}
	}

	INT	nVolume = lpszCur - lpszPath;
	if( 30 < nVolume+5+::strlen(FileName.c_str()) ) {
		::strcpy_s(lpszPath, FileName.length() + 1, FileName.c_str());
		return;
	}

	while ( nVolume+4+::strlen(lpszCur) > 30 ) {
		do {
			lpszCur = _tcsinc(lpszCur);
		}
		while( *lpszCur != '\\' );
	}

	lpszPath[nVolume] = '\0';
	::strcat_s(lpszPath, strlen(lpszPath) + 5, "\\...");
	::strcat_s(lpszPath, strlen(lpszPath) + strlen(lpszCur) + 1, lpszCur);
}

void	CRecent::UpdateMenu( HMENU hMenu )
{
	// No menu?
	if( !hMenu )
		return;

	// File(&F) Getting a menu
	HMENU hSubMenu = ::GetSubMenu( hMenu, 0 );

	// Recent folder(&P)Get pop-up menu
	HMENU hPathMenu = ::GetSubMenu( hSubMenu, 12 );
	// Recent files(&F)Get pop-up menu
	HMENU hFileMenu = ::GetSubMenu( hSubMenu, 13 );

	// When there is no item
	if( ::strlen(m_RecentPath[0]) <= 0 ) {
		// disable
		::EnableMenuItem( hPathMenu, ID_MRU_PATH0, MF_BYCOMMAND|MF_GRAYED );
	} else {
		INT	i;
		// Delete menu item
		for( i = 0; i < RECENT_MAX; i++ ) {
			::DeleteMenu( hPathMenu, ID_MRU_PATH0+i, MF_BYCOMMAND );
		}

		CHAR	szRecent[_MAX_PATH];
		CHAR	szTemp[_MAX_PATH];
		for( i = 0; i < RECENT_MAX; i++ ) {
			if( ::strlen(m_RecentPath[i]) > 0 ) {
				// Shorten paths for menus
				::strcpy_s( szRecent, m_RecentPath[i] );

				// Convert '&' in file with '&' to '&&'
				LPCSTR	pSrc = szRecent;
				LPSTR	pDst = szTemp;
				while( *pSrc != 0 ) {
					if( *pSrc == '&' )
						*pDst++ = '&';
					if( _istlead(*pSrc) )
						*pDst++ = *pSrc++;
					*pDst++ = *pSrc++;
				}
				*pDst = 0;
				::wsprintf( szRecent, "&%d ", (i+1)%10 );
				::strcat_s(szRecent, _countof(szRecent), szTemp);

				// Add to menu
				::InsertMenu( hPathMenu, i, MF_BYPOSITION, ID_MRU_PATH0+i, szRecent );
			} else {
				break;
			}
		}
	}

	// When there is no item
	if( ::strlen(m_RecentName[0]) <= 0 ) {
		// Disable
		::EnableMenuItem( hFileMenu, ID_MRU_FILE0, MF_BYCOMMAND|MF_GRAYED );
	} else {
		INT	i;
		// Delete menu item
		for( i = 0; i < RECENT_MAX; i++ ) {
			::DeleteMenu( hFileMenu, ID_MRU_FILE0+i, MF_BYCOMMAND );
		}

		CHAR	szRecent[_MAX_PATH];
		CHAR	szTemp[_MAX_PATH];
		for( i = 0; i < RECENT_MAX; i++ ) {
			if( ::strlen(m_RecentName[i]) > 0 ) {
				// Shorten paths for menus
				::strcpy_s( szRecent, m_RecentName[i] );
				MakeManuPath( szRecent );

				// '&'Convert '&' in file with '&&'
				LPCSTR	pSrc = szRecent;
				LPSTR	pDst = szTemp;
				while( *pSrc != 0 ) {
					if( *pSrc == '&' )
						*pDst++ = '&';
					if( _istlead(*pSrc) )
						*pDst++ = *pSrc++;
					*pDst++ = *pSrc++;
				}
				*pDst = 0;
				::wsprintf( szRecent, "&%d ", (i+1)%10 );
				::strcat_s(szRecent, _countof(szRecent), szTemp);

				// Add to menu
				::InsertMenu( hFileMenu, i, MF_BYPOSITION, ID_MRU_FILE0+i, szRecent );
			} else {
				break;
			}
		}
	}
}

void	CRecent::Add( LPCSTR lpszPath )
{
	INT	i, j;

	if( ::strlen(m_RecentName[0]) > 0 ) {
		for( i = 0; i < RECENT_MAX; i++ ) {
			if( ::strlen(m_RecentName[i]) <= 0 )
				break;
		}
		for( j = 0; j < i; j++ ) {
			if( ::strcmp( lpszPath, m_RecentName[j] ) == 0 )
				break;
		}
		if( j == RECENT_MAX )
			j--;
		for( ; j > 0; j-- ) {
			::strcpy_s(&m_RecentName[j][0], strlen(&m_RecentName[j - 1][0]) + 1, &m_RecentName[j - 1][0]);
		}
	}
	::strcpy_s( m_RecentName[0], lpszPath );

	string	temp = CPathlib::SplitPath( lpszPath );
	if( ::strlen(m_RecentPath[0]) > 0 ) {
		for( i = 0; i < RECENT_MAX; i++ ) {
			if( ::strlen(m_RecentPath[i]) <= 0 )
				break;
		}
		for( j = 0; j < i; j++ ) {
			if( ::strcmp( m_RecentPath[j], temp.c_str() ) == 0 )
				break;
		}
		if( j == RECENT_MAX )
			j--;
		for( ; j > 0; j-- ) {
			::strcpy_s( m_RecentPath[j], m_RecentPath[j-1] );
		}
	}
	::strcpy_s( m_RecentPath[0], temp.c_str() );
}

void	CRecent::Load()
{
	INT	i;
	CHAR	szTemp[MAX_PATH];
	CHAR	szEntry[32];
	for( i = 0; i < RECENT_MAX; i++ ) {
		::wsprintf( szEntry, "Path%d", i+1 );
		if( CRegistry::GetProfileString( "Recent Path List", szEntry, szTemp, sizeof(szTemp) ) )
			::strcpy_s( m_RecentPath[i], szTemp );
	}
	for( i = 0; i < RECENT_MAX; i++ ) {
		::wsprintf( szEntry, "File%d", i+1 );
		if( CRegistry::GetProfileString( "Recent File List", szEntry, szTemp, sizeof(szTemp) ) )
			::strcpy_s( m_RecentName[i], szTemp );
	}
}

void	CRecent::Save()
{
	INT	i;
	CHAR	szEntry[32];
	for( i = 0; i < RECENT_MAX; i++ ) {
		if( ::strlen(m_RecentPath[i]) > 0 ) {
			::wsprintf( szEntry, "Path%d", i+1 );
			CRegistry::WriteProfileString( "Recent Path List", szEntry, m_RecentPath[i] );
		}
	}
	for( i = 0; i < RECENT_MAX; i++ ) {
		if( ::strlen(m_RecentName[i]) > 0 ) {
			::wsprintf( szEntry, "File%d", i+1 );
			CRegistry::WriteProfileString( "Recent File List", szEntry, m_RecentName[i] );
		}
	}
}

