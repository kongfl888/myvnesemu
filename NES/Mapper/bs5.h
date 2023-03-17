//////////////////////////////////////////////////////////////////////////
// Bs_5                                                  [K]2023 CHECK  //
//////////////////////////////////////////////////////////////////////////
class	Bs_5 : public Mapper
{
public:
	Bs_5( NES* parent ) : Mapper(parent) {}

	void	Reset();
	void	Write( WORD addr, BYTE data );

	// For state save
	BOOL	IsStateSave() { return TRUE; }
	void	SaveState( LPBYTE p );
	void	LoadState( LPBYTE p );

protected:
	BYTE	reg_prg[4], reg_chr[4];
	BYTE	dip_s;
private:
	void	SetBank();
};
