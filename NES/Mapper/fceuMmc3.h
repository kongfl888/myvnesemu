//////////////////////////////////////////////////////////////////////////
// fceuMMC3                                                             //
//////////////////////////////////////////////////////////////////////////

class fceuMMC3 : public Mapper
{
public:
	fceuMMC3( NES* parent,int imap);
	//virtual	~MMC3();

	// For state save
	BOOL	IsStateSave() { return TRUE; }
	void	SaveState( LPBYTE p ){};
	void	LoadState( LPBYTE p ){};

	
	void	Reset();

	void	Write( WORD addr, BYTE data );
	void	Mmc3Write( WORD addr, BYTE data );
	void	(fceuMMC3::*pWrite)( WORD addr, BYTE data );
	void	WriteLow( WORD addr, BYTE data );
	void	Mmc3WriteLow( WORD addr, BYTE data );
	void	(fceuMMC3::*pWriteLow)( WORD addr, BYTE data );
	BYTE	ReadLow( WORD addr );
	BYTE	Mmc3ReadLow( WORD addr );
	BYTE	(fceuMMC3::*pReadLow)( WORD addr );
	void	Read( WORD addr, BYTE data );
	void	Mmc3Read( WORD addr, BYTE data );
	void	(fceuMMC3::*pRead)( WORD addr, BYTE data );
	void	HSync( INT scanline );

	//////////////////////////////////////////////////////////////////////////
	// MMC3
	//////////////////////////////////////////////////////////////////////////	
	uint8 MMC3_cmd;
	uint8 EXPREGS[8];
	uint8 DRegBuf[8];	
	
	uint8 IRQCount,IRQLatch,IRQa;
	uint8 IRQReload;
	
	
	uint8 A000B,A001B;
	int mmc3opts;
	//int wrams;
	int isRevB;
	int iMapper;

	void (fceuMMC3::*pwrap)(uint32 A, uint8 V);
	void (fceuMMC3::*cwrap)(uint32 A, uint8 V);
	void (fceuMMC3::*mwrap)(uint8 V);

	void GenMMC3Power(void);
	void GenMMC3Restore(int version);
	void MMC3RegReset(void);
	void FixMMC3PRG(int V);
	void FixMMC3CHR(int V);
	void MMC3_CMDWrite(uint32 A, uint8 V);
	void MMC3_IRQWrite(uint32 A, uint8 V);
	
	void ClockMMC3Counter(void);	
	void GENCWRAP(uint32 A, uint8 V);
	void GENPWRAP(uint32 A, uint8 V);
	void GENMWRAP(uint8 V);
	void GENNOMWRAP(uint8 V);

	//mapper 47
	void Reset47();
	void M47PW(uint32 A, uint8 V);
	void M47CW(uint32 A, uint8 V);
	void M47Write(uint16 A, uint8 V);

	//mapper 49
	void Reset49();
	void M49PW(uint32 A, uint8 V);
	void M49CW(uint32 A, uint8 V);
	void M49Write(uint16 A, uint8 V);

	//mapper 52
	void Reset52();
	void M52PW(uint32 A, uint8 V);
	void M52CW(uint32 A, uint8 V);
	void M52Write(uint16 A, uint8 V);
	BYTE M52ReadLow( WORD addr );

	//mapper 121
	void Reset121();
	void M121Sync();
	void M121CW(uint32 A, uint8 V);
	void M121PW(uint32 A, uint8 V);
	void M121Write(uint16 A, uint8 V);
	void M121LoWrite(uint16 A, uint8 V);
	BYTE M121Read(WORD A);

	//mapper 134
	void Reset134();
	void M134PW(uint32 A, uint8 V);
	void M134CW(uint32 A, uint8 V);
	void M134Write(uint16 A, uint8 V);

	//mapper 194
	void M194CW(uint32 A, uint8 V);
	void Reset194();

	//mapper 199
	void Reset199();	
	void M199PW(uint32 A, uint8 V);
	void M199CW(uint32 A, uint8 V);
	void M199MW(uint8 V);
	void M199Write(uint16 A, uint8 V);

	//mapper 205
	void Reset205();
	void M205PW(uint32 A, uint8 V);
	void M205CW(uint32 A, uint8 V);
	void M205Write(uint16 A, uint8 V);

	
	//mapper 217
	uint8 cmdin;
	void Reset217();
	void M217CW(uint32 A, uint8 V);
	void M217PW(uint32 A, uint8 V);
	void M217Write(uint16 A, uint8 V);
	void M217ExWrite(uint16 A, uint8 V);

	//SACHEN_STREETHEROES
	uint8 tekker;
	void MSHCW(uint32 A, uint8 V);
	void MSHWrite(uint16 A, uint8 V);
	BYTE MSHRead(uint16 A);
	void MSHMWRAP(uint8 V);
	void MSHReset();

	//Super 24-in-1
	void Super24Reset();
	void Super24Write(uint16 A, uint8 V);
	void Super24PW(uint32 A, uint8 V);;
	void Super24CW(uint32 A, uint8 V);
	
	//Fk23c
	uint8 unromchr;
	uint32 dipswitch;
	void BMCFK23CCW(uint32 A, uint8 V);
	void BMCFK23CPW(uint32 A, uint8 V);
	void BMCFK23CHiWrite(uint16 A, uint8 V);
	void BMCFK23CWrite(uint16 A, uint8 V);
	void BMCFK23CReset();

	void BMCFK23CAReset();
};
