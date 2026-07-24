// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/gamewindow /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// GameWindow field accessors, byte-matched against the reconstructed BFME
// GameWindow layout (reference/shims/gamewindow/GameClient/GameWindow.h). These
// are the retail bodies the incremental-link thunks jump to; each is a single
// field load off the real BFME offset (m_status@0x08, m_instData@0x30, ...).
//
// They live here rather than in GUI/GameWindow.cpp because that TU resolves
// GameClient/GameWindow.h to the ZH-layout reference header (m_instData@0x2c);
// the private /Ireference/shims/gamewindow above makes only this TU see the
// true BFME offsets, so converting these leaves does not disturb GameWindow.cpp.
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"          // GWS_COMBO_BOX
#include "GameClient/GadgetComboBox.h"  // GadgetComboBoxSet*TextColors

// ?winGetInstanceData@GameWindow@@QAEPAVWinInstanceData@@XZ
WinInstanceData *GameWindow::winGetInstanceData( void )
{
	return &m_instData;
}

// ?winGetUserData@GameWindow@@QAEPAXXZ
void *GameWindow::winGetUserData( void )
{
	return m_userData;
}

// ?winGetStatus@GameWindow@@QAEIXZ
UnsignedInt GameWindow::winGetStatus( void )
{
	return m_status;
}

// ?winGetStyle@GameWindow@@QAEIXZ
UnsignedInt GameWindow::winGetStyle( void )
{
	return m_instData.m_style;
}

// ?winGetWindowId@GameWindow@@QAEHXZ
Int GameWindow::winGetWindowId( void )
{
	return m_instData.m_id;
}

// ?winIsHidden@GameWindow@@QAE_NXZ
Bool GameWindow::winIsHidden( void )
{
	return BitTest( m_status, WIN_STATUS_HIDDEN );
}

// Read m_instData.m_owner (@0x44) directly rather than via getOwner(): the inline
// WinInstanceData::getOwner() otherwise emits an out-of-line COMDAT with no ledger
// row. Same bytes.
// ?winGetOwner@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetOwner( void )
{
	return m_instData.m_owner;
}

// The window-list / layout pointer leaves below prove the reconstructed tail
// (m_next@0x1f8, m_prev@0x1fc, m_parent@0x200, m_child@0x204,
//  m_nextLayout@0x208, m_prevLayout@0x20c, m_layout@0x210).

// ?winGetNext@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetNext( void )
{
	return m_next;
}

// ?winGetPrev@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetPrev( void )
{
	return m_prev;
}

// ?winGetParent@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetParent( void )
{
	return m_parent;
}

// ?winGetChild@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetChild( void )
{
	return m_child;
}

// ?winGetNextInLayout@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetNextInLayout( void )
{
	return m_nextLayout;
}

// ?winGetPrevInLayout@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetPrevInLayout( void )
{
	return m_prevLayout;
}

// ?winGetLayout@GameWindow@@QAEPAVWindowLayout@@XZ
WindowLayout *GameWindow::winGetLayout( void )
{
	return m_layout;
}

// ?winGetSize@GameWindow@@QAEHPAH0@Z
Int GameWindow::winGetSize( Int *width, Int *height )
{
	if( width == NULL || height == NULL )
		return WIN_ERR_INVALID_PARAMETER;

	*width  = m_size.x;
	*height = m_size.y;

	return WIN_ERR_OK;
}

// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
Int GameWindow::winGetScreenPosition( Int *x, Int *y )
{
	GameWindow *parent = m_parent;

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	while( parent )
	{
		*x += parent->m_region.lo.x;
		*y += parent->m_region.lo.y;
		parent = parent->m_parent;
	}

	return WIN_ERR_OK;
}

// ?winSetUserData@GameWindow@@QAEXPAX@Z
void GameWindow::winSetUserData( void *userData )
{
	m_userData = userData;
}

// ?winClearStatus@GameWindow@@QAEII@Z
UnsignedInt GameWindow::winClearStatus( UnsignedInt status )
{
	UnsignedInt oldStatus;

	oldStatus = m_status;
	BitClear( m_status, status );

	return oldStatus;
}

// ?winNextTab@GameWindow@@QAEHXZ
Int GameWindow::winNextTab( void )
{
	return WIN_ERR_OK;
}

// ?winPrevTab@GameWindow@@QAEHXZ
Int GameWindow::winPrevTab( void )
{
	return WIN_ERR_OK;
}

// ?winGetEnabledTextBorderColor@GameWindow@@QAEHXZ
Color GameWindow::winGetEnabledTextBorderColor( void )
{
	return m_instData.m_enabledText.borderColor;
}

// ?winSetEnabledTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetEnabledTextColors( Color color, Color borderColor )
{
	m_instData.m_enabledText.color = color;
	m_instData.m_enabledText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetEnabledTextColors( this, color, borderColor );
}

// ?winSetDisabledTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetDisabledTextColors( Color color, Color borderColor )
{
	m_instData.m_disabledText.color = color;
	m_instData.m_disabledText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetDisabledTextColors( this, color, borderColor );
}

// ?winSetHiliteTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetHiliteTextColors( Color color, Color borderColor )
{
	m_instData.m_hiliteText.color = color;
	m_instData.m_hiliteText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetHiliteTextColors( this, color, borderColor );
}

// ?winSetIMECompositeTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetIMECompositeTextColors( Color color, Color borderColor )
{
	m_instData.m_imeCompositeText.color = color;
	m_instData.m_imeCompositeText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetIMECompositeTextColors( this, color, borderColor );
}
