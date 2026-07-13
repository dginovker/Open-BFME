// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Anim2D.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   A collection of 2D images to make animation
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define DEFINE_ANIM_2D_MODE_NAMES
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/Image.h"
#include "GameLogic/GameLogic.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// GLOBAL /////////////////////////////////////////////////////////////////////////////////////////
Anim2DCollection *TheAnim2DCollection = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
// Body in Anim2DTemplate_ctor_dtor.asm (exact 124B retail; BFME AsciiString
// copy-ctor is out-of-line, ours inlines -- AsciiString reconciliation wall).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1Anim2DTemplate@@UAE@XZ
// Body in Anim2DTemplate_ctor_dtor.asm (exact 34B retail; same AsciiString wall).

// ------------------------------------------------------------------------------------------------
/** Field parse table for 2D animation templates */
// ---------i---------------------------------------------------------------------------------------
const FieldParse Anim2DTemplate::s_anim2DFieldParseTable[] = 
{

	{ "NumberImages",					Anim2DTemplate::parseNumImages,			NULL,							0 },
	{ "Image",								Anim2DTemplate::parseImage,					NULL,							0 },
	{ "ImageSequence",				Anim2DTemplate::parseImageSequence, NULL,							0 },
	{ "AnimationMode",				INI::parseIndexList,								Anim2DModeNames,	offsetof( Anim2DTemplate, m_animMode ) },
	{ "AnimationDelay",				INI::parseDurationUnsignedShort,		NULL,							offsetof( Anim2DTemplate, m_framesBetweenUpdates ) },
	{ "RandomizeStartFrame",	INI::parseBool,											NULL,							offsetof( Anim2DTemplate, m_randomizeStartFrame ) },
	{ NULL,										NULL,																NULL,							0 }

};

// ------------------------------------------------------------------------------------------------
/** Parse the number of images we will have in this animation and allocate the array for them */
// ------------------------------------------------------------------------------------------------
// ?parseNumImages@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// Body in Anim2DTemplate_parse_walls.asm (exact 158B retail; BFME keeps the
// INI error-crash path in release, ours strips DEBUG_CRASH).

// ------------------------------------------------------------------------------------------------
/** Allocate the image array for an animation template and store the number of frames we have */
// ------------------------------------------------------------------------------------------------
void Anim2DTemplate::allocateImages( UnsignedShort numFrames )
{

	// store the number of frames
	m_numFrames = numFrames;

	// allocate an array to hold the image pointers
	m_images = NEW const Image *[ m_numFrames ];	// pool[]ify

	// set all the images to NULL;
	for( Int i = 0; i < m_numFrames; ++i )
		m_images[ i ] = NULL;

}  // end allocateImages

// ------------------------------------------------------------------------------------------------
/** Parsing a single image definition for an animation */
// ------------------------------------------------------------------------------------------------
void Anim2DTemplate::parseImage( INI *ini, void *instance, void *store, const void *userData )
{

	// parse the image name from the file and store as an image pointer
	const Image *image;
	ini->parseMappedImage( ini, instance, &image, userData );

	// sanity
	if( image == NULL )
	{

		//We don't care if we're in the builder
		//DEBUG_CRASH(( "Anim2DTemplate::parseImage - Image not found\n" ));
		//throw INI_INVALID_DATA;

	}  // end if

	//
	// assign the image to the animation template list of images ... note since we've pre-allocated
	// the array of images and the index an image is loaded into depends on its order specified
	// in INI, we need to get the number of images currently loaded into this animation template
	// so that we can put it at the next free image spot ... and then tell the animation 
	// template we've loaded one more
	//
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	animTemplate->storeImage( image );

}  // end parseImage

// ------------------------------------------------------------------------------------------------
/** This will parse the image sequence of an animation.  You can use this as a shortcut to
	* specifying a series of images for an animation instead of having to specify them all
	* individually.  Image names will be assumed to start with an appended "000" to the end
	* end of the first image name and incremented up to the number of images for the 
	* animation.  NOTE: That the number images *must* have already been specified before
	* we can parse this entry so we know how many images to allocate and look for */
