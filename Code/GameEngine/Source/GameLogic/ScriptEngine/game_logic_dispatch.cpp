// cl: /EHsc
// GameLogic dispatch functions. Generals GameLogicDispatch.cpp is the source
// skeleton; BFME drifted (extra guarded hides, background-layout cleanup moved
// here from clearGameData). Reconciled against the binary at 0x396950.
#include "game_logic_dispatch.h"

// ?closeWindows@GameLogic@@QAEXXZ
void GameLogic::closeWindows( void )
{
	HideDiplomacy();
	HideInGameChat();
	ResetInGameChat();
	TheControlBar->hidePurchaseScience();
	TheControlBar->hideSpecialPowerShortcut();

	if (TheQuitMenuWindow)
	{
		HideQuitMenu();
		TheInGameChat->reset();
	}
	if (TheSaveLoadWindow)
	{
		HideSaveLoadMenu();
		TheInGameChat->reset();
	}
	TheWindowManager->reset();

	// hide the options menu
	NameKeyType buttonID = TheNameKeyGenerator->nameToKey( "OptionsMenu.wnd:ButtonBack" );
	GameWindow *button = TheWindowManager->winGetWindowFromId( 0, buttonID );
	GameWindow *window = TheWindowManager->winGetWindowFromId( 0, TheNameKeyGenerator->nameToKey("OptionsMenu.wnd:OptionsMenuParent") );
	if (window)
		TheWindowManager->winSendSystemMsg( window, GBM_SELECTED,
																			(WindowMsgData)button, buttonID );

	if (m_backgroundPending)
	{
		m_backgroundPending = 0;
		if (m_background)
		{
			m_background->destroyWindows();
			delete m_background;
		}
		else
			ReleaseWindowLayout(0);
		m_background = 0;
	}
}
