SUBDIRS = data src debian

dist_man_MANS = $(PACKAGE).1
EXTRA_DIST=ChangeLog $(PACKAGE).spec Info.plist.in version.plist.in

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