// ------------------------------------------------------------------------------------------------
// ?parseImageSequence@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// Body in Anim2DTemplate_parse_walls.asm (exact 381B retail; same release-crash wall).

// ------------------------------------------------------------------------------------------------
/** Store the image at the next open image slot for the animation */
// ------------------------------------------------------------------------------------------------
// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z
// Body in Anim2DTemplate_parse_walls.asm (exact 201B retail; same release-crash wall).

// ------------------------------------------------------------------------------------------------
/** Return the Image* for the frame number requested */
// ------------------------------------------------------------------------------------------------
const Image* Anim2DTemplate::getFrame( UnsignedShort frameNumber ) const
{ 

	// sanity
	DEBUG_ASSERTCRASH( m_images != NULL, 
										 ("Anim2DTemplate::getFrame - Image data is NULL for animation '%s'\n",
										  getName().str()) );
	
	// sanity										
	if( frameNumber < 0 || frameNumber >= m_numFrames )
	{
		
		DEBUG_CRASH(( "Anim2DTemplate::getFrame - Illegal frame number '%d' for animation '%s'\n",
									frameNumber, getName().str() ));
		return NULL;

	}  // end if
	else
	{

		// return the image frame
		return m_images[ frameNumber ];

	}  // end else

}  // end getFrame

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z
// Body in Anim2D_ctor.asm (exact 297B retail; retail inlines reset()
// and registerAnimation() and writes BFME-only cached fields +0x2c/+0x30).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1Anim2D@@MAE@XZ present-unmatched
Anim2D::~Anim2D( void )
{

	// if we were registered with a system, un-register ourselves
	if( m_collectionSystem )
		m_collectionSystem->unRegisterAnimation( this );

}  // end ~Anim2D

// ------------------------------------------------------------------------------------------------
/** Set the current animation frame */
// ------------------------------------------------------------------------------------------------
void Anim2D::setCurrentFrame( UnsignedShort frame )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	// sanity
	DEBUG_ASSERTCRASH( TheGameLogic != NULL,	
										 ("Anim2D::setCurrentFrame - TheGameLogic must exist to use animation instances (%s)\n",
										  m_template->getName().str()) );

	// sanity
	DEBUG_ASSERTCRASH( frame >= 0 && frame < m_template->getNumFrames(),
										 ("Anim2D::setCurrentFrame - Illegal frame number '%d' in animation\n", 
										 frame, m_template->getName().str()) );

	// set the frame
	m_currentFrame = frame;

	// record the frame of this update to our current frame
	m_lastUpdateFrame = TheGameClient->getFrame();

}  // end setCurrentFrame

// ------------------------------------------------------------------------------------------------
/** Randomize the current frame */
// ------------------------------------------------------------------------------------------------
#line 424 "F:\\\\bfme\\\\Code\\\\gameengine\\\\Source\\\\GameClient\\\\System\\\\Anim2D.cpp"
void Anim2D::randomizeCurrentFrame( void )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	// set the current frame to a random frame
	setCurrentFrame( GameClientRandomValue( 0, m_template->getNumFrames() - 1 ) );

}  // end randomizeCurrentFrame

// ------------------------------------------------------------------------------------------------
/** Reset this animation instance to the "start" of the animation */
// ------------------------------------------------------------------------------------------------
void Anim2D::reset( void )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	switch( m_template->getAnimMode() )
	{

		// --------------------------------------------------------------------------------------------
		case ANIM_2D_ONCE:
		case ANIM_2D_LOOP:
		case ANIM_2D_PING_PONG:
			setCurrentFrame( m_minFrame );
			break;

		// --------------------------------------------------------------------------------------------
		case ANIM_2D_ONCE_BACKWARDS:
		case ANIM_2D_LOOP_BACKWARDS:
		case ANIM_2D_PING_PONG_BACKWARDS:
			setCurrentFrame( m_maxFrame );
			break;

		// --------------------------------------------------------------------------------------------
		default:
			DEBUG_CRASH(( "Anim2D::reset - Unknown animation mode '%d' for '%s'\n",
										m_template->getAnimMode(), m_template->getName().str() ));
			break;

	}  // end switch, animation mode

}  // end reset

