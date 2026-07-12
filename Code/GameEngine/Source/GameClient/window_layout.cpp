// cl: /EHsc
// WindowLayout (Generals GameClient/GUI/WindowLayout.cpp). The original was
// compiled with exception handling; BFME's set(str) wrapper folds strlen of
// the literal into the two-arg set call.
#include "window_layout.h"

WindowLayout::WindowLayout( void )
{
	m_filenameString.set("EmptyLayout", 11);
	m_windowList = 0;
	m_windowTail = 0;
	m_windowCount = 0;
	m_hidden = 0;
	m_init = 0;
	m_update = 0;
	m_shutdown = 0;
}  // end WindowLayout

void WindowLayout::hide( int hide )
{
	GameWindow *window;

	// hide or unhide all windows in this layout
	for( window = m_windowList; window; window = window->winGetNextInLayout() )
	{

		window->winHide( hide );

	}  // end for window

	// save the new visible state of the system
	m_hidden = (char)hide;

}  // end hide

void WindowLayout::addWindow( GameWindow *window )
{
	GameWindow *win = findWindow( window );

	// only add window if window is not in this layout already
	if( win == 0 )
	{

		window->winSetPrevInLayout( 0 );
		window->winSetNextInLayout( m_windowList );
		if( m_windowList )
			m_windowList->winSetPrevInLayout( window );
		m_windowList = window;

		// set layout into window
		window->winSetLayout( this );

		// if no tail pointer, this is it
		if( m_windowTail == 0 )
			m_windowTail = window;

		// we gots another window now
		m_windowCount++;

	}  // end if

}  // end addWindow

void WindowLayout::removeWindow( GameWindow *window )
{
	GameWindow *win = findWindow( window );

	// can't remove window unless it's really part of this layout
	if( win )
	{
		GameWindow *prev, *next;

		prev = win->winGetPrevInLayout();
		next = win->winGetNextInLayout();

		if( next )
			next->winSetPrevInLayout( prev );
		if( prev )
			prev->winSetNextInLayout( next );
		else
			m_windowList = next;

		// set window as having no layout info
		win->winSetLayout( 0 );
		win->winSetNextInLayout( 0 );
		win->winSetPrevInLayout( 0 );

		// if we removed the tail, set the new tail
		if( m_windowTail == win )
			m_windowTail = prev;

		// we lost one sir!
		m_windowCount--;

	}  // end if

}  // end removeWindow

void WindowLayout::bringForward( void )
{
	GameWindow *window, *prev;
	int countLeft = m_windowCount;

	for( window = m_windowTail; countLeft; window = prev )
	{

		prev = window->winGetPrevInLayout();
		window->winBringToTop();
		countLeft--;

	}  // end for window

}  // end bringForward

GameWindow *WindowLayout::findWindow( GameWindow *window )
{
	GameWindow *win;

	for( win = m_windowList; win; win = win->winGetNextInLayout() )
		if( win == window )
			return win;

	return 0;  // window not found

}  // end findWindow

WindowLayout::~WindowLayout( void )
{
}  // end ~WindowLayout

void WindowLayout::destroyWindows( void )
{
	if( this == 0 )
		return;

	GameWindow *window;

	while( 1 )
	{

		window = getFirstWindow();
		if( window == 0 )
			break;

		// remove window from this layout
		removeWindow( window );

		// destroy window in window system
		TheWindowManager->winDestroy( window );

	}  // end while

}  // end destroyWindows
