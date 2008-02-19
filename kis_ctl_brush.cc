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
#include <OpenCTL/Value.h>

#include <kis_paint_device.h>

KisCTLBrush::KisCTLBrush(int width, int height, const OpenCTL::Function* f) : KisBrush(""), m_function(f)
{
  QImage img( width, height, QImage::Format_RGB32);
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
  Q_UNUSED(subPixelX);
  Q_UNUSED(subPixelY);

    // Generate the paint device from the mask
  const KoColorSpace* cs = dst->colorSpace();
    
  int dstWidth = maskWidth(scaleX, angle);
  int dstHeight = maskHeight(scaleY, angle);
    
    // Apply the alpha mask
    
  std::vector<OpenCTL::Value> params;
  params.push_back( OpenCTL::Value( 0 ) );
  params.push_back( OpenCTL::Value( 0 ) );
  params.push_back( OpenCTL::Value( dstWidth ) );
  params.push_back( OpenCTL::Value( dstHeight ) );
  KisHLineIteratorPixel hiter = dst->createHLineIterator(0, 0, dstWidth);
  for (int y = 0; y < dstHeight; y++)
  {
    params[1].setInt(y);
    while(! hiter.isDone())
    {
      params[0].setInt( hiter.x() );
      OpenCTL::Value v = m_function->call( params );
      
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