// ------------------------------------------------------------------------------------------------
/** This is called after we are drawn ... if sufficient time has passed since our last
	* frame update we will update our current frame */
// ------------------------------------------------------------------------------------------------
void Anim2D::tryNextFrame( void )
{

	// sanity
	DEBUG_ASSERTCRASH( TheGameLogic != NULL,	
										 ("Anim2D::tryNextFrame - TheGameLogic must exist to use animation instances (%s)\n",
										  m_template->getName().str()) );

	// how many frames have passed since our last update
	if( TheGameClient->getFrame() - m_lastUpdateFrame >= m_framesBetweenUpdates )
	{

		switch( m_template->getAnimMode() )
		{

			// ------------------------------------------------------------------------------------------
			case ANIM_2D_ONCE:
			{

				if( m_currentFrame < m_maxFrame )
					setCurrentFrame( m_currentFrame + 1 );
				else
					setStatus( ANIM_2D_STATUS_COMPLETE );
				break;

			}  // end once

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_ONCE_BACKWARDS:
			{

				if( m_currentFrame > m_minFrame )
					setCurrentFrame( m_currentFrame - 1 );
				else
					setStatus( ANIM_2D_STATUS_COMPLETE );
				break;

			}  // end once backwards

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_LOOP:
			{

				if( m_currentFrame == m_maxFrame )
					setCurrentFrame( m_minFrame );
				else
					setCurrentFrame( m_currentFrame + 1 );
				break;

			}  // end loop

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_LOOP_BACKWARDS:
			{

				if( m_currentFrame > m_minFrame )
					setCurrentFrame( m_currentFrame - 1 );
				else
					setCurrentFrame( m_maxFrame );
				break;
			
			}  // end loop backwards
				
			// -------------------------------------------------------------------------------------------
			case ANIM_2D_PING_PONG:
			case ANIM_2D_PING_PONG_BACKWARDS:
			{

				if( BitTest( m_status, ANIM_2D_STATUS_REVERSED ) )
				{
					//
					// decrement frame, unless we're at frame 0 in which case we
					// increment and reverse directions
					//
					if( m_currentFrame == m_minFrame )
					{

						setCurrentFrame( m_currentFrame + 1 );
						clearStatus( ANIM_2D_STATUS_REVERSED );

					}  // end if
					else
					{

						setCurrentFrame( m_currentFrame - 1 );

					}  // end else

				}  // end if
				else
				{

					//
					// increment frame, unless we're at the end in which case we decrement
					// and reverse directions
					//
					if( m_currentFrame == m_maxFrame )
					{

						setCurrentFrame( m_currentFrame - 1 );
						setStatus( ANIM_2D_STATUS_REVERSED );

					}  // end if
					else
					{

						setCurrentFrame( m_currentFrame + 1 );

					}  // end else

				}  // end else

				break;

			}  // end ping pong / ping pong backwards

			// -------------------------------------------------------------------------------------------
			default:
			{

				DEBUG_CRASH(( "Anim2D::tryNextFrame - Unknown animation mode '%d' for '%s'\n",
											m_template->getAnimMode(), m_template->getName().str() ));
				break;

			}  // end default
							
		}  // end switch

	}  // end if

}  // end tryNextFrame

// ------------------------------------------------------------------------------------------------
/** Set status bit */
// ------------------------------------------------------------------------------------------------
void Anim2D::setStatus( UnsignedByte statusBits )
{

	// set the bits
	BitSet( m_status, statusBits );

}  // end setStatus

// ------------------------------------------------------------------------------------------------
/** Clear status bit */
// ------------------------------------------------------------------------------------------------
void Anim2D::clearStatus( UnsignedByte statusBits )
{

	// clear bits
	BitClear( m_status, statusBits );

}  // end clearStatus

