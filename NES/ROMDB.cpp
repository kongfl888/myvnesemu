//
// NES ROMDB class
//
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <mbstring.h>

#include "typedef.h"
#include "macro.h"

#include "DebugOut.h"
#include "App.h"
#include "Plugin.h"
#include "Pathlib.h"
#include "Crclib.h"

#include "Archive.h"

#include "romdb.h"

ROMDATABASE	romdatabase;

//
// ROM DATABASE (NESToy&NNNesterJ database)
//
INT	ROMDATABASE::HeaderCheck( NESHEADER& hdr, DWORD crcall, DWORD crc, ROMDB& data )
{
	if( m_DataBaseList.empty() ) {
		LoadDatabase();
	}

	if( m_DataBaseList.empty() )
		return	-2;	// データベースが無い

	map<DWORD, ROMDB, ROMDBCMP>::iterator it = m_DataBaseList.find( crcall );

	if( it == m_DataBaseList.end() )
		return	-1;	// データベースに無い

	data = (*it).second;

	// 一応チェック
	if( data.crcall == crcall || (data.crc == crc && data.crc) ) {
		if( hdr.control1 == data.control1 && hdr.control2 == data.control2 ) {
			return	0;	// 完全適合
		}
	}
	return	1;	// CRCは一致したがヘッダが違う
}

BOOL	ROMDATABASE::HeaderCorrect( NESHEADER& hdr, DWORD crcall, DWORD crc )
{
	if( m_DataBaseList.empty() ) {
		LoadDatabase();
	}

	if( m_DataBaseList.empty() )
		return	FALSE;	// データベースが無い

	map<DWORD, ROMDB, ROMDBCMP>::iterator it = m_DataBaseList.find( crcall );

	if( it == m_DataBaseList.end() )
		return	FALSE;	// データベースに無い

	ROMDB	data = (*it).second;

	// 一応チェック
	if( data.crcall == crcall || (data.crc == crc && data.crc) ) {
		hdr.control1 = data.control1;
		hdr.control2 = data.control2;
		//for( INT i = 0; i < 8; i++ ) {
		//	hdr.reserved[i] = 0;
		//}
		return	TRUE;
	}
	return	FALSE;
}

void	ROMDATABASE::LoadDatabase()
{
FILE*	fp = NULL;
CHAR	buf[512];
const UCHAR seps[] = ";\n\0";	// セパレータ
ROMDB	db;
unsigned char *next_token1 = NULL;

DEBUGOUT( "Database loading...\n" );

	string	Path = CPathlib::MakePathExt( CApp::GetModulePath(), "nesromdb", "dat" );

DEBUGOUT( "File:%s\n", Path.c_str() );

	m_DataBaseList.clear();

	if( (fp = fopen( Path.c_str(), "r" )) ) {
		while( fgets( buf, 512, fp ) ) {
			if( buf[0] == ';' ) {	// コメントフィールドとみなす
				continue;
			}

			CHAR*	pToken;

			// ALL CRC
			if( !(pToken = (CHAR*)_mbstok_s( (UCHAR*)buf, seps, &next_token1 )) )
				continue;
			db.crcall = strtoul( pToken, NULL, 16 );
			// PRG CRC
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.crc = strtoul( pToken, NULL, 16 );

			// Title
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.title = pToken;

			// Control 1
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.control1 = atoi( pToken );
			// Control 2
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.control2 = atoi( pToken );

			// PRG SIZE
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.prg_size = atoi( pToken );
			// CHR SIZE
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.chr_size = atoi( pToken );

			// Country
			if( !(pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1)) )
				continue;
			db.country = pToken;

			db.bNTSC = TRUE;
			// Europe (PAL???)
			if( strcmp( pToken, "E"   ) == 0
			 || strcmp( pToken, "Fra" ) == 0
			 || strcmp( pToken, "Ger" ) == 0
			 || strcmp( pToken, "Spa" ) == 0
			 || strcmp( pToken, "Swe" ) == 0
			 || strcmp( pToken, "Ita" ) == 0
			 || strcmp( pToken, "Aus" ) == 0 ) {
				db.bNTSC = FALSE;
			}

			// Manufacturer
			if( pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1) ) {
				db.manufacturer = pToken;
			} else {
				db.manufacturer.erase( db.manufacturer.begin(), db.manufacturer.end() );
			}

			// Sale date
			if( pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1) ) {
				db.saledate = pToken;
			} else {
				db.saledate.erase( db.saledate.begin(), db.saledate.end() );
			}

			// Price
			if( pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1) ) {
				db.price = pToken;
			} else {
				db.price.erase( db.price.begin(), db.price.end() );
			}

			// Genre
			if( pToken = (CHAR*)_mbstok_s( NULL, seps, &next_token1) ) {
				db.genre = pToken;
			} else {
				db.genre.erase( db.genre.begin(), db.genre.end() );
			}

			m_DataBaseList[db.crcall] = db;
		}
		FCLOSE( fp );
	} else {
DEBUGOUT( "Database file not found.\n" );
	}
}

