//////////////////////////////////////////////////////////////////////////
// Mapper177  HengGe                                                    //
//////////////////////////////////////////////////////////////////////////
void    Mapper177::Reset()
{
	reg=0;
	Sync(); 
}

void Mapper177::Sync()
{
  SetVROM_8K_Bank(0);
  //setprg8r(0x10,0x6000,0);
  SetPROM_32K_Bank(reg&0x1f);
  SetVRAM_Mirror(((reg&0x20)>>5)^1);
}

void	Mapper177::Write( WORD addr, BYTE data )
{
  reg=data;
  Sync();
}