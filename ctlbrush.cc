/*
 *  Copyright (c) 2008 Cyrille Berger (cberger@cberger.net)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "ctlbrush.h"

#include <stdlib.h>

#include <QTimer>

#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kis_debug.h>
#include <kgenericfactory.h>
#include <klocale.h>
#include <kstandarddirs.h>

#include <KoDockFactory.h>

#include "kis_config.h"
#include "kis_cursor.h"
#include "kis_global.h"
#include "kis_types.h"
#include "kis_view2.h"

#include "ctlbrush_dock.h"

typedef KGenericFactory<CTLBrushPlugin> CTLBrushPluginFactory;
K_EXPORT_COMPONENT_FACTORY( kritactlbrush, CTLBrushPluginFactory( "krita" ) )

class CTLBrushDockFactory : public KoDockFactory {
public:
    CTLBrushDockFactory(KisView2 * view)
        : m_view( view )
    {
    }

    virtual QString id() const
    {
        return QString( "CTLBrush" );
    }

    virtual Qt::DockWidgetArea defaultDockWidgetArea() const
    {
        return Qt::RightDockWidgetArea;
    }

    virtual QDockWidget* createDockWidget()
    {
        CTLBrushDock * dockWidget = new CTLBrushDock(m_view);
        
        dockWidget->setObjectName(id());

        return dockWidget;
    }

private:
    KisView2 * m_view;

};


CTLBrushPlugin::CTLBrushPlugin(QObject *parent, const QStringList &)
    : KParts::Plugin(parent)
{
    dbgPlugins << "CTLBrushPlugin";
    if ( parent->inherits("KisView2") )
    {
        m_view = (KisView2*) parent;

        setComponentData(CTLBrushPluginFactory::componentData());
        CTLBrushDockFactory dockFactory( m_view);
        m_view->createDockWidget( &dockFactory );
    }
}

CTLBrushPlugin::~CTLBrushPlugin()
{
    m_view = 0;
}

#include "ctlbrush.moc"
