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

#ifndef _CTLBRUSH_DOCK_H_
#define _CTLBRUSH_DOCK_H_

#include <QDockWidget>

namespace OpenCTL {
  class Module;
};

class KisView2;
class Ui_CTLBrushEditor;
class KoResource;

class CTLBrushDock : public QDockWidget {
  Q_OBJECT
  public:
    CTLBrushDock( KisView2 *view );
  public slots:
    void slotCreateBrush();
signals:
    void activatedResource(KoResource *r);
private:
    KisView2* m_view;
    Ui_CTLBrushEditor* m_ctlBrushEditor;
    OpenCTL::Module* m_module;
};


#endif