// ------------------------------------------------------------------------------------------------
/** Return the "natural" width of the image for our current frame */
// ------------------------------------------------------------------------------------------------
UnsignedInt Anim2D::getCurrentFrameWidth( void ) const
{
	const Image *currentFrameImage = m_template->getFrame( m_currentFrame );

	if( currentFrameImage )
		return currentFrameImage->getImageWidth();
	
	return 0;

}  // end getCurrentFrameWidth

// ------------------------------------------------------------------------------------------------
/** Return the "natural" height of the image for our current frame */
// ------------------------------------------------------------------------------------------------
UnsignedInt Anim2D::getCurrentFrameHeight( void ) const
{
	const Image *currentFrameImage = m_template->getFrame( m_currentFrame );

	if( currentFrameImage )
		return currentFrameImage->getImageHeight();
	
	return 0;

}  // end getCurrentFrameHeight

// ------------------------------------------------------------------------------------------------
/** Draw an Anim2D using the natural width and height of the image data */
// ------------------------------------------------------------------------------------------------
void Anim2D::draw( Int x, Int y )
{

	// get the current image
	const Image *image = m_template->getFrame( m_currentFrame );

	// sanity
	DEBUG_ASSERTCRASH( image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
										 m_currentFrame, m_template->getName().str()) );

	// get the natural width and height of this image
	const ICoord2D *imageSize = image->getImageSize();

	// draw the image
	Color color = GameMakeColor( 255, 255, 255, 255 * m_alpha );
	TheDisplay->drawImage( image, x, y, x + imageSize->x, y + imageSize->y, color );

	//
	// see if it's time for us to go to the next frame in the sequence, we do not update
	// frame numbers for animation instances that are registered with a system as the
	// system will update them during its update phase
	//
 	if( m_collectionSystem == NULL && BitTest( m_status, ANIM_2D_STATUS_FROZEN ) == FALSE )
		tryNextFrame();

}  // end draw

// ------------------------------------------------------------------------------------------------
/** Drawing an Anim2D using a forced width and height */
// ------------------------------------------------------------------------------------------------
// ?draw@Anim2D@@ present-unmatched
void Anim2D::draw( Int x, Int y, Int width, Int height )
{

	// get the current image
	const Image *image = m_template->getFrame( m_currentFrame );
	
	// sanity
	DEBUG_ASSERTCRASH( image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
										 m_currentFrame, m_template->getName().str()) );


	// draw image to the display
	Color color = GameMakeColor( 255, 255, 255, 255 * m_alpha );
	TheDisplay->drawImage( image, x, y, x + width, y + height, color );

	//
	// see if it's time for us to go to the next frame in the sequence, we do not update
	// frame numbers for animation instances that are registered with a system as the
	// system will update them during its update phase
	//
 	if( m_collectionSystem == NULL && BitTest( m_status, ANIM_2D_STATUS_FROZEN ) == FALSE )
		tryNextFrame();

}  // end draw

// ------------------------------------------------------------------------------------------------
/** Xfer Method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@Anim2D@@MAEXPAVXfer@@@Z present-unmatched
void Anim2D::xfer( Xfer *xfer )
{
	
	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// current frame
	xfer->xferUnsignedShort( &m_currentFrame );

	// last update frame
	xfer->xferUnsignedInt( &m_lastUpdateFrame );

	// status
	xfer->xferUnsignedByte( &m_status );

	// min frame
	xfer->xferUnsignedShort( &m_minFrame );

	// max frame
	xfer->xferUnsignedShort( &m_maxFrame );

	// frames between updates
	xfer->xferUnsignedInt( &m_framesBetweenUpdates );

	// alpha
	xfer->xferReal( &m_alpha );

}  // end xfer

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Anim2DCollection::Anim2DCollection( void )
{

	m_templateList = NULL;
	m_instanceList = NULL;
}  // end Anim2DCollection

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Anim2DCollection::~Anim2DCollection( void )
{

	// there should not be any animation instances registered with us since we're being destroyed
	DEBUG_ASSERTCRASH( m_instanceList == NULL, ("Anim2DCollection - instance list is not NULL\n") );

	// delete all the templates
	Anim2DTemplate *nextTemplate;
	while( m_templateList )
	{

		// get next template
		nextTemplate = m_templateList->friend_getNextTemplate();

		// delete this template
		delete m_templateList;  // BFME: no memory pool for Anim2DTemplate

		// set the head of our list to the next template
		m_templateList = nextTemplate;

	}  // end while

}  // end ~Anim2DCollection

// ------------------------------------------------------------------------------------------------
/** Initialize 2D animation collection */
// ------------------------------------------------------------------------------------------------
// ?init@Anim2DCollection@@UAEXXZ present-unmatched
void Anim2DCollection::init( void )
{
	INI ini;

	ini.load( "Data\\INI\\Animation2D.ini", INI_LOAD_OVERWRITE, NULL );

}  // end init

