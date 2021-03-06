/* Copyright (C) 2011 Uni Osnabrück
 * This file is part of the LAS VEGAS Reconstruction Toolkit,
 *
 * LAS VEGAS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LAS VEGAS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 */

/**
 * LVRPoseItem.hpp
 *
 *  @date Feb 17, 2014
 *  @author Thomas Wiemann
 */
#ifndef LVRPOSEITEM_HPP_
#define LVRPOSEITEM_HPP_

#include <QtGui/qtreewidget.h>

#include "../vtkBridge/LVRModelBridge.hpp"

namespace lvr
{

class LVRPoseItem: public QTreeWidgetItem
{
public:
    LVRPoseItem(ModelBridgePtr bridge, QTreeWidgetItem* parent = 0);
    virtual ~LVRPoseItem();

    void setPose(const Pose& pose);
    Pose getPose();

protected:
    Pose m_pose;
    QTreeWidgetItem* m_xItem;
    QTreeWidgetItem* m_yItem;
    QTreeWidgetItem* m_zItem;
    QTreeWidgetItem* m_rItem;
    QTreeWidgetItem* m_tItem;
    QTreeWidgetItem* m_pItem;
};

} /* namespace lvr */

#endif /* LVRPOSEITEM_HPP_ */
