SUBDIRS = data src

EXTRA_DIST=ChangeLog $(PACKAGE).spec Info.plist PkgInfo version.plist

.PHONY : rpm deb bundle packages doc
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES/
	rpm -ba $(PACKAGE).spec
	cp /usr/src/redhat/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

deb:
	debian/rules
	debuild
	debc
	debi
	release

# the macos type
bundle: all
	${INSTALL} -d $(PACKAGE).app/Contents/MacOS $(PACKAGE).app/Contents/Resources
	${INSTALL} Info.plist version.plist $(PACKAGE).app/Contents
	${INSTALL} -s src/$(PACKAGE) $(PACKAGE).app/Contents/MacOS
	echo "APPL????" > $(PACKAGE).app/Contents/PkgInfo
	(cd data && make bundle)

packages: rpm deb

