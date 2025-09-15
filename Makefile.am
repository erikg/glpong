# glpong - opengl/sdl game of the original video game; pong.
# Copyright (C) 2001-2025 Erik Greenwald <erik@elfga.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

SUBDIRS = data src debian

dist_man_MANS = $(PACKAGE).1
EXTRA_DIST=ChangeLog $(PACKAGE).spec Info.plist.in version.plist.in CMakeLists.txt src/CMakeLists.txt

.PHONY : rpm deb bundle packages doc
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz ${HOME}/rpm/SOURCES/
	rpmbuild -ba $(PACKAGE).spec
	cp ${HOME}/rpm/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp ${HOME}/rpm/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

deb: dist
	rm -rf $(PACKAGE)-$(VERSION)
	tar zxvf $(PACKAGE)-$(VERSION).tar.gz
	(cd $(PACKAGE)-$(VERSION) && fakeroot debian/rules binary)
	(cd $(PACKAGE)-$(VERSION) && debuild -us -uc)
	rm -rf $(PACKAGE)-$(VERSION)

# the macos type
bundle: all
	${INSTALL} -d $(PACKAGE).app/Contents/MacOS $(PACKAGE).app/Contents/Resources
	${INSTALL} Info.plist version.plist $(PACKAGE).app/Contents
	${INSTALL} -s src/$(PACKAGE) $(PACKAGE).app/Contents/MacOS
	echo "APPL????" > $(PACKAGE).app/Contents/PkgInfo
	(cd data && make bundle)

