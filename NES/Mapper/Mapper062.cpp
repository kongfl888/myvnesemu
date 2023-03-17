//////////////////////////////////////////////////////////////////////////
// Mapper062                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper062::Reset()
{
	SetPROM_32K_Bank( 0 );
	SetVROM_8K_Bank( 0 );
}

void	Mapper062::Write( WORD addr, BYTE data )
{	

	//fceu
	SetVROM_8K_Bank(((addr&0x1F)<<2)|(data&0x03));

	if(addr&0x20) {
		SetPROM_16K_Bank(0x8000>>13,(addr&0x40)|((addr>>8)&0x3F));
		SetPROM_16K_Bank(0xc000>>13,(addr&0x40)|((addr>>8)&0x3F));
	}
	else
		SetPROM_32K_Bank(((addr&0x40)|((addr>>8)&0x3F))>>1);
	SetVRAM_Mirror( ((addr&0x80)>>7)^1 );
}

