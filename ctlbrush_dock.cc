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

#include "ctlbrush_dock.h"


#include <kis_view2.h>
#include "kis_canvas_resource_provider.h"

#include <QLabel>

#include "ui_CTLBrushEditor.h"

#include <OpenCTL/Module.h>

#include "kis_ctl_brush.h"

CTLBrushDock::CTLBrushDock( KisView2 *view ) : QDockWidget(i18n("CTLBrush")), m_view(view), m_ctlBrushEditor(new Ui_CTLBrushEditor), m_module(new OpenCTL::Module("CTLBrush"))
{
  QWidget* wdg = new QWidget(this);
  m_ctlBrushEditor->setupUi(wdg);
  connect(m_ctlBrushEditor->createButton, SIGNAL(released()), SLOT(slotCreateBrush()));
  setWidget( wdg );
  connect(this, SIGNAL(activatedResource(KoResource*)),
            m_view->resourceProvider(),
            SLOT(slotBrushActivated( KoResource* )));
}

void CTLBrushDock::slotCreateBrush()
{
  dbgPlugins << "slotCreateBrush";
  m_module->setSource( m_ctlBrushEditor->sourceEditor->toPlainText().toAscii().data());
  m_module->compile();
  if( not m_module->isCompiled() )
  {
//     dbgPlugins << m_module->compilationError().c_str();
    return;
  }
  const OpenCTL::Function* function = m_module->function("valueAt");
  if(not function)
  {
    dbgPlugins << "no function valueAt";
    return;
  }
  emit(activatedResource(new KisCTLBrush( m_ctlBrushEditor->width->value(),m_ctlBrushEditor->height->value(),  function)));
}

#include "ctlbrush_dock.moc"
