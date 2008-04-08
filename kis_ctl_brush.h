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

#ifndef _KIS_CTL_BRUSH_H_
#define _KIS_CTL_BRUSH_H_

#include "kis_brush.h"

namespace GTLCore {
  class Function;
};

class KisCTLBrush : public KisBrush
{
  public:
    KisCTLBrush(int width, int height, const GTLCore::Function* );
    virtual ~KisCTLBrush();
  public:
    virtual void generateMask(KisPaintDeviceSP dst, KisBrush::ColoringInformation* src, double scaleX, double scaleY, double angle, const KisPaintInformation& info = KisPaintInformation(), double subPixelX = 0, double subPixelY = 0) const;
  public:
    virtual bool load() { return false; }
    virtual void toXML(QDomDocument& , QDomElement&) const;
  private:
    const GTLCore::Function* m_function;
};

#endif
