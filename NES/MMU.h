//////////////////////////////////////////////////////////////////////////
//                                                                      //
//      NES Memory Management Unit                                      //
//                                                           Norix      //
//                                               written     2001/02/21 //
//                                               last modify 2017/--/-- //
//////////////////////////////////////////////////////////////////////////

#ifndef	__MMU_INCLUDED__
#define	__MMU_INCLUDED__

#include "typedef.h"
#include "macro.h"

extern	BYTE	nnn;

// CPU �������o���N
extern  BYTE	CPU_BACKUP[256];
extern	LPBYTE	CPU_MEM_BANK[8];	// 8K�P��
extern	BYTE	CPU_MEM_TYPE[8];
extern	INT	CPU_MEM_PAGE[8];	// �X�e�[�g�Z�[�u�p

// PPU �������o���N
extern	LPBYTE	PPU_MEM_BANK[12];	// 1K�P��
extern	BYTE	PPU_MEM_TYPE[12];
extern	INT	PPU_MEM_PAGE[12];	// �X�e�[�g�Z�[�u�p
extern	BYTE	CRAM_USED[16];		// �X�e�[�g�Z�[�u�p
extern	PBYTE	VROM_WRITED;		// for mapper 74

// NES������
extern	BYTE	RAM [  8*1024];		// NES����RAM
extern	BYTE	WRAM[128*1024];		// ���[�N/�o�b�N�A�b�vRAM
extern	BYTE	DRAM[ 40*1024];		// �f�B�X�N�V�X�e��RAM
extern	BYTE	XRAM[  8*1024];		// �_�~�[�o���N
extern	BYTE	ERAM[ 32*1024];		// �g���@��pRAM
extern  BYTE	MRAM[128*1024];		//byemu

extern	BYTE	CRAM[ 32*1024];		// �L�����N�^�p�^�[��RAM
extern	BYTE	VRAM[  4*1024];		// �l�[���e�[�u��/�A�g���r���[�gRAM

extern	BYTE	YWRAM[1024*1024];	// for YuXing 98/F 1024K PRam
extern	BYTE	YSRAM[  32*1024];	// for YuXing 98/F 32K SRam
extern	BYTE	YCRAM[ 128*1024];	// for YuXing 98/F 128K CRam

extern	BYTE	BDRAM[ 512*1024];	// for BBK 512K PRam
extern	BYTE	BSRAM[  32*1024];	// for BBK 32K SRam
extern	BYTE	BCRAM[ 512*1024];	// for BBK 512K CRam

extern	BYTE	JDRAM[ 512*1024];	// for DrPCJr 512K PRam
extern	BYTE	JSRAM[   8*1024];	// for DrPCJr 8K SRam
extern	BYTE	JCRAM[ 512*1024];	// for DrPCJr 512K CRam

extern	BYTE	tempRAM[ 4*1024];

extern	BYTE	WAVRAM[256];


extern	BYTE	SPRAM[0x100];		// �X�v���C�gRAM
extern	BYTE	BGPAL[0x10];		// BG�p���b�g
extern	BYTE	SPPAL[0x10];		// SP�p���b�g

// ���W�X�^
extern	BYTE	CPUREG[0x18];		// Nes $4000-$4017
extern	BYTE	PPUREG[0x04];		// Nes $2000-$2003

// Frame-IRQ���W�X�^($4017)
extern	BYTE	FrameIRQ;

// PPU�������W�X�^
extern	BYTE	PPU56Toggle;		// $2005-$2006 Toggle
extern	BYTE	PPU7_Temp;		// $2007 read buffer
extern	WORD	loopy_t;		// same as $2005/$2006
extern	WORD	loopy_v;		// same as $2005/$2006
extern	WORD	loopy_x;		// tile x offset

// ROM�f�[�^�|�C���^
extern	LPBYTE	PROM;		// PROM ptr
extern	LPBYTE	VROM;		// VROM ptr

extern LPBYTE	PROMPTR[16];
extern LPBYTE	VROMPTR[16];

extern INT PPROM_8K_SIZE[16];
extern INT PVROM_1K_SIZE[16];

#ifdef	_DATATRACE
// For dis...
extern	LPBYTE	PROM_ACCESS;
#endif

// ROM �o���N�T�C�Y
extern	INT	PROM_8K_SIZE, PROM_16K_SIZE, PROM_32K_SIZE;
extern	INT	VROM_1K_SIZE, VROM_2K_SIZE, VROM_4K_SIZE,  VROM_8K_SIZE;


// �֐�
extern	void	NesSub_MemoryInitial();

//add
//extern	void	SetPrg2 ( WORD A, INT bank );
//extern	void	SetPrg4 ( WORD A, INT bank );
extern	void	SetPrg8 ( WORD A, WORD bank );
extern	void	SetPrg16( WORD A, WORD bank );
extern	void	SetPrg32( WORD A, WORD bank );

//extern	void	SetPrg2r (int r, WORD A, INT bank);
//extern	void	SetPrg4r (int r, WORD A, INT bank);
extern	void	SetPrg8r (int r, WORD A, WORD bank);
extern	void	SetPrg16r(int r, WORD A, WORD bank);
extern	void	SetPrg32r(int r, WORD A, WORD bank);

