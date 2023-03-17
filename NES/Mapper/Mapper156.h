//////////////////////////////////////////////////////////////////////////
// Mapper156                                               [K]2023 CHECK//
//////////////////////////////////////////////////////////////////////////

class	Mapper156 : public Mapper
{
public:
	Mapper156( NES* parent ) : Mapper(parent) {}

	void	Reset();
	void	Sync();
	BYTE	ReadLow ( WORD addr );
	void	WriteLow( WORD addr, BYTE data );
	void	Write(WORD addr, BYTE data);
   
protected:
	BYTE chrlo[8], chrhi[8], prg, mirr, mirrisused;
private:
};
