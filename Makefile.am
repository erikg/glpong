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
	rm -rf $(PACKAGE).app
	mkdir $(PACKAGE).app $(PACKAGE).app/Contents $(PACKAGE).app/Contents/Resources $(PACKAGE).app/Contents/MacOS
	ln src/$(PACKAGE) $(PACKAGE).app/Contents/MacOS/$(PACKAGE)
	echo "APPL????" > $(PACKAGE).app/Contents/PkgInfo
	for a in Info.plist version.plist ; do sed -e "s/%%VERSION%%/$(VERSION)/g" -e "s/%%PACKAGE%%/$(PACKAGE)/g" $$a > $(PACKAGE).app/Contents/$$a ; done

	cd data && make bundle
	
packages: rpm deb