extern	void	SetPROM_Bank( BYTE page, LPBYTE ptr, BYTE type );
extern	void	SetPROM_8K_Bank ( BYTE page, INT bank );
extern	void	SetPROM_16K_Bank( BYTE page, INT bank );
extern	void	SetPROM_32K_Bank( INT bank );
extern	void	SetPROM_32K_Bank( INT bank0, INT bank1, INT bank2, INT bank3 );

extern	void	SetVROM_Bank( BYTE page, LPBYTE ptr, BYTE type );
extern	void	SetVROM_1K_Bank( BYTE page, INT bank );
extern	void	SetVROM_2K_Bank( BYTE page, INT bank );
extern	void	SetVROM_4K_Bank( BYTE page, INT bank );
extern	void	SetVROM_8K_Bank( INT bank );
extern	void	SetVROM_8K_Bank( INT bank0, INT bank1, INT bank2, INT bank3,
				 INT bank4, INT bank5, INT bank6, INT bank7 );

extern	void	SetChr1( WORD A, INT bank );
extern	void	SetChr2( WORD A, INT bank );
extern	void	SetChr4( WORD A, INT bank );
extern	void	SetChr8( WORD A, INT bank );
extern	void	SetChr1r(int r, WORD A, INT bank);
extern	void	SetChr2r(int r, WORD A, INT bank);
extern	void	SetChr4r(int r, WORD A, INT bank);
extern	void	SetChr8r(int r, WORD A, INT bank);

extern	void	SetCRAM_1K_Bank( BYTE page, INT bank );
extern	void	SetCRAM_2K_Bank( BYTE page, INT bank );
extern	void	SetCRAM_4K_Bank( BYTE page, INT bank );
extern	void	SetCRAM_8K_Bank( INT bank );

extern	void	SetVRAM_1K_Bank( BYTE page, INT bank );
extern	void	SetVRAM_Bank( INT bank0, INT bank1, INT bank2, INT bank3 );
extern	void	SetVRAM_Mirror( INT type );
extern	void	SetVRAM_Mirror( INT bank0, INT bank1, INT bank2, INT bank3 );

// for YuXing 98/F 1024K PRam
extern	void	SetYWRAM_8K_Bank ( BYTE page, INT bank );
extern	void	SetYWRAM_16K_Bank( BYTE page, INT bank );
extern	void	SetYWRAM_32K_Bank( INT bank );
extern	void	SetYWRAM_32K_Bank( INT bank0, INT bank1, INT bank2, INT bank3 );
// for YuXing 98/F 128K CRam
extern	void	SetYCRAM_1K_Bank( BYTE page, INT bank );
extern	void	SetYCRAM_2K_Bank( BYTE page, INT bank );
extern	void	SetYCRAM_4K_Bank( BYTE page, INT bank );
extern	void	SetYCRAM_8K_Bank( INT bank );

extern	void	SetBDRAM_8K_Bank( BYTE page, INT bank );
extern	void	SetBDRAM_16K_Bank( BYTE page, INT bank );
extern	void	SetBDRAM_32K_Bank( INT bank );

extern	void	SetPROM_4K_Bank( WORD addr, INT bank );

extern	void	SetJCRAM_1K_Bank( BYTE page, INT bank );
extern	void	SetJCRAM_2K_Bank( BYTE page, INT bank );
extern	void	SetJCRAM_4K_Bank( BYTE page, INT bank );
extern	void	SetJCRAM_8K_Bank( INT bank );
extern	void	SetJCRAM_8K_Bank( INT bank0, INT bank1, INT bank2, INT bank3,
				 INT bank4, INT bank5, INT bank6, INT bank7 );
extern	void	SetJDRAM_8K_Bank ( BYTE page, INT bank );
extern	void	SetJDRAM_32K_Bank( INT bank );

extern	void	SetOBCRAM_1K_Bank( BYTE page, INT bank );


// �������^�C�v
// For PROM (CPU)
#define	BANKTYPE_ROM	0x00
#define	BANKTYPE_RAM	0xFF
#define	BANKTYPE_DRAM	0x01
#define	BANKTYPE_MAPPER	0x80
// For VROM/VRAM/CRAM (PPU)
#define	BANKTYPE_VROM	0x00
#define	BANKTYPE_CRAM	0x01
#define	BANKTYPE_YCRAM	0x02
#define	BANKTYPE_JCRAM	0x03
#define	BANKTYPE_VRAM	0x80

// �~���[�^�C�v
#define	VRAM_HMIRROR	0x00	// Horizontal
#define	VRAM_VMIRROR	0x01	// Virtical
#define	VRAM_MIRROR4	0x02	// All screen
#define	VRAM_MIRROR4L	0x03	// PA10 L�Œ� $2000-$23FF�̃~���[
#define	VRAM_MIRROR4H	0x04	// PA10 H�Œ� $2400-$27FF�̃~���[
#define	VRAM_MIRROR3H	0x05

#endif	// !__MMU_INCLUDED__