// ------------------------------------------------------------------------------------------------
/** System update phase */
// ------------------------------------------------------------------------------------------------
void Anim2DCollection::update( void )
{
	Anim2D *anim;

	// go through all our animations
	for( anim = m_instanceList; anim; anim = anim->m_collectionSystemNext )
	{

		// try to update the frame
		if( BitTest( anim->getStatus(), ANIM_2D_STATUS_FROZEN ) == FALSE )	
			anim->tryNextFrame();

	}  // end for, anim

}  // end update

// ------------------------------------------------------------------------------------------------
/** Search the template list for a template with a matching name */
// ------------------------------------------------------------------------------------------------
// ?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
// Body in Anim2DCollection_walls.asm (exact 155B retail; BFME AsciiString
// compare with TheEmptyString fallback -- AsciiString reconciliation wall).

//-------------------------------------------------------------------------------------------------
Anim2DTemplate* Anim2DCollection::getNextTemplate( Anim2DTemplate *animTemplate ) const
{
	if( animTemplate )
	{
		return animTemplate->friend_getNextTemplate();
	}
	return NULL;
}

// ------------------------------------------------------------------------------------------------
/** Allocate a new template, assign name, and link to our internal list */
// ------------------------------------------------------------------------------------------------
// ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
// Body in Anim2DCollection_walls.asm (exact 106B retail; by-value AsciiString
// arg copy is out-of-line in BFME -- AsciiString reconciliation wall).

// ------------------------------------------------------------------------------------------------
/** Register animation instance with us.  When an animation instance is registered it can
	* be updated even when it's not drawn */
// ------------------------------------------------------------------------------------------------
void Anim2DCollection::registerAnimation( Anim2D *anim )
{

	// sanity
	if( anim == NULL )
		return;

	// sanity
	DEBUG_ASSERTCRASH( anim->m_collectionSystemNext == NULL &&
										 anim->m_collectionSystemPrev == NULL,
										 ("Registering animation instance, instance '%s' is already in a system\n",
										 anim->getAnimTemplate()->getName().str()) );

	// tie to our list
	anim->m_collectionSystemPrev = NULL;
	anim->m_collectionSystemNext = m_instanceList;
	if( m_instanceList )
		m_instanceList->m_collectionSystemPrev = anim;
	m_instanceList = anim;

}  // end registerAnimation

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void Anim2DCollection::unRegisterAnimation( Anim2D *anim )
{

	// sanity
	if( anim == NULL )
		return;

	// if animation is not registered with us do nothing
	if( anim->m_collectionSystem != this )
		return;

	// unlink from our instnace list
	if( anim->m_collectionSystemNext )
		anim->m_collectionSystemNext->m_collectionSystemPrev = anim->m_collectionSystemPrev;
	if( anim->m_collectionSystemPrev )
		anim->m_collectionSystemPrev->m_collectionSystemNext = anim->m_collectionSystemNext;
	else
		m_instanceList = anim->m_collectionSystemNext;

}  // end unRegisterAnimation

