/* -*-c++-*- 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.

   Authors:

   Jeremy Moles  <jeremy@emperorlinux.com>
   Cedric Pinson <mornifle@plopbyte.net>
*/

#ifndef ANIMTKVIEWERGUI_H
#define ANIMTKVIEWERGUI_H

#include <osgWidget/WindowManager>

class AnimtkViewerGUI: public osgWidget::WindowManager {
    osg::ref_ptr<osgWidget::Box> _buttonBox;
    osg::ref_ptr<osgWidget::Box> _listBox;
    osg::ref_ptr<osgWidget::Box> _labelBox;

protected:
    osgWidget::Widget* _createButton(const std::string&);
    
    bool _buttonPush(osgWidget::Event&);
    bool _listMouseHover(osgWidget::Event&);

    void _createButtonBox();
    void _createListBox();
    void _createLabelBox();

public:
    AnimtkViewerGUI(osgViewer::View*, float, float, unsigned int);
};

#endif
