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

#include "kis_ctl_brush.h"

#include <KoColorSpace.h>

#include <OpenCTL/Function.h>
#include <OpenCTL/Variable.h>

#include <kis_paint_device.h>

KisCTLBrush::KisCTLBrush(const OpenCTL::Function* f) : KisBrush(""), m_function(f)
{
  QImage img(10,10, QImage::Format_RGB32);
  setImage(img);
  setBrushType(MASK);
}
KisCTLBrush::~KisCTLBrush()
{
}

void KisCTLBrush::generateMask(KisPaintDeviceSP dst, KisBrush::ColoringInformation* src, double scaleX, double scaleY, double angle, const KisPaintInformation& info, double subPixelX , double subPixelY ) const
{
  dbgPlugins << "start generating mask";
  Q_UNUSED(info);

    // Generate the paint device from the mask
  const KoColorSpace* cs = dst->colorSpace();
  quint32 pixelSize = cs->pixelSize();
    
  int dstWidth = maskWidth(scaleX, angle);
  int dstHeight = maskHeight(scaleY, angle);
    
    // Apply the alpha mask
    
  KisHLineIteratorPixel hiter = dst->createHLineIterator(0, 0, dstWidth);
  for (int y = 0; y < dstHeight; y++)
  {
    while(! hiter.isDone())
    {
      std::vector<OpenCTL::Variable> params;
      params.push_back( OpenCTL::Variable( hiter.x() ) );
      params.push_back( OpenCTL::Variable( y ) );
      params.push_back( OpenCTL::Variable( dstWidth ) );
      params.push_back( OpenCTL::Variable( dstHeight ) );
      OpenCTL::Variable v = m_function->call( params );
            
      cs->setAlpha( hiter.rawData(), v.asInt(), 1 );
      ++hiter;
    }
    if(src) src->nextRow();
    hiter.nextRow();
  }
  dbgPlugins << "end generating mask";


}



void KisCTLBrush::toXML(QDomDocument& doc, QDomElement& e) const
{
  KisBrush::toXML(doc,e);
//     e.setAttribute( "type", "autobrush" );
//     d->shape->toXML(doc, e);
}
