/***************************************************************************
 *   Copyright (C) 2004 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef THUMBNAILLIST_H
#define THUMBNAILLIST_H

#include <qscrollview.h>
#include <qvaluevector.h>
#include "document.h"

class QTimer;
class KActionCollection;
class KConfigGroup;
class Thumbnail;

class ThumbnailList : public QScrollView, public KPDFDocumentObserver
{
Q_OBJECT
	public:
		ThumbnailList(QWidget *parent, KPDFDocument *document);

		// create actions that interact with this widget and load/save settings
		void setupActions( KActionCollection * collection, KConfigGroup * config );
		void saveSettings( KConfigGroup * config );

		// create thumbnails ( inherited as a DocumentObserver )
		void pageSetup( const QValueList<int> & pages );

		// hilihght current thumbnail ( inherited as DocumentObserver )
		void pageSetCurrent( int pageNumber, float position );

		// redraw thumbnail ( inherited as DocumentObserver )
		void notifyThumbnailChanged( int pageNumber );

	protected:
		// scroll up/down the view
		void keyPressEvent( QKeyEvent * e );

		// select a thumbnail by clicking on it
		void contentsMousePressEvent( QMouseEvent * );

		// resize thumbnails to fit the width
		void viewportResizeEvent( QResizeEvent * );

	public slots:
		// make requests for generating pixmaps for visible thumbnails
		void slotRequestThumbnails( int newContentsX = -1, int newContentsY = -1 );

	private:
		void requestThumbnails( int delayMs = 0 );
		KPDFDocument *m_document;
		Thumbnail *m_selected;
		QTimer *m_delayTimer;
		QValueVector<Thumbnail *> m_thumbnails;
		int m_vectorIndex;
};

#endif
